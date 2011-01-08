/*********************************************************\
 *  File: JointUniversal.cpp                             *
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
#include "PLPhysicsODE/World.h"
#include "PLPhysicsODE/BodyImpl.h"
#include "PLPhysicsODE/JointImpl.h"
#include "PLPhysicsODE/JointUniversal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsODE {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
JointUniversal::~JointUniversal()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointUniversal::JointUniversal(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
							   const Vector3 &vPivotPoint, const Vector3 &vPinDir1, const Vector3 &vPinDir2) :
	PLPhysics::JointUniversal(cWorld, ((World&)cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir1, vPinDir2)
{
	// Get the ODE physics world
	dWorldID pODEWorld = ((World&)cWorld).GetODEWorld();

	// Get the ODE physics parent and child bodies
	const dBodyID pODEParentBody = pParentBody ? ((BodyImpl&)pParentBody->GetBodyImpl()).GetODEBody() : nullptr;
	const dBodyID pODEChildBody  = pChildBody  ? ((BodyImpl&)pChildBody ->GetBodyImpl()).GetODEBody() : nullptr;

	// Create the ODE physics joint
	dJointID pODEJoint = dJointCreateUniversal(pODEWorld, 0);
	dJointSetUniversalAnchor(pODEJoint, m_vPivotPoint.x, m_vPivotPoint.y, m_vPivotPoint.z);
	dJointSetUniversalAxis1(pODEJoint, m_vPinDir1.x, m_vPinDir1.y, m_vPinDir1.z);
	dJointSetUniversalAxis2(pODEJoint, m_vPinDir2.x, m_vPinDir2.y, m_vPinDir2.z);
	dJointAttach(pODEJoint, pODEParentBody, pODEChildBody);

	// Initialize the ODE physics joint
	((JointImpl&)GetJointImpl()).InitializeODEJoint(*this, pODEJoint);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointUniversal functions    ]
//[-------------------------------------------------------]
void JointUniversal::AddOmega(float fOmega1, float fOmega2)
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
