/*********************************************************\
 *  File: SensorAABoundingBox.cpp                        *
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
#include "PLPhysicsNewton/SensorAABoundingBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Private static Newton callback variable               ]
//[-------------------------------------------------------]
SensorAABoundingBox *SensorAABoundingBox::m_pCurrentSensor = nullptr;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SensorAABoundingBox::~SensorAABoundingBox()
{
}


//[-------------------------------------------------------]
//[ Public Newton callback functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton function to be called for each body hit during the axis aligned bounding box check
*/
void SensorAABoundingBox::AABoundingBoxIteratorCallback(const Newton::NewtonBody *pPhysicsBody, void *pUserData)
{
	// Get the pointer to the axis aligned bounding box sensor
	if (m_pCurrentSensor) {
		// Get the pointer to the PL physics body
		PLPhysics::Body *pBody = static_cast<PLPhysics::Body*>(NewtonBodyGetUserData(pPhysicsBody));
		if (pBody && pBody->IsActive()) {
			// Call the sensor callback function
			m_pCurrentSensor->Callback(*pBody, 0.0f, Vector3::Zero, 0);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SensorAABoundingBox::SensorAABoundingBox(PLPhysics::World &cWorld, const Vector3 &vMin, const Vector3 &vMax, uint32 nFlags) :
	PLPhysics::SensorAABoundingBox(cWorld, vMin, vMax, nFlags)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::Sensor functions            ]
//[-------------------------------------------------------]
uint32 SensorAABoundingBox::Check()
{
	// Call base implementation
	Sensor::Check();

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = static_cast<World&>(GetWorld()).GetNewtonWorld();

	// Perform Newton physics axis aligned bounding box check
	m_pCurrentSensor = this;
	NewtonWorldForEachBodyInAABBDo(pNewtonWorld, m_vMin, m_vMax, AABoundingBoxIteratorCallback, nullptr);

	// Done
	return GetNumOfHitBodies();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
