/*********************************************************\
 *  File: Source.cpp                                     *
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
	m_pChannel(nullptr),
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

/**
*  @brief
*    Returns the current FMOD Ex mode
*/
FMOD_MODE Source::GetFMODExMode() const
{
	FMOD_MODE nFMODExMode = FMOD_HARDWARE;

	// 2D or 3D sound?
	nFMODExMode |= m_b2D ? FMOD_2D : FMOD_3D;

	// Loop?
	nFMODExMode |= m_bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	// Return the current FMOD Ex mode
	return nFMODExMode;
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
	Buffer *pBuffer = static_cast<Buffer*>(GetBuffer());
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
			FMOD::System *pSystem = static_cast<SoundManager&>(GetSoundManager()).GetSystem();
			if (pSystem) {
				// Set looping
				pBuffer->GetSound()->setLoopCount(m_bLooping ? -1 : 0);

				// Play FMOD Ex sound
				FMOD_RESULT nResult = pSystem->playSound(FMOD_CHANNEL_FREE, pBuffer->GetSound(), false, &m_pChannel);
				if (SoundManager::ErrorCheck(nResult)) {
					// Add source to sound manager
					static_cast<SoundManager&>(GetSoundManager()).AddActiveSource(*this);

					// Set mode
					m_pChannel->setMode(GetFMODExMode());

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
		m_pChannel = nullptr;

		// Remove source from sound manager
		static_cast<SoundManager&>(GetSoundManager()).RemoveActiveSource(*this);
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
		if (m_pChannel)
			m_pChannel->setMode(GetFMODExMode());
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
			m_pChannel->setMode(GetFMODExMode());
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
				m_pChannel->set3DAttributes(reinterpret_cast<const FMOD_VECTOR*>(&m_vAttributes[Position].x), nullptr);
				return true; // Done

			case Velocity:
				m_pChannel->set3DAttributes(nullptr, reinterpret_cast<const FMOD_VECTOR*>(&m_vAttributes[Velocity].x));
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
