/*********************************************************\
 *  File: Source.cpp                                     *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLSoundNull/SoundManager.h"
#include "PLSoundNull/Buffer.h"
#include "PLSoundNull/Source.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLSoundNull {


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

bool Source::Play(bool bRestart)
{
	// Done
	return true;
}

bool Source::IsPlaying() const
{
	// Not playing
	return false;
}

void Source::Pause()
{
}

bool Source::IsPaused() const
{
	// Not paused
	return false;
}

void Source::Stop()
{
}

float Source::GetVolume() const
{
	return m_fVolume;
}

void Source::SetVolume(float fVolume)
{
	m_fVolume = fVolume;
}

bool Source::Is2D() const
{
	return m_b2D;
}

void Source::Set2D(bool b2D)
{
	m_b2D = b2D;
}

bool Source::IsLooping() const
{
	return m_bLooping;
}

void Source::SetLooping(bool bLooping)
{
	m_bLooping = bLooping;
}

float Source::GetPitch() const
{
	return m_fPitch;
}

void Source::SetPitch(float fPitch)
{
	m_fPitch = fPitch;
}

float Source::GetReferenceDistance() const
{
	return m_fReferenceDistance;
}

void Source::SetReferenceDistance(float fReferenceDistance)
{
	m_fReferenceDistance = fReferenceDistance;
}

float Source::GetMaxDistance() const
{
	return m_fMaxDistance;
}

void Source::SetMaxDistance(float fMaxDistance)
{
	m_fMaxDistance = fMaxDistance;
}

float Source::GetRolloffFactor() const
{
	return m_fRolloffFactor;
}

void Source::SetRolloffFactor(float fRolloffFactor)
{
	m_fRolloffFactor = fRolloffFactor;
}

Vector3 Source::GetAttribute(EAttributes nAttribute) const
{
	// Check parameter
	return (nAttribute < NumOfAttributes) ? m_vAttributes[nAttribute] : Vector3::Zero;
}

bool Source::SetAttribute(EAttributes nAttribute, const Vector3 &vV)
{
	// Check parameter
	if (nAttribute >= NumOfAttributes)
		return false; // Error!

	// Set attribute
	m_vAttributes[nAttribute] = vV;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundNull
