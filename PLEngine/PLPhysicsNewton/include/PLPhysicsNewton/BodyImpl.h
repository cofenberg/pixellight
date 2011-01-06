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


#ifndef __PLPHYSICSNEWTON_BODYIMPL_H__
#define __PLPHYSICSNEWTON_BODYIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLMath/Quaternion.h>
#include <PLPhysics/BodyImpl.h>
#include "PLPhysicsNewton/PLPhysicsNewton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton physics (rigid) body implementation class
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
		*    Returns the Newton physics body
		*
		*  @return
		*    The Newton physics body, a null pointer on error (if that's the case, something went totally wrong :)
		*
		*  @note
		*    - Do NOT change the user data of the Newton physics body! (using NewtonBodySetUserData())
		*      This data MUST hold a pointer to the PL physics body.
		*/
		PLPHYSICSNEWTON_API Newton::NewtonBody *GetNewtonBody() const;

		/**
		*  @brief
		*    Flushs the body
		*
		*  @remarks
		*    Sets for instance the current transform matrix of the Newton physics body.
		*/
		PLPHYSICSNEWTON_API void Flush();

		/**
		*  @brief
		*    Initializes the Newton physics body
		*
		*  @param[in] cBody
		*    PL physics body this is the implementation from
		*  @param[in] cNewtonBody
		*    Newton physics body
		*  @param[in] fCollisionVolume
		*    Collision volume
		*/
		void InitializeNewtonBody(PLPhysics::Body &cBody, Newton::NewtonBody &cNewtonBody, float fCollisionVolume);

		/**
		*  @brief
		*    Sets the Newton physics body freeze state
		*
		*  @param[in] bFreeze
		*    Freeze the physics body?
		*
		*  @note
		*    - The physics body is only unfrozen if it's currently active
		*/
		void SetNewtonBodyFreezeState(bool bFreeze);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::BodyImpl functions          ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNEWTON_API virtual PLPhysics::Body *GetBody() const;
		PLPHYSICSNEWTON_API virtual bool IsActive() const;
		PLPHYSICSNEWTON_API virtual void SetActive(bool bActive = true);
		PLPHYSICSNEWTON_API virtual float GetCollisionVolume() const;
		PLPHYSICSNEWTON_API virtual float GetMass() const;
		PLPHYSICSNEWTON_API virtual void SetMass(float fMass = 0.0f);
		PLPHYSICSNEWTON_API virtual void GetCenterOfMass(PLMath::Vector3 &vPosition) const;
		PLPHYSICSNEWTON_API virtual void SetCenterOfMass(const PLMath::Vector3 &vPosition);
		PLPHYSICSNEWTON_API virtual void GetPosition(PLMath::Vector3 &vPosition) const;
		PLPHYSICSNEWTON_API virtual void SetPosition(const PLMath::Vector3 &vPosition);
		PLPHYSICSNEWTON_API virtual void GetRotation(PLMath::Quaternion &qRotation) const;
		PLPHYSICSNEWTON_API virtual void SetRotation(const PLMath::Quaternion &qRotation);
		PLPHYSICSNEWTON_API virtual void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const;
		PLPHYSICSNEWTON_API virtual void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans);
		PLPHYSICSNEWTON_API virtual void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const;
		PLPHYSICSNEWTON_API virtual void GetLinearVelocity(PLMath::Vector3 &vVelocity) const;
		PLPHYSICSNEWTON_API virtual void SetLinearVelocity(const PLMath::Vector3 &vVelocity);
		PLPHYSICSNEWTON_API virtual void GetAngularVelocity(PLMath::Vector3 &vVelocity) const;
		PLPHYSICSNEWTON_API virtual void SetAngularVelocity(const PLMath::Vector3 &vVelocity);
		PLPHYSICSNEWTON_API virtual void GetForce(PLMath::Vector3 &vForce) const;
		PLPHYSICSNEWTON_API virtual void AddForce(const PLMath::Vector3 &vForce);
		PLPHYSICSNEWTON_API virtual void SetForce(const PLMath::Vector3 &vForce);
		PLPHYSICSNEWTON_API virtual void GetTorque(PLMath::Vector3 &vTorque) const;
		PLPHYSICSNEWTON_API virtual void AddTorque(const PLMath::Vector3 &vTorque);
		PLPHYSICSNEWTON_API virtual void SetTorque(const PLMath::Vector3 &vTorque);
		PLPHYSICSNEWTON_API virtual bool IsAutoFreeze() const;
		PLPHYSICSNEWTON_API virtual void SetAutoFreeze(bool bAutoFreeze = true);
		PLPHYSICSNEWTON_API virtual bool IsFrozen() const;
		PLPHYSICSNEWTON_API virtual void SetFrozen(bool bFrozen = true);
		PLPHYSICSNEWTON_API virtual bool IsCollisionActive() const;
		PLPHYSICSNEWTON_API virtual void SetCollisionActive(bool bActive = true);
		PLPHYSICSNEWTON_API virtual bool GetUseGravity() const;
		PLPHYSICSNEWTON_API virtual void SetUseGravity(bool bUseGravity = true);
		PLPHYSICSNEWTON_API virtual void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLGeneral::uint32 &nSteps) const;
		PLPHYSICSNEWTON_API virtual void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLGeneral::uint32 nSteps = 10);
		PLPHYSICSNEWTON_API virtual PLGeneral::uint8 GetCollisionGroup() const;
		PLPHYSICSNEWTON_API virtual void SetCollisionGroup(PLGeneral::uint8 nCollisionGroup = 0);
		PLPHYSICSNEWTON_API virtual PLGeneral::uint32 GetNumOfPartners() const;
		PLPHYSICSNEWTON_API virtual PLPhysics::Body *GetPartner(PLGeneral::uint32 nIndex) const;


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
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Changed flags
		*/
		enum EChangedFlags {
			Position		= 1<<0,
			Rotation		= 1<<1,
			LinearVelocity	= 1<<2,
			AngularVelocity	= 1<<3,
			Force			= 1<<4,
			Torque			= 1<<5,
			Freeze			= 1<<6,
			Unfreeze		= 1<<7
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Newton::NewtonBody *m_pNewtonBody;				/**< Newton physics body, can be a null pointer */
		bool			    m_bActive;					/**< Currently active? */
		float				m_fCollisionVolume;			/**< Collision volume */
		float				m_fMass;					/**< Mass of the physics body */
		PLMath::Vector3		m_vPosition;				/**< Body position */
		PLMath::Quaternion	m_qRotation;				/**< Body rotation */
		PLMath::Vector3		m_vLinearVelocity;			/**< Linear body velocity */
		PLMath::Vector3		m_vAngularVelocity;			/**< Angular body velocity */
		PLMath::Vector3		m_vForce;					/**< Force applied to the body at the next simulation update */
		PLMath::Vector3		m_vNewtonForce;				/**< Newton force applied to the body at the next simulation update */
		PLMath::Vector3		m_vTorque;					/**< Torque applied to the body at the next simulation update */
		PLMath::Vector3		m_vNewtonTorque;			/**< Newton torque applied to the body at the next simulation update */
		bool				m_bFrozen;					/**< Is the body currently frozen? */
		bool				m_bAutoFreeze;				/**< Automatically freeze the body? */
		float				m_fFreezeLinearVelocity;	/**< Linear velocity freeze threshold */
		float				m_fFreezeAngularVelocity;	/**< Angular velocity freeze threshold */
		PLGeneral::uint32	m_nFreezeSteps;				/**< Number of steps the linear and angular velocity must be below the thresholds before the body is frozen */
		PLGeneral::uint32	m_nCurrentFreezeSteps;		/**< Current freeze steps */
		bool				m_bCollisionActive;			/**< Can the body collide? */
		bool				m_bUseGravity;				/**< Use gravity? */
		PLGeneral::uint8	m_nCollisionGroup;			/**< Collision group the body is in */
		PLGeneral::uint16	m_nChangedByUserFlags;		/**< Changed by user flags */
		PLGeneral::uint8	m_nChangedByPhysicsFlags;	/**< Changed by physics flags */

		/** List of partner bodies */
		PLGeneral::Array<PLPhysics::Body*> m_lstPartnerBodies;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_BODYIMPL_H__
