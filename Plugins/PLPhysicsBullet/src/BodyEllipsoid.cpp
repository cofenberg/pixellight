/*********************************************************\
 *  File: BodyEllipsoid.cpp                                 *
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
#include "PLPhysicsBullet/BodyEllipsoid.h"
#include "PLPhysicsBullet/BodyImpl.h"
#include "PLPhysicsBullet/World.h"
#include <PLPhysicsBullet/Helper.h>


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
BodyEllipsoid::~BodyEllipsoid()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyEllipsoid::BodyEllipsoid(PLPhysics::World &cWorld, const PLMath::Vector3 &vRadius, bool bStatic) :
	PLPhysics::BodyEllipsoid(cWorld, static_cast<World&>(cWorld).CreateBodyImpl(), vRadius)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Bullet physics world
	btDynamicsWorld *pBulletWorld = ((World&)cWorld).GetBulletWorld();
	if (pBulletWorld) {
		float rad = 2;
		btVector3 vPos;
		
		btMultiSphereShape* collisionShape = new btMultiSphereShape(&vPos, &rad, 1);
		collisionShape->setLocalScaling(Helper::PLVector3TobtVector3(vRadius));
		
		// Initialize the Bullet physics body
		((BodyImpl&)GetBodyImpl()).InitializeBulletBody(*this, *collisionShape, bStatic);
	}

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet
