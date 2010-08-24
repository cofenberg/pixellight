/*********************************************************\
 *  File: BodyCapsule.cpp                                *
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
#include "PLPhysicsNewton/BodyImpl.h"
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/BodyCapsule.h"


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
BodyCapsule::~BodyCapsule()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyCapsule::BodyCapsule(PLPhysics::World &cWorld, float fRadius, float fHeight) :
	PLPhysics::BodyCapsule(cWorld, ((World&)cWorld).CreateBodyImpl(), fRadius, fHeight)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = ((World&)cWorld).GetNewtonWorld();

	// Create collision primitive
	Newton::NewtonCollision *pCollision = NewtonCreateCapsule(pNewtonWorld, m_fRadius, m_fHeight, 0, NULL);

	// Create the rigid body
	Newton::NewtonBody *pNewtonBody = NewtonCreateBody(pNewtonWorld, pCollision);
	NewtonReleaseCollision(pNewtonWorld, pCollision);

	// Calculate the collision volume
	// [TODO] Find the correct formular...
	const float fCollisionVolume = float(Math::Pi*m_fRadius*m_fRadius*m_fHeight);

	// Initialize the Newton physics body
	((BodyImpl&)GetBodyImpl()).InitializeNewtonBody(*this, *pNewtonBody, fCollisionVolume);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
