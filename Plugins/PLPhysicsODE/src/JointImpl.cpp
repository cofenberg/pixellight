/*********************************************************\
 *  File: JointImpl.cpp                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


// [TODO] Implement breakable joints (we have to change ODE a bit and recompile it...)


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysicsODE/JointImpl.h"


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
*    Returns the ODE physics joint
*/
dJointID JointImpl::GetODEJoint() const
{
	return m_pODEJoint;
}

/**
*  @brief
*    Initializes the ODE physics joint
*/
void JointImpl::InitializeODEJoint(PLPhysics::Joint &cJoint, dJointID pODEJoint)
{
	// Set data
	m_pODEJoint = pODEJoint;

	// Save the pointer to the PL physics joint
	dJointSetData(m_pODEJoint, &cJoint);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointImpl functions         ]
//[-------------------------------------------------------]
PLPhysics::Joint *JointImpl::GetJoint() const
{
	return static_cast<PLPhysics::Joint*>(dJointGetData(m_pODEJoint));
}

bool JointImpl::IsBreakable() const
{
	// [TODO] Implement me
	// return dJointIsBreakable(m_pODEJoint);
	return false;
}

void JointImpl::SetBreakable(bool bBreakable)
{
	// [TODO] Implement me
	// dJointSetBreakable(m_pODEJoint, bBreakable);
}

void JointImpl::GetBreakForce(Vector3 &vForce) const
{
	// [TODO] Implement me
//	dJointGetBreakForce(m_pODEJoint, 0, vForce);
}

void JointImpl::SetBreakForce(const Vector3 &vForce)
{
	// [TODO] Implement me
//	dJointSetBreakForce(m_pODEJoint, 0, vForce.x, vForce.y, vForce.z);
//	dJointSetBreakForce(m_pODEJoint, 1, vForce.x, vForce.y, vForce.z);
}

void JointImpl::GetBreakTorque(Vector3 &vTorque) const
{
	// [TODO] Implement me
//	dJointGetBreakTorque(m_pODEJoint, 0, vTorque);
}

void JointImpl::SetBreakTorque(const Vector3 &vTorque)
{
	// [TODO] Implement me
//	dJointSetBreakTorque(dJointID, 0, vTorque.x, vTorque.y, vTorque.z);
//	dJointSetBreakTorque(dJointID, 1, vTorque.x, vTorque.y, vTorque.z);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointImpl::JointImpl() :
	m_pODEJoint(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
JointImpl::~JointImpl()
{
	// Destroy the ODE physics joint
	dJointDestroy(m_pODEJoint);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
