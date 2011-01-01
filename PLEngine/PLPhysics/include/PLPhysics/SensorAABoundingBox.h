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


#ifndef __PLPHYSICS_SENSORAABOUNDINGBOX_H__
#define __PLPHYSICS_SENSORAABOUNDINGBOX_H__
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
*    Abstract PL physics axis aligned bounding box sensor
*/
class SensorAABoundingBox : public Sensor {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SensorAABoundingBox();

		/**
		*  @brief
		*    Returns the minimum point
		*
		*  @return
		*    The minimum point
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetMin() const;

		/**
		*  @brief
		*    Sets the minimum point
		*
		*  @param[in] vMin
		*    The new minimum point
		*/
		PLPHYSICS_API void SetMin(const PLMath::Vector3 &vMin);

		/**
		*  @brief
		*    Returns the maximum point
		*
		*  @return
		*    The maximum point
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetMax() const;

		/**
		*  @brief
		*    Sets the maximum point
		*
		*  @param[in] vMax
		*    The new maximum point
		*/
		PLPHYSICS_API void SetMax(const PLMath::Vector3 &vMax);


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
		*  @param[in] vMin
		*    Minimum of the axis aligned bounding box in global space
		*  @param[in] vMax
		*    Maximum of the axis aligned bounding box in global space
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		PLPHYSICS_API SensorAABoundingBox(World &cWorld, const PLMath::Vector3 &vMin = PLMath::Vector3::Zero, const PLMath::Vector3 &vMax = PLMath::Vector3::Zero, PLGeneral::uint32 nFlags = 0);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vMin;	/**< The minimum point */
		PLMath::Vector3 m_vMax;	/**< The maximum point */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SENSORAABOUNDINGBOX_H__
