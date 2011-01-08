/*********************************************************\
 *  File: PGFountain.cpp                                 *
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
#include "PLParticleGroups/PGFountain.h"


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
pl_implement_class(PGFountain)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
uint32 PGFountain::GetSteps() const
{
	return m_nSteps;
}

void PGFountain::SetSteps(uint32 nValue)
{
	if (m_nSteps != nValue) {
		m_nSteps = nValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

uint32 PGFountain::GetRaysPerStep() const
{
	return m_nRaysPerStep;
}

void PGFountain::SetRaysPerStep(uint32 nValue)
{
	if (m_nRaysPerStep != nValue) {
		m_nRaysPerStep = nValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

uint32 PGFountain::GetDropsPerRay() const
{
	return m_nDropsPerRay;
}

void PGFountain::SetDropsPerRay(uint32 nValue)
{
	if (m_nDropsPerRay != nValue) {
		m_nDropsPerRay = nValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

float PGFountain::GetAngleOfDeepestStep() const
{
	return m_fAngleOfDeepestStep;
}

void PGFountain::SetAngleOfDeepestStep(float fValue)
{
	if (m_fAngleOfDeepestStep != fValue) {
		m_fAngleOfDeepestStep = fValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

float PGFountain::GetAngleOfHighestStep() const
{
	return m_fAngleOfHighestStep;
}

void PGFountain::SetAngleOfHighestStep(float fValue)
{
	if (m_fAngleOfHighestStep != fValue) {
		m_fAngleOfHighestStep = fValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

float PGFountain::GetRandomAngleAddition() const
{
	return m_fRandomAngleAddition;
}

void PGFountain::SetRandomAngleAddition(float fValue)
{
	if (m_fRandomAngleAddition != fValue) {
		m_fRandomAngleAddition = fValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}

float PGFountain::GetAccFactor() const
{
	return m_fAccFactor;
}

void PGFountain::SetAccFactor(float fValue)
{
	if (m_fAccFactor != fValue) {
		m_fAccFactor = fValue;
		if (IsInitialized()) {
			DeInitFunction();
			InitFunction();
		}
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGFountain::PGFountain() :
	Steps(this),
	RaysPerStep(this),
	DropsPerRay(this),
	AngleOfDeepestStep(this),
	AngleOfHighestStep(this),
	RandomAngleAddition(this),
	AccFactor(this),
	Material(this),
	Particles(this),
	m_bUpdate(false),
	m_nSteps(8),
	m_nRaysPerStep(6),
	m_nDropsPerRay(50),
	m_fAngleOfDeepestStep(80.0f),
	m_fAngleOfHighestStep(85.0f),
	m_fRandomAngleAddition(20.0f),
	m_fAccFactor(0.11f),
	EventHandlerUpdate(&PGFountain::NotifyUpdate, this)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial  = "Data/Textures/PGFountain.dds";
	m_nParticles = 600;
}

/**
*  @brief
*    Destructor
*/
PGFountain::~PGFountain()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGFountain::InitFunction()
{
	// Call base implementation
	SNParticleGroup::InitFunction();

	// Initialize all particles
	for (uint32 k=0; k<m_nSteps; k++) {
		for (uint32 j=0; j<m_nRaysPerStep; j++) {
			for (uint32 i=0; i<m_nDropsPerRay; i++) {
				Particle *pParticle = AddParticle();
				if (pParticle) {
					// Different from AccFactor because of the random change
					float fDropAccFactor = m_fAccFactor + Math::GetRandFloat()*0.005f;

					// Angle, which the ray gets out of the fountain with
					float fStepAngle;
					if (m_nSteps > 1)
						fStepAngle = m_fAngleOfDeepestStep + (m_fAngleOfHighestStep-m_fAngleOfDeepestStep)
									 *float(k)/(m_nSteps-1) + Math::GetRandFloat()*m_fRandomAngleAddition;
					else fStepAngle = m_fAngleOfDeepestStep + Math::GetRandFloat()*m_fRandomAngleAddition;
				
					// This is the speed caused by the step
					Vector3 &vNewSpeed = pParticle->vVelocity;
					vNewSpeed.x = Math::Cos(float(fStepAngle*Math::DegToRad))*(0.2f+0.04f*k);
					vNewSpeed.y = Math::Sin(float(fStepAngle*Math::DegToRad))*(0.2f+0.04f*k);

					// Angle you see when you look down on the fountain
					float fRayAngle = (float)j/(float)m_nRaysPerStep*360.0f + 12.0f;	// +12.0 causes a rotation (12°)

					// For the next computations "vNewSpeed.x" is the radius. Care! Dont swap the two
					// lines, because the second one changes vNewSpeed.x!
					vNewSpeed.z = vNewSpeed.x*Math::Sin(float(fRayAngle*Math::DegToRad));
					vNewSpeed.x = vNewSpeed.x*Math::Cos(float(fRayAngle*Math::DegToRad));
					vNewSpeed *= 3.0f;

					// Calculate how many steps are required, that a drop comes out and falls down again
					float fTimeNeeded = vNewSpeed.y/fDropAccFactor;

					// Setup particle
					pParticle->fSize	= 0.2f;
					pParticle->vColor	= 0.5f;
					pParticle->fCustom1 = fDropAccFactor;				// Acc factor
					pParticle->fCustom2 = fTimeNeeded*i/m_nDropsPerRay;	// Time
				} else {
					// Error!
					k = m_nSteps;
					j = m_nRaysPerStep;
					i = m_nDropsPerRay;
				}
			}
		}
	}
}

void PGFountain::OnActivate(bool bActivate)
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

void PGFountain::OnAddedToVisibilityTree(VisNode &cVisNode)
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
void PGFountain::NotifyUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				// Increase time
				cParticle.fCustom2 += fTimeDiff*2;

				// Check time
				if (cParticle.fCustom2 > 0.0f) {
					cParticle.bActive = true;

					// Constant speed * time
					cParticle.vPos.x = cParticle.vVelocity.x*cParticle.fCustom2;

					// Constant speed * time - acc factor * time * time
					cParticle.vPos.y = cParticle.vVelocity.y*cParticle.fCustom2-cParticle.fCustom1*cParticle.fCustom2*cParticle.fCustom2;

					// Constant speed * time
					cParticle.vPos.z = cParticle.vVelocity.z*cParticle.fCustom2;
					cParticle.vPos *= 4;
					cParticle.vPos += GetTransform().GetPosition();

					// Check height
					if (cParticle.vPos.y < GetTransform().GetPosition().y) {
						cParticle.fCustom2 = cParticle.fCustom2 - int(cParticle.fCustom2);
						if (cParticle.fCustom2 > 0.0f) cParticle.fCustom2 -= 1.0f;
					}
				} else {
					cParticle.bActive = false;
					cParticle.vPos    = Vector3::Zero;
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
