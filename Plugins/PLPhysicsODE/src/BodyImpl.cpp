/*********************************************************\
 *  File: BodyImpl.cpp                                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLMath/Matrix3x4.h>
#include <PLMath/Quaternion.h>
#include <PLMath/AABoundingBox.h>
#include <PLPhysics/Body.h>
#include "PLPhysicsODE/World.h"
#include "PLPhysicsODE/BodyImpl.h"


//[-------------------------------------------------------]
//[ Macros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    ODE matrix access helper macro
*
*  @param[in] i
*    Row (0-2)
*  @param[in] j
*    Column (0-3)
*/
#define _R(i, j) R[(i)*4+(j)]


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
*    Returns the ODE physics body
*/
dBodyID BodyImpl::GetODEBody() const
{
	return m_pODEBody;
}

/**
*  @brief
*    Returns the ODE physics geometry
*/
dGeomID BodyImpl::GetODEGeometry() const
{
	return m_pODEGeometry;
}

/**
*  @brief
*    Initializes the ODE physics geometry
*/
void BodyImpl::InitializeODEGeometry(PLPhysics::Body &cBody, dGeomID pODEGeometry)
{
	// Set data
	m_pODEGeometry = pODEGeometry;

	// Save the pointer to the PL physics body
	dGeomSetData(m_pODEGeometry, &cBody);
}

/**
*  @brief
*    Sets the ODE physics body mass
*/
void BodyImpl::SetODEMass(const dMass &sMass)
{
	m_sMass = sMass;
	if (m_vCenterOfMass.IsNull())
		dBodySetMass(m_pODEBody, &m_sMass);
	else {
		dMass sMassT = m_sMass;
		dMassTranslate(&sMassT, m_vCenterOfMass.x, m_vCenterOfMass.y, m_vCenterOfMass.z);
		dBodySetMass(m_pODEBody, &sMassT);
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::BodyImpl functions          ]
//[-------------------------------------------------------]
PLPhysics::Body *BodyImpl::GetBody() const
{
	return static_cast<PLPhysics::Body*>(dGeomGetData(m_pODEGeometry));
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
	}
}

float BodyImpl::GetCollisionVolume() const
{
	return m_fCollisionVolume;
}

float BodyImpl::GetMass() const
{
	return m_fMass;
}

void BodyImpl::SetMass(float fMass)
{
	m_fMass = fMass;
	if (m_fMass) {
		// Create the ODE physics body
		if (!m_pODEBody) {
			// Create the body
			m_pODEBody = dBodyCreate(static_cast<World&>(GetBody()->GetWorld()).GetODEWorld());
			dBodySetAutoDisableFlag(m_pODEBody, m_bAutoFreeze);
			SetFrozen(m_bFrozen);
			dBodySetGravityMode(m_pODEBody, m_bUseGravity);
			const dReal *pfPosition = dGeomGetPosition(m_pODEGeometry);
			dBodySetPosition(m_pODEBody, pfPosition[0], pfPosition[1], pfPosition[2]);
			float fRotation[4];
			dGeomGetQuaternion(m_pODEGeometry, fRotation);
			dBodySetQuaternion(m_pODEBody, fRotation);
			dMassSetZero(&m_sMass);

			// Save the pointer to the PL physics body
			dBodySetData(m_pODEBody, dGeomGetData(m_pODEGeometry));

			// Assign the body with the geometry
			dGeomSetBody(m_pODEGeometry, m_pODEBody);
		}
	} else {
		// Destroy the ODE physics body
		if (m_pODEBody) {
			m_bFrozen = (dBodyIsEnabled(m_pODEBody) == 0);
			dGeomSetBody(m_pODEGeometry, nullptr);
			dBodyDestroy(m_pODEBody);
			m_pODEBody = nullptr;
		}
	}
}

void BodyImpl::GetCenterOfMass(Vector3 &vPosition) const
{
	vPosition = m_vCenterOfMass;
}

void BodyImpl::SetCenterOfMass(const Vector3 &vPosition)
{
	m_vCenterOfMass = vPosition;
	if (m_fMass && !m_vCenterOfMass.IsNull()) {
		dMass sMass = m_sMass;
		dMassTranslate(&sMass, m_vCenterOfMass.x, m_vCenterOfMass.y, m_vCenterOfMass.z);
		dBodySetMass(m_pODEBody, &sMass);
	}
}

void BodyImpl::GetPosition(Vector3 &vPosition) const
{
	vPosition = m_pODEBody ? dBodyGetPosition(m_pODEBody) : dGeomGetPosition(m_pODEGeometry);
}

void BodyImpl::SetPosition(const Vector3 &vPosition)
{
	if (m_pODEBody)
		dBodySetPosition(m_pODEBody,     vPosition.x, vPosition.y, vPosition.z);
	else
		dGeomSetPosition(m_pODEGeometry, vPosition.x, vPosition.y, vPosition.z);
}

