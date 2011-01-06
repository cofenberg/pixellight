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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysicsNull/JointImpl.h"


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
*    Initializes the null physics body
*/
void JointImpl::InitializeNullJoint(PLPhysics::Joint &cJoint)
{
	// Set data
	m_pJoint = &cJoint;
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointImpl functions         ]
//[-------------------------------------------------------]
PLPhysics::Joint *JointImpl::GetJoint() const
{
	return m_pJoint;
}

bool JointImpl::IsBreakable() const
{
	return m_bBreakable;
}

void JointImpl::SetBreakable(bool bBreakable)
{
	m_bBreakable = bBreakable;
}

void JointImpl::GetBreakForce(Vector3 &vForce) const
{
	vForce = m_vBreakForce;
}

void JointImpl::SetBreakForce(const Vector3 &vForce)
{
	m_vBreakForce = vForce;
}

void JointImpl::GetBreakTorque(Vector3 &vTorque) const
{
	vTorque = m_vBreakTorque;
}

void JointImpl::SetBreakTorque(const Vector3 &vTorque)
{
	m_vBreakTorque = vTorque;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointImpl::JointImpl() :
	m_pJoint(nullptr),
	m_bBreakable(false)
{
}

/**
*  @brief
*    Destructor
*/
JointImpl::~JointImpl()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNull
