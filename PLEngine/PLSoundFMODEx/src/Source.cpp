/*********************************************************\
 *  File: Source.cpp                                     *
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
#include "PLSoundFMODEx/Buffer.h"
#include "PLSoundFMODEx/Source.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4505) // "'function' : unreferenced local function has been removed"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLSoundFMODEx {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Source::~Source()
{
	// Unload buffer
	Unload();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Source::Source(PLSound::SoundManager &cSoundManager) : PLSound::Source(cSoundManager),
	m_pChannel(NULL),
	m_fFrequency(0.0f),
	m_fVolume(1.0f),
	m_b2D(false),
	m_bLooping(false),
	m_fPitch(1.0f),
	m_fReferenceDistance(1.0f),
	m_fMaxDistance(10000.0f),
	m_fRolloffFactor(1.0f)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::Source functions              ]
//[-------------------------------------------------------]
bool Source::Load(PLSound::Buffer *pBuffer)
{
	// Call base implementation
	return PLSound::Source::Load(pBuffer);
}

void Source::Unload()
{
	// Stop playback
	Stop();

	// Call base implementation
	PLSound::Source::Unload();
}

bool Source::Play(bool bRestart)
{
	// Is a buffer loaded?
	Buffer *pBuffer = (Buffer*)GetBuffer();
	if (pBuffer && pBuffer->GetSound()) {
		// Paused?
		if (IsPaused() && !bRestart) {
			// Unpause
			m_pChannel->setPaused(false);

			// Done
			return true;
		} else {
			// Play
			if (IsPlaying()) {
				if (!bRestart)
					return true; // Done
				Stop();
			}

			// Get FMOD Ex system instance
			FMOD::System *pSystem = ((SoundManager&)GetSoundManager()).GetSystem();
			if (pSystem) {
				// Set looping
				pBuffer->GetSound()->setLoopCount(m_bLooping ? -1 : 0);

				// Play FMOD Ex sound
				FMOD_RESULT nResult = pSystem->playSound(FMOD_CHANNEL_FREE, pBuffer->GetSound(), false, &m_pChannel);
				if (SoundManager::ErrorCheck(nResult)) {
					// Add source to sound manager
					((SoundManager&)GetSoundManager()).AddActiveSource(*this);

					// Set mode
					if (m_b2D)
						m_pChannel->setMode(FMOD_DEFAULT);
//						m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D_LINEARROLLOFF);
					else
						m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D);
//						m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D_LINEARROLLOFF | FMOD_3D);

					// Get frequency and setup pitch
					m_pChannel->getFrequency(&m_fFrequency);
					float fPitch = m_fPitch;
					m_fPitch = -1.0f;
					SetPitch(fPitch);

					// Set range
					SetReferenceDistance(m_fReferenceDistance);
					SetMaxDistance(m_fMaxDistance);

					// Set attributes
					SetAttribute(Position, m_vAttributes[Position]);
					SetAttribute(Velocity, m_vAttributes[Velocity]);

					// Update FMOD Ex right now before setting the volume of the source, else we may
					// hear the source loudly before the volume is updated...
					pSystem->update();

					// Set volume
					m_pChannel->setVolume(m_fVolume);

					// Done
					return true;
				}
			}
		}
	}

	// Error!
	return false;
}

bool Source::IsPlaying() const
{
	if (m_pChannel) {
		bool bIsPlaying;
		m_pChannel->isPlaying(&bIsPlaying);
		return bIsPlaying;
	} else {
		// Not playing
		return false;
	}
}

void Source::Pause()
{
	// Is the source currently playing?
	if (IsPlaying()) {
		// Pause now ('m_pChannel' is valid if we are in here :)
		m_pChannel->setPaused(true);
	}
}

bool Source::IsPaused() const
{
	if (m_pChannel) {
		bool bIsPaused;
		m_pChannel->getPaused(&bIsPaused);
		return bIsPaused;
	} else {
		// Not paused
		return false;
	}
}

void Source::Stop()
{
	// Is the source currently playing? (using 'IsPlaying()' to test this is NOT correct in here!)
	if (m_pChannel) {
		// Stop playback
		m_pChannel->stop();
		m_pChannel = NULL;

		// Remove source from sound manager
		((SoundManager&)GetSoundManager()).RemoveActiveSource(*this);
	}
}

float Source::GetVolume() const
{
	return m_fVolume;
}

void Source::SetVolume(float fVolume)
{
	// No change = nothing to do :)
	if (m_fVolume != fVolume) {
		m_fVolume = fVolume;
		if (m_pChannel)
			m_pChannel->setVolume(fVolume);
	}
}

bool Source::Is2D() const
{
	return m_b2D;
}

void Source::Set2D(bool b2D)
{
	// Set 2D state
	if (m_b2D != b2D) {
		m_b2D = b2D;
		if (m_pChannel) {
			if (m_b2D)
				m_pChannel->setMode(FMOD_DEFAULT);
//				m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D_LINEARROLLOFF);
			else//
				m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D);
//				m_pChannel->setMode(FMOD_DEFAULT | FMOD_3D_LINEARROLLOFF | FMOD_3D);
		}
	}
}

bool Source::IsLooping() const
{
	return m_bLooping;
}

void Source::SetLooping(bool bLooping)
{
	// Set looping state
	if (m_bLooping != bLooping) {
		m_bLooping = bLooping;
		if (m_pChannel)
			m_pChannel->setLoopCount(m_bLooping ? -1 : 0);
	}
}

float Source::GetPitch() const
{
	return m_fPitch;
}

void Source::SetPitch(float fPitch)
{
	m_fPitch = fPitch;
	if (IsPlaying()) {
		float fFrequency = m_fFrequency*m_fPitch;
		if (!(GetFlags() & Source::NoMasterPitch))
			fFrequency *= GetSoundManager().GetPitch();
		if (fFrequency < 100.0f)
			fFrequency = 100.0f;
		if (fFrequency > 705600.0f)
			fFrequency = 705600.0f;
		m_pChannel->setFrequency(fFrequency);
	}
}

float Source::GetReferenceDistance() const
{
	return m_fReferenceDistance;
}

void Source::SetReferenceDistance(float fReferenceDistance)
{
	m_fReferenceDistance = fReferenceDistance;

	// Currently playing?
	if (m_pChannel) {
		// Set sound API value
		m_pChannel->set3DMinMaxDistance(m_fReferenceDistance, m_fMaxDistance);
	}
}

float Source::GetMaxDistance() const
{
	return m_fMaxDistance;
}

void Source::SetMaxDistance(float fMaxDistance)
{
	m_fMaxDistance = fMaxDistance;

	// Currently playing?
	if (m_pChannel) {
		// Set sound API value
		m_pChannel->set3DMinMaxDistance(m_fReferenceDistance, m_fMaxDistance);
	}
}

float Source::GetRolloffFactor() const
{
	return m_fRolloffFactor;
}

void Source::SetRolloffFactor(float fRolloffFactor)
{
	// [TODO] Use this?
	m_fRolloffFactor = fRolloffFactor;
}

Vector3 Source::GetAttribute(EAttributes nAttribute) const
{
	// Check parameter
	return (nAttribute < NumOfAttributes) ? m_vAttributes[nAttribute] : Vector3::Zero;
}

bool Source::SetAttribute(EAttributes nAttribute, const Vector3 &vV)
{
	// Set value
	m_vAttributes[nAttribute] = vV;

	// Currently playing?
	if (m_pChannel) {
		// Set sound API value
		switch (nAttribute) {
			case Position:
				m_pChannel->set3DAttributes((const FMOD_VECTOR*)&m_vAttributes[Position].x, NULL);
				return true; // Done

			case Velocity:
				m_pChannel->set3DAttributes(NULL, (const FMOD_VECTOR*)&m_vAttributes[Velocity].x);
				return true; // Done
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMODEx


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
