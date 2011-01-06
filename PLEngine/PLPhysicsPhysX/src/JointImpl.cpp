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
#include "PLPhysicsPhysX/JointImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the PhysX physics joint
*/
NxJoint *JointImpl::GetPhysXJoint() const
{
	return m_pPhysXJoint;
}

/**
*  @brief
*    Initializes the PhysX physics joint
*/
void JointImpl::InitializePhysXJoint(PLPhysics::Joint &cJoint, NxJoint &cPhysXJoint)
{
	// Set data
	m_pPhysXJoint = &cPhysXJoint;

	// Save the pointer to the PL physics joint
	cPhysXJoint.userData = &cJoint;
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointImpl functions         ]
//[-------------------------------------------------------]
PLPhysics::Joint *JointImpl::GetJoint() const
{
	return m_pPhysXJoint ? (PLPhysics::Joint*)m_pPhysXJoint->userData : nullptr;
}

bool JointImpl::IsBreakable() const
{
	return m_bBreakable;
}

void JointImpl::SetBreakable(bool bBreakable)
{
	// Set new value?
	if (m_bBreakable != bBreakable) {
		// Set new value
		m_bBreakable = bBreakable;

		// Setup PhysX joint
		if (m_pPhysXJoint) {
			if (m_bBreakable)
				m_pPhysXJoint->setBreakable(m_vBreakForce.GetGreatestValue(), m_vBreakTorque.GetGreatestValue());
			else
				m_pPhysXJoint->setBreakable(NX_MAX_REAL, NX_MAX_REAL);
		}
	}
}

void JointImpl::GetBreakForce(Vector3 &vForce) const
{
	vForce = m_vBreakForce;
}

void JointImpl::SetBreakForce(const Vector3 &vForce)
{
	m_vBreakForce = vForce;
	if (m_pPhysXJoint)
		m_pPhysXJoint->setBreakable(m_vBreakForce.GetGreatestValue(), m_vBreakTorque.GetGreatestValue());
}

void JointImpl::GetBreakTorque(Vector3 &vTorque) const
{
	vTorque = m_vBreakTorque;
}

void JointImpl::SetBreakTorque(const Vector3 &vTorque)
{
	m_vBreakTorque = vTorque;
	if (m_pPhysXJoint)
		m_pPhysXJoint->setBreakable(m_vBreakForce.GetGreatestValue(), m_vBreakTorque.GetGreatestValue());
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointImpl::JointImpl() :
	m_pPhysXJoint(nullptr),
	m_bBreakable(false)
{
}

/**
*  @brief
*    Destructor
*/
JointImpl::~JointImpl()
{
	// Release the joint
	if (m_pPhysXJoint)
		m_pPhysXJoint->getScene().releaseJoint(*m_pPhysXJoint);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
