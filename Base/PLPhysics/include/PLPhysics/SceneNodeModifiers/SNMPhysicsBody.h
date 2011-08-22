/*********************************************************\
 *  File: SNMPhysicsBody.h                               *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_BODY_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_BODY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Body;
class ElementHandler;
class SCPhysicsWorld;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract physics body scene node modifier
*
*  @note
*    - During runtime, do NOT change the scale of the body scene node itself!
*    - This scene container MUST be within a SCPhysicsWorld scene container - else
*      this physics body will have no physics behavior at all
*    - If there's no mass, the body is static
*/
class SNMPhysicsBody : public SNMPhysics {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (PLScene::SceneNodeModifier flags extension)
		*/
		enum EFlags {
			InitUnfrozen = 1<<2,	/**< The body is not frozen on initialization */
			NoAutoFreeze = 1<<3,	/**< Do not freeze the body automatically */
			NoGravity    = 1<<4,	/**< The body is not influenced by gravity */
			NoRotation   = 1<<5		/**< Rotation is not used */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMPhysics::EFlags)
			pl_enum_value(InitUnfrozen,	"The body is not frozen on initialization")
			pl_enum_value(NoAutoFreeze,	"Do not freeze the body automatically")
			pl_enum_value(NoGravity,	"The body is not influenced by gravity")
			pl_enum_value(NoRotation,	"Rotation is not used")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsBody, "PLPhysics", PLPhysics::SNMPhysics, "Abstract physics body scene node modifier")
		// Attributes
		pl_attribute(Mass,				float,					0.0f,								ReadWrite,	GetSet,	"Mass of the physics body, 0=static body",				"Min='0.0'")
		pl_attribute(CenterOfMass,		PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Relative center of mass",								"")
		pl_attribute(PositionOffset,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Position offset relative to the scene node (=origin)",	"")
		pl_attribute(CollisionGroup,	PLCore::uint8,			0,									ReadWrite,	GetSet,	"The collision group the body is in (0-31)",			"Min='0' Max='31'")
			// Overwritten PLScene::SceneNodeModifier attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,									ReadWrite,	GetSet,	"Flags",												"")
		// Slots
		pl_slot_0(OnActive,		"Called when the scene node active state changed",		"")
		pl_slot_0(OnPosition,	"Called when the scene node position changed",			"")
		pl_slot_0(OnRotation,	"Called when the scene node rotation changed",			"")
		pl_slot_0(OnTransform,	"Called when the transform was changed by the physics",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API float GetMass() const;
		PLPHYSICS_API void SetMass(float fValue);
		PLPHYSICS_API const PLMath::Vector3 &GetCenterOfMass() const;
		PLPHYSICS_API void SetCenterOfMass(const PLMath::Vector3 &vValue);
		PLPHYSICS_API const PLMath::Vector3 &GetPositionOffset() const;
		PLPHYSICS_API void SetPositionOffset(const PLMath::Vector3 &vValue);
		PLPHYSICS_API PLCore::uint8 GetCollisionGroup() const;
		PLPHYSICS_API void SetCollisionGroup(PLCore::uint8 nValue);
		PLPHYSICS_API virtual void SetFlags(PLCore::uint32 nValue) override;	// From PLScene::SceneNodeModifier


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the PL physics world scene node container the physics body is in
		*
		*  @return
		*    The PL physics world scene node container the physics body is in, a null pointer on error
		*    (if that's the case, something went totally wrong :)
		*
		*  @note
		*    - This PL physics world scene node container can be another as the scene node container this scene node is in
		*/
		PLPHYSICS_API SCPhysicsWorld *GetWorldContainer() const;

		/**
		*  @brief
		*    Returns the PL physics body
		*
		*  @return
		*    The PL physics body, a null pointer on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICS_API Body *GetBody() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsBody(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsBody();

		/**
		*  @brief
		*    Recreates the PL physics body
		*/
		PLPHYSICS_API void RecreatePhysicsBody();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Protected virtual SNMPhysicsBody functions            ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Creates the PL physics body
		*/
		PLPHYSICS_API virtual void CreatePhysicsBody();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float			  m_fMass;				/**< Mass of the physics body, 0=static body */
		PLMath::Vector3	  m_vCenterOfMass;		/**< Relative center of mass */
		PLMath::Vector3	  m_vPositionOffset;	/**< Position offset relative to the scene node (=origin) */
		PLCore::uint8	  m_nCollisionGroup;	/**< The collision group the body is in (0-31) */
		SCPhysicsWorld   *m_pWorldContainer;	/**< The PL physics world scene node container the physics body is in, can be a null pointer */
		ElementHandler   *m_pBodyHandler;		/**< Holds the PL physics body (ALWAYS valid!) */
		bool			  m_bListening;			/**< Listening scene node position changes etc.? */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node active state changed
		*/
		void OnActive();

		/**
		*  @brief
		*    Called when the scene node position changed
		*/
		void OnPosition();

		/**
		*  @brief
		*    Called when the scene node rotation changed
		*/
		void OnRotation();

		/**
		*  @brief
		*    Called when the transform was changed by the physics
		*/
		void OnTransform();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void InformedOnInit();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_BODY_H__
