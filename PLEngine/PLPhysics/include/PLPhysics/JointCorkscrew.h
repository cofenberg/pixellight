/*********************************************************\
 *  File: JointCorkscrew.h                               *
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


#ifndef __PLPHYSICS_JOINTCORKSCREW_H__
#define __PLPHYSICS_JOINTCORKSCREW_H__
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
*    Abstract PL physics corkscrew joint
*/
class JointCorkscrew : public Joint {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~JointCorkscrew();

		/**
		*  @brief
		*    Returns the origin of the corkscrew in world space
		*
		*  @return
		*    The origin of the corkscrew in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPivotPoint() const;

		/**
		*  @brief
		*    Returns the line of action of the corkscrew in world space
		*
		*  @return
		*    The line of action of the corkscrew in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir() const;


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
		*    Origin of the corkscrew in world space
		*  @param[in] vPinDir
		*    The line of action of the corkscrew in world space
		*/
		PLPHYSICS_API JointCorkscrew(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody,
									 const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vPivotPoint;	/**< Origin of the corkscrew in world space */
		PLMath::Vector3 m_vPinDir;		/**< The line of action of the corkscrew in world space */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_JOINTCORKSCREW_H__
