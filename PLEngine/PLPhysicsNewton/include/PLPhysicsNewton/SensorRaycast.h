/*********************************************************\
 *  File: SensorRaycast.h                                *
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


#ifndef __PLPHYSICSNEWTON_SENSORRAYCAST_H__
#define __PLPHYSICSNEWTON_SENSORRAYCAST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/SensorRaycast.h>
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
*    Newton physics raycast sensor
*/
class SensorRaycast : public PLPhysics::SensorRaycast {


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
		PLPHYSICSNEWTON_API virtual ~SensorRaycast();


	//[-------------------------------------------------------]
	//[ Public Newton callback functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Newton function to be called for each body hit during the ray scan
		*
		*  @param[in] pPhysicsBody
		*    Newton body (always valid!)
		*  @param[in] pfNormal
		*    Normal (always valid!)
		*  @param[in] nCollisionID
		*    Collision ID
		*  @param[in] pUserData
		*    User data, can be NULL
		*  @param[in] fIntersectParam
		*    Intersection parameter
		*
		*  @return
		*    Intersection parameter: If 0 is retured the ray cast will terminate immediately!
		*/
		PLPHYSICSNEWTON_API static float RayFilterCallback(const Newton::NewtonBody *pPhysicsBody, const float *pfNormal,
														   int nCollisionID, void *pUserData, float fIntersectParam);


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
		*  @param[in] vStart
		*    Beginning of the ray in global space
		*  @param[in] vEnd
		*    End of the ray in global space
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		SensorRaycast(PLPhysics::World &cWorld, const PLMath::Vector3 &vStart = PLMath::Vector3::Zero, const PLMath::Vector3 &vEnd = PLMath::Vector3::Zero, PLGeneral::uint32 nFlags = 0);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::Sensor functions            ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNEWTON_API virtual PLGeneral::uint32 Check();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_SENSORRAYCAST_H__
