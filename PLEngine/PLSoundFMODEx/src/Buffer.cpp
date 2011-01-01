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
#include "PLSoundFMODEx/SoundManager.h"
#include "PLSoundFMODEx/Source.h"
#include "PLSoundFMODEx/Buffer.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4505) // "'function' : unreferenced local function has been removed"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLSoundFMODEx {


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
*    Returns the FMOD Ex sound instance
*/
FMOD::Sound *Buffer::GetSound() const
{
	return m_pSound;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Buffer::Buffer(PLSound::SoundManager &cSoundManager, const String &sName, bool bStream) : PLSound::Buffer(cSoundManager, sName),
	m_pSound(NULL),
	m_bStreamed(false)
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
		// Get FMOD Ex system instance
		FMOD::System *pSystem = ((SoundManager&)GetSoundManager()).GetSystem();
		if (pSystem) {
			// Use streaming?
			FMOD_RESULT nResult;
			if (bStream)
				nResult = pSystem->createStream(sFilename, FMOD_DEFAULT | FMOD_3D, 0, &m_pSound);
			else
				nResult = pSystem->createSound (sFilename, FMOD_DEFAULT | FMOD_3D, 0, &m_pSound);
			if (SoundManager::ErrorCheck(nResult)) {
				m_bStreamed = bStream;

				// Set the default volume of the buffer to 0
				float fFrequency, fVolume, fPan;
				int nPriority;
				m_pSound->getDefaults(&fFrequency, &fVolume, &fPan, &nPriority);
				m_pSound->setDefaults(fFrequency, 0.0f, fPan, nPriority);

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool Buffer::LoadBuffer(const uint8 nData[], uint32 nSize, bool bStream)
{
	// Check parameter
	if (nSize) {
		// Get FMOD Ex system instance
		FMOD::System *pSystem = ((SoundManager&)GetSoundManager()).GetSystem();
		if (pSystem) {
			// Use streaming?
			FMOD_RESULT nResult;
			if (bStream)
				nResult = pSystem->createStream((const char*)&nData, FMOD_DEFAULT | FMOD_OPENMEMORY | FMOD_3D, 0, &m_pSound);
			else
				nResult = pSystem->createSound ((const char*)&nData, FMOD_DEFAULT | FMOD_OPENMEMORY | FMOD_3D, 0, &m_pSound);
			if (SoundManager::ErrorCheck(nResult)) {
				m_bStreamed = bStream;

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool Buffer::IsLoaded() const
{
	return (m_pSound != NULL);
}

bool Buffer::IsStreamed() const
{
	return m_bStreamed;
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
	// Stop playback of all sources using this buffer
	for (uint32 i=0; i<GetNumOfSources(); i++)
		GetSource(i)->Stop();

	// Release the FMOD Ex sound
	if (m_pSound) {
		m_pSound->release();
		m_pSound = NULL;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMODEx


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
