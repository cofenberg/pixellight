/*********************************************************\
 *  File: JointImpl.cpp                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
