/*********************************************************\
 *  File: BodyImpl.h                                     *
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


#ifndef __PLPHYSICSPHYSX_BODYIMPL_H__
#define __PLPHYSICSPHYSX_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
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
		*    The PhysX physics actor, NEVER a null pointer
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
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *GetBody() const override;
		PLPHYSICSPHYSX_API virtual bool IsActive() const override;
		PLPHYSICSPHYSX_API virtual void SetActive(bool bActive = true) override;
		PLPHYSICSPHYSX_API virtual float GetCollisionVolume() const override;
		PLPHYSICSPHYSX_API virtual float GetMass() const override;
		PLPHYSICSPHYSX_API virtual void SetMass(float fMass = 0.0f) override;
		PLPHYSICSPHYSX_API virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSPHYSX_API virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSPHYSX_API virtual void GetPosition(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSPHYSX_API virtual void SetPosition(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSPHYSX_API virtual void GetRotation(PLMath::Quaternion &qRotation) const override;
		PLPHYSICSPHYSX_API virtual void SetRotation(const PLMath::Quaternion &qRotation) override;
		PLPHYSICSPHYSX_API virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const override;
		PLPHYSICSPHYSX_API virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans) override;
		PLPHYSICSPHYSX_API virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const override;
		PLPHYSICSPHYSX_API virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSPHYSX_API virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSPHYSX_API virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSPHYSX_API virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSPHYSX_API virtual void GetForce(PLMath::Vector3 &vForce) const override;
		PLPHYSICSPHYSX_API virtual void AddForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSPHYSX_API virtual void SetForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSPHYSX_API virtual void GetTorque(PLMath::Vector3 &vTorque) const override;
		PLPHYSICSPHYSX_API virtual void AddTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSPHYSX_API virtual void SetTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSPHYSX_API virtual bool IsAutoFreeze() const override;
		PLPHYSICSPHYSX_API virtual void SetAutoFreeze(bool bAutoFreeze = true) override;
		PLPHYSICSPHYSX_API virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLCore::uint32 &nSteps) const override;
		PLPHYSICSPHYSX_API virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLCore::uint32 nSteps = 10) override;
		PLPHYSICSPHYSX_API virtual bool IsFrozen() const override;
		PLPHYSICSPHYSX_API virtual void SetFrozen(bool bFrozen = true) override;
		PLPHYSICSPHYSX_API virtual bool IsCollisionActive() const override;
		PLPHYSICSPHYSX_API virtual void SetCollisionActive(bool bActive = true) override;
		PLPHYSICSPHYSX_API virtual bool GetUseGravity() const override;
		PLPHYSICSPHYSX_API virtual void SetUseGravity(bool bUseGravity = true) override;
		PLPHYSICSPHYSX_API virtual PLCore::uint8 GetCollisionGroup() const override;
		PLPHYSICSPHYSX_API virtual void SetCollisionGroup(PLCore::uint8 nCollisionGroup = 0) override;
		PLPHYSICSPHYSX_API virtual PLCore::uint32 GetNumOfPartners() const override;
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *GetPartner(PLCore::uint32 nIndex) const override;


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
		NxActor			*m_pPhysXActor;			/**< PhysX physics actor, can be a null pointer */
		bool			 m_bActive;				/**< Currently active? */
		float			 m_fCollisionVolume;	/**< Collision volume */
		PLMath::Vector3	 m_vForce;				/**< Force applied to the body at the next simulation update */
		PLMath::Vector3	 m_vTorque;				/**< Torque applied to the body at the next simulation update */
		bool			 m_bAutoFreeze;			/**< Automatically freeze the body? */
		bool			 m_bCollisionActive;	/**< Can the body collide? */
		bool			 m_bChangedByUser;		/**< Was this body changed by the used since the last physics update? */

		/** List of partner bodies */
		PLCore::Array<PLPhysics::Body*> m_lstPartnerBodies;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX


#endif // __PLPHYSICSPHYSX_BODYIMPL_H__
