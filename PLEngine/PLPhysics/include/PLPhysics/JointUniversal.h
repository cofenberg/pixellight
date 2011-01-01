/*********************************************************\
 *  File: JointUniversal.h                               *
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


#ifndef __PLPHYSICS_JOINTUNIVERSAL_H__
#define __PLPHYSICS_JOINTUNIVERSAL_H__
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
*    Abstract PL physics universal joint
*
*  @remarks
*    A universal joint is a constraint that restricts two rigid bodies to be connected to a point
*    fixed on both bodies, while and allowing one body to spin around a fix axis in is own frame,
*    and the other body to spin around another axis fixes on it own frame. Both axis must be
*    mutually perpendicular.
*
*    DOFs removed: 2 DOFs remaining: 4
*/
class JointUniversal : public Joint {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~JointUniversal();

		/**
		*  @brief
		*    Returns the origin of the universal in world space
		*
		*  @return
		*    The origin of the universal in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPivotPoint() const;

		/**
		*  @brief
		*    Returns the first axis of rotation fixed on THIS body and perpendicular to 'PinDir2' in world space
		*
		*  @return
		*    The first axis of rotation fixed on THIS body and perpendicular to 'PinDir2' in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir1() const;

		/**
		*  @brief
		*    Returns the second axis of rotation fixed on 'Parent' body and perpendicular to 'PinDir1' in world space
		*
		*  @return
		*    The second axis of rotation fixed on 'Parent' body and perpendicular to 'PinDir1' in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir2() const;

		/**
		*  @brief
		*    Returns the low range of the first axis
		*
		*  @return
		*    The low range of the first axis in degree
		*/
		PLPHYSICS_API float GetLowRange1() const;

		/**
		*  @brief
		*    Sets the low range of the first axis
		*
		*  @param[in] fLowRange
		*    New low range of the first axis in degree
		*/
		PLPHYSICS_API void SetLowRange1(float fLowRange = -180.0f);

		/**
		*  @brief
		*    Returns the high range of the first axis
		*
		*  @return
		*    The high range of the first axis in degree
		*/
		PLPHYSICS_API float GetHighRange1() const;

		/**
		*  @brief
		*    Sets the high range of the first axis
		*
		*  @param[in] fHighRange
		*    New high range of the first axis in degree
		*/
		PLPHYSICS_API void SetHighRange1(float fHighRange = 180.0f);

		/**
		*  @brief
		*    Returns the low range of the second axis
		*
		*  @return
		*    The low range of the second axis in degree
		*/
		PLPHYSICS_API float GetLowRange2() const;

		/**
		*  @brief
		*    Sets the low range of the second axis
		*
		*  @param[in] fLowRange
		*    New low range of the second axis in degree
		*/
		PLPHYSICS_API void SetLowRange2(float fLowRange = -180.0f);

		/**
		*  @brief
		*    Returns the high range of the second axis
		*
		*  @return
		*    The high range of the second axis in degree
		*/
		PLPHYSICS_API float GetHighRange2() const;

		/**
		*  @brief
		*    Sets the high range of the second axis
		*
		*  @param[in] fHighRange
		*    New high range of the second axis in degree
		*/
		PLPHYSICS_API void SetHighRange2(float fHighRange = 180.0f);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds omega to the bodies assigned with this joint
		*
		*  @param[in] fOmega1
		*    Omega 1 to add
		*  @param[in] fOmega2
		*    Omega 2 to add
		*/
		virtual void AddOmega(float fOmega1, float fOmega2) = 0;


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
		*    Pointer to the parent rigid body, can be NULL
		*  @param[in] pChildBody
		*    Pointer to the attached rigid body, can be NULL
		*  @param[in] vPivotPoint
		*    Origin of the universal in world space
		*  @param[in] vPinDir1
		*    First axis of rotation fixed on THIS body and perpendicular to 'PinDir2' in world space
		*  @param[in] vPinDir2
		*    Second axis of rotation fixed on 'Parent' body and perpendicular to 'PinDir1' in world space
		*/
		PLPHYSICS_API JointUniversal(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
									 const PLMath::Vector3 &vPinDir1, const PLMath::Vector3 &vPinDir2);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vPivotPoint;	/**< Origin of the universal in world space */
		PLMath::Vector3 m_vPinDir1;		/**< First axis of rotation fixed on THIS body and perpendicular to 'PinDir2' in world space */
		PLMath::Vector3 m_vPinDir2;		/**< Second axis of rotation fixed on 'Parent' body and perpendicular to 'PinDir1' in world space */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fLowRange1;		/**< Low range of the first axis in degree */
		float m_fHighRange1;	/**< High range of the first axis  in degree */
		float m_fLowRange2;		/**< Low range of the second axis in degree */
		float m_fHighRange2;	/**< High range of the second axis  in degree */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_JOINTUNIVERSAL_H__
