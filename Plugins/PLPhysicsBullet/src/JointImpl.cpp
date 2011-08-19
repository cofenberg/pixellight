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
#include <PLPhysics/Joint.h>
#include "PLPhysicsBullet/World.h"
#include "PLPhysicsBullet/JointImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsBullet {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the Newton physics joint
*/
btTypedConstraint *JointImpl::GetBulletConstraint() const
{
	return m_pBulletConstraint;
}

/**
*  @brief
*    Initializes the Bullet physics constraint
*/
void JointImpl::InitializeBulletConstraint(PLPhysics::Joint &cJoint, btTypedConstraint *pBulletConstraint)
{
	// Set data
	m_pBulletConstraint = pBulletConstraint;
	m_pJoint = &cJoint;
	if (m_pBulletConstraint)
	{
		btDynamicsWorld *pBulletWorld = static_cast<World&>(cJoint.GetWorld()).GetBulletWorld();
		if (pBulletWorld) {
			pBulletWorld->addConstraint(m_pBulletConstraint);
		}
		// Save the pointer to the PL physics joint
		m_pBulletConstraint->setUserConstraintPtr(&cJoint);
	}

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
	m_pBulletConstraint(nullptr),
	m_bBreakable(false),
	m_pJoint(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
JointImpl::~JointImpl()
{
	// Is there a Newton physics joint?
	if (m_pBulletConstraint) {
		// Get the physics world
		PLPhysics::Joint *pJoint = GetJoint();
		if (pJoint) {
			PLPhysics::World &cWorld = pJoint->GetWorld();

			// Deactivate the physics simulation if required
			const bool bSimulationActive = cWorld.IsSimulationActive();
			if (bSimulationActive)
				cWorld.SetSimulationActive(false);

			btDynamicsWorld *pBulletWorld = static_cast<World&>(cWorld).GetBulletWorld();
			if (pBulletWorld) {
				pBulletWorld->removeConstraint(m_pBulletConstraint);
			}

			delete m_pBulletConstraint;

			// Reactivate the physics simulation if required
			if (bSimulationActive)
				cWorld.SetSimulationActive(bSimulationActive);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet
