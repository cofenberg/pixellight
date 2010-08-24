/*********************************************************\
 *  File: JointHinge.cpp                                 *
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
#include <PLMath/Matrix3x4.h>
#include <PLPhysics/Body.h>
#include "PLPhysicsNewton/BodyImpl.h"
#include "PLPhysicsNewton/JointImpl.h"
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/JointHinge.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
JointHinge::~JointHinge()
{
}


//[-------------------------------------------------------]
//[ Public Newton callback functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static Newton joint user callback function
*/
unsigned JointHinge::JointUserCallback(const Newton::NewtonJoint *pNewtonJoint, Newton::NewtonHingeSliderUpdateDesc *pDesc)
{
	// Get joint
	const JointHinge *pJoint = (JointHinge*)NewtonJointGetUserData(pNewtonJoint);
	if (pJoint) {
		// Check break
		if (pJoint->IsBreakable()) {
			bool bBreak = false;

			// Check force
			dFloat fCurrentForce[3];
			NewtonHingeGetJointForce(pNewtonJoint, fCurrentForce);
			Vector3 vForce;
			pJoint->GetBreakForce(vForce);
			if (fCurrentForce[0] > vForce.x || fCurrentForce[1] > vForce.y || fCurrentForce[2] > vForce.z)
				bBreak = true;

			// Check torque
			if (!bBreak) {
				dFloat fCurrentTorque = NewtonHingeGetJointOmega(pNewtonJoint);
				Vector3 vTorque;
				pJoint->GetBreakTorque(vTorque);
				if (fCurrentTorque > vTorque.x || fCurrentTorque > vTorque.y || fCurrentTorque > vTorque.z)
					bBreak = true;
			}

			// Destroy the joint?
			if (bBreak)
				NewtonDestroyJoint(((World&)pJoint->GetWorld()).GetNewtonWorld(), pNewtonJoint);
		}

		// Get min/max angle limits
		const float fAngleMinLimit = float(pJoint->GetLowRange());
		const float fAngleMaxLimit = float(pJoint->GetHighRange());

		// Check limits
		const float fAngle = NewtonHingeGetJointAngle(pNewtonJoint);
		if (fAngle > fAngleMaxLimit) {
			// If the joint angle is large than the defined value, stop the hinge
			pDesc->m_accel = NewtonHingeCalculateStopAlpha(pNewtonJoint, pDesc, fAngleMaxLimit);
			return 1;
		} else if (fAngle < fAngleMinLimit) {
			// If the joint angle is smaller than the defined value, stop the hinge
			pDesc->m_accel = NewtonHingeCalculateStopAlpha(pNewtonJoint, pDesc, fAngleMinLimit);
			return 1;
		}
	}

	// No action need it if the joint angle is with the limits
	return 0;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointHinge::JointHinge(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
					   const Vector3 &vPivotPoint, const Vector3 &vPinDir) :
	PLPhysics::JointHinge(cWorld, ((World&)cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = ((World&)cWorld).GetNewtonWorld();

	// Flush assigned bodies (MUST be done before creating the joint!)
	if (pParentBody)
		((BodyImpl&)pParentBody->GetBodyImpl()).Flush();
	if (pChildBody)
		((BodyImpl&)pChildBody ->GetBodyImpl()).Flush();

	// Get the Newton physics parent and child bodies
	const Newton::NewtonBody *pNewtonParentBody = pParentBody ? ((BodyImpl&)pParentBody->GetBodyImpl()).GetNewtonBody() : NULL;
	const Newton::NewtonBody *pNewtonChildBody  = pChildBody  ? ((BodyImpl&)pChildBody ->GetBodyImpl()).GetNewtonBody() : NULL;

	// Get body initial transform matrix
	if (pParentBody) {
		Quaternion qQ;
		pParentBody->GetRotation(qQ);
		Vector3 vPos;
		pParentBody->GetPosition(vPos);
		Matrix3x4 mTrans;
		mTrans.FromQuatTrans(qQ, vPos);

		// And transform the initial joint anchor into the body object space
		mTrans.Invert();
		m_vLocalAnchor = mTrans*vPivotPoint;
	}

	// Create the Newton physics joint
	Newton::NewtonJoint *pNewtonJoint = NewtonConstraintCreateHinge(pNewtonWorld, m_vPivotPoint,
																	m_vPinDir, pNewtonChildBody, pNewtonParentBody);

	// Set Newton hinge callback function
	NewtonHingeSetUserCallback(pNewtonJoint, JointUserCallback);

	// Initialize the Newton physics joint
	((JointImpl&)GetJointImpl()).InitializeNewtonJoint(*this, *pNewtonJoint);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::Joint functions             ]
//[-------------------------------------------------------]
void JointHinge::GetCurrentPivotPoint(Vector3 &vPosition) const
{
	const PLPhysics::Body *pParentBody = GetParentBody();
	if (pParentBody) {
		// Get transform matrix
		Quaternion qQ;
		pParentBody->GetRotation(qQ);
		Vector3 vPos;
		pParentBody->GetPosition(vPos);
		Matrix3x4 mTrans;
		mTrans.FromQuatTrans(qQ, vPos);

		// Get the current joint anchor in world space
		vPosition = m_vLocalAnchor;
		vPosition *= mTrans;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointHinge functions        ]
//[-------------------------------------------------------]
void JointHinge::AddOmega(float fOmega)
{
	// [TODO]
	/*
	// [TESTME] ... unlike ODE Newton offers no add omega functions... :(
	const Matrix3x4 &mTrans = GetSceneNode()->GetTransformMatrix();
	m_vPinDirTransformed = mTrans.RotateVector(m_vPinDir);
	const Vector3 vOmega = m_vPinDirTransformed*fOmega;
	Newton::NewtonBody *pPhysicsBody = GetPhysicsBody();
	if (pPhysicsBody) {
		float fOmega[3];
		NewtonBodyGetOmega(pPhysicsBody, fOmega);
		fOmega[0] += vOmega.x;
		fOmega[1] += vOmega.y;
		fOmega[2] += vOmega.z;
		NewtonBodySetOmega(pPhysicsBody, fOmega);
	}
	if (GetParentModifier() && (pPhysicsBody=GetParentModifier()->GetPhysicsBody())) {
		float fOmega[3];
		NewtonBodyGetOmega(pPhysicsBody, fOmega);
		fOmega[0] -= vOmega.x;
		fOmega[1] -= vOmega.y;
		fOmega[2] -= vOmega.z;
		NewtonBodySetOmega(pPhysicsBody, fOmega);
	}
	*/
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
