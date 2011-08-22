/*********************************************************\
 *  File: PGRain.cpp                                     *
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
#include <PLCore/Tools/Timing.h>
#include <PLCore/System/System.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGRain.h"


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
pl_implement_class(PGRain)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGRain::PGRain() :
	EnergyPerSec(this),
	EnergyMin(this),
	EnergyRange(this),
	Brightness(this),
	MediumSpeed(this),
	MediumSize(this),
	DownVsAwayRatio(this),
	BuildPerSec(this),
	Material(this),
	Particles(this),
	EventHandlerUpdate(&PGRain::OnUpdate, this),
	m_bUpdate(false)
{
	// Overwritten SNParticleGroup variables
	m_sMaterial  = "Data/Textures/PGRain.dds";
	m_nParticles = 800;
}

/**
*  @brief
*    Destructor
*/
PGRain::~PGRain()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGRain::OnActivate(bool bActivate)
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

void PGRain::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes a particle
*/
void PGRain::InitParticle(Particle &cParticle) const
{
	cParticle.vPos = GetTransform().GetPosition();
	cParticle.vPos.x += Math::GetRandNegFloat()*20;
	cParticle.vPos.z += Math::GetRandNegFloat()*20;

	cParticle.vVelocity.x =  Math::GetRandNegFloat()/100.0f;
	cParticle.vVelocity.y = -Math::GetRandFloat();
	cParticle.vVelocity.z =  Math::GetRandNegFloat()/100.0f;

	if (System::GetInstance()->GetMicroseconds() % DownVsAwayRatio) {
		float fVelLength = MediumSpeed/cParticle.vVelocity.GetLength();
		cParticle.vVelocity.x *= fVelLength;
		cParticle.vVelocity.z *= fVelLength;
		fVelLength += static_cast<float>(0.2*fVelLength);
		cParticle.vVelocity.y *= fVelLength;
	} else {
		float fVelLength = 1/cParticle.vVelocity.GetLength();
		cParticle.vVelocity.x *= fVelLength*MediumSpeed/5;
		cParticle.vVelocity.y *= fVelLength*MediumSpeed/5;
		cParticle.vVelocity.z *= (fVelLength*MediumSpeed);
		if (cParticle.vVelocity.z > 1)
			cParticle.vVelocity.z = -cParticle.vVelocity.z;
	}
	cParticle.fEnergy = Math::GetRandNegFloat()*EnergyRange + EnergyMin;

	float fColor = Math::GetRandFloat()*0.5f;
	cParticle.vColor[0] = (static_cast<float>(Brightness)/255.0f)-fColor;
	cParticle.vColor[1] = (static_cast<float>(Brightness)/255.0f)-fColor;
	cParticle.vColor[2] = (static_cast<float>(Brightness)/255.0f)-fColor;
	cParticle.vColor[3] = cParticle.fEnergy/255.0f;

	cParticle.fSize    = (static_cast<float>(MediumSize) + Math::GetRandNegFloat()*static_cast<float>(MediumSize)*0.1f)/10.0f;
	cParticle.fCustom1 = cParticle.fSize*1.9f;

	cParticle.bDistorted	= true;
	cParticle.vDistortion.x = 0.0f;
	cParticle.vDistortion.y = 0.0f;
	cParticle.vDistortion.z = 0.0f;
}

/**
*  @brief
*    Called when the scene node needs to be updated
*/
void PGRain::OnUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		// If there are free particles, create new particles
		if (!(System::GetInstance()->GetMicroseconds() % BuildPerSec)) {
			while (Math::GetRand() % 5) {
				Particle *pParticle = AddParticle();
				if (pParticle)
					InitParticle(*pParticle);
				else
					break;
			}
		}

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				// Update velocity
				cParticle.vVelocity.y += GetGravity().y*fTimeDiff*(200-cParticle.fEnergy)/10;
				cParticle.vVelocity.y -= cParticle.vVelocity.y*fTimeDiff;

				// Update position
				Vector3 vMove = cParticle.vVelocity*fTimeDiff*cParticle.fEnergy/100;
				cParticle.vPos += vMove/10;

				// Update distortion
				cParticle.fCustom1 += fTimeDiff;
				float dLength = cParticle.fCustom1/vMove.GetLength()*5;
				cParticle.vDistortion = vMove*dLength;

				// Update energy, size and lifetime
				cParticle.fEnergy -= fTimeDiff*EnergyPerSec;
				cParticle.fSize   -= fTimeDiff/2;
				if (cParticle.fEnergy <= 0 || cParticle.fSize <= 0)
					InitParticle(cParticle);
				else
					cParticle.vColor[3] = cParticle.fEnergy/255;
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
