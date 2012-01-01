/*********************************************************\
 *  File: RagdollJoint.cpp                               *
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
#include "PLPhysics/Body.h"
#include "PLPhysics/JointHinge.h"
#include "PLPhysics/JointUniversal.h"
#include "PLPhysics/World.h"
#include "PLPhysics/ElementHandler.h"
#include "PLPhysics/SceneNodes/SNRagdoll.h"
#include "PLPhysics/SceneNodes/RagdollBody.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodes/RagdollJoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RagdollJoint::RagdollJoint(SNRagdoll *pParent) :
	m_pParentRagdoll(pParent),
	m_pJointHandler(new ElementHandler()),
	bAttachToWorld(false),
	nJointType(Universal),
	fLowJointRange1(-0.3f),
	fHighJointRange1(0.3f),
	fLowJointRange2(-0.3f),
	fHighJointRange2(0.3f)
{
}

/**
*  @brief
*    Destructor
*/
RagdollJoint::~RagdollJoint()
{
	DestroyPhysicsJoint();
	delete m_pJointHandler;
}

/**
*  @brief
*    Returns the PL physics joint
*/
Joint *RagdollJoint::GetJoint() const
{
	return static_cast<Joint*>(m_pJointHandler->GetElement());
}

/**
*  @brief
*    Sets the name of the joint
*/
bool RagdollJoint::SetName(const String &sName)
{
	// Is this the current name?
	if (this->sName != sName) {
		// Is there a parent ragdoll and is this joint name already used within the ragdoll?
		if (!m_pParentRagdoll || m_pParentRagdoll->m_mapJoints.Get(sName))
			return false; // Error!

		// Set the new name
		m_pParentRagdoll->m_mapJoints.Remove(this->sName);
		this->sName = sName;
		m_pParentRagdoll->m_mapJoints.Add(this->sName, this);
	}

	// Done
	return true;
}

/**
*  @brief
*    Creates the physics joint
*/
void RagdollJoint::CreatePhysicsJoint()
{
	// Is there a parent ragdoll?
	if (m_pParentRagdoll) {
		// Destroy the old physics joint
		DestroyPhysicsJoint();

		// Get data
		SCPhysicsWorld *pWorldContainer = m_pParentRagdoll->GetWorldContainer();
		if (pWorldContainer && pWorldContainer->GetWorld()) {
			World *pWorld = pWorldContainer->GetWorld();
			const Vector3    &vNodePosition    = m_pParentRagdoll->GetTransform().GetPosition();
			const Quaternion &qNodeRotation    = m_pParentRagdoll->GetTransform().GetRotation();
			const Vector3    &vNodeScale	   = m_pParentRagdoll->GetTransform().GetScale();
			const Vector3	  vRealJointAnchor = qNodeRotation*(vJointAnchor*vNodeScale) + vNodePosition;

			// Get the attached body
			const RagdollBody *pAttachedBody = m_pParentRagdoll->GetBody(sAttached);
			if (pAttachedBody && pAttachedBody->bEnabled) {
				// Get the parent body
				const RagdollBody *pParentBody = m_pParentRagdoll->GetBody(sParent);

				// Attach to world allowed by the parent ragdoll?
				bool bAttachToWorldT = bAttachToWorld;
				if (!m_pParentRagdoll->AttachToWorldEnabled)
					bAttachToWorldT = false;
				if (pParentBody || bAttachToWorldT) {
					// Create the PL physics joint
					switch (nJointType) {
						case Hinge:
						{
							JointHinge *pJoint = static_cast<JointHinge*>(pWorld->CreateJointHinge(bAttachToWorldT ? nullptr : pParentBody->GetBody(), pAttachedBody->GetBody(), vRealJointAnchor, qNodeRotation*vRotAxis1));
							if (pJoint) {
								pJoint->SetLowRange(fLowJointRange1);
								pJoint->SetHighRange(fHighJointRange1);
								m_pJointHandler->SetElement(pJoint);
							}
							break;
						}

						case Universal:
						{
							JointUniversal *pJoint = static_cast<JointUniversal*>(pWorld->CreateJointUniversal(bAttachToWorldT ? nullptr : pParentBody->GetBody(), pAttachedBody->GetBody(), vRealJointAnchor, qNodeRotation*vRotAxis1, qNodeRotation*vRotAxis2));
							if (pJoint) {
								pJoint->SetLowRange1(fLowJointRange1);
								pJoint->SetHighRange1(fHighJointRange1);
								pJoint->SetLowRange2(fLowJointRange2);
								pJoint->SetHighRange2(fHighJointRange2);
								m_pJointHandler->SetElement(pJoint);
							}
							break;
						}
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Destroys the physics joint
*/
void RagdollJoint::DestroyPhysicsJoint()
{
	if (m_pJointHandler->GetElement())
		delete m_pJointHandler->GetElement();
}

/**
*  @brief
*    Returns the current joint anchor position
*/
void RagdollJoint::GetCurrentAnchor(Vector3 &vPosition) const
{
	const Joint *pJoint = static_cast<Joint*>(m_pJointHandler->GetElement());
	if (pJoint)
		pJoint->GetCurrentPivotPoint(vPosition);

	// We need to calculate the current anchor by hand :(
	else {
		// Get the attached body
		const RagdollBody *pAttachedBody = m_pParentRagdoll->GetBody(sAttached);
		if (pAttachedBody && pAttachedBody->bEnabled) {
			// Get the attached physics body
			const Body *pBody = static_cast<Body*>(pAttachedBody->GetBody());
			if (pBody) {
				// Get initial physics body transform matrix
				Matrix3x4 mInitTrans;
				mInitTrans.FromQuatTrans(pAttachedBody->qRot, pAttachedBody->vPos);

				// Get current physics body transform matrix
				Matrix3x4 mTrans;
				pBody->GetTransformMatrix(mTrans);

				// Get the current joint anchor in local space
				const Vector3 vLocalAnchor = mInitTrans.GetInverted()*vJointAnchor;

				// Get the current joint anchor in world space
				vPosition = vLocalAnchor;
				vPosition *= mTrans;
			}
		}
	}
}

/**
*  @brief
*    Computes and applies PD-controller torques to each body part assigned with this joint
*/
void RagdollJoint::ApplyControlTorques(JointController *pController, float fMaxTorque)
{
	// Nothing do to in here
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cap the torque generated by the controller to a reasonable value
*/
void RagdollJoint::ClampTorque(float &fTorque, float fMaxTorque)
{
	if (fTorque >  fMaxTorque)
		fTorque =  fMaxTorque;
	if (fTorque < -fMaxTorque)
		fTorque = -fMaxTorque;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
