/*********************************************************\
 *  File: JointBall.cpp                                  *
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
#include "PLPhysicsNull/World.h"
#include "PLPhysicsNull/JointImpl.h"
#include "PLPhysicsNull/JointBall.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsNull {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
JointBall::~JointBall()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointBall::JointBall(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
					 const Vector3 &vPivotPoint, const Vector3 &vPinDir) :
	PLPhysics::JointBall(cWorld, ((World&)cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir)
{
	// Initialize the null physics joint
	((JointImpl&)GetJointImpl()).InitializeNullJoint(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNull
