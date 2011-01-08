/*********************************************************\
 *  File: SoundManager.cpp                               *
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
#include <stdio.h>
#include <PLGeneral/Core/MemoryManager.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/File/File.h>
#include "PLSoundFMOD/Buffer.h"
#include "PLSoundFMOD/Source.h"
#include "PLSoundFMOD/SoundManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
namespace PLSoundFMOD {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SoundManager)


//[-------------------------------------------------------]
//[ Custom FMOD file callbacks                            ]
//[-------------------------------------------------------]
void *F_CALLBACKAPI FSOpen(const char *pszName)
{
	if (pszName) {
		// Create the file object
		File *pFile = new File();

		// Because absolute filenames can be accessed fastest by the file system, we first give
		// the file system an absolute filename which is hopefully the correct one... if
		// not, we must search the file which is quite slow...
		String sUrl = pszName;
		Url cUrl(sUrl);
		if (cUrl.IsAbsolute()) {
			// The given filename is already absolute! :)
			pFile->Assign(sUrl);
		} else {
			// Loop through all base directories
			for (uint32 nBaseDir=0; nBaseDir<LoadableManager::GetInstance()->GetNumOfBaseDirs() && !pFile->IsFile(); nBaseDir++) {
				String sBaseDir = LoadableManager::GetInstance()->GetBaseDir(nBaseDir);

				// Construct absolute filename and check file
				String sAbsFilename = sBaseDir + sUrl;
				pFile->Assign(sAbsFilename);

				// Is this a correct file?
				if (!pFile->IsFile()) {
					// Try to open the file directly
					sAbsFilename = sBaseDir + sUrl;
					pFile->Assign(sAbsFilename);
				}
			}
		}

		// Try to open the file
		if (pFile->Open(File::FileRead)) {
			return (void*)pFile; // Return opend file object
		}

		// Cleanup on error
		delete pFile;
	}

	// Error!
	return nullptr;
}

void F_CALLBACKAPI FSClose(void *pHandle)
{
	if (pHandle) {
		((File*)pHandle)->Close();
		delete ((File*)pHandle);
	}
}

int F_CALLBACKAPI FSRead(void *pBuffer, int nSize, void *pHandle)
{
	return pHandle ? ((File*)pHandle)->Read(pBuffer, 1, nSize) : -1;
}

int F_CALLBACKAPI FSSeek(void *pHandle, int nPos, signed char nMode)
{
	if (pHandle) {
		switch (nMode) {
			case SEEK_SET:
				return !((File*)pHandle)->Seek(nPos, File::SeekSet);

			case SEEK_CUR:
				return !((File*)pHandle)->Seek(nPos, File::SeekCurrent);

			case SEEK_END:
				return !((File*)pHandle)->Seek(nPos, File::SeekEnd);
		}
	}

	// Error!
	return -1;
}

int F_CALLBACKAPI FSTell(void *pHandle)
{
	return pHandle ? ((File*)pHandle)->Tell() : -1;
}


//[-------------------------------------------------------]
//[ Custom FMOD memory callbacks                          ]
//[-------------------------------------------------------]
void * F_CALLBACKAPI FMODAllocationFunction(unsigned int nSize)
{
	return MemoryManager::Allocator(MemoryManager::NewArray, nSize);
}

void * F_CALLBACKAPI FMODReallocationFunction(void *pAddress, unsigned int nSize)
{
	return MemoryManager::Reallocator(pAddress, nSize);
}

void F_CALLBACKAPI FMODDeallocationFunction(void *pAddress)
{
	if (pAddress) MemoryManager::Deallocator(MemoryManager::DeleteArray, pAddress);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SoundManager::SoundManager() :
	BufferSize(this),
	Output(this),
	Driver(this),
	Mixer(this),
	OutputRate(this),
	Channels(this),
	m_fVolume(1.0f),
	m_fPitch(1.0f),
	m_fDopplerFactor(1.0f)
{
	// Log message
	PL_LOG(Info, "Create sound manager: " + GetDescription())

	// Initialize listener attributes
	SetListenerAttribute(ListenerForward, Vector3(0.0f, 0.0f, 1.0f));
	SetListenerAttribute(ListenerUpward,  Vector3(0.0f, 1.0f, 0.0f));
}

/**
*  @brief
*    Destructor
*/
SoundManager::~SoundManager()
{
	// Log message
	PL_LOG(Info, "Destroy sound manager: " + GetDescription())

	// De-initialize
	DeInit();
}

/**
*  @brief
*    Adds an active sound source to the sound manager
*/
bool SoundManager::AddActiveSource(PLSound::Source &cSource)
{
	return !m_lstActiveSources.IsElement(&cSource) && m_lstActiveSources.Add(&cSource) != nullptr;
}

/**
*  @brief
*    Removes an active sound source from the sound manager
*/
bool SoundManager::RemoveActiveSource(PLSound::Source &cSource)
{
	return m_lstActiveSources.Remove(&cSource);
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::SoundManager functions        ]
//[-------------------------------------------------------]
String SoundManager::GetDescription() const
{
	static const String sString = "FMOD sound";
	return sString;
}

bool SoundManager::GetFormatList(List<Format> &lstList) const
{
	{ // mp3
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "mp3";
			cFormat.sDescription = PLT("Audio files");
		}
	}

	{ // wav
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "wav";
			cFormat.sDescription = PLT("Audio files");
		}
	}

	{ // mid
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "mid";
			cFormat.sDescription = PLT("Midi files");
		}
	}

	{ // midi
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "midi";
			cFormat.sDescription = PLT("Midi files");
		}
	}

	{ // it
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "it";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	{ // mod
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "mod";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	// s3m
	{
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "s3m";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	{ // xm
		Format &cFormat = lstList.Add();
		if (&cFormat != &Array<Format>::Null) {
			cFormat.sFormat		 = "xm";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	// Done
	return true;
}

float SoundManager::GetVolume() const
{
	return m_fVolume;
}

void SoundManager::SetVolume(float fVolume)
{
	// No change = nothing to do :)
	if (m_fVolume != fVolume) {
		m_fVolume = fVolume;
		FSOUND_SetSFXMasterVolume((int)(fVolume*255));
	}
}

float SoundManager::GetPitch() const
{
	return m_fPitch;
}

void SoundManager::SetPitch(float fPitch)
{
	// Check and set pitch -> no change = nothing to do :)
	if (m_fPitch != fPitch) {
		m_fPitch = fPitch;

		// Update the pitch of all sources
		for (uint32 i=0; i<m_lstActiveSources.GetNumOfElements(); i++) {
			PLSound::Source *pSource = m_lstActiveSources[i];
			pSource->SetPitch(pSource->GetPitch());
		}
	}
}

float SoundManager::GetDopplerFactor() const
{
	return m_fDopplerFactor;
}

void SoundManager::SetDopplerFactor(float fFactor)
{
	// No change = nothing to do :)
	if (m_fDopplerFactor != fFactor) {
		m_fDopplerFactor = fFactor;
		FSOUND_3D_SetDopplerFactor(m_fDopplerFactor);
	}
}


//[-------------------------------------------------------]
//[ Create sound buffer/source                            ]
//[-------------------------------------------------------]
PLSound::Buffer *SoundManager::CreateSoundBuffer(const String &sFilename, bool bStream)
{
	// Is there already a sound buffer with this name?
	PLSound::Buffer *pSB = Get(sFilename);
	return pSB ? pSB : new Buffer(*this, sFilename, bStream);
}

PLSound::Source *SoundManager::CreateSoundSource(PLSound::Buffer *pSoundBuffer)
{
	// Create the FMOD sound source
	PLSound::Source *pSS = new Source(*this);
	if (pSoundBuffer) pSS->Load(pSoundBuffer);

	// Return the created sound source
	return pSS;
}


//[-------------------------------------------------------]
//[ Listener                                              ]
//[-------------------------------------------------------]
Vector3 SoundManager::GetListenerAttribute(EListener nAttribute) const
{
	return m_vListenerAttributes[nAttribute];
}

bool SoundManager::SetListenerAttribute(EListener nAttribute, const Vector3 &vV)
{
	// Set attribute
	m_vListenerAttributes[nAttribute] = vV;

	// Setup listener... FMOD uses a left handed coordinate system so we need to convert
	Vector3 &vAt = m_vListenerAttributes[ListenerForward];
	Vector3 &vUp = m_vListenerAttributes[ListenerUpward];
	FSOUND_3D_Listener_SetAttributes(m_vListenerAttributes[ListenerPosition],
									 m_vListenerAttributes[ListenerVelocity],
									 vAt.x, vAt.y, -vAt.z,
									 vUp.x, vUp.y, -vUp.z);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::ResourceManager functions      ]
//[-------------------------------------------------------]
bool SoundManager::Init()
{
	// Show FMOD version
	PL_LOG(Info, String::Format("Initialize FMOD (v%.1f)", FMOD_VERSION))

	// Set new memory management functions
	FSOUND_SetMemorySystem(nullptr, 0, FMODAllocationFunction, FMODReallocationFunction, FMODDeallocationFunction);

	// Set custom file callbacks to use the PixelLight file system
	FSOUND_File_SetCallbacks(FSOpen, FSClose, FSRead, FSSeek, FSTell);

	// Check FMOD version
	if (FSOUND_GetVersion() >= FMOD_VERSION) {
		// Millisecond value for FMOD buffersize
		FSOUND_SetBufferSize(BufferSize);

		// Initialize FSOUND
		FSOUND_SetOutput(Output-1); // -1: Because the FMOD settings start with -1!
		FSOUND_SetDriver(Driver);
		FSOUND_SetMixer (Mixer);
		FSOUND_SetHWND(nullptr);

		// Try to initialize fmod
		int nRetryCount = 0;
		while (!FSOUND_Init(OutputRate, Channels, FSOUND_INIT_USEDEFAULTMIDISYNTH) && nRetryCount < 10) {
			System::GetInstance()->Sleep(100);
			nRetryCount++;
		}

		// FMOD initialization done?
		if (nRetryCount < 10) {
			// Done
			return true;
		} else PL_LOG(Error, String::Format("Error on FMOD initialization! (%s)", FMOD_ErrorString(FSOUND_GetError())))
	} else PL_LOG(Error, String::Format("Invalid FMOD version! (v%.1f required!)", FMOD_VERSION))

	// Error!
	return false;
}

bool SoundManager::DeInit()
{
	// Destroy all resources - the resources unregister automatically from the list, so, this while loop will terminate!
	while (m_lstResources.GetNumOfElements())
		delete m_lstResources[0];
	m_lstResources.Clear();

	// Call base implementation
	PLSound::SoundManager::DeInit();

	// Close FSOUND
	FSOUND_Close();

	// Done
	return true;
}

bool SoundManager::Update()
{
	// Update FSOUND
	FSOUND_Update();

	// Check active sources
	for (uint32 i=0; i<m_lstActiveSources.GetNumOfElements(); i++) {
		PLSound::Source *pSource = m_lstActiveSources[i];
		if (!pSource->IsPlaying()) {
			m_lstActiveSources.RemoveAtIndex(i);
			i--;
		}
	}

	// Update statistics
	m_sStatistics.nNumOfActiveSources = m_lstActiveSources.GetNumOfElements();

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
PLSound::Buffer *SoundManager::CreateResource(const String &sName)
{
	return CreateSoundBuffer(sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD
