/*********************************************************\
 *  File: SCSound.cpp                                    *
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
#include <PLMath/Matrix3x3.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLSound/SoundManager.h"
#include "PLSound/SceneNodes/SCSound.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLSound {


// [TODO]
//	if (m_pSoundManager) m_pSoundManager->UnloadUnused();


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SCSound)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
float SCSound::GetVolume() const
{
	return m_fVolume;
}

void SCSound::SetVolume(float fValue)
{
	if (m_fVolume != fValue) {
		m_fVolume = fValue;
		if (m_pSoundManager)
			m_pSoundManager->SetVolume(m_fVolume);
	}
}

float SCSound::GetPitch() const
{
	return m_fPitch;
}

void SCSound::SetPitch(float fValue)
{
	if (m_fPitch != fValue) {
		m_fPitch = fValue;
		if (m_pSoundManager)
			m_pSoundManager->SetPitch(m_fPitch);
	}
}

String SCSound::GetListener() const
{
	return m_sListener;
}

void SCSound::SetListener(const String &sValue)
{
	if (m_sListener != sValue) {
		m_sListener = sValue;
		m_cListenerNodeHandler.SetElement(Get(m_sListener));
		NotifyUpdate();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SCSound::SCSound() :
	SoundAPI(this),
	Volume(this),
	Pitch(this),
	Listener(this),
	EventHandlerUpdate(&SCSound::NotifyUpdate, this),
	m_fVolume(1.0f),
	m_fPitch(1.0f),
	m_pSoundManager(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SCSound::~SCSound()
{
	// De-initialize the scene container
	DeInit();

	// Destroy the PL sound manager
	if (m_pSoundManager)
		delete m_pSoundManager;
}

/**
*  @brief
*    Returns the PL sound manager
*/
SoundManager *SCSound::GetSoundManager() const
{
	return m_pSoundManager;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SCSound::NotifyUpdate()
{
	// Update the PL sound manager
	if (m_pSoundManager) {
		// Get the scene node used as listener
		SceneNode *pListener = m_cListenerNodeHandler.GetElement();
		if (!pListener) {
			pListener = Get(m_sListener);
			m_cListenerNodeHandler.SetElement(pListener);
		}
		if (pListener && pListener->GetContainer()) {
			// Set the position and rotation of the listener. If the sound takes
			// place within another container, we need to transform...
			Matrix3x4 matTransform;
			pListener->GetContainer()->GetTransformMatrixTo(*this, matTransform);
			Vector3    vPosition = matTransform*pListener->GetTransform().GetPosition();
			Quaternion qRotation = pListener->GetTransform().GetRotation()*matTransform;

			// Set listener position
			m_pSoundManager->SetListenerAttribute(SoundManager::ListenerPosition, vPosition);

			// Get/set listener direction vectors
			m_pSoundManager->SetListenerAttribute(SoundManager::ListenerForward, qRotation.GetZAxis());
			m_pSoundManager->SetListenerAttribute(SoundManager::ListenerUpward,  qRotation.GetYAxis());
		}

		// Update sound manger
		m_pSoundManager->Update();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNode functions        ]
//[-------------------------------------------------------]
void SCSound::InitFunction()
{
	// Call base implementation
	SceneContainer::InitFunction();

	// Is the sound manager already created?
	if (!m_pSoundManager) {
		// Create the PL sound manager
		const Class *pClass = ClassManager::GetInstance()->GetClass(SoundAPI.Get());
		if (pClass && pClass->IsDerivedFrom("PLSound::SoundManager")) {
			Object *pObject = pClass->Create();
			if (pObject) {
				m_pSoundManager = (SoundManager*)pObject;
				if (m_pSoundManager->Init()) {
					m_pSoundManager->SetVolume(m_fVolume);
					m_pSoundManager->SetPitch (m_fPitch);
					NotifyUpdate();
				}
			}
		}
	}
}

void SCSound::OnActivate(bool bActivate)
{
	// Call the base implementation
	SceneContainer::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
