/*********************************************************\
 *  File: JointImpl.cpp                                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLPhysics/Joint.h>
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/JointImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the Newton physics joint
*/
Newton::NewtonJoint *JointImpl::GetNewtonJoint() const
{
	return m_pNewtonJoint;
}

/**
*  @brief
*    Initializes the Newton physics joint
*/
void JointImpl::InitializeNewtonJoint(PLPhysics::Joint &cJoint, Newton::NewtonJoint &cNewtonJoint)
{
	// Set data
	m_pNewtonJoint = &cNewtonJoint;

	// Save the pointer to the PL physics joint
	NewtonJointSetUserData(m_pNewtonJoint, &cJoint);

	// Set a destrutor for this joint
	NewtonJointSetDestructor(m_pNewtonJoint, World::PhysicsJointDestructor);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::JointImpl functions         ]
//[-------------------------------------------------------]
PLPhysics::Joint *JointImpl::GetJoint() const
{
	return (PLPhysics::Joint*)NewtonJointGetUserData(m_pNewtonJoint);
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
	m_pNewtonJoint(NULL),
	m_bBreakable(false)
{
}

/**
*  @brief
*    Destructor
*/
JointImpl::~JointImpl()
{
	// Is there a Newton physics joint?
	if (m_pNewtonJoint) {
		// Get the physics world
		PLPhysics::Joint *pJoint = GetJoint();
		if (pJoint) {
			PLPhysics::World &cWorld = pJoint->GetWorld();

			// Deactivate the physics simulation if required
			const bool bSimulationActive = cWorld.IsSimulationActive();
			if (bSimulationActive)
				cWorld.SetSimulationActive(false);

			// Reset the pointer to the PL physics joint
			NewtonJointSetUserData(m_pNewtonJoint, NULL);

			// Destroy the Newton physics joint, there's no function like NewtonJointGetWorld(m_pNewtonJoint) :(
			NewtonDestroyJoint(((World&)cWorld).GetNewtonWorld(), m_pNewtonJoint);

			// Reactivate the physics simulation if required
			if (bSimulationActive)
				cWorld.SetSimulationActive(bSimulationActive);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
