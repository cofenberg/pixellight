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
#include <PLCore/Log/Log.h>
#include "PLSoundFMOD/SoundManager.h"
#include "PLSoundFMOD/Source.h"
#include "PLSoundFMOD/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLSoundFMOD {


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


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Buffer::Buffer(PLSound::SoundManager &cSoundManager, const String &sName, bool bStream) :
	PLSound::Buffer(cSoundManager, sName),
	m_pMod(nullptr),
	m_pSample(nullptr),
	m_pStream(nullptr)
{
	// Load the sound buffer
	if (sName.GetLength())
		LoadBuffer(sName, bStream);
}

/**
*  @brief
*    Plays the buffer
*/
int Buffer::Play()
{
	// Play mod music
	if (m_pMod)
		FMUSIC_PlaySong(m_pMod);
	else {
		// Play sound
		if (m_pSample)
			return FSOUND_PlaySound(FSOUND_FREE, m_pSample);

		// Play stream
		if (m_pStream)
			return FSOUND_Stream_Play(FSOUND_FREE, m_pStream);
	}

	// No channel used...
	return -1;
}

/**
*  @brief
*    Checks whether the buffer is currently playing or not
*/
bool Buffer::IsPlaying(int nChannel) const
{
	if (m_pMod)
		 return (FMUSIC_IsPlaying(m_pMod) != 0);
	else if (m_pSample)
		return (FSOUND_IsPlaying(nChannel) != 0);
	else if (m_pStream)
		return (nChannel != -1);
	else
		return false;
}

/**
*  @brief
*    Stops the buffer playback
*/
void Buffer::Stop(int nChannel)
{
	if (m_pMod)
		FMUSIC_StopSong(m_pMod);
	if (m_pSample && nChannel >= 0)
		FSOUND_StopSound(nChannel);
	if (m_pStream)
		FSOUND_Stream_Stop(m_pStream);
}

/**
*  @brief
*    Sets the volume
*/
bool Buffer::SetVolume(int nChannel, float fVolume)
{
	// Set volume
	if (m_pMod) {
		FMUSIC_SetMasterVolume(m_pMod, static_cast<int>(fVolume*256));
	} else {
		if ((m_pSample || m_pStream) && nChannel > -1) {
			FSOUND_SetVolume(nChannel, static_cast<int>(fVolume*255));
		} else {
			// Error!
			return false;
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Sets whether the sound is looping or not
*/
void Buffer::SetLooping(int nChannel, bool bLooping)
{
	if (m_pMod)
		FMUSIC_SetLooping(m_pMod, bLooping);
	if (m_pSample && nChannel > -1)
		FSOUND_SetLoopMode(nChannel, bLooping ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF);
	if (m_pStream && nChannel > -1)
		FSOUND_Stream_SetMode(m_pStream, bLooping ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF);
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::Buffer functions              ]
//[-------------------------------------------------------]
bool Buffer::LoadBuffer(const String &sFilename, bool bStream)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Load buffer
		bool bError = false;
		m_pMod = FMUSIC_LoadSong(sFilename);
		if (m_pMod) {
			if (FMUSIC_GetType(m_pMod) == FMUSIC_TYPE_MOD || FMUSIC_GetType(m_pMod) == FMUSIC_TYPE_S3M)
				FMUSIC_SetPanSeperation(m_pMod, 0.85f); // 15% crossover
		} else {
			if (bStream) {
				m_pStream = FSOUND_Stream_Open(sFilename, FSOUND_NORMAL | FSOUND_MPEGACCURATE | FSOUND_LOOP_OFF, 0, 0);
				if (!m_pStream)
					bError = true;
			} else {
				// [TODO] 3D sound
				int nFlag = 0;
	//			int nFlag = FSOUND_HW3D;
				m_pSample = FSOUND_Sample_Load(FSOUND_FREE, sFilename, FSOUND_NORMAL | nFlag, 0, 0);
				if (m_pSample)
					FSOUND_Sample_SetMode(m_pSample, FSOUND_LOOP_OFF);
				else
					bError = true;
			}
		}

		// Check if there was an error
		if (bError)
			PL_LOG(Error, "Couldn't load sound " + sFilename + " Error: " + FMOD_ErrorString(FSOUND_GetError()))
		else {
			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool Buffer::LoadBuffer(const uint8 nData[], uint32 nSize, bool bStream)
{
	// Check parameter
	if (nSize) {
		// Load buffer
		bool bError = false;
		m_pMod = FMUSIC_LoadSongEx(reinterpret_cast<const char*>(&nData), 0, nSize, FSOUND_LOADMEMORY, nullptr, 0);
		if (m_pMod) {
			if (FMUSIC_GetType(m_pMod) == FMUSIC_TYPE_MOD || FMUSIC_GetType(m_pMod) == FMUSIC_TYPE_S3M)
				FMUSIC_SetPanSeperation(m_pMod, 0.85f); // 15% crossover
		} else {
			if (bStream) {
				m_pStream = FSOUND_Stream_Open(reinterpret_cast<const char*>(&nData), FSOUND_NORMAL | FSOUND_MPEGACCURATE | FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, 0, nSize);
				if (!m_pStream)
					bError = true;
			} else {
				// [TODO] 3D sound
				int nFlag = 0;
	//			int nFlag = FSOUND_HW3D;
				m_pSample = FSOUND_Sample_Load(FSOUND_FREE, reinterpret_cast<const char*>(&nData), FSOUND_NORMAL | FSOUND_LOADMEMORY | nFlag, 0, nSize);
				if (m_pSample)
					FSOUND_Sample_SetMode(m_pSample, FSOUND_LOOP_OFF);
				else
					bError = true;
			}
		}

		// Check if there was an error
		if (bError)
			PL_LOG(Error, String("Couldn't load sound. Error: ") + FMOD_ErrorString(FSOUND_GetError()))
		else {
			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool Buffer::IsLoaded() const
{
	return (m_pMod != nullptr || m_pSample != nullptr || m_pStream != nullptr);
}

bool Buffer::IsStreamed() const
{
	return (m_pStream != nullptr);
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Buffer::Load(const String &sName, const String &sParams, const String &sMethod)
{
	return LoadBuffer(sName, false);
}

bool Buffer::Unload()
{
	// Stop playback of all sources using this buffer
	for (uint32 i=0; i<GetNumOfSources(); i++)
		GetSource(i)->Stop();

	// Unload buffer
	if (m_pMod) {
		FMUSIC_FreeSong(m_pMod);
		m_pMod = nullptr;
	}
	if (m_pSample) {
		FSOUND_Sample_Free(m_pSample);
		m_pSample = nullptr;
	}
	if (m_pStream) {
		FSOUND_Stream_Close(m_pStream);
		m_pStream = nullptr;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD
