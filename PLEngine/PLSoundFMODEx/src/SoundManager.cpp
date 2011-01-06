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
#include <PLGeneral/File/File.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/Core/MemoryManager.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLSoundFMODEx/SoundManager.h"
#include "PLSoundFMODEx/Buffer.h"
#include "PLSoundFMODEx/Source.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
namespace PLSoundFMODEx {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SoundManager)


//[-------------------------------------------------------]
//[ Custom FMOD Ex file callbacks                         ]
//[-------------------------------------------------------]
FMOD_RESULT F_CALLBACK FSOpen(const char *pszName, int nUnicode, unsigned int *pFileSize, void **ppHandle, void **ppUserData)
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
			// Return opend file object
			*pFileSize	= pFile->GetSize();
			*ppHandle	= pFile;
			*ppUserData	= (void*)0x12345678;

			// Done
			return FMOD_OK;
		}

		// Cleanup on error
		delete pFile;
	}

	// Error!
	return FMOD_ERR_FILE_NOTFOUND;
}

FMOD_RESULT F_CALLBACK FSClose(void *pHandle, void *pUserData)
{
	if (pHandle) {
		((File*)pHandle)->Close();
		delete ((File*)pHandle);

		return FMOD_OK;
	} else return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALLBACK FSRead(void *pHandle, void *pBuffer, unsigned int nSizeBytes, unsigned int *pnBytesRead, void *pUserData)
{
	if (pHandle) {
		if (pnBytesRead) {
			*pnBytesRead = ((File*)pHandle)->Read(pBuffer, 1, nSizeBytes);
			if (*pnBytesRead < nSizeBytes)
				return FMOD_ERR_FILE_EOF;
		}

		return FMOD_OK;
	} else return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALLBACK FSSeek(void *pHandle, unsigned int nPos, void *pUserData)
{
	if (pHandle) {
		((File*)pHandle)->Seek(nPos, File::SeekSet);

		return FMOD_OK;
	} else return FMOD_ERR_INVALID_PARAM;
}


//[-------------------------------------------------------]
//[ Custom FMOD Ex memory callbacks                       ]
//[-------------------------------------------------------]
void * F_CALLBACK FMODExAllocationFunction(unsigned int nSize, FMOD_MEMORY_TYPE nType)
{
	// 'nType' is not used (that's NO problem!)
	return MemoryManager::Allocator(MemoryManager::NewArray, nSize);
}

void * F_CALLBACK FMODExReallocationFunction(void *pAddress, unsigned int nSize, FMOD_MEMORY_TYPE nType)
{
	// 'nType' is not used (that's NO problem!)
	return MemoryManager::Reallocator(pAddress, nSize);
}

void F_CALLBACK FMODExDeallocationFunction(void *pAddress, FMOD_MEMORY_TYPE nType)
{
	// 'nType' is not used (that's NO problem!)
	if (pAddress) MemoryManager::Deallocator(MemoryManager::DeleteArray, pAddress);
}


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Checks for an FMOD Ex error
*/
bool SoundManager::ErrorCheck(FMOD_RESULT nResult)
{
	if (nResult != FMOD_OK) {
		PL_LOG(Error, String::Format("FMOD error! (%d) %s\n", nResult, FMOD_ErrorString(nResult)))

		// Error!
		return false;
	} else return true;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SoundManager::SoundManager() :
	Driver(this),
	Output(this),
	Channels(this),
	BufferLength(this),
	NumOfBuffers(this),
	m_pSystem(nullptr),
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

/**
*  @brief
*    Returns the FMOD Ex system instance
*/
FMOD::System *SoundManager::GetSystem() const
{
	return m_pSystem;
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::SoundManager functions        ]
//[-------------------------------------------------------]
String SoundManager::GetDescription() const
{
	static const String sString = "FMOD Ex sound";
	return sString;
}

bool SoundManager::GetFormatList(List<Format> &lstList) const
{
	{ // mp3
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "mp3";
			cFormat.sDescription = PLT("Audio files");
		}
	}

	{ // wav
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "wav";
			cFormat.sDescription = PLT("Audio files");
		}
	}

	{ // mid
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "mid";
			cFormat.sDescription = PLT("Midi files");
		}
	}

	{ // midi
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "midi";
			cFormat.sDescription = PLT("Midi files");
		}
	}

	{ // it
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "it";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	{ // mod
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "mod";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	// s3m
	{
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
			cFormat.sFormat		 = "s3m";
			cFormat.sDescription = PLT("Mod files");
		}
	}

	{ // xm
		Format &cFormat = lstList.Add();
		if (&cFormat != &List<Format>::Null) {
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

		// Call FMOD Ex function
		if (m_pSystem) {
			FMOD::ChannelGroup *pChannelGroup;
			m_pSystem->getMasterChannelGroup(&pChannelGroup);
			if (pChannelGroup) pChannelGroup->setVolume(fVolume);
		}
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

		// Call FMOD Ex function
		if (m_pSystem) {
			FMOD::ChannelGroup *pChannelGroup;
			m_pSystem->getMasterChannelGroup(&pChannelGroup);
			if (pChannelGroup) pChannelGroup->setPitch(fPitch);
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

		// Call FMOD Ex function
		if (m_pSystem) {
			float fDopplerscale, fDistancefactor, fRolloffscale;
			if (m_pSystem->get3DSettings(&fDopplerscale, &fDistancefactor, &fRolloffscale) == FMOD_OK)
				m_pSystem->set3DSettings(fFactor, fDistancefactor, fRolloffscale);
		}
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
	// Create the FMOD Ex sound source
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

	// FMODEx uses a left handed coordinate system so we need to convert
	Vector3 vForward = m_vListenerAttributes[ListenerForward];
	vForward.z = -vForward.z;
	Vector3 vUpward = m_vListenerAttributes[ListenerUpward];
	vUpward.z = -vUpward.z;

	// Setup listener
	m_pSystem->set3DListenerAttributes(0,
									   (const FMOD_VECTOR*)&m_vListenerAttributes[ListenerPosition].x,
									   (const FMOD_VECTOR*)&m_vListenerAttributes[ListenerVelocity].x,
									   (const FMOD_VECTOR*)&vForward.x,
									   (const FMOD_VECTOR*)&vUpward.x);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::ResourceManager functions      ]
//[-------------------------------------------------------]
bool SoundManager::Init()
{
	// Show FMOD Ex version
	PL_LOG(Info, String::Format("Initialize FMOD Ex (v%08x)", FMOD_VERSION))

	// Set new memory management functions
	FMOD_RESULT nResult = FMOD_Memory_Initialize(nullptr, 0, FMODExAllocationFunction, FMODExReallocationFunction, FMODExDeallocationFunction, FMOD_MEMORY_NORMAL);
	if (ErrorCheck(nResult)) {
		// Create a system object
		FMOD::System_Create(&m_pSystem);
		if (ErrorCheck(nResult)) {
			// Check the version
			unsigned int nVersion;
			nResult = m_pSystem->getVersion(&nVersion);
			if (ErrorCheck(nResult)) {
				if (nVersion >= FMOD_VERSION) {
					// Set driver
					m_pSystem->setDriver(Driver);

					// Set output
					m_pSystem->setOutput((FMOD_OUTPUTTYPE)Output.GetInt());

					// Set buffer size
					m_pSystem->setDSPBufferSize(BufferLength, NumOfBuffers);

					// Initialize the system object
					nResult = m_pSystem->init(Channels, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
					if (ErrorCheck(nResult)) {
						// Set file system callback functions
						nResult = m_pSystem->setFileSystem(FSOpen, FSClose, FSRead, FSSeek, 2048);
						if (ErrorCheck(nResult))
							return true; // Done
					}
				} else PL_LOG(Error, String::Format("You are using an old version of FMOD %08x. This program requires %08x", nVersion, FMOD_VERSION))
			}

			// Cleanup on error
			m_pSystem->release();
			m_pSystem = nullptr;
		}
	}

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

	// Close FMOD Ex
	if (m_pSystem) {
		m_pSystem->release();
		m_pSystem = nullptr;
	}

	// Done
	return true;
}

bool SoundManager::Update()
{
	// Check system instance
	if (!m_pSystem) return false; // Error!

	// Update FMOD Ex
	m_pSystem->update();

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
} // PLSoundFMODEx
