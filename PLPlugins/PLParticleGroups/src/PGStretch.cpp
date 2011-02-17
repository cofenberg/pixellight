/*********************************************************\
 *  File: PGStretch.cpp                                  *
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
#include "PLParticleGroups/PGStretch.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGStretch)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGStretch::PGStretch() :
	Size(this),
	Length(this),
	Color(this),
	Material(this),
	Particles(this),
	EventHandlerUpdate(&PGStretch::NotifyUpdate, this),
	m_bUpdate(false)
{
	// Overwritten SNParticleGroup variables
	m_sMaterial  = "Data/Textures/PGStretch.dds";
	m_nParticles = 1;
}

/**
*  @brief
*    Destructor
*/
PGStretch::~PGStretch()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGStretch::OnActivate(bool bActivate)
{
	// Call the base implementation
	SNParticleGroup::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}

void PGStretch::OnAddedToVisibilityTree(VisNode &cVisNode)
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
void PGStretch::NotifyUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		// If there are free particles, create new particles
		Particle *pParticle = AddParticle();
		while (pParticle) {
			pParticle->fSize	   = Size;
			pParticle->vColor	   = Color.Get();
			pParticle->vPos		   = GetTransform().GetPosition();
			pParticle->bDistorted  = true;
			pParticle->fEnergy	   = 1;
			pParticle->vVelocity.x = Math::GetRandNegFloat();
			pParticle->vVelocity.y = Math::GetRandNegFloat();
			pParticle->vVelocity.z = Math::GetRandNegFloat();

			// Next particle, please
			pParticle = AddParticle();
		}

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				cParticle.vPos = GetTransform().GetPosition();
				cParticle.vDistortion.SetXYZ(GetTransform().GetMatrix().GetZAxis().Normalize()*Length);

				// Texture animation
				cParticle.fAnimationTimer += fTimeDiff;
				if (cParticle.fAnimationTimer > 0.2f) {
					cParticle.fAnimationTimer = 0.0f;
					cParticle.nAnimationStep++;
					if (cParticle.nAnimationStep >= GetTextureAnimationSteps())
						cParticle.nAnimationStep = 0;
				}
			}
		}

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
