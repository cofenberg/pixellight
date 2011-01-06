/*********************************************************\
 *  File: JointBall.h                                    *
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


#ifndef __PLPHYSICSNEWTON_JOINTBALL_H__
#define __PLPHYSICSNEWTON_JOINTBALL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/JointBall.h>
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
*    Newton physics ball and socket joint implementation
*/
class JointBall : public PLPhysics::JointBall {


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
		PLPHYSICSNEWTON_API virtual ~JointBall();


	//[-------------------------------------------------------]
	//[ Public Newton callback functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Static Newton joint user callback function
		*
		*  @param[in] pNewtonJoint
		*    Newton joint(always valid!)
		*  @param[in] fTimeStep
		*    Time step
		*/
		PLPHYSICSNEWTON_API static void JointUserCallback(const Newton::NewtonJoint *pNewtonJoint, dFloat fTimeStep);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this joint is in
		*  @param[in] pParentBody
		*    Pointer to the parent rigid body, can be a null pointer
		*  @param[in] pChildBody
		*    Pointer to the attached rigid body, can be a null pointer
		*  @param[in] vPivotPoint
		*    Origin of the ball and socket in world space
		*  @param[in] vPinDir
		*    Vector defining the cone axis in world space
		*/
		JointBall(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
				  const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_JOINTBALL_H__
