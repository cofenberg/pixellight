/*********************************************************\
 *  File: SoundManager.cpp                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLSoundOpenSLES/Buffer.h"
#include "PLSoundOpenSLES/Source.h"
#include "PLSoundOpenSLES/SoundManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLSoundOpenSLES {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SoundManager)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SoundManager::SoundManager() :
	m_fVolume(1.0f),
	m_fPitch(1.0f),
	m_fDopplerFactor(1.0f)
{
	PL_LOG(Info, "Create sound manager: " + GetDescription())

	// Initialize listener attributes
	m_vListenerAttributes[ListenerForward].SetXYZ(0.0f, 0.0f, 1.0f);
	m_vListenerAttributes[ListenerUpward]. SetXYZ(0.0f, 1.0f, 0.0f);
}

/**
*  @brief
*    Destructor
*/
SoundManager::~SoundManager()
{
	PL_LOG(Info, "Destroy sound manager: " + GetDescription())

	// De-initialize
	DeInit();
}


//[-------------------------------------------------------]
//[ Public virtual SoundManager functions                 ]
//[-------------------------------------------------------]
String SoundManager::GetDescription() const
{
	static const String sString = "OpenSL ES sound";
	return sString;
}

bool SoundManager::GetFormatList(List<Format> &lstList) const
{
	// All went fine - but this backend doesn't support any sound file formats :)
	return true;
}

float SoundManager::GetVolume() const
{
	return m_fVolume;
}

void SoundManager::SetVolume(float fVolume)
{
	m_fVolume = fVolume;
}

float SoundManager::GetPitch() const
{
	return m_fPitch;
}

void SoundManager::SetPitch(float fPitch)
{
	m_fPitch = fPitch;
}

float SoundManager::GetDopplerFactor() const
{
	return m_fDopplerFactor;
}

void SoundManager::SetDopplerFactor(float fFactor)
{
	m_fDopplerFactor = fFactor;
}


//[-------------------------------------------------------]
//[ Create sound buffer/source                            ]
//[-------------------------------------------------------]
PLSound::Buffer *SoundManager::CreateSoundBuffer(const String &sFilename, bool bStream)
{
	// Is there already a sound buffer with this name?
	PLSound::Buffer *pSB = GetByName(sFilename);
	return pSB ? pSB : new Buffer(*this, sFilename, bStream);
}

PLSound::Source *SoundManager::CreateSoundSource(PLSound::Buffer *pSoundBuffer)
{
	// Create the OpenSL ES sound source
	PLSound::Source *pSS = new Source(*this);
	if (pSoundBuffer)
		pSS->Load(pSoundBuffer);

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

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::SoundManager functions        ]
//[-------------------------------------------------------]
bool SoundManager::Init()
{
	// Done
	return true;
}

bool SoundManager::DeInit()
{
	// Call base implementation
	PLSound::SoundManager::DeInit();

	// Done
	return true;
}

bool SoundManager::Update()
{
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
} // PLSoundOpenSLES
