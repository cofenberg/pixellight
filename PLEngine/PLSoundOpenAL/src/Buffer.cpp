/*********************************************************\
 *  File: Buffer.cpp                                     *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLSoundOpenAL/Ogg.h"
#include "PLSoundOpenAL/Wav.h"
#include "PLSoundOpenAL/StreamOgg.h"
#include "PLSoundOpenAL/StreamWav.h"
#include "PLSoundOpenAL/Source.h"
#include "PLSoundOpenAL/SoundManager.h"
#include "PLSoundOpenAL/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Buffer::~Buffer()
{
	// Unload sound
	Unload();
}

/**
*  @brief
*    Creates a stream
*/
Stream *Buffer::CreateStream(ALuint nSource)
{
	// Stream the buffer?
	if (m_bStream) {
		// Get filename extension
		String sExtension;
		if (m_pnData) {
			// Try to read wav header
			if (m_nDataSize >= sizeof(StreamWav::Header)) {
				StreamWav::Header sWavHeader;

				// Read wav header
				MemoryManager::Copy(&sWavHeader, m_pnData, sizeof(StreamWav::Header));

				// Is this wav file?
				sExtension = MemoryManager::Compare((const char*)sWavHeader.wave, "WAVE", 4) ? "ogg" : "wav";
			} else {
				sExtension = "ogg";
			}
		} else {
			sExtension = Url(m_sFilename).GetExtension();
		}

		// Create stream
		if (sExtension == "ogg")
			return new StreamOgg(nSource, *this);
		else if (sExtension == "wav")
			return new StreamWav(nSource, *this);
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns the OpenAL buffer
*/
ALuint Buffer::GetOpenALBuffer() const
{
	return m_nBuffer;
}

/**
*  @brief
*    Returns the buffer filename
*/
String Buffer::GetFilename() const
{
	return m_sFilename;
}

/**
*  @brief
*    Opens the file the buffer is using
*/
File *Buffer::OpenFile() const
{
	// Filename given?
	if (m_sFilename.GetLength()) {
		// Create the file object
		File *pFile = new File();

		// Because absolute filenames can be accessed fastest by the file system, we first give
		// the file system an absolute filename which is hopefully the correct one... if
		// not, we must search the file which is quite slow...
		const Url cUrl(m_sFilename);
		if (cUrl.IsAbsolute()) {
			// The given filename is already absolute! :)
			pFile->Assign(m_sFilename);
		} else {
			// Loop through all base directories
			for (uint32 nBaseDir=0; nBaseDir<LoadableManager::GetInstance()->GetNumOfBaseDirs() && !pFile->IsFile(); nBaseDir++) {
				const String sBaseDir = LoadableManager::GetInstance()->GetBaseDir(nBaseDir);

				// Construct absolute filename and check file
				String sAbsFilename = sBaseDir + m_sFilename;
				pFile->Assign(sAbsFilename);

				// Is this a correct file?
				if (!pFile->IsFile()) {
					// Try to open the file directly
					sAbsFilename = sBaseDir + m_sFilename;
					pFile->Assign(sAbsFilename);
				}
			}
		}

		// Try to open the file
		if (pFile->Open(File::FileRead))
			return pFile; // Return opend file object

		// Cleanup on error
		delete pFile;
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns the buffer data
*/
const uint8 *Buffer::GetData() const
{
	return m_pnData;
}

/**
*  @brief
*    Returns the buffer data size (in bytes)
*/
uint32 Buffer::GetDataSize() const
{
	return m_nDataSize;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Buffer::Buffer(PLSound::SoundManager &cSoundManager, const String &sName,  bool bStream) :
	PLSound::Buffer(cSoundManager, sName),
	m_bStream(false),
	m_nBuffer(0),
	m_pnData(nullptr),
	m_nDataSize(0)
{
	// Load the sound buffer
	if (sName.GetLength())
		LoadBuffer(sName, bStream);
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::Buffer functions              ]
//[-------------------------------------------------------]
bool Buffer::LoadBuffer(const String &sFilename, bool bStream)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Unload old sound buffer
		Unload();

		// Load buffer
		m_bStream = bStream;
		if (m_bStream) {
			m_sFilename = sFilename;

			// Done
			return true;
		} else {
			// Create the buffer
			alGenBuffers(1, &m_nBuffer);
			ALuint nError = alGetError();
			if (nError == AL_NO_ERROR) {
				// Try to load ogg
				m_sFilename = sFilename;
				File *pFile = OpenFile();
				if (pFile) {
					ALsizei nFreq;
					ALenum  nFormat;
					Array<uint8> lstBufferData;
					if (LoadOGG(pFile, lstBufferData, nFormat, nFreq)) {
						// Fill buffer
						alBufferData(m_nBuffer, nFormat, &lstBufferData[0], lstBufferData.GetNumOfElements(), nFreq);
						nError = alGetError();
						if (nError == AL_NO_ERROR)
							return true; // Done
						else
							PL_LOG(Error, String::Format("alBufferData: %s", alGetString(nError)))
					} else {
						// Check whether this is a wav file
						const String sExtension = Url(sFilename).GetExtension();
						if (sExtension == "wav") {
							// Try to load wav
							if (LoadWav(pFile, lstBufferData, nFormat, nFreq)) {
								// Fill buffer
								alBufferData(m_nBuffer, nFormat, &lstBufferData[0], lstBufferData.GetNumOfElements(), nFreq);
								nError = alGetError();
								if (nError == AL_NO_ERROR)
									return true; // Done
								else
									PL_LOG(Error, String::Format("alBufferData: %s", alGetString(nError)))
							} else {
								delete pFile;
							}
						} else {
							delete pFile;
						}
					}
				}

				// Cleanup on error
				alDeleteBuffers(1, &m_nBuffer);
				m_nBuffer   = 0;
				m_sFilename = "";
			} else {
				PL_LOG(Error, String::Format("alGenBuffers: %s", alGetString(nError)))
			}
		}
	}

	// Error!
	return false;
}

bool Buffer::LoadBuffer(const uint8 nData[], uint32 nSize, bool bStream)
{
	// Check parameters
	if (nSize) {
		// Unload old sound buffer
		Unload();

		// Load buffer
		m_bStream = bStream;
		if (m_bStream) {
			m_pnData    = nData;
			m_nDataSize = nSize;

			// Done
			return true;
		} else {
			// Create the buffer
			alGenBuffers(1, &m_nBuffer);
			ALuint nError = alGetError();
			if (nError == AL_NO_ERROR) {
				// Try to load ogg
				ALenum  nFormat;
				ALsizei nFreq;
				Array<uint8> lstBufferData;
				if (LoadOGG(nData, nSize, lstBufferData, nFormat, nFreq)) {
					// Fill buffer
					alBufferData(m_nBuffer, nFormat, &lstBufferData[0], lstBufferData.GetNumOfElements(), nFreq);
					nError = alGetError();
					if (nError == AL_NO_ERROR)
						return true; // Done
					else
						PL_LOG(Error, String::Format("alBufferData: %s", alGetString(nError)))
				} else {
					// Try to load wav
					if (LoadWav(nData, nSize, lstBufferData, nFormat, nFreq)) {
						// Fill buffer
						alBufferData(m_nBuffer, nFormat, &lstBufferData[0], lstBufferData.GetNumOfElements(), nFreq);
						nError = alGetError();
						if (nError == AL_NO_ERROR)
							return true; // Done
						else
							PL_LOG(Error, String::Format("alBufferData: %s", alGetString(nError)))
					}
				}

				// Cleanup on error
				alDeleteBuffers(1, &m_nBuffer);
				m_nBuffer = 0;
			} else {
				PL_LOG(Error, String::Format("alGenBuffers: %s", alGetString(nError)))
			}
		}
	}

	// Error!
	return false;
}

bool Buffer::IsLoaded() const
{
	return (m_nBuffer != 0 || m_bStream);
}

bool Buffer::IsStreamed() const
{
	return m_bStream;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Resource functions             ]
//[-------------------------------------------------------]
bool Buffer::Load(const String &sName)
{
	return LoadBuffer(sName, false);
}

bool Buffer::Unload()
{
	// Is the buffer loaded?
	if (m_nBuffer || m_bStream) {
		// Stop playback of all sources using this buffer
		for (uint32 i=0; i<GetNumOfSources(); i++)
			GetSource(i)->Stop();

		// Unload buffer
		m_bStream   = false;
		m_sFilename = "";
		m_pnData    = nullptr;
		m_nDataSize = 0;
		if (m_nBuffer) {
			alDeleteBuffers(1, &m_nBuffer);
			m_nBuffer = 0;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL
