/*********************************************************\
 *  File: Body.h                                         *
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


#ifndef __PLPHYSICS_BODY_H__
#define __PLPHYSICS_BODY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLPhysics/Element.h"


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
	class BodyImpl;
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
*    Abstract PL physics (rigid) body base class
*
*  @remarks
*    If a physics body is created, it is frozen automatically. Bodies can interact if they are in
*    collision groups (see GetCollisionGroup()) which can collide, (see World::GetGroupCollision())
*    and if within the body pair flag (see World::GetBodyPairFlags()) World::Ignore is NOT set -
*    AND at least, IsCollisionActive() of both must return 'true'.
*/
class Body : public Element {


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>	EventTransform;	/**< Transform was changed by the physics */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~Body();

		/**
		*  @brief
		*    Returns a reference to the physics API specific body implementation
		*
		*  @return
		*    Reference to the physics API specific body implementation
		*/
		PLPHYSICS_API BodyImpl &GetBodyImpl() const;

		/**
		*  @brief
		*    Returns whether the body is currently active or not
		*
		*  @return
		*    'true' if the body is currently active, else 'false'
		*
		*  @note
		*    - With 'active' we mean 'totally ignored' and not 'just currently frozen' (see IsFrozen())
		*/
		PLPHYSICS_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the body is currently active or not
		*
		*  @param[in] bActive
		*    'true' if the body is currently active, else 'false'
		*
		*  @see
		*    - IsActive()
		*/
		PLPHYSICS_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Returns the collision volume of the physics body
		*
		*  @return
		*    The collision volume of the physics body
		*
		*  @remarks
		*    The collision volume of the body can for instance be used for buoyancy.
		*/
		PLPHYSICS_API float GetCollisionVolume() const;

		/**
		*  @brief
		*    Returns the mass of the physics body
		*
		*  @return
		*    Mass of the physics body
		*/
		PLPHYSICS_API float GetMass() const;

		/**
		*  @brief
		*    Sets the mass of the physics body
		*
		*  @param[in] fMass
		*    New mass of the physics body, 0 = static body
		*
		*  @see
		*    - World::IsAlwaysStatic()
		*/
		PLPHYSICS_API virtual void SetMass(float fMass = 0.0f);

		/**
		*  @brief
		*    Gets the relativ center of the mass
		*
		*  @param[out] vPosition
		*    Will receive the relativ center of the mass
		*
		*  @note
		*    - The relativ center of the mass does't 'move' the body, it just has an influcence on it's behaviour
		*/
		PLPHYSICS_API void GetCenterOfMass(PLMath::Vector3 &vPosition) const;

		/**
		*  @brief
		*    Sets the relativ center of the mass
		*
		*  @param[in] vPosition
		*    New relativ center of the mass (PLMath::Vector3::Zero by default)
		*
		*  @see
		*    - GetCenterOfMass()
		*/
		PLPHYSICS_API void SetCenterOfMass(const PLMath::Vector3 &vPosition);

		/**
		*  @brief
		*    Gets the body position
		*
		*  @param[out] vPosition
		*    Will receive the current body position
		*/
		PLPHYSICS_API void GetPosition(PLMath::Vector3 &vPosition) const;

		/**
		*  @brief
		*    Sets the body position
		*
		*  @param[in] vPosition
		*    New body position
		*/
		PLPHYSICS_API void SetPosition(const PLMath::Vector3 &vPosition);

		/**
		*  @brief
		*    Gets the body rotation
		*
		*  @param[out] qRotation
		*    Will receive the body rotation
		*/
		PLPHYSICS_API void GetRotation(PLMath::Quaternion &qRotation) const;

		/**
		*  @brief
		*    Sets the body rotation
		*
		*  @param[in] qRotation
		*    New body rotation
		*/
		PLPHYSICS_API void SetRotation(const PLMath::Quaternion &qRotation);

		/**
		*  @brief
		*    Gets the body transform matrix
		*
		*  @param[out] mTrans
		*    Will receive the body transform matrix
		*/
		PLPHYSICS_API void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const;

		/**
		*  @brief
		*    Sets the body transform matrix
		*
		*  @param[in] mTrans
		*    New body transform matrix
		*/
		PLPHYSICS_API void SetTransformMatrix(const PLMath::Matrix3x4 &mTrans);

		/**
		*  @brief
		*    Gets the global space axis aligned bounding box of the body
		*
		*  @param[out] cAABoundingBox
		*    Will receive the global space axis aligned bounding box of the body
		*/
		PLPHYSICS_API void GetAABoundingBox(PLMath::AABoundingBox &cAABoundingBox) const;

		/**
		*  @brief
		*    Gets the linear body velocity
		*
		*  @param[out] vVelocity
		*    Will receive the current linear body velocity
		*/
		PLPHYSICS_API void GetLinearVelocity(PLMath::Vector3 &vVelocity) const;

		/**
		*  @brief
		*    Sets the linear body velocity
		*
		*  @param[in] vVelocity
		*    New linear body velocity
		*/
		PLPHYSICS_API void SetLinearVelocity(const PLMath::Vector3 &vVelocity);

		/**
		*  @brief
		*    Gets the angular body velocity
		*
		*  @param[out] vVelocity
		*    Will receive the current angular body velocity
		*/
		PLPHYSICS_API void GetAngularVelocity(PLMath::Vector3 &vVelocity) const;

		/**
		*  @brief
		*    Sets the angular body velocity
		*
		*  @param[in] vVelocity
		*    New angular body velocity
		*/
		PLPHYSICS_API void SetAngularVelocity(const PLMath::Vector3 &vVelocity);

		/**
		*  @brief
		*    Gets the force applied to the body at the next simulation update
		*
		*  @param[out] vForce
		*    Will receive the force applied to the body at the next simulation update
		*
		*  @remarks
		*    The forces are accumulated on to each body, and the accumulators are zeroed after each simulation update.
		*/
		PLPHYSICS_API void GetForce(PLMath::Vector3 &vForce) const;

		/**
		*  @brief
		*    Adds a force to the body
		*
		*  @param[in] vForce
		*    Force to add
		*
		*  @remarks
		*    If the simulation is currently inactive, it's NOT recommended to add forces because they are not reset each frame!
		*
		*  @see
		*    - GetForce()
		*/
		PLPHYSICS_API void AddForce(const PLMath::Vector3 &vForce);

		/**
		*  @brief
		*    Sets the force applied to the body at the next simulation update
		*
		*  @param[in] vForce
		*    Force to set
		*
		*  @remarks
		*    It's not recommended to set the force directly by using this function, use AddForce()
		*    instead whenever possible!
		*
		*  @see
		*    - GetForce()
		*/
		PLPHYSICS_API void SetForce(const PLMath::Vector3 &vForce);

		/**
		*  @brief
		*    Gets the torque applied to the body at the next simulation update
		*
		*  @param[out] vTorque
		*    Will receive the torque applied to the body at the next simulation update
		*
		*  @remarks
		*    The torques are accumulated on to each body, and the accumulators are zeroed after each simulation update.
		*/
		PLPHYSICS_API void GetTorque(PLMath::Vector3 &vTorque) const;

		/**
		*  @brief
		*    Adds a torque to the body
		*
		*  @param[in] vTorque
		*    Torque to add
		*
		*  @remarks
		*    If the simulation is currently inactive, it's NOT recommended to add torques because they are not reset each frame!
		*
		*  @see
		*    - GetTorque()
		*/
		PLPHYSICS_API void AddTorque(const PLMath::Vector3 &vTorque);

		/**
		*  @brief
		*    Sets the torque applied to the body at the next simulation update
		*
		*  @param[in] vTorque
		*    Torque to set
		*
		*  @remarks
		*    It's not recommended to set the torque directly by using this function, use AddTorque()
		*    instead whenever possible!
		*
		*  @see
		*    - GetTorque()
		*/
		PLPHYSICS_API void SetTorque(const PLMath::Vector3 &vTorque);

		/**
		*  @brief
		*    Returns whether the body is frozen automatically or not
		*
		*  @return
		*    'true' if the body is frozen automatically, else 'false'
		*
		*  @remarks
		*    A disabled body that is connected through a joint to an enabled body will be automatically re-enabled at
		*/
		PLPHYSICS_API bool IsAutoFreeze() const;

		/**
		*  @brief
		*    Sets whether the body is frozen automatically or not
		*
		*  @param[in] bAutoFreeze
		*    'true' if the body is frozen automatically, else 'false'
		*/
		PLPHYSICS_API void SetAutoFreeze(bool bAutoFreeze = true);

