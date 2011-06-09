/*********************************************************\
 *  File: SNMSound.cpp                                   *
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
#include <PLSound/Source.h>
#include <PLSound/SoundManager.h>
#include <PLSound/ResourceHandler.h>
#include "PLSound/SceneNodes/SCSound.h"
#include "PLSound/SceneNodeModifiers/SNMSound.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLSound {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMSound)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMSound::GetSound() const
{
	return m_sSound;
}

void SNMSound::SetSound(const String &sValue)
{
	if (m_sSound != sValue) {
		m_sSound = sValue;

		// Load/reload the sound
		Load();
	}
}

float SNMSound::GetVolume() const
{
	return m_fVolume;
}

void SNMSound::SetVolume(float fValue)
{
	if (m_fVolume != fValue) {
		m_fVolume = fValue;
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS)
			pSS->SetVolume(m_fVolume);
	}
}

float SNMSound::GetPitch() const
{
	return m_fPitch;
}

void SNMSound::SetPitch(float fValue)
{
	if (m_fPitch != fValue) {
		m_fPitch = fValue;
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS)
			pSS->SetPitch(m_fPitch);
	}
}

float SNMSound::GetReferenceDistance() const
{
	return m_fReferenceDistance;
}

void SNMSound::SetReferenceDistance(float fValue)
{
	if (m_fReferenceDistance != fValue) {
		m_fReferenceDistance = fValue;
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS)
			pSS->SetReferenceDistance(m_fReferenceDistance);
	}
}

float SNMSound::GetMaxDistance() const
{
	return m_fMaxDistance;
}

void SNMSound::SetMaxDistance(float fValue)
{
	if (m_fMaxDistance != fValue) {
		m_fMaxDistance = fValue;
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS)
			pSS->SetMaxDistance(m_fMaxDistance);
	}
}

float SNMSound::GetRolloffFactor() const
{
	return m_fRolloffFactor;
}

void SNMSound::SetRolloffFactor(float fValue)
{
	if (m_fRolloffFactor != fValue) {
		m_fRolloffFactor = fValue;
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS)
			pSS->SetRolloffFactor(m_fRolloffFactor);
	}
}

void SNMSound::SetFlags(uint32 nValue)
{
	if (GetFlags() != nValue) {
		// Call base implementation
		SceneNodeModifier::SetFlags(nValue);

		// Load/reload the sound
		Load();
	}

	// [TODO] Start/stop sound playback
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMSound::SNMSound(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Sound(this),
	Volume(this),
	Pitch(this),
	ReferenceDistance(this),
	MaxDistance(this),
	RolloffFactor(this),
	Flags(this),
	SlotOnPosition(this),
	m_fVolume(1.0f),
	m_fPitch(1.0f),
	m_fReferenceDistance(1.0f),
	m_fMaxDistance(10000.0f),
	m_fRolloffFactor(1.0f),
	m_pSoundSourceHandler(new PLSound::ResourceHandler())
{
}

/**
*  @brief
*    Destructor
*/
SNMSound::~SNMSound()
{
	// Destroy used sound source
	Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
	if (pSS)
		delete pSS;
	delete m_pSoundSourceHandler;
}

/**
*  @brief
*    Returns the sound source
*/
Source *SNMSound::GetSoundSource() const
{
	return static_cast<Source*>(m_pSoundSourceHandler->GetResource());
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMSound::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	if (bActivate)
		GetSceneNode().GetTransform().EventPosition.Connect(&SlotOnPosition);
	else
		GetSceneNode().GetTransform().EventPosition.Disconnect(&SlotOnPosition);

	// [TODO] Start/stop sound playback
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the sound container this sound is in
*/
SCSound *SNMSound::GetSoundContainer() const
{
	// Get the PL sound container this scene node is in
	SceneContainer *pContainer = GetSceneNode().GetContainer();
	while (pContainer && !pContainer->IsInstanceOf("PLSound::SCSound"))
		pContainer = pContainer->GetContainer();

	// Done
	return (pContainer && pContainer->IsInstanceOf("PLSound::SCSound")) ? static_cast<SCSound*>(pContainer) : nullptr;
}

/**
*  @brief
*    Called when the scene node position changed
*/
void SNMSound::OnPosition()
{
	// Update sound source position
	if (GetSceneNode().GetContainer()) {
		Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
		if (pSS) {
			// Get the PL sound container this scene node is in
			SCSound *pSoundContainer = GetSoundContainer();
			if (pSoundContainer) {
				Matrix3x4 matTransform;
				GetSceneNode().GetContainer()->GetTransformMatrixTo(*pSoundContainer, matTransform);
				pSS->SetAttribute(Source::Position, matTransform*GetSceneNode().GetTransform().GetPosition());
			}
		}
	}
}

/**
*  @brief
*    Loads/reloads the sound
*/
void SNMSound::Load()
{
	// Destroy currently used sound source
	Source *pSS = static_cast<Source*>(m_pSoundSourceHandler->GetResource());
	if (pSS)
		delete pSS;

	// Get the PL sound container this scene node is in
	SceneContainer *pContainer = GetSceneNode().GetContainer();
	while (pContainer && !pContainer->IsInstanceOf("PLSound::SCSound"))
		pContainer = pContainer->GetContainer();
	if (pContainer) {
		SoundManager *pSoundManager = static_cast<SCSound*>(pContainer)->GetSoundManager();
		if (pSoundManager) {
			Source *pSoundSource = pSoundManager->CreateSoundSource(pSoundManager->CreateSoundBuffer(m_sSound, (GetFlags() & Stream) != 0));
			m_pSoundSourceHandler->SetResource(pSoundSource);
			pSoundSource->SetAttribute(Source::Position, GetSceneNode().GetTransform().GetPosition());
			pSoundSource->SetVolume(m_fVolume);
			pSoundSource->Set2D((GetFlags() & No3D) != 0);
			pSoundSource->SetLooping(!(GetFlags() & NoLoop));
			pSoundSource->SetPitch(m_fPitch);
			pSoundSource->SetReferenceDistance(m_fReferenceDistance);
			pSoundSource->SetMaxDistance(m_fMaxDistance);
			pSoundSource->SetRolloffFactor(m_fRolloffFactor);
			OnPosition();
			if (!(GetFlags() & NoStartPlayback))
				pSoundSource->Play();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
