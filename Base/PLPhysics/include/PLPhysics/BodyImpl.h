/*********************************************************\
 *  File: BodyImpl.h                                     *
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


#ifndef __PLPHYSICS_BODYIMPL_H__
#define __PLPHYSICS_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3;
	class Matrix3x4;
	class Quaternion;
	class AABoundingBox;
}
namespace PLPhysics {
	class Body;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics (rigid) body implementation base class
*/
class BodyImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Body;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the PL physics body this is the implementation from
		*
		*  @return
		*    The PL physics body this is the implementation from, a null pointer on error
		*/
		virtual Body *GetBody() const = 0;


	//[-------------------------------------------------------]
	//[ Public virtual Body functions                         ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsActive() const = 0;
		virtual void SetActive(bool bActive = true) = 0;
		virtual float GetCollisionVolume() const = 0;
		virtual float GetMass() const = 0;
		virtual void SetMass(float fMass = 0.0f) = 0;
		virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const = 0;
		virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition) = 0;
		virtual void GetPosition(PLMath::Vector3 &vPosition) const = 0;
		virtual void SetPosition(const PLMath::Vector3 &vPosition) = 0;
		virtual void GetRotation(PLMath::Quaternion &qRotation) const = 0;
		virtual void SetRotation(const PLMath::Quaternion &qRotation) = 0;
		virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const = 0;
		virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans) = 0;
		virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const = 0;
		virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const = 0;
		virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity) = 0;
		virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const = 0;
		virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity) = 0;
		virtual void GetForce(PLMath::Vector3 &vForce) const = 0;
		virtual void AddForce(const PLMath::Vector3 &vForce) = 0;
		virtual void SetForce(const PLMath::Vector3 &vForce) = 0;
		virtual void GetTorque(PLMath::Vector3 &vTorque) const = 0;
		virtual void AddTorque(const PLMath::Vector3 &vTorque) = 0;
		virtual void SetTorque(const PLMath::Vector3 &vTorque) = 0;
		virtual bool IsAutoFreeze() const = 0;
		virtual void SetAutoFreeze(bool bAutoFreeze = true) = 0;
		virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLCore::uint32 &nSteps) const = 0;
		virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLCore::uint32 nSteps = 10) = 0;
		virtual bool IsFrozen() const = 0;
		virtual void SetFrozen(bool bFrozen = true) = 0;
		virtual bool IsCollisionActive() const = 0;
		virtual void SetCollisionActive(bool bActive = true) = 0;
		virtual bool GetUseGravity() const = 0;
		virtual void SetUseGravity(bool bUseGravity = true) = 0;
		virtual PLCore::uint8 GetCollisionGroup() const = 0;
		virtual void SetCollisionGroup(PLCore::uint8 nCollisionGroup = 0) = 0;
		virtual PLCore::uint32 GetNumOfPartners() const = 0;
		virtual Body *GetPartner(PLCore::uint32 nIndex) const = 0;


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyImpl() {}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYIMPL_H__
