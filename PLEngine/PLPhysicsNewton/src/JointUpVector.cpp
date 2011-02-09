/*********************************************************\
 *  File: JointUpVector.cpp                              *
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
#include "PLPhysicsNewton/BodyImpl.h"
#include "PLPhysicsNewton/JointImpl.h"
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/JointUpVector.h"


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
JointUpVector::~JointUpVector()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointUpVector::JointUpVector(PLPhysics::World &cWorld, PLPhysics::Body &cParentBody, const Vector3 &vPinDir) :
	PLPhysics::JointUpVector(cWorld, static_cast<World&>(cWorld).CreateJointImpl(), cParentBody, vPinDir)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = static_cast<World&>(cWorld).GetNewtonWorld();

	// Flush assigned body (MUST be done before creating the joint!)
	static_cast<BodyImpl&>(cParentBody.GetBodyImpl()).Flush();

	// Get the Newton physics parent bodiy
	const Newton::NewtonBody *pNewtonParentBody = static_cast<BodyImpl&>(cParentBody.GetBodyImpl()).GetNewtonBody();

	// Create the Newton physics joint
	Newton::NewtonJoint *pNewtonJoint = NewtonConstraintCreateUpVector(pNewtonWorld, m_vPinDir, pNewtonParentBody);

	// Initialize the Newton physics joint
	static_cast<JointImpl&>(GetJointImpl()).InitializeNewtonJoint(*this, *pNewtonJoint);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
