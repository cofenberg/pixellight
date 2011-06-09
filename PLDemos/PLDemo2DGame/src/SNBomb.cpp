/*********************************************************\
 *  File: SNBomb.cpp                                     *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLSound/Source.h>
#include "SNBomb.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLSound;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNBomb)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNBomb::SNBomb() :
	Killed(this),
	Sound(this),
	Flags(this),
	EventHandlerUpdate(&SNBomb::OnUpdate, this),
	m_fTimer(0.0f),
	m_nFrame(0),
	m_fFrame(0.0f),
	m_bAnimationDirection(1)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoLoop|NoStartPlayback|No3D);

	// Overwritten PLSound::SNSound variables
	m_sSound = "Data/Sounds/Explosion.ogg";

	// Set the bounding box
	SetAABoundingBox(AABoundingBox(-8.0f, -8.0f, -1.0f, 8.0f, 8.0f, 1.0f));
}

/**
*  @brief
*    Destructor
*/
SNBomb::~SNBomb()
{
}

/**
*  @brief
*    Returns the current frame
*/
char SNBomb::GetFrame() const
{
	return m_nFrame;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNBomb::OnUpdate()
{
	// Get time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Update timer
	m_fTimer += fTimeDiff/10;

	// Update position and check whether the bomb hits the ground
	bool bFalling = false;
	if (GetTransform().GetPosition().y < 180.0f) {
		bFalling = true;
		GetTransform().SetPosition(GetTransform().GetPosition() + Vector3(0.0f, 20.0f, 0.0f)*fTimeDiff);
	} else {
		// Kill the bomb
		Killed = true;
	}

	// Is the bomb killed?
	if (Killed) {
		// Animate bomb death
		if (m_nFrame < 7) {
			// Start killed animation
			m_nFrame = 7;
			m_fFrame = 0.0f;

			// Play sound
			Source *pSoundSource = GetSoundSource();
			if (pSoundSource)
				pSoundSource->Play();
		} else {
			m_fFrame += fTimeDiff*10;
			while (m_fFrame >= 1.0f) {
				m_fFrame -= 1.0f;
				m_nFrame++;
				if (m_nFrame >= 11) {
					// Destroy the bomb scene node if the sound is finished
					Source *pSoundSource = GetSoundSource();
					if (!pSoundSource || pSoundSource && !pSoundSource->IsPlaying())
						Delete();
				}
			}
		}
	} else {
		// Animate the bomb while falling
		if (bFalling) {
			m_fFrame += fTimeDiff*10;
			while (m_fFrame >= 1.0f) {
				m_fFrame -= 1.0f;
				if (m_bAnimationDirection) {
					m_nFrame++;
					if (m_nFrame >= 6)
						m_bAnimationDirection = 0;
				} else {
					m_nFrame--;
					if (m_nFrame <= 0)
						m_bAnimationDirection = 1;
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNBomb::OnActivate(bool bActivate)
{
	// Call the base implementation
	SNSound::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}
