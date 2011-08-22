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


#ifndef __PLPHYSICSNULL_BODYIMPL_H__
#define __PLPHYSICSNULL_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
#include <PLMath/Quaternion.h>
#include <PLPhysics/BodyImpl.h>
#include "PLPhysicsNull/PLPhysicsNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null physics (rigid) body implementation class
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
		*    Initializes the null physics body
		*
		*  @param[in] cBody
		*    PL physics body this is the implementation from
		*/
		void InitializeNullBody(PLPhysics::Body &cBody);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::BodyImpl functions          ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNULL_API virtual PLPhysics::Body *GetBody() const override;
		PLPHYSICSNULL_API virtual bool IsActive() const override;
		PLPHYSICSNULL_API virtual void SetActive(bool bActive = true) override;
		PLPHYSICSNULL_API virtual float GetCollisionVolume() const override;
		PLPHYSICSNULL_API virtual float GetMass() const override;
		PLPHYSICSNULL_API virtual void SetMass(float fMass = 0.0f) override;
		PLPHYSICSNULL_API virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSNULL_API virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSNULL_API virtual void GetPosition(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSNULL_API virtual void SetPosition(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSNULL_API virtual void GetRotation(PLMath::Quaternion &qRotation) const override;
		PLPHYSICSNULL_API virtual void SetRotation(const PLMath::Quaternion &qRotation) override;
		PLPHYSICSNULL_API virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const override;
		PLPHYSICSNULL_API virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans) override;
		PLPHYSICSNULL_API virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const override;
		PLPHYSICSNULL_API virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSNULL_API virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSNULL_API virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSNULL_API virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSNULL_API virtual void GetForce(PLMath::Vector3 &vForce) const override;
		PLPHYSICSNULL_API virtual void AddForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSNULL_API virtual void SetForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSNULL_API virtual void GetTorque(PLMath::Vector3 &vTorque) const override;
		PLPHYSICSNULL_API virtual void AddTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSNULL_API virtual void SetTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSNULL_API virtual bool IsAutoFreeze() const override;
		PLPHYSICSNULL_API virtual void SetAutoFreeze(bool bAutoFreeze = true) override;
		PLPHYSICSNULL_API virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLCore::uint32 &nSteps) const override;
		PLPHYSICSNULL_API virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLCore::uint32 nSteps = 10) override;
		PLPHYSICSNULL_API virtual bool IsFrozen() const override;
		PLPHYSICSNULL_API virtual void SetFrozen(bool bFrozen = true) override;
		PLPHYSICSNULL_API virtual bool IsCollisionActive() const override;
		PLPHYSICSNULL_API virtual void SetCollisionActive(bool bActive = true) override;
		PLPHYSICSNULL_API virtual bool GetUseGravity() const override;
		PLPHYSICSNULL_API virtual void SetUseGravity(bool bUseGravity = true) override;
		PLPHYSICSNULL_API virtual PLCore::uint8 GetCollisionGroup() const override;
		PLPHYSICSNULL_API virtual void SetCollisionGroup(PLCore::uint8 nCollisionGroup = 0) override;
		PLPHYSICSNULL_API virtual PLCore::uint32 GetNumOfPartners() const override;
		PLPHYSICSNULL_API virtual PLPhysics::Body *GetPartner(PLCore::uint32 nIndex) const override;


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
		PLPhysics::Body	  *m_pBody;						/**< PL physics body this is the implementation from, can be a null pointer */
		bool			   m_bActive;					/**< Currently active? */
		float			   m_fCollisionVolume;			/**< Collision volume */
		float			   m_fMass;						/**< Mass of the physics body */
		PLMath::Vector3	   m_vCenterOfMass;				/**< Relative center of the mass */
		PLMath::Vector3	   m_vPosition;					/**< Body position */
		PLMath::Quaternion m_qRotation;					/**< Body rotation */
		PLMath::Vector3	   m_vLinearVelocity;			/**< Linear body velocity */
		PLMath::Vector3	   m_vAngularVelocity;			/**< Angular body velocity */
		PLMath::Vector3	   m_vForce;					/**< Force applied to the body at the next simulation update */
		PLMath::Vector3	   m_vTorque;					/**< Torque applied to the body at the next simulation update */
		bool			   m_bAutoFreeze;				/**< Automatically freeze the body? */
		bool			   m_bFrozen;					/**< Currently frozen? */
		bool			   m_bCollisionActive;			/**< Can the body collide? */
		bool			   m_bUseGravity;				/**< Use gravity? */
		float			   m_fFreezeLinearVelocity;		/**< Linear velocity freeze threshold */
		float			   m_fFreezeAngularVelocity;	/**< Angular velocity freeze threshold */
		PLCore::uint32     m_nFreezeSteps;				/**< Number of steps the linear and angular velocity must be below the thresholds before the body is frozen */
		PLCore::uint8      m_nCollisionGroup;			/**< Collision group the body is in */
		bool			   m_bChangedByUser;			/**< Was this body changed by the used since the last physics update? */

		/** List of partner bodies */
		PLCore::Array<PLPhysics::Body*> m_lstPartnerBodies;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNull


#endif // __PLPHYSICSNULL_BODYIMPL_H__
