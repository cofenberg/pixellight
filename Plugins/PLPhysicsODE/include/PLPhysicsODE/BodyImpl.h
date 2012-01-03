/*********************************************************\
 *  File: BodyImpl.h                                     *
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


#ifndef __PLPHYSICSODE_BODYIMPL_H__
#define __PLPHYSICSODE_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLCore/Container/Array.h>
#include <PLPhysics/BodyImpl.h>
#include "PLPhysicsODE/PLPhysicsODE.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsODE {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    ODE physics (rigid) body implementation class
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
		*    Returns the ODE physics body
		*
		*  @return
		*    The ODE physics body, a null pointer if there's no ODE physics body which means
		*    that this body is static
		*
		*  @note
		*    - Do NOT change the user data of the ODE physics body! (using dBodySetData())
		*      This data MUST hold a pointer to the PL physics body.
		*/
		PLPHYSICSODE_API dBodyID GetODEBody() const;

		/**
		*  @brief
		*    Returns the ODE physics geometry
		*
		*  @return
		*    The ODE physics geometry, a null pointer on error (if that's the case, something went totally wrong :)
		*
		*  @note
		*    - Do NOT change the user data of the ODE physics geometry! (using dGeomSetData())
		*      This data MUST hold a pointer to the PL physics body.
		*/
		PLPHYSICSODE_API dGeomID GetODEGeometry() const;

		/**
		*  @brief
		*    Initializes the ODE physics geometry
		*
		*  @param[in] cBody
		*    PL physics body this is the implementation from
		*  @param[in] pODEGeometry
		*    ODE physics geometry
		*/
		void InitializeODEGeometry(PLPhysics::Body &cBody, dGeomID pODEGeometry);

		/**
		*  @brief
		*    Sets the ODE physics body mass
		*
		*  @param[in] sMass
		*    The ODE physics body mass
		*/
		PLPHYSICSODE_API void SetODEMass(const dMass &sMass);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::BodyImpl functions          ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSODE_API virtual PLPhysics::Body *GetBody() const override;
		PLPHYSICSODE_API virtual bool IsActive() const override;
		PLPHYSICSODE_API virtual void SetActive(bool bActive = true) override;
		PLPHYSICSODE_API virtual float GetCollisionVolume() const override;
		PLPHYSICSODE_API virtual float GetMass() const override;
		PLPHYSICSODE_API virtual void SetMass(float fMass = 0.0f) override;
		PLPHYSICSODE_API virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSODE_API virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSODE_API virtual void GetPosition(PLMath::Vector3 &vPosition) const override;
		PLPHYSICSODE_API virtual void SetPosition(const PLMath::Vector3 &vPosition) override;
		PLPHYSICSODE_API virtual void GetRotation(PLMath::Quaternion &qRotation) const override;
		PLPHYSICSODE_API virtual void SetRotation(const PLMath::Quaternion &qRotation) override;
		PLPHYSICSODE_API virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const override;
		PLPHYSICSODE_API virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans) override;
		PLPHYSICSODE_API virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const override;
		PLPHYSICSODE_API virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSODE_API virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSODE_API virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const override;
		PLPHYSICSODE_API virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity) override;
		PLPHYSICSODE_API virtual void GetForce(PLMath::Vector3 &vForce) const override;
		PLPHYSICSODE_API virtual void AddForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSODE_API virtual void SetForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSODE_API virtual void GetTorque(PLMath::Vector3 &vTorque) const override;
		PLPHYSICSODE_API virtual void AddTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSODE_API virtual void SetTorque(const PLMath::Vector3 &vTorque) override;
		PLPHYSICSODE_API virtual bool IsAutoFreeze() const override;
		PLPHYSICSODE_API virtual void SetAutoFreeze(bool bAutoFreeze = true) override;
		PLPHYSICSODE_API virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLCore::uint32 &nSteps) const override;
		PLPHYSICSODE_API virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLCore::uint32 nSteps = 10) override;
		PLPHYSICSODE_API virtual bool IsFrozen() const override;
		PLPHYSICSODE_API virtual void SetFrozen(bool bFrozen = true) override;
		PLPHYSICSODE_API virtual bool IsCollisionActive() const override;
		PLPHYSICSODE_API virtual void SetCollisionActive(bool bActive = true) override;
		PLPHYSICSODE_API virtual bool GetUseGravity() const override;
		PLPHYSICSODE_API virtual void SetUseGravity(bool bUseGravity = true) override;
		PLPHYSICSODE_API virtual PLCore::uint8 GetCollisionGroup() const override;
		PLPHYSICSODE_API virtual void SetCollisionGroup(PLCore::uint8 nCollisionGroup = 0) override;
		PLPHYSICSODE_API virtual PLCore::uint32 GetNumOfPartners() const override;
		PLPHYSICSODE_API virtual PLPhysics::Body *GetPartner(PLCore::uint32 nIndex) const override;


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
		dBodyID			 m_pODEBody;			/**< ODE physics body, can be a null pointer */
		dGeomID			 m_pODEGeometry;		/**< ODE physics geometry, can be a null pointer */
		bool			 m_bActive;				/**< Currently active? */
		float			 m_fCollisionVolume;	/**< Collision volume */
		float			 m_fMass;				/**< Mass of the physics body */
		dMass			 m_sMass;				/**< Mass of the physics body */
		PLMath::Vector3	 m_vCenterOfMass;		/**< Relative center of the mass */
		bool			 m_bAutoFreeze;			/**< Automatically freeze the body? */
		bool			 m_bFrozen;				/**< Currently frozen? */
		bool			 m_bCollisionActive;	/**< Can the body collide? */
		bool			 m_bUseGravity;			/**< Use gravity? */
		PLCore::uint8    m_nCollisionGroup;		/**< Collision group the body is in */

		/** List of partner bodies */
		PLCore::Array<PLPhysics::Body*> m_lstPartnerBodies;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE


#endif // __PLPHYSICSODE_BODYIMPL_H__
