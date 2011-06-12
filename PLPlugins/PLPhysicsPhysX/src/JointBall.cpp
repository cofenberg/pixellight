/*********************************************************\
 *  File: JointBall.cpp                                  *
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
#include <PLPhysics/Body.h>
#include "PLPhysicsPhysX/BodyImpl.h"
#include "PLPhysicsPhysX/JointImpl.h"
#include "PLPhysicsPhysX/World.h"
#include "PLPhysicsPhysX/JointBall.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
JointBall::~JointBall()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointBall::JointBall(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
					 const Vector3 &vPivotPoint, const Vector3 &vPinDir) :
	PLPhysics::JointBall(cWorld, ((World&)cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir)
{
	// Get the PhysX physics scene
	NxScene *pPhysXScene = ((World&)cWorld).GetPhysXScene();
	if (pPhysXScene) {
		// Create the PhysX physics joint
		NxSphericalJointDesc sJointDesc;
		sJointDesc.actor[0] = pParentBody ? ((BodyImpl&)pParentBody->GetBodyImpl()).GetPhysXActor() : nullptr;
		sJointDesc.actor[1] = pChildBody  ? ((BodyImpl&)pChildBody ->GetBodyImpl()).GetPhysXActor() : nullptr;
		sJointDesc.setGlobalAnchor(NxVec3(m_vPivotPoint.x, m_vPivotPoint.y, m_vPivotPoint.z));
		sJointDesc.setGlobalAxis(NxVec3(m_vPinDir.x, m_vPinDir.y, m_vPinDir.z));
		NxJoint *pPhysXJoint = pPhysXScene->createJoint(sJointDesc);

		// Initialize the PhysX physics joint
		((JointImpl&)GetJointImpl()).InitializePhysXJoint(*this, *pPhysXJoint);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