void BodyImpl::GetRotation(Quaternion &qRotation) const
{
	if (m_pODEBody)
		qRotation.SetWXYZ(dBodyGetQuaternion(m_pODEBody));
	else
		dGeomGetQuaternion(m_pODEGeometry, qRotation);
}

void BodyImpl::SetRotation(const Quaternion &qRotation)
{
	if (m_pODEBody)
		dBodySetQuaternion(m_pODEBody,     qRotation);
	else
		dGeomSetQuaternion(m_pODEGeometry, qRotation);
}

void BodyImpl::GetTransformMatrix(Matrix3x4 &mTrans) const
{
	if (m_pODEBody) {
		// We can't pass through the matrix directly :(
		const dReal *R = dBodyGetRotation(m_pODEBody);
		mTrans.xx = _R(0, 0); mTrans.xy = _R(0, 1); mTrans.xz = _R(0, 2); mTrans.xw = _R(0, 3);
		mTrans.yx = _R(1, 0); mTrans.yy = _R(1, 1); mTrans.yz = _R(1, 2); mTrans.yw = _R(1, 3);
		mTrans.zx = _R(2, 0); mTrans.zy = _R(2, 1); mTrans.zz = _R(2, 2); mTrans.zw = _R(2, 3);

		// Set translation
		mTrans.SetTranslation(dBodyGetPosition(m_pODEBody));
	} else {
		// We can't pass through the matrix directly :(
		const dReal *R = dGeomGetRotation(m_pODEGeometry);
		mTrans.xx = _R(0, 0); mTrans.xy = _R(0, 1); mTrans.xz = _R(0, 2); mTrans.xw = _R(0, 3);
		mTrans.yx = _R(1, 0); mTrans.yy = _R(1, 1); mTrans.yz = _R(1, 2); mTrans.yw = _R(1, 3);
		mTrans.zx = _R(2, 0); mTrans.zy = _R(2, 1); mTrans.zz = _R(2, 2); mTrans.zw = _R(2, 3);

		// Set translation
		mTrans.SetTranslation(dGeomGetPosition(m_pODEGeometry));
	}
}

void BodyImpl::SetTransformMatrix(const Matrix3x4 &mTrans)
{
	// We can't pass through our matrix directly :(
	dMatrix3 R;
	_R(0, 0) = mTrans.xx; _R(0, 1) = mTrans.xy; _R(0, 2) = mTrans.xz; _R(0, 3) = mTrans.xw;
	_R(1, 0) = mTrans.yx; _R(1, 1) = mTrans.yy; _R(1, 2) = mTrans.yz; _R(1, 3) = mTrans.yw;
	_R(2, 0) = mTrans.zx; _R(2, 1) = mTrans.zy; _R(2, 2) = mTrans.zz; _R(2, 3) = mTrans.zw;

	// Set rotation and position
	if (m_pODEBody) {
		dBodySetRotation(m_pODEBody, R);
		dBodySetPosition(m_pODEBody, mTrans.xw, mTrans.yw, mTrans.zw);
	} else {
		dGeomSetRotation(m_pODEGeometry, R);
		dGeomSetPosition(m_pODEGeometry, mTrans.xw, mTrans.yw, mTrans.zw);
	}
}

void BodyImpl::GetAABoundingBox(AABoundingBox &cAABoundingBox) const
{
	if (m_pODEGeometry) {
		dReal fAABB[6]; // minx, maxx, miny, maxy, minz, maxz
		dGeomGetAABB(m_pODEGeometry, fAABB);
		cAABoundingBox.vMin.SetXYZ(fAABB[0], fAABB[2], fAABB[4]);
		cAABoundingBox.vMax.SetXYZ(fAABB[1], fAABB[3], fAABB[5]);
	} else {
		cAABoundingBox.vMin = cAABoundingBox.vMax = Vector3::Zero;
	}
}

void BodyImpl::GetLinearVelocity(Vector3 &vVelocity) const
{
	if (m_pODEBody)
		vVelocity = dBodyGetLinearVel(m_pODEBody);
}

void BodyImpl::SetLinearVelocity(const Vector3 &vVelocity)
{
	if (m_pODEBody)
		dBodySetLinearVel(m_pODEBody, vVelocity.x, vVelocity.y, vVelocity.z);
}

void BodyImpl::GetAngularVelocity(Vector3 &vVelocity) const
{
	if (m_pODEBody)
		vVelocity = dBodyGetAngularVel(m_pODEBody);
}

void BodyImpl::SetAngularVelocity(const Vector3 &vVelocity)
{
	if (m_pODEBody)
		dBodySetAngularVel(m_pODEBody, vVelocity.x, vVelocity.y, vVelocity.z);
}

