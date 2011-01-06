/*********************************************************\
 *  File: JointImpl.cpp                                  *
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
	return (PLPhysics::Joint*)dJointGetData(m_pODEJoint);
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
