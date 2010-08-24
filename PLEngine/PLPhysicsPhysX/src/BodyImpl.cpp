/*********************************************************\
 *  File: BodyImpl.cpp                                   *
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
#include <PLMath/Matrix3x4.h>
#include <PLMath/Quaternion.h>
#include <PLMath/AABoundingBox.h>
#include <PLPhysics/Body.h>
#include "PLPhysicsPhysX/World.h"
#include "PLPhysicsPhysX/BodyImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the PhysX physics actor
*/
NxActor *BodyImpl::GetPhysXActor() const
{
	return m_pPhysXActor;
}

/**
*  @brief
*    Initializes the PhysX physics actor
*
*/
void BodyImpl::InitializePhysXActor(PLPhysics::Body &cBody, NxActor &cPhysXActor)
{
	// Set data
	m_pPhysXActor = &cPhysXActor;

	// Save the pointer to the PL physics body
	m_pPhysXActor->userData = &cBody;
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::BodyImpl functions          ]
//[-------------------------------------------------------]
PLPhysics::Body *BodyImpl::GetBody() const
{
	return m_pPhysXActor ? (PLPhysics::Body*)m_pPhysXActor->userData : NULL;
}

bool BodyImpl::IsActive() const
{
	return m_bActive;
}

void BodyImpl::SetActive(bool bActive)
{
	// State change?
	if (m_bActive != bActive) {
		m_bActive = bActive;
		SetFrozen(!bActive);
		if (m_pPhysXActor) {
			if (m_bCollisionActive && m_bActive)
				m_pPhysXActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
			else
				m_pPhysXActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		}
	}
}

float BodyImpl::GetCollisionVolume() const
{
	return m_fCollisionVolume;
}

float BodyImpl::GetMass() const
{
	return m_pPhysXActor ? m_pPhysXActor->getMass() : 0.0f;
}

void BodyImpl::SetMass(float fMass)
{
	if (m_pPhysXActor)
		m_pPhysXActor->setMass(fMass);
}

void BodyImpl::GetCenterOfMass(Vector3 &vPosition) const
{
	if (m_pPhysXActor) {
		const NxVec3 vPos = m_pPhysXActor->getCMassLocalPosition();
		vPosition.x = vPos.x;
		vPosition.y = vPos.y;
		vPosition.z = vPos.z;
	} else {
		vPosition = Vector3::Zero;
	}
}

void BodyImpl::SetCenterOfMass(const Vector3 &vPosition)
{
	if (m_pPhysXActor) {
		NxVec3 vPos;
		vPos.x = vPosition.x;
		vPos.y = vPosition.y;
		vPos.z = vPosition.z;
		m_pPhysXActor->setCMassOffsetLocalPosition(vPos);
	}
}

void BodyImpl::GetPosition(Vector3 &vPosition) const
{
	if (m_pPhysXActor) {
		const NxVec3 vPos = m_pPhysXActor->getGlobalPosition();
		vPosition.x = vPos.x;
		vPosition.y = vPos.y;
		vPosition.z = vPos.z;
	} else {
		vPosition = Vector3::Zero;
	}
}

void BodyImpl::SetPosition(const Vector3 &vPosition)
{
	if (m_pPhysXActor) {
		NxVec3 vPos;
		vPos.x = vPosition.x;
		vPos.y = vPosition.y;
		vPos.z = vPosition.z;
		m_pPhysXActor->setGlobalPosition(vPos);
	}
}

void BodyImpl::GetRotation(Quaternion &qRotation) const
{
	if (m_pPhysXActor) {
		const NxQuat q = m_pPhysXActor->getGlobalOrientationQuat();
		qRotation.SetWXYZ(q.w, q.x, q.y, q.z);
	} else {
		qRotation = Quaternion::Identity;
	}
}

void BodyImpl::SetRotation(const Quaternion &qRotation)
{
	if (m_pPhysXActor) {
		NxQuat q;
		q.setWXYZ(qRotation);
		m_pPhysXActor->setGlobalOrientationQuat(q);
	}
}

void BodyImpl::GetTransformMatrix(Matrix3x4 &mTrans) const
{
	if (m_pPhysXActor) {
		// Get PhysX transform matrix
		const NxMat34 mNx = m_pPhysXActor->getGlobalPose();
		const NxMat33 &mNxRot = mNx.M;

		// Set to PL transform matrix
		mTrans.xx = mNxRot(0, 0); mTrans.xy = mNxRot(0, 1); mTrans.xz = mNxRot(0, 2); mTrans.xw = mNx.t.x;
		mTrans.yx = mNxRot(1, 0); mTrans.yy = mNxRot(1, 1); mTrans.yz = mNxRot(1, 2); mTrans.yw = mNx.t.y;
		mTrans.zx = mNxRot(2, 0); mTrans.zy = mNxRot(2, 1); mTrans.zz = mNxRot(2, 2); mTrans.zw = mNx.t.z;
	} else {
		mTrans = Matrix3x4::Identity;
	}
}

