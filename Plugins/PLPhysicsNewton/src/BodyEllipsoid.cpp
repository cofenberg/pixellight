/*********************************************************\
 *  File: BodyEllipsoid.cpp                              *
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
#include <PLMath/Matrix4x4.h>
#include "PLPhysicsNewton/BodyImpl.h"
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/BodyEllipsoid.h"


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
BodyEllipsoid::BodyEllipsoid(PLPhysics::World &cWorld, const Vector3 &vRadius) :
	PLPhysics::BodyEllipsoid(cWorld, static_cast<World&>(cWorld).CreateBodyImpl(), vRadius)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = static_cast<World&>(cWorld).GetNewtonWorld();

	// Create collision primitive
	Newton::NewtonCollision *pCollision = NewtonCreateSphere(pNewtonWorld, m_vRadius.x, m_vRadius.y, m_vRadius.z, 0, nullptr);

	// Create the rigid body
	// [TODO] Remove this as soon as there's an up-to-date Linux version of Newton Game Dynamics available!
	#if (NEWTON_MAJOR_VERSION == 2) && (NEWTON_MINOR_VERSION >= 28)
		Newton::NewtonBody *pNewtonBody = NewtonCreateBody(pNewtonWorld, pCollision, Matrix4x4::Identity);
	#else
		Newton::NewtonBody *pNewtonBody = NewtonCreateBody(pNewtonWorld, pCollision);
	#endif
	NewtonReleaseCollision(pNewtonWorld, pCollision);

	// Calculate the collision volume
	const float fCollisionVolume = static_cast<float>((4/3)*Math::Pi*m_vRadius.x*m_vRadius.y*m_vRadius.z);

	// Initialize the Newton physics body
	static_cast<BodyImpl&>(GetBodyImpl()).InitializeNewtonBody(*this, *pNewtonBody, fCollisionVolume);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
