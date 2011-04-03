/*********************************************************\
 *  File: SNMPhysicsJointUniversal.cpp                   *
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
#include "PLPhysics/Joint.h"
#include "PLPhysics/World.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsJointUniversal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsJointUniversal)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNMPhysicsJointUniversal::GetPivotPoint() const
{
	return m_vPivotPoint;
}

void SNMPhysicsJointUniversal::SetPivotPoint(const Vector3 &vValue)
{
	if (m_vPivotPoint != vValue) {
		m_vPivotPoint = vValue;
		RecreatePhysicsJoint();
	}
}

const Vector3 &SNMPhysicsJointUniversal::GetPinDir1() const
{
	return m_vPinDir1;
}

void SNMPhysicsJointUniversal::SetPinDir1(const Vector3 &vValue)
{
	if (m_vPinDir1 != vValue) {
		m_vPinDir1 = vValue;
		RecreatePhysicsJoint();
	}
}

const Vector3 &SNMPhysicsJointUniversal::GetPinDir2() const
{
	return m_vPinDir2;
}

void SNMPhysicsJointUniversal::SetPinDir2(const Vector3 &vValue)
{
	if (m_vPinDir2 != vValue) {
		m_vPinDir2 = vValue;
		RecreatePhysicsJoint();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsJointUniversal::SNMPhysicsJointUniversal(SceneNode &cSceneNode) : SNMPhysicsJoint(cSceneNode),
	PivotPoint(this),
	PinDir1(this),
	PinDir2(this),
	m_vPinDir1(0.0f, 1.0f, 0.0f),
	m_vPinDir2(0.0f, 0.0f, 1.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsJointUniversal::~SNMPhysicsJointUniversal()
{
}


//[-------------------------------------------------------]
//[ Private virtual SNMPhysicsJoint functions             ]
//[-------------------------------------------------------]
void SNMPhysicsJointUniversal::CreatePhysicsJoint()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Get the owner and target physics bodies the joint is attached to
		const SNMPhysicsBody *pOwnerBody  = GetOwnerBodyModifier();
		const SNMPhysicsBody *pTargetBody = GetTargetBodyModifier();

		// Get the pin directions
		const Matrix3x4 &mTrans = GetSceneNode().GetTransform().GetMatrix();
		const Vector3 vPinDir1 = ((GetFlags() & LocalPinDirection) ? mTrans.RotateVector(m_vPinDir1) : m_vPinDir1).Normalize();
		const Vector3 vPinDir2 = ((GetFlags() & LocalPinDirection) ? mTrans.RotateVector(m_vPinDir2) : m_vPinDir2).Normalize();

		// Create the joint
		m_pJointHandler->SetElement(m_pWorldContainer->GetWorld()->CreateJointUniversal(pTargetBody ? pTargetBody->GetBody() : nullptr,
																						pOwnerBody  ? pOwnerBody->GetBody()  : nullptr,
																						mTrans*m_vPivotPoint,
																						vPinDir1,
																						vPinDir2));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
