/*********************************************************\
 *  File: BodyMotionState.cpp                            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLPhysicsBullet/BodyMotionState.h"
#include "PLPhysicsBullet/Helper.h"
#include <PLPhysics/Body.h>
#include <PLMath/Vector3.h>
#include <PLMath/Quaternion.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLPhysicsBullet {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
BodyMotionState::BodyMotionState(PLPhysics::Body *pBody)
	: m_pBody(pBody)
{
}

void BodyMotionState::setWorldTransform(const btTransform& worldTrans)
{
	if (!m_pBody)
		return;
	m_pBody->SetPosition(Helper::btVector3ToPLVector3(worldTrans.getOrigin()));
	m_pBody->SetRotation(Helper::btQuaternionToPLQuaternion(worldTrans.getRotation()));
	m_pBody->EventTransform();
}

void BodyMotionState::getWorldTransform(btTransform& worldTrans) const
{
	PLMath::Vector3 vPos;
	m_pBody->GetPosition(vPos);
	btVector3 btPos(Helper::PLVector3TobtVector3(vPos));
	worldTrans.setOrigin(btPos);
	
	PLMath::Quaternion qRot;
	m_pBody->GetRotation(qRot);
	btQuaternion btRot(Helper::PLQuaternionTobtQuaternion(qRot));
	worldTrans.setRotation(btRot);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
