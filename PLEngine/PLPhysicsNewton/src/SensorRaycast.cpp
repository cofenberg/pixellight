/*********************************************************\
 *  File: SensorRaycast.cpp                              *
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
#include <PLPhysics/BodyBox.h>
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/SensorRaycast.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SensorRaycast::~SensorRaycast()
{
}


//[-------------------------------------------------------]
//[ Public Newton callback functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton function to be called for each body hit during the ray scan
*/
float SensorRaycast::RayFilterCallback(const Newton::NewtonBody *pPhysicsBody, const float *pfNormal,
									   int nCollisionID, void *pUserData, float fIntersectParam)
{
	// Get the pointer to the raycast sensor
	SensorRaycast *pSensor = (SensorRaycast*)pUserData;
	if (pSensor) {
		// Get the pointer to the PL physics body
		PLPhysics::Body *pBody = (PLPhysics::Body*)NewtonBodyGetUserData(pPhysicsBody);
		if (pBody && pBody->IsActive()) {
			// Call the sensor callback function
			if (pSensor->Callback(*pBody, fIntersectParam, pfNormal, nCollisionID)) {
				// Return 'fIntersectParam' if 'ClosestBody' performance hint flag is set
				return (pSensor->GetFlags() & ClosestBody) ? fIntersectParam : 1.0f; // Continue
			} else {
				// Stop right now!
				return 0.0f;
			}
		}
	}

	// Continue
	return 1.0f;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SensorRaycast::SensorRaycast(PLPhysics::World &cWorld, const Vector3 &vStart, const Vector3 &vEnd, uint32 nFlags) :
	PLPhysics::SensorRaycast(cWorld, vStart, vEnd, nFlags)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::Sensor functions            ]
//[-------------------------------------------------------]
uint32 SensorRaycast::Check()
{
	// Call base implementation
	Sensor::Check();

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = ((World&)GetWorld()).GetNewtonWorld();

	// Perform Newton physics ray cast
	NewtonWorldRayCast(pNewtonWorld, m_vStart, m_vEnd, RayFilterCallback, this, NULL);

	// Done
	return GetNumOfHitBodies();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
