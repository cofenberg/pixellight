/*********************************************************\
 *  File: Buffer.cpp                                     *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
using namespace PLCore;
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
	m_pSound(nullptr),
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
		FMOD::System *pSystem = static_cast<SoundManager&>(GetSoundManager()).GetSystem();
		if (pSystem) {
			// Use streaming?
			FMOD_RESULT nResult;
			if (bStream)
				nResult = pSystem->createStream(sFilename, FMOD_DEFAULT | FMOD_3D, 0, &m_pSound);
			else
				nResult = pSystem->createSound(sFilename, FMOD_DEFAULT | FMOD_3D, 0, &m_pSound);
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
		FMOD::System *pSystem = static_cast<SoundManager&>(GetSoundManager()).GetSystem();
		if (pSystem) {
			// Use streaming?
			FMOD_RESULT nResult;
			if (bStream)
				nResult = pSystem->createStream(reinterpret_cast<const char*>(&nData), FMOD_DEFAULT | FMOD_OPENMEMORY | FMOD_3D, 0, &m_pSound);
			else
				nResult = pSystem->createSound (reinterpret_cast<const char*>(&nData), FMOD_DEFAULT | FMOD_OPENMEMORY | FMOD_3D, 0, &m_pSound);
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
	return (m_pSound != nullptr);
}

bool Buffer::IsStreamed() const
{
	return m_bStreamed;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Buffer::LoadByFilename(const String &sFilename, const String &sParams, const String &sMethod)
{
	return LoadBuffer(sFilename, false);
}

bool Buffer::Unload()
{
	// Stop playback of all sources using this buffer
	for (uint32 i=0; i<GetNumOfSources(); i++)
		GetSource(i)->Stop();

	// Release the FMOD Ex sound
	if (m_pSound) {
		m_pSound->release();
		m_pSound = nullptr;
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
