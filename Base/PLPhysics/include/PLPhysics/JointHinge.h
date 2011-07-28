/*********************************************************\
 *  File: JointHinge.h                                   *
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


#ifndef __PLPHYSICS_JOINTHINGE_H__
#define __PLPHYSICS_JOINTHINGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/Joint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics hinge (other name: revolute) joint
*
*  @remarks
*    DOFs removed: 5 DOFs remaining: 1
*/
class JointHinge : public Joint {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~JointHinge();

		/**
		*  @brief
		*    Returns the origin of the hinge in world space
		*
		*  @return
		*    The origin of the hinge in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPivotPoint() const;

		/**
		*  @brief
		*    Returns the line of action of the hinge in world space
		*
		*  @return
		*    The line of action of the hinge in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir() const;

		/**
		*  @brief
		*    Returns the low range
		*
		*  @return
		*    The low range in degree
		*/
		PLPHYSICS_API float GetLowRange() const;

		/**
		*  @brief
		*    Sets the low range
		*
		*  @param[in] fLowRange
		*    New low range in degree
		*/
		PLPHYSICS_API void SetLowRange(float fLowRange = -180.0f);

		/**
		*  @brief
		*    Returns the high range
		*
		*  @return
		*    The high range in degree
		*/
		PLPHYSICS_API float GetHighRange() const;

		/**
		*  @brief
		*    Sets the high range
		*
		*  @param[in] fHighRange
		*    New high range in degree
		*/
		PLPHYSICS_API void SetHighRange(float fHighRange = 180.0f);


	//[-------------------------------------------------------]
	//[ Public virtual JointHinge functions                   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds omega to the bodies assigned with this joint
		*
		*  @param[in] fOmega
		*    Omega to add
		*/
		virtual void AddOmega(float fOmega) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this joint is in
		*  @param[in] cJointImpl
		*    Reference to the physics API specific joint implementation
		*  @param[in] pParentBody
		*    Pointer to the parent rigid body, can be a null pointer
		*  @param[in] pChildBody
		*    Pointer to the attached rigid body, can be a null pointer
		*  @param[in] vPivotPoint
		*    Origin of the hinge in world space
		*  @param[in] vPinDir
		*    The line of action of the hinge in world space
		*/
		PLPHYSICS_API JointHinge(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody,
								 const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vPivotPoint;	/**< Origin of the hinge in world space */
		PLMath::Vector3 m_vPinDir;		/**< The line of action of the hinge in world space */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fLowRange;	/**< Low range in degree */
		float m_fHighRange;	/**< High range in degree */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_JOINTHINGE_H__
