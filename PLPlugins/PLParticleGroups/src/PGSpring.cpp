/*********************************************************\
 *  File: PGSpring.cpp                                   *
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
#include <PLGeneral/Tools/Timing.h>
#include "PLParticleGroups/PGSpring.h"


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
pl_implement_class(PGSpring)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGSpring::PGSpring() :
	Size(this),
	RotVelocity(this),
	VelocityScale(this),
	Material(this),
	Particles(this)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial  = "Data/Textures/PGSpring.dds";
	m_nParticles = 20;
}

/**
*  @brief
*    Destructor
*/
PGSpring::~PGSpring()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGSpring::UpdateFunction()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || GetDrawn()) {
		// Call base implementation
		SNParticleGroup::UpdateFunction();

		// If there are free particles, create new particles
		Particle *pParticle = AddParticle();
		while (pParticle) {
			pParticle->fSize	   = Math::GetRandFloat()*10*Size;
			pParticle->vColor.a    = Math::GetRandFloat();
			pParticle->vPos		   = GetTransform().GetPosition();
			pParticle->fEnergy	   = Math::GetRandFloat()*2;
			pParticle->vVelocity.x = Math::GetRandNegFloat()*VelocityScale;
			pParticle->vVelocity.y = Math::GetRandNegFloat()*VelocityScale;
			pParticle->vVelocity.z = Math::GetRandNegFloat()*VelocityScale;
			pParticle->vColor.r    = pParticle->vColor.g = pParticle->vColor.b = pParticle->fEnergy;

			// Next particle, please
			pParticle = AddParticle();
		}

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				cParticle.fEnergy -= fTimeDiff;
				if (cParticle.fEnergy < 0.0f) {
					RemoveParticle(cParticle);
				} else {
					cParticle.fSize		+= fTimeDiff*4*Size;
					cParticle.vColor.r   = cParticle.vColor.g = cParticle.vColor.b = cParticle.fEnergy;
					cParticle.vVelocity += GetGravity()*fTimeDiff/10*VelocityScale;
					cParticle.vPos		+= cParticle.vVelocity*fTimeDiff;
					cParticle.fRot		+= fTimeDiff*5*RotVelocity;

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
		}

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
