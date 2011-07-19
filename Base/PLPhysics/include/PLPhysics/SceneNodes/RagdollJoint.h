/*********************************************************\
 *  File: RagdollJoint.h                                 *
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


#ifndef __PLPHYSICS_SCENENODES_RAGDOLLJOINT_H__
#define __PLPHYSICS_SCENENODES_RAGDOLLJOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Joint;
class SNRagdoll;
class ElementHandler;
struct JointController;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Ragdoll joint
*
*  @note
*    - If you changed some of the initial settings you have to recreate
*      the physics object in order to see the changes.
*/
class RagdollJoint {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Simulated joints will be either hinge (1-DOF) or universal (2-DOF)
		*/
		enum EType {
			Hinge     = 0,
			Universal = 1
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent ragdoll
		*/
		PLPHYSICS_API RagdollJoint(SNRagdoll *pParent);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~RagdollJoint();

		/**
		*  @brief
		*    Returns the PL physics joint
		*
		*  @return
		*    The PL physics joint, a null pointer on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICS_API Joint *GetJoint() const;

		/**
		*  @brief
		*    Sets the name of the joint
		*
		*  @param[in] sName
		*    New joint name
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe this name is already used within the ragdoll?)
		*/
		PLPHYSICS_API bool SetName(const PLCore::String &sName);

		/**
		*  @brief
		*    Creates the physics joint
		*
		*  @note
		*    - After this function the physics joint is in it's initial pose
		*/
		PLPHYSICS_API void CreatePhysicsJoint();

		/**
		*  @brief
		*    Destroys the physics joint
		*/
		PLPHYSICS_API void DestroyPhysicsJoint();

		/**
		*  @brief
		*    Returns the current joint anchor position
		*
		*  @param[out] vPosition
		*    Will receive the current joint anchor position
		*/
		PLPHYSICS_API void GetCurrentAnchor(PLMath::Vector3 &vPosition) const;

		/**
		*  @brief
		*    Computes and applies PD-controller torques to each body part assigned with this joint
		*
		*  @param[in] pController
		*    Joint controller
		*  @param[in] fMaxTorque
		*    Maximum torque
		*/
		PLPHYSICS_API void ApplyControlTorques(JointController *pController, float fMaxTorque);


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		SNRagdoll *m_pParentRagdoll;
		ElementHandler *m_pJointHandler;	/**< Holds the PL physics joint */

		PLCore::uint32 nIndex;

		PLCore::String sName;		/**< Name of this ragdoll joint */
		PLCore::String sAttached;	/**< Name of the attached ragdoll body */
		PLCore::String sParent;		/**< Name of the attached parent ragdoll body */

		PLCore::String sThisJointName; /**< Name of the orginal skeleton joint */
		PLCore::String sNextJointName; /**< Name of the next orginal skeleton joint which 'created' this joint */

		// Specifies whether attachedBody is connected to the world instead of another body part
		bool bAttachToWorld;

		EType nJointType;

		// Joint range of motion contraints for each axis (hinge joint only defined one range)
		float fLowJointRange1, fHighJointRange1;
		float fLowJointRange2, fHighJointRange2;

		// Anchor position of the joint
		PLMath::Vector3 vJointAnchor;

		// Axis that the joint rotates about (hinge joint only defines one axis)
		PLMath::Vector3 vRotAxis1;
		PLMath::Vector3 vRotAxis2;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Cap the torque generated by the controller to a reasonable value
		*
		*  @param[in, out] fTorque
		*    Torque to cap
		*  @param[in]      fMaxTorque
		*    Maximum torque
		*/
		PLPHYSICS_API void ClampTorque(float &fTorque, float fMaxTorque);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODES_RAGDOLLJOINT_H__
