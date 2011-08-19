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
#include "PLPhysicsBullet/BodyImpl.h"
#include "PLPhysicsBullet/JointImpl.h"
#include "PLPhysicsBullet/World.h"
#include "PLPhysicsBullet/JointUpVector.h"
#include "PLPhysicsBullet/Helper.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsBullet {


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

	// Get the Bullet physics parent bodiy
	btRigidBody *pBulletParentBody = static_cast<BodyImpl&>(cParentBody.GetBodyImpl()).GetBulletBody();

	pBulletParentBody->setAngularFactor(Helper::PLVector3TobtVector3(vPinDir));

	// Initialize the Newton physics joint
	static_cast<JointImpl&>(GetJointImpl()).InitializeBulletConstraint(*this, nullptr);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet
