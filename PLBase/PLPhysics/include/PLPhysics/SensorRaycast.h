/*********************************************************\
 *  File: SensorRaycast.h                                *
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


#ifndef __PLPHYSICS_SENSORRAYCAST_H__
#define __PLPHYSICS_SENSORRAYCAST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/Sensor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics raycast sensor
*/
class SensorRaycast : public Sensor {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SensorRaycast();

		/**
		*  @brief
		*    Returns the start point
		*
		*  @return
		*    The start point
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetStart() const;

		/**
		*  @brief
		*    Sets the start point
		*
		*  @param[in] vPoint
		*    The new start point
		*/
		PLPHYSICS_API void SetStart(const PLMath::Vector3 &vPoint);

		/**
		*  @brief
		*    Returns the end point
		*
		*  @return
		*    The end point
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetEnd() const;

		/**
		*  @brief
		*    Sets the end point
		*
		*  @param[in] vPoint
		*    The new end point
		*/
		PLPHYSICS_API void SetEnd(const PLMath::Vector3 &vPoint);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
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
		PLPHYSICS_API SensorRaycast(World &cWorld, const PLMath::Vector3 &vStart = PLMath::Vector3::Zero, const PLMath::Vector3 &vEnd = PLMath::Vector3::Zero, PLGeneral::uint32 nFlags = 0);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vStart;	/**< The start point */
		PLMath::Vector3 m_vEnd;		/**< The end point */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SENSORRAYCAST_H__
