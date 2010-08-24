/*********************************************************\
 *  File: Joint.cpp                                      *
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
#include <PLMath/Vector3.h>
#include "PLPhysics/ElementHandler.h"
#include "PLPhysics/JointImpl.h"
#include "PLPhysics/Joint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Joint::~Joint()
{
	// Destroy the physics body handlers
	delete m_pParentBodyHandler;
	delete m_pChildBodyHandler;

	// Destroy the physics API joint implementation
	delete m_pJointImpl;
}

/**
*  @brief
*    Returns a reference to the physics API specific joint implementation
*/
JointImpl &Joint::GetJointImpl() const
{
	return *m_pJointImpl;
}

/**
*  @brief
*    Returns a pointer to the parent rigid body
*/
Body *Joint::GetParentBody() const
{
	return (Body*)m_pParentBodyHandler->GetElement();
}

/**
*  @brief
*    Returns a pointer to the attached rigid body
*/
Body *Joint::GetChildBody() const
{
	return (Body*)m_pChildBodyHandler->GetElement();
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the current pivot point of the joint
*/
void Joint::GetCurrentPivotPoint(Vector3 &vPosition) const
{
	// Nothing do to in here
}

/**
*  @brief
*    Returns whether the joint is breakable or not
*/
bool Joint::IsBreakable() const
{
	return m_pJointImpl->IsBreakable();
}

/**
*  @brief
*    Sets whether the joint is breakable or not
*/
void Joint::SetBreakable(bool bBreakable)
{
	m_pJointImpl->SetBreakable(bBreakable);
}

/**
*  @brief
*    Returns the break force
*/
void Joint::GetBreakForce(Vector3 &vForce) const
{
	m_pJointImpl->GetBreakForce(vForce);
}

/**
*  @brief
*    Sets the break force
*/
void Joint::SetBreakForce(const Vector3 &vForce)
{
	m_pJointImpl->SetBreakForce(vForce);
}

/**
*  @brief
*    Returns the break torque
*/
void Joint::GetBreakTorque(Vector3 &vTorque) const
{
	m_pJointImpl->GetBreakTorque(vTorque);
}

/**
*  @brief
*    Sets the break torque
*/
void Joint::SetBreakTorque(const Vector3 &vTorque)
{
	m_pJointImpl->SetBreakTorque(vTorque);
}


//[-------------------------------------------------------]
//[ Public virtual Element functions                      ]
//[-------------------------------------------------------]
bool Joint::IsBody() const
{
	return false;
}

bool Joint::IsJoint() const
{
	return true;
}

bool Joint::IsSensor() const
{
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Joint::Joint(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody) : Element(cWorld),
	m_pJointImpl(&cJointImpl),
	m_pParentBodyHandler(new ElementHandler()),
	m_pChildBodyHandler(new ElementHandler())
{
	// Set the physics bodies this joint is attached to
	m_pParentBodyHandler->SetElement((Element*)pParentBody);
	m_pChildBodyHandler ->SetElement((Element*)pChildBody);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