void BodyImpl::GetForce(Vector3 &vForce) const
{
	if (m_pODEBody)
		vForce = dBodyGetForce(m_pODEBody);
}

void BodyImpl::AddForce(const Vector3 &vForce)
{
	if (m_pODEBody)
		dBodyAddForce(m_pODEBody, vForce.x, vForce.y, vForce.z);
}

void BodyImpl::SetForce(const Vector3 &vForce)
{
	if (m_pODEBody)
		dBodySetForce(m_pODEBody, vForce.x, vForce.y, vForce.z);
}

void BodyImpl::GetTorque(Vector3 &vTorque) const
{
	if (m_pODEBody)
		vTorque = dBodyGetTorque(m_pODEBody);
}

void BodyImpl::AddTorque(const Vector3 &vTorque)
{
	if (m_pODEBody)
		dBodyAddTorque(m_pODEBody, vTorque.x, vTorque.y, vTorque.z);
}

void BodyImpl::SetTorque(const Vector3 &vTorque)
{
	if (m_pODEBody)
		dBodySetTorque(m_pODEBody, vTorque.x, vTorque.y, vTorque.z);
}

bool BodyImpl::IsAutoFreeze() const
{
	return m_bAutoFreeze;
}

void BodyImpl::SetAutoFreeze(bool bAutoFreeze)
{
	m_bAutoFreeze = bAutoFreeze;
	if (m_pODEBody)
		dBodySetAutoDisableFlag(m_pODEBody, bAutoFreeze);
}

void BodyImpl::GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLCore::uint32 &nSteps) const
{
	if (m_pODEBody) {
		fLinearVelocity  = dBodyGetAutoDisableLinearThreshold(m_pODEBody);
		fAngularVelocity = dBodyGetAutoDisableAngularThreshold(m_pODEBody);
		nSteps			 = dBodyGetAutoDisableSteps(m_pODEBody);
	}
}

void BodyImpl::SetFreezeThreshold(float fLinearVelocity, float fAngularVelocity, PLCore::uint32 nSteps)
{
	if (m_pODEBody) {
		dBodySetAutoDisableLinearThreshold (m_pODEBody, fLinearVelocity);
		dBodySetAutoDisableAngularThreshold(m_pODEBody, fAngularVelocity);
		dBodySetAutoDisableSteps		   (m_pODEBody, nSteps);
	}
}

bool BodyImpl::IsFrozen() const
{
	return m_pODEBody ? !dBodyIsEnabled(m_pODEBody) : m_bFrozen;
}

void BodyImpl::SetFrozen(bool bFrozen)
{
	if (m_pODEBody) {
		if (bFrozen)
			dBodyDisable(m_pODEBody);
		else
			dBodyEnable(m_pODEBody);
	} else {
		m_bFrozen = bFrozen;
	}
}

bool BodyImpl::IsCollisionActive() const
{
	return m_bCollisionActive;
}

void BodyImpl::SetCollisionActive(bool bActive)
{
	m_bCollisionActive = bActive;
}

bool BodyImpl::GetUseGravity() const
{
	return m_pODEBody ? (dBodyGetGravityMode(m_pODEBody) != 0) : m_bUseGravity;
}

void BodyImpl::SetUseGravity(bool bUseGravity)
{
	m_bUseGravity = bUseGravity;
	if (m_pODEBody)
		dBodySetGravityMode(m_pODEBody, bUseGravity);
}

PLCore::uint32 BodyImpl::GetNumOfPartners() const
{
	return m_lstPartnerBodies.GetNumOfElements();
}

PLCore::uint8 BodyImpl::GetCollisionGroup() const
{
	return m_nCollisionGroup;
}

void BodyImpl::SetCollisionGroup(PLCore::uint8 nCollisionGroup)
{
	if (nCollisionGroup <= 31)
		m_nCollisionGroup = nCollisionGroup;
}

PLPhysics::Body *BodyImpl::GetPartner(PLCore::uint32 nIndex) const
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
	m_pODEBody(nullptr),
	m_pODEGeometry(nullptr),
	m_bActive(true),
	m_fCollisionVolume(0.0f),
	m_fMass(0.0f),
	m_bAutoFreeze(true),
	m_bFrozen(true),
	m_bCollisionActive(true),
	m_bUseGravity(true),
	m_nCollisionGroup(0)
{
}

/**
*  @brief
*    Destructor
*/
BodyImpl::~BodyImpl()
{
	// Remove all relationships of this body
	while (m_lstPartnerBodies.GetNumOfElements())
		GetBody()->GetWorld().SetBodyPairFlags(*GetBody(), *m_lstPartnerBodies[0], 0);

	// Destroy the ODE physics body
	if (m_pODEBody)
		dBodyDestroy(m_pODEBody);

	// Destroy ODE physics geometry
	if (m_pODEGeometry)
		dGeomDestroy(m_pODEGeometry);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
