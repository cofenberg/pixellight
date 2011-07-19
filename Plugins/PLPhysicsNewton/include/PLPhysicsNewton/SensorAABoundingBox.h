/*********************************************************\
 *  File: SensorAABoundingBox.h                          *
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


#ifndef __PLPHYSICSNEWTON_SENSORAABOUNDINGBOX_H__
#define __PLPHYSICSNEWTON_SENSORAABOUNDINGBOX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/SensorAABoundingBox.h>
#include "PLPhysicsNewton/PLPhysicsNewton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton physics axis aligned bounding box sensor
*/
class SensorAABoundingBox : public PLPhysics::SensorAABoundingBox {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSNEWTON_API virtual ~SensorAABoundingBox();


	//[-------------------------------------------------------]
	//[ Public Newton callback functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Newton function to be called for each body hit during the axis aligned bounding box check
		*
		*  @param[in] pPhysicsBody
		*    Newton body (always valid!)
		*  @param[in] pUserData
		*    User data, can be a null pointer
		*/
		PLPHYSICSNEWTON_API static void AABoundingBoxIteratorCallback(const Newton::NewtonBody *pPhysicsBody, void *pUserData);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this sensor is in
		*  @param[in] vMin
		*    Minimum of the axis aligned bounding box in global space
		*  @param[in] vMax
		*    Maximum of the axis aligned bounding box in global space
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		SensorAABoundingBox(PLPhysics::World &cWorld, const PLMath::Vector3 &vMin = PLMath::Vector3::Zero, const PLMath::Vector3 &vMax = PLMath::Vector3::Zero, PLCore::uint32 nFlags = 0);


	//[-------------------------------------------------------]
	//[ Private static Newton callback variable               ]
	//[-------------------------------------------------------]
	private:
		static SensorAABoundingBox *m_pCurrentSensor;	/**< Totally ugly, but we have no change to pass the sensor instance by parameter to the Newton iterator callback function */


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::Sensor functions            ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNEWTON_API virtual PLCore::uint32 Check();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_SENSORAABOUNDINGBOX_H__
