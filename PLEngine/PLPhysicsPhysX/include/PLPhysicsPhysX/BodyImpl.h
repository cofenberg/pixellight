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


#ifndef __PLPHYSICSPHYSX_BODYIMPL_H__
#define __PLPHYSICSPHYSX_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLMath/Vector3.h>
#include <PLPhysics/BodyImpl.h>
#include "PLPhysicsPhysX/PLPhysicsPhysX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PhysX physics (rigid) body implementation class
*
*  @note
*    - Freeze threshold steps is NOT supported (see GetFreezeThreshold())
*    - IsAutoFreeze()/SetAutoFreeze() is NOT supported, bodies are always frozen automatically
*/
class BodyImpl : public PLPhysics::BodyImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the PhysX physics actor
		*
		*  @return
		*    The PhysX physics actor, NEVER NULL
		*
		*  @note
		*    - Do NOT change the user data of the PhysX physics actor! (using NxActor::userData)
		*      This data MUST hold a pointer to the PL physics body.
		*/
		PLPHYSICSPHYSX_API NxActor *GetPhysXActor() const;

		/**
		*  @brief
		*    Initializes the PhysX physics actor
		*
		*  @param[in] cBody
		*    PL physics body this is the implementation from
		*  @param[in] cPhysXActor
		*    PhysX actor
		*/
		void InitializePhysXActor(PLPhysics::Body &cBody, NxActor &cPhysXActor);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::BodyImpl functions          ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *GetBody() const;
		PLPHYSICSPHYSX_API virtual bool IsActive() const;
		PLPHYSICSPHYSX_API virtual void SetActive(bool bActive = true);
		PLPHYSICSPHYSX_API virtual float GetCollisionVolume() const;
		PLPHYSICSPHYSX_API virtual float GetMass() const;
		PLPHYSICSPHYSX_API virtual void SetMass(float fMass = 0.0f);
		PLPHYSICSPHYSX_API virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const;
		PLPHYSICSPHYSX_API virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition);
		PLPHYSICSPHYSX_API virtual void GetPosition(PLMath::Vector3 &vPosition) const;
		PLPHYSICSPHYSX_API virtual void SetPosition(const PLMath::Vector3 &vPosition);
		PLPHYSICSPHYSX_API virtual void GetRotation(PLMath::Quaternion &qRotation) const;
		PLPHYSICSPHYSX_API virtual void SetRotation(const PLMath::Quaternion &qRotation);
		PLPHYSICSPHYSX_API virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const;
		PLPHYSICSPHYSX_API virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans);
		PLPHYSICSPHYSX_API virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const;
		PLPHYSICSPHYSX_API virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const;
		PLPHYSICSPHYSX_API virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity);
		PLPHYSICSPHYSX_API virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const;
		PLPHYSICSPHYSX_API virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity);
		PLPHYSICSPHYSX_API virtual void GetForce(PLMath::Vector3 &vForce) const;
		PLPHYSICSPHYSX_API virtual void AddForce(const PLMath::Vector3 &vForce);
		PLPHYSICSPHYSX_API virtual void SetForce(const PLMath::Vector3 &vForce);
		PLPHYSICSPHYSX_API virtual void GetTorque(PLMath::Vector3 &vTorque) const;
		PLPHYSICSPHYSX_API virtual void AddTorque(const PLMath::Vector3 &vTorque);
		PLPHYSICSPHYSX_API virtual void SetTorque(const PLMath::Vector3 &vTorque);
		PLPHYSICSPHYSX_API virtual bool IsAutoFreeze() const;
		PLPHYSICSPHYSX_API virtual void SetAutoFreeze(bool bAutoFreeze = true);
		PLPHYSICSPHYSX_API virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLGeneral::uint32 &nSteps) const;
		PLPHYSICSPHYSX_API virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLGeneral::uint32 nSteps = 10);
		PLPHYSICSPHYSX_API virtual bool IsFrozen() const;
		PLPHYSICSPHYSX_API virtual void SetFrozen(bool bFrozen = true);
		PLPHYSICSPHYSX_API virtual bool IsCollisionActive() const;
		PLPHYSICSPHYSX_API virtual void SetCollisionActive(bool bActive = true);
		PLPHYSICSPHYSX_API virtual bool GetUseGravity() const;
		PLPHYSICSPHYSX_API virtual void SetUseGravity(bool bUseGravity = true);
		PLPHYSICSPHYSX_API virtual PLGeneral::uint8 GetCollisionGroup() const;
		PLPHYSICSPHYSX_API virtual void SetCollisionGroup(PLGeneral::uint8 nCollisionGroup = 0);
		PLPHYSICSPHYSX_API virtual PLGeneral::uint32 GetNumOfPartners() const;
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *GetPartner(PLGeneral::uint32 nIndex) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		BodyImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BodyImpl();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		NxActor			*m_pPhysXActor;			/**< PhysX physics actor, can be NULL */
		bool			 m_bActive;				/**< Currently active? */
		float			 m_fCollisionVolume;	/**< Collision volume */
		PLMath::Vector3	 m_vForce;				/**< Force applied to the body at the next simulation update */
		PLMath::Vector3	 m_vTorque;				/**< Torque applied to the body at the next simulation update */
		bool			 m_bAutoFreeze;			/**< Automatically freeze the body? */
		bool			 m_bCollisionActive;	/**< Can the body collide? */
		bool			 m_bChangedByUser;		/**< Was this body changed by the used since the last physics update? */

		/** List of partner bodies */
		PLGeneral::Array<PLPhysics::Body*> m_lstPartnerBodies;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX


#endif // __PLPHYSICSPHYSX_BODYIMPL_H__
