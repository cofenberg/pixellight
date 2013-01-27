/*********************************************************\
 *  File: Source.cpp                                     *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLSoundFMOD/SoundManager.h"
#include "PLSoundFMOD/Buffer.h"
#include "PLSoundFMOD/Source.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4505) // "'function' : unreferenced local function has been removed"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLSoundFMOD {


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
	m_nChannel(-1),
	m_nFrequency(0),
	m_fVolume(1.0f),
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
	Buffer *pBuffer = static_cast<Buffer*>(GetBuffer());
	if (!pBuffer)
		return false; // Error!

	// Paused?
	if (IsPaused() && !bRestart) {
		FSOUND_SetPaused(m_nChannel, 0);
	} else {
		// Play
		if (IsPlaying()) {
			if (!bRestart)
				return true; // Done
			Stop();
		}
		m_nChannel = pBuffer->Play();

		// Add source to sound manager
		static_cast<SoundManager&>(GetSoundManager()).AddActiveSource(*this);

		// Get frequency and setup pitch
		m_nFrequency = FSOUND_GetFrequency(m_nChannel);
		float fPitch = m_fPitch;
		m_fPitch = -1.0f;
		SetPitch(fPitch);

		// Set volume
		pBuffer->SetVolume(m_nChannel, m_fVolume);

		// [HACK] HW sound: We have to pause the playback if we want to change the looping mode...
	//	FSOUND_SetPaused(m_nChannel, 1);
		pBuffer->SetLooping(m_nChannel, m_bLooping);
	//	FSOUND_SetPaused(m_nChannel, 0);

		// Set attributes
		SetAttribute(Position, m_vAttributes[Position]);
		SetAttribute(Velocity, m_vAttributes[Velocity]);
	}

	// Done
	return true;
}

bool Source::IsPlaying() const
{
	// Is a buffer loaded?
	const Buffer *pBuffer = static_cast<const Buffer*>(GetBuffer());
	return (pBuffer && pBuffer->IsPlaying(m_nChannel));
}

void Source::Pause()
{
	// Is the source currently playing?
	if (IsPlaying()) {
		// Pause now
		FSOUND_SetPaused(m_nChannel, 1);
	}
}

bool Source::IsPaused() const
{
	return (GetBuffer() && FSOUND_GetPaused(m_nChannel) != 0);
}

void Source::Stop()
{
	// Is a buffer loaded? (using 'IsPlaying()' to test this is NOT correct in here!)
	Buffer *pBuffer = static_cast<Buffer*>(GetBuffer());
	if (pBuffer) {
		// Stop playback
		pBuffer->Stop(m_nChannel);
		m_nChannel = -1;

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
		Buffer *pBuffer = static_cast<Buffer*>(GetBuffer());
		if (pBuffer)
			pBuffer->SetVolume(m_nChannel, m_fVolume);
	}
}

bool Source::Is2D() const
{
	// [TODO]
	return false;
}

void Source::Set2D(bool b2D)
{
	// [TODO]
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

		// Is a buffer loaded?
		Buffer *pBuffer = static_cast<Buffer*>(GetBuffer());
		if (pBuffer) {
			// Set looping state
			// [HW sound] We have to pause the playback if we want to change the looping mode...
		//	bool bPaused = IsPaused();
		//	if (!bPaused)
		//		Pause();
			pBuffer->SetLooping(m_nChannel, m_bLooping);
		//	if (!bPaused)
		//		Play();
		}
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
		int nFrequency = (GetFlags() & Source::NoMasterPitch) ? static_cast<int>(m_nFrequency*m_fPitch) : static_cast<int>(m_nFrequency*(m_fPitch*GetSoundManager().GetPitch()));
		if (nFrequency < 100)
			nFrequency = 100;
		if (nFrequency > 705600)
			nFrequency = 705600;
		FSOUND_SetFrequency(m_nChannel, nFrequency);
	}
}

float Source::GetReferenceDistance() const
{
	return m_fReferenceDistance;
}

void Source::SetReferenceDistance(float fReferenceDistance)
{
	m_fReferenceDistance = fReferenceDistance;
	// [TODO]
}

float Source::GetMaxDistance() const
{
	return m_fMaxDistance;
}

void Source::SetMaxDistance(float fMaxDistance)
{
	m_fMaxDistance = fMaxDistance;
	// [TODO]
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
	if (m_nChannel > -1) {
		// Set sound API value
		switch (nAttribute) {
			case Position:
				FSOUND_3D_SetAttributes(m_nChannel, vV, m_vAttributes[Position]);
				break;

			case Velocity:
				FSOUND_3D_SetAttributes(m_nChannel, m_vAttributes[Velocity], vV);
				break;

			// Error!
			default:
				return false;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
