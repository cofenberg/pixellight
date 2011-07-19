/*********************************************************\
 *  File: Sensor.h                                       *
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


#ifndef __PLPHYSICS_SENSOR_H__
#define __PLPHYSICS_SENSOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/Element.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Body;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics sensor base class
*
*  @remarks
*    Can for instance be used for simple collision detection.
*/
class Sensor : public Element {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*   Flags
		*/
		enum EFlags {
			ClosestBody = 1<<0	/**< A performance hint that we are looking for the closest body */
		};


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Holds information about a detected body
		*/
		struct BodyInfo {
			Body			*pBody;			/**< Detected physics body (always valid!) */
			float			 fDistance;		/**< Distance (if supported by the sensor) */
			PLMath::Vector3  vNormal;		/**< Hit normal (if supported by the sensor) */
			int				 nCollisionID;	/**< Collision ID (if supported by the sensor) */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~Sensor();

		/**
		*  @brief
		*    Returns the flags
		*
		*  @return
		*    Flags (see EFlags)
		*/
		PLPHYSICS_API PLCore::uint32 GetFlags() const;

		/**
		*  @brief
		*    Sets the flags
		*
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		PLPHYSICS_API void SetFlags(PLCore::uint32 nFlags = 0);

		/**
		*  @brief
		*    Clears the list of hit bodies
		*/
		PLPHYSICS_API void ClearHitList();

		/**
		*  @brief
		*    Returns the number of hit physics bodies
		*
		*  @return
		*    The number of hit physics bodies
		*/
		PLPHYSICS_API PLCore::uint32 GetNumOfHitBodies() const;

		/**
		*  @brief
		*    Returns a hit physics body by index
		*
		*  @param[in] nIndex
		*    Index of the hit physics body
		*
		*  @return
		*    The hit physics body information, a null pointer on error (do NOT store a pointer on it!)
		*/
		PLPHYSICS_API const BodyInfo *GetHitBody(PLCore::uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the closest hit physics body
		*
		*  @return
		*    The closest hit physics body information, a null pointer on error (do NOT store a pointer on it!)
		*/
		PLPHYSICS_API const BodyInfo *GetClosestBody() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Performs an immediate sensor check
		*
		*  @return
		*    The number of hit physics bodies
		*/
		PLPHYSICS_API virtual PLCore::uint32 Check();


	//[-------------------------------------------------------]
	//[ Public virtual Element functions                      ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual bool IsBody() const;
		PLPHYSICS_API virtual bool IsJoint() const;
		PLPHYSICS_API virtual bool IsSensor() const;


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
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		PLPHYSICS_API Sensor(World &cWorld, PLCore::uint32 nFlags = 0);

		/**
		*  @brief
		*    Returns a free body information
		*
		*  @return
		*    Free body information
		*
		*  @note
		*    - Use FreeBodyInfo() if you no longer need this body information
		*/
		PLPHYSICS_API BodyInfo &GetFreeBodyInfo();

		/**
		*  @brief
		*    Frees a body information
		*
		*  @param[in] cBodyInfo
		*    Body information to free
		*/
		PLPHYSICS_API void FreeBodyInfo(BodyInfo &cBodyInfo);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Sensor callback function
		*
		*  @param[in] cBody
		*    Detected physics body
		*  @param[in] fDistance
		*    Distance
		*  @param[in] vNormal
		*    Hit normal
		*  @param[in] nCollisionID
		*    Collision ID
		*
		*  @return
		*    'true' to continue the sensor check, 'false' if stop it right now
		*
		*  @remarks
		*    The default implementation just adds the found body into a result list.
		*/
		PLPHYSICS_API virtual bool Callback(Body &cBody, float fDistance, const PLMath::Vector3 &vNormal, int nCollisionID);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<BodyInfo*>  m_lstBodyInfo;		/**< List of detected body information */
		BodyInfo				 *m_pClosedBodyInfo;	/**< Closest body information, can be a null pointer */
		PLCore::uint32			  m_nFlags;				/**< Flags (see EFlags) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SENSOR_H__