void BodyImpl::SetTransformMatrix(const Matrix3x4 &mTrans)
{
	if (m_pPhysXActor) {
		// PL to PhysX transform matrix
		NxMat34 mNx;
		NxMat33 &mNxRot = mNx.M;
		mNxRot(0, 0) = mTrans.xx; mNxRot(0, 1) = mTrans.xy; mNxRot(0, 2) = mTrans.xz; mNx.t.x = mTrans.xw;
		mNxRot(1, 0) = mTrans.yx; mNxRot(1, 1) = mTrans.yy; mNxRot(1, 2) = mTrans.yz; mNx.t.y = mTrans.yw;
		mNxRot(2, 0) = mTrans.zx; mNxRot(2, 1) = mTrans.zy; mNxRot(2, 2) = mTrans.zz; mNx.t.z = mTrans.zw;

		// Set PhysX transform matrix
		m_pPhysXActor->setGlobalPose(mNx);
	}
}

void BodyImpl::GetAABoundingBox(AABoundingBox &cAABoundingBox) const
{
	if (m_pPhysXActor && m_pPhysXActor->getNbShapes()) {
		NxBounds3 cDest;
		m_pPhysXActor->getShapes()[0]->getWorldBounds(cDest);
		cAABoundingBox.vMin.SetXYZ(cDest.min.x, cDest.min.y, cDest.min.z);
		cAABoundingBox.vMax.SetXYZ(cDest.max.x, cDest.max.y, cDest.max.z);
	} else {
		cAABoundingBox.vMin = cAABoundingBox.vMax = Vector3::Zero;
	}
}

void BodyImpl::GetLinearVelocity(Vector3 &vVelocity) const
{
	if (m_pPhysXActor) {
		const NxVec3 vNxVelocity = m_pPhysXActor->getLinearVelocity();
		vVelocity.x = vNxVelocity.x;
		vVelocity.y = vNxVelocity.y;
		vVelocity.z = vNxVelocity.z;
	} else {
		vVelocity = Vector3::Zero;
	}
}

void BodyImpl::SetLinearVelocity(const Vector3 &vVelocity)
{
	if (m_pPhysXActor)
		m_pPhysXActor->setLinearVelocity(NxVec3(vVelocity.x, vVelocity.y, vVelocity.z));
}

void BodyImpl::GetAngularVelocity(Vector3 &vVelocity) const
{
	if (m_pPhysXActor) {
		const NxVec3 vNxVelocity = m_pPhysXActor->getAngularVelocity();
		vVelocity.x = vNxVelocity.x;
		vVelocity.y = vNxVelocity.y;
		vVelocity.z = vNxVelocity.z;
	} else {
		vVelocity = Vector3::Zero;
	}
}

void BodyImpl::SetAngularVelocity(const Vector3 &vVelocity)
{
	if (m_pPhysXActor)
		m_pPhysXActor->setAngularVelocity(NxVec3(vVelocity.x, vVelocity.y, vVelocity.z));
}

void BodyImpl::GetForce(Vector3 &vForce) const
{
	vForce = m_vForce;
}

void BodyImpl::AddForce(const Vector3 &vForce)
{
	m_vForce += vForce;
	PLPhysics::Body *pBody = GetBody();
	if (pBody && !m_bChangedByUser) {
		((World&)pBody->GetWorld()).m_lstChangedByUser.Add(pBody);
		m_bChangedByUser = true;
	}
}

void BodyImpl::SetForce(const Vector3 &vForce)
{
	m_vForce = vForce;
	PLPhysics::Body *pBody = GetBody();
	if (pBody && !m_bChangedByUser) {
		((World&)pBody->GetWorld()).m_lstChangedByUser.Add(pBody);
		m_bChangedByUser = true;
	}
}

void BodyImpl::GetTorque(Vector3 &vTorque) const
{
	vTorque = m_vTorque;
}

void BodyImpl::AddTorque(const Vector3 &vTorque)
{
	m_vTorque += vTorque;
	PLPhysics::Body *pBody = GetBody();
	if (pBody && !m_bChangedByUser) {
		((World&)pBody->GetWorld()).m_lstChangedByUser.Add(pBody);
		m_bChangedByUser = true;
	}
}

