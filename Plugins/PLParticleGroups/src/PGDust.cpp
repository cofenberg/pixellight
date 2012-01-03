/*********************************************************\
 *  File: PGDust.cpp                                     *
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
#include <PLCore/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGDust.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGDust)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGDust::PGDust() :
	EventHandlerUpdate(&PGDust::OnUpdate, this),
	m_bUpdate(false)
{
}

/**
*  @brief
*    Destructor
*/
PGDust::~PGDust()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGDust::InitFunction()
{
	// Call base implementation
	PGPhysics::InitFunction();

	// If there are free particles, create new particles
	float fLength = 0.01f;
	Particle *pParticle = AddParticle();
	while (pParticle) {
		pParticle->fSize	   = fLength + static_cast<float>(Math::GetRand() % 100) / 400.0f;
		pParticle->vColor.a    = pParticle->fEnergy = 0.4f + static_cast<float>(Math::GetRand() % 100) / 500.0f;
		pParticle->vPos		   = GetTransform().GetPosition();
		pParticle->vVelocity.x = Math::GetRandNegFloat()*fLength;
		pParticle->vVelocity.y = Math::GetRandNegFloat()*fLength;
		pParticle->vVelocity.z = -fLength*2-Math::GetRandFloat()*fLength*0.5f;
		pParticle->vColor.r    = pParticle->vColor.g = pParticle->vColor.b = pParticle->fEnergy/2;

		// Next particle, please
		pParticle = AddParticle();
	}
}

void PGDust::OnActivate(bool bActivate)
{
	// Call the base implementation
	PGPhysics::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(EventHandlerUpdate);
	}
}

void PGDust::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void PGDust::OnUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		uint32 nActive = 0;

		m_bUpdate = false;

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				cParticle.fEnergy -= fTimeDiff;
				if (cParticle.fEnergy < 0.0f) {
					RemoveParticle(cParticle);
				} else {
					nActive++;
					cParticle.fSize     += fTimeDiff*4;
					cParticle.vColor.a   = cParticle.fEnergy;
					cParticle.vVelocity += GetGravity()*fTimeDiff*2;
					cParticle.vPos      += cParticle.vVelocity*fTimeDiff;

					// Texture animation
					cParticle.fAnimationTimer += fTimeDiff;
					if (cParticle.fAnimationTimer > 0.04f) {
						cParticle.fAnimationTimer = 0.0f;
						cParticle.nAnimationStep++;
						if (cParticle.nAnimationStep >= GetTextureAnimationSteps())
							cParticle.nAnimationStep = 0;
					}
				}
			}
		}

		// Remove particle group?
		if (nActive) {
			// We have to recalculate the current axis align bounding box in 'scene node space'
			DirtyAABoundingBox();
		} else {
			Delete();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
