/*********************************************************\
 *  File: PGExplosion.cpp                                *
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
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGExplosion.h"


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
pl_implement_class(PGExplosion)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGExplosion::PGExplosion() :
	Mode(this),
	Material(this),
	Particles(this),
	TextureAnimationColumns(this),
	TextureAnimationRows(this),
	EventHandlerUpdate(&PGExplosion::NotifyUpdate, this),
	m_bUpdate(false)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial				   = "Data/Textures/PGExplosion.dds";
	m_nParticles			   = 5;
	m_nTextureAnimationColumns = 4;
	m_nTextureAnimationRows    = 4;
}

/**
*  @brief
*    Destructor
*/
PGExplosion::~PGExplosion()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGExplosion::InitFunction()
{
	// Call base implementation
	PGPhysics::InitFunction();

	// Initialize the particles
	InitParticles();
}

void PGExplosion::OnActivate(bool bActivate)
{
	// Call the base implementation
	PGPhysics::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}

void PGExplosion::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the particles
*/
void PGExplosion::InitParticles()
{
	// If there are free particles, create new particles
	float fLength = 0.1f;
	Particle *pParticle = AddParticle();
	while (pParticle) {
		pParticle->fSize	= fLength+Math::GetRandFloat()*3.5f;
		pParticle->vColor.a = pParticle->fEnergy = 0.6f+Math::GetRandFloat()*0.4f;
		for (int i=0; i<3; i++)
			pParticle->vPos[i] = GetTransform().GetPosition()[i]+Math::GetRandNegFloat();
		pParticle->vVelocity.x = Math::GetRandNegFloat()*fLength;
		pParticle->vVelocity.y = Math::GetRandNegFloat()*fLength;
		pParticle->vVelocity.z = -fLength*2-Math::GetRandFloat()*fLength*0.5f;
		pParticle->vColor.r = pParticle->vColor.g = pParticle->vColor.b = 0.6f+Math::GetRandFloat()*0.4f;
		pParticle->nAnimationStep = 0;

		// Next particle, please
		pParticle = AddParticle();
	}
}

/**
*  @brief
*    Called when the scene node needs to be updated
*/
void PGExplosion::NotifyUpdate()
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
					cParticle.vVelocity -= GetGravity()*fTimeDiff;
					cParticle.vPos      += cParticle.vVelocity*fTimeDiff;

					// Texture animation
					cParticle.fAnimationTimer += fTimeDiff;
					if (cParticle.fAnimationTimer > 0.04f) {
						cParticle.fAnimationTimer = 0.0f;
						cParticle.nAnimationStep++;
						if (cParticle.nAnimationStep >= GetTextureAnimationSteps())
							RemoveParticle(cParticle);
					}
				}
			}
		}

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();

		// Explosion finished?
		if (!nActive) {
			switch (Mode) {
				case Repeat: InitParticles(); break;
				case Remove: Delete();		  break;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