void BodyImpl::SetTorque(const Vector3 &vTorque)
{
	m_vTorque = vTorque;
	PLPhysics::Body *pBody = GetBody();
	if (pBody && !m_bChangedByUser) {
		((World&)pBody->GetWorld()).m_lstChangedByUser.Add(pBody);
		m_bChangedByUser = true;
	}
}

bool BodyImpl::IsAutoFreeze() const
{
	// [TODO] Implement auto freeze
	return m_bAutoFreeze;
}

void BodyImpl::SetAutoFreeze(bool bAutoFreeze)
{
	// [TODO] Implement auto freeze
	m_bAutoFreeze = bAutoFreeze;
}

void BodyImpl::GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, uint32 &nSteps) const
{
	if (m_pPhysXActor) {
		fLinearVelocity  = m_pPhysXActor->getSleepLinearVelocity();
		fAngularVelocity = m_pPhysXActor->getSleepAngularVelocity();
		nSteps			 = 0; // nSteps is NOT supported :(
	} else {
		fLinearVelocity  = 0.0f;
		fAngularVelocity = 0.0f;
		nSteps			 = 0;
	}
}

void BodyImpl::SetFreezeThreshold(float fLinearVelocity, float fAngularVelocity, uint32 nSteps)
{
	if (m_pPhysXActor) {
		m_pPhysXActor->setSleepLinearVelocity(fLinearVelocity);
		m_pPhysXActor->setSleepAngularVelocity(fAngularVelocity);
		// nSteps is NOT supported :(
	}
}

bool BodyImpl::IsFrozen() const
{
	return m_pPhysXActor ? m_pPhysXActor->isSleeping() : true;
}

void BodyImpl::SetFrozen(bool bFrozen)
{
	if (m_pPhysXActor) {
		if (bFrozen)
			m_pPhysXActor->putToSleep();
		else
			m_pPhysXActor->wakeUp();
	}
}

bool BodyImpl::IsCollisionActive() const
{
	return m_bCollisionActive;
}

void BodyImpl::SetCollisionActive(bool bActive)
{
	m_bCollisionActive = bActive;
	if (m_pPhysXActor) {
		if (m_bCollisionActive && m_bActive)
			m_pPhysXActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
		else
			m_pPhysXActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}
}

bool BodyImpl::GetUseGravity() const
{
	return m_pPhysXActor ? (m_pPhysXActor->readBodyFlag(NX_BF_DISABLE_GRAVITY) == 0) : true;
}

void BodyImpl::SetUseGravity(bool bUseGravity)
{
	if (m_pPhysXActor) {
		if (bUseGravity)
			m_pPhysXActor->clearBodyFlag(NX_BF_DISABLE_GRAVITY);
		else
			m_pPhysXActor->raiseBodyFlag(NX_BF_DISABLE_GRAVITY);
	}
}

uint8 BodyImpl::GetCollisionGroup() const
{
	if (m_pPhysXActor) {
		const NxShape *pShape = m_pPhysXActor->getShapes()[0];
		return (uint8)pShape->getGroup();
	} else {
		return 0;
	}
}

void BodyImpl::SetCollisionGroup(uint8 nCollisionGroup)
{
	if (m_pPhysXActor && nCollisionGroup <= 31) {
		NxShape *pShape = m_pPhysXActor->getShapes()[0];
		pShape->setGroup(nCollisionGroup);
	}
}

uint32 BodyImpl::GetNumOfPartners() const
{
	return m_lstPartnerBodies.GetNumOfElements();
}

PLPhysics::Body *BodyImpl::GetPartner(uint32 nIndex) const
{
	return m_lstPartnerBodies[nIndex];
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyImpl::BodyImpl() :
	m_pPhysXActor(NULL),
	m_bActive(false),
	m_fCollisionVolume(0.0f),
	m_bAutoFreeze(true),
	m_bCollisionActive(true),
	m_bChangedByUser(false)
{
}

/**
*  @brief
*    Destructor
*/
BodyImpl::~BodyImpl()
{
	// Remove all relationships of this body
	while (m_lstPartnerBodies.GetNumOfElements()) {
		const PLPhysics::Body *pBody = GetBody();
		if (pBody)
			pBody->GetWorld().SetBodyPairFlags(*pBody, *m_lstPartnerBodies[0], 0);
	}

	// Release the actor
	if (m_pPhysXActor)
		m_pPhysXActor->getScene().releaseActor(*m_pPhysXActor);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
