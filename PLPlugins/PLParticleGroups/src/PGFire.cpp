/*********************************************************\
 *  File: PGFire.cpp                                     *
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
#include <PLMath/Matrix3x3.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGFire.h"


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
pl_implement_class(PGFire)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Public constructor
*/
PGFire::PGFire() :
	Size(this),
	Material(this),
	Particles(this),
	EventHandlerUpdate(&PGFire::NotifyUpdate, this),
	m_bUpdate(false)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial  = "Data/Textures/PGFire.dds";
	m_nParticles = 50;
}

/**
*  @brief
*    Destructor
*/
PGFire::~PGFire()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGFire::OnActivate(bool bActivate)
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

void PGFire::OnAddedToVisibilityTree(VisNode &cVisNode)
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
void PGFire::NotifyUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		// If there are free particles, create new particles
		Particle *pParticle = AddParticle();
		while (pParticle) {
			pParticle->fSize	   = (0.02f+Math::GetRandFloat()*0.1f)*Size;
			pParticle->vPos		   = GetTransform().GetPosition();
			pParticle->fEnergy	   = Math::GetRandFloat()*0.5f;
			pParticle->vVelocity.x = Math::GetRandNegFloat()*10*Size;
			pParticle->vVelocity.y = Math::GetRandNegFloat()*10*Size;
			pParticle->vVelocity.z = Math::GetRandNegFloat()*10*Size;
			pParticle->vColor.a    = pParticle->fEnergy;
			pParticle->vColor.r    = pParticle->vColor.g = pParticle->vColor.b = 1.0f;
			pParticle->bDistorted  = false;

			if (!pParticle->pRot) pParticle->pRot = new Quaternion();
			Matrix3x3 mRot;
			mRot.LookAt(Vector3::Zero, pParticle->vVelocity.GetNormalized(), Vector3::UnitY);
			pParticle->pRot->FromRotationMatrix(mRot);

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
					cParticle.fSize += fTimeDiff*2*Size;
					cParticle.vColor.a = cParticle.fEnergy*5;
					if (cParticle.vColor.a > 1.0f) cParticle.vColor.a = 1.0f;

					cParticle.vVelocity += GetGravity()*fTimeDiff*2*Size;

					Matrix3x3 mRot;
					mRot.LookAt(Vector3::Zero, cParticle.vVelocity.GetNormalized(), Vector3::UnitY);
					cParticle.pRot->FromRotationMatrix(mRot);

					cParticle.vPos += cParticle.vVelocity*fTimeDiff/5;
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