		/**
		*  @brief
		*    Returns the freeze threshold
		*
		*  @param[out] fLinearVelocity
		*    Receives the linear velocity threshold
		*  @param[out] fAngularVelocity
		*    Receives the angular velocity threshold
		*  @param[out] nSteps
		*    Receives the number of steps the linear and angular velocity must be
		*    below the thresholds before the body is frozen
		*
		*  @note
		*    - nSteps may not be supported by each physics API, in this case, this setting has no effect
		*/
		PLPHYSICS_API void GetFreezeThreshold(float &fLinearVelocity, float &fAngularVelocity, PLGeneral::uint32 &nSteps) const;

		/**
		*  @brief
		*    Sets the freeze threshold
		*
		*  @param[in] fLinearVelocity
		*    Linear velocity threshold
		*  @param[in] fAngularVelocity
		*    Angular velocity threshold
		*  @param[in] nSteps
		*    Number of steps the linear and angular velocity must be below the thresholds
		*    before the body is frozen
		*
		*  @see
		*    - SetFreezeThreshold()
		*/
		PLPHYSICS_API void SetFreezeThreshold(float fLinearVelocity = 0.01f, float fAngularVelocity = 0.01f, PLGeneral::uint32 nSteps = 10);

		/**
		*  @brief
		*    Returns whether the body is currently frozen or not
		*
		*  @return
		*    'true' if the body is currently frozen, else 'false'
		*/
		PLPHYSICS_API bool IsFrozen() const;

		/**
		*  @brief
		*    Sets whether the body is currently frozen or not
		*
		*  @param[in] bFrozen
		*    'true' if the body is currently frozen, else 'false'
		*/
		PLPHYSICS_API void SetFrozen(bool bFrozen = true);

		/**
		*  @brief
		*    Returns whether the body can collide or not
		*
		*  @return
		*    'true' if the body can collide, else 'false'
		*/
		PLPHYSICS_API bool IsCollisionActive() const;

		/**
		*  @brief
		*    Sets whether the body can collide or not
		*
		*  @param[in] bActive
		*    'true' if the body can collide, else 'false'
		*/
		PLPHYSICS_API void SetCollisionActive(bool bActive = true);

		/**
		*  @brief
		*    Returns whether the body ignores the gravity or not
		*
		*  @return
		*    'false' if the body ignores the gravity, else 'true'
		*/
		PLPHYSICS_API bool GetUseGravity() const;

		/**
		*  @brief
		*    Sets whether the body ignores the gravity or not
		*
		*  @param[in] bUseGravity
		*    'false' if the body ignores the gravity, else 'true'
		*/
		PLPHYSICS_API void SetUseGravity(bool bUseGravity = true);

		/**
		*  @brief
		*    Returns the collision group the body is in
		*
		*  @return
		*    The collision group the body is in (0-31)
		*
		*  @see
		*    - World::GetGroupCollision()
		*/
		PLPHYSICS_API PLGeneral::uint8 GetCollisionGroup() const;

		/**
		*  @brief
		*    Sets the collision group the body is in
		*
		*  @param[in] nCollisionGroup
		*    The collision group the body is in (0-31)
		*
		*  @see
		*    - World::GetGroupCollision()
		*/
		PLPHYSICS_API void SetCollisionGroup(PLGeneral::uint8 nCollisionGroup = 0);

		/**
		*  @brief
		*    Returns the number of partner bodies
		*
		*  @return
		*    The number of partner bodies
		*
		*  @remarks
		*    Each body can have multiple partners. You can set certain flags for each
		*    of this pairs using World::SetBodyPairFlags(), for instance disabling contact
		*    generation between them. If a body pair flag is set to 0, the partners are removed
		*    automatically from each other.
		*
		*  @see
		*    - GetBodyPairFlags() & SetBodyPairFlags()
		*/
		PLPHYSICS_API PLGeneral::uint32 GetNumOfPartners() const;

		/**
		*  @brief
		*    Returns a partner body
		*
		*  @param[in] nIndex
		*    Index of the partner body to return
		*
		*  @return
		*    The requested partner body, a null pointer on error
		*
		*  @see
		*    - GetNumOfPartners()
		*/
		PLPHYSICS_API Body *GetPartner(PLGeneral::uint32 nIndex) const;


	//[-------------------------------------------------------]
	//[ Public virtual Element functions                      ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual bool IsBody() const;
		PLPHYSICS_API virtual bool IsJoint() const;
		PLPHYSICS_API virtual bool IsSensor() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] cBodyImpl
		*    Reference to the physics API specific body implementation
		*/
		PLPHYSICS_API Body(World &cWorld, BodyImpl &cBodyImpl);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		BodyImpl *m_pBodyImpl;	/**< Pointer to the physics API specific body implementation (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODY_H__
