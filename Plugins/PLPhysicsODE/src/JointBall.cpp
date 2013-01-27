/*********************************************************\
 *  File: JointBall.cpp                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/Body.h>
#include "PLPhysicsODE/World.h"
#include "PLPhysicsODE/BodyImpl.h"
#include "PLPhysicsODE/JointImpl.h"
#include "PLPhysicsODE/JointBall.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsODE {


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
	PLPhysics::JointBall(cWorld, static_cast<World&>(cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir)
{
	// Get the ODE physics world
	dWorldID pODEWorld = static_cast<World&>(cWorld).GetODEWorld();

	// Get the ODE physics parent and child bodies
	const dBodyID pODEParentBody = pParentBody ? static_cast<BodyImpl&>(pParentBody->GetBodyImpl()).GetODEBody() : nullptr;
	const dBodyID pODEChildBody  = pChildBody  ? static_cast<BodyImpl&>(pChildBody ->GetBodyImpl()).GetODEBody() : nullptr;

	// Create the ODE physics joint
	dJointID pODEJoint = dJointCreateBall(pODEWorld, 0);
	dJointSetBallAnchor(pODEJoint, m_vPivotPoint.x, m_vPivotPoint.y, m_vPivotPoint.z);
	// m_vPinDir is not used
	dJointAttach(pODEJoint, pODEParentBody, pODEChildBody);

	// Initialize the ODE physics joint
	static_cast<JointImpl&>(GetJointImpl()).InitializeODEJoint(*this, pODEJoint);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
