/*********************************************************\
 *  File: SNMPhysicsCharacterController.h                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsCharacter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Basic PL physics character controller scene node modifier class
*
*  @remarks
*    Use a/w/d/s or cursor keys to walk, q/e to rotate and 'space' to jump. 'PageUp/PageDown'
*    to move upwards/downwards. Hold the 'shift'-key to speed up, hold the 'strg'-key to slow down.
*
*  @note
*    - Normally only used for debugging
*    - 'SpaceMouse'-support
*/
class SNMPhysicsCharacterController : public SNMPhysicsCharacter {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (PLScene::SceneNodeModifier flags extension)
		*/
		enum EFlags {
			FlipXAxis = 1<<3,	/**< Flip x axis */
			FlipZAxis = 1<<4,	/**< Flip z axis */
			NoJump    = 1<<5,	/**< Do not allow jumping */
			NoRun     = 1<<6,	/**< Do not allow running */
			NoCreep   = 1<<7	/**< Do not allow creeping */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMPhysicsCharacter::EFlags)
			pl_enum_value(FlipXAxis, "Flip x axis")
			pl_enum_value(FlipZAxis, "Flip z axis")
			pl_enum_value(NoJump,	 "Do not allow jumping")
			pl_enum_value(NoRun,	 "Do not allow running")
			pl_enum_value(NoCreep,	 "Do not allow creeping")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsCharacterController, "PLPhysics", PLPhysics::SNMPhysicsCharacter, "Basic PL physics character controller scene node modifier class")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(YRotVelocity,					float,					0.0f,		ReadWrite,	DirectValue,	"Y rotation velocity, if 0, there's no rotation control",											"")
		pl_attribute(SpaceMouseTranslationFactor,	float,					0.0025f,	ReadWrite,	DirectValue,	"Space mouse translation scale factor",																"Min='0.0001'")
		pl_attribute(IdleAnimation,					PLGeneral::String,		"",			ReadWrite,	DirectValue,	"Idle animation",																					"")
		pl_attribute(IdleAnimationSpeed,			float,					24.0f,		ReadWrite,	DirectValue,	"Idle animation playback speed",																	"Min='0.0001'")
		pl_attribute(WalkAnimation,					PLGeneral::String,		"",			ReadWrite,	DirectValue,	"Walk animation",																					"")
		pl_attribute(WalkAnimationSpeed,			float,					24.0f,		ReadWrite,	DirectValue,	"Walk animation playback speed",																	"Min='0.0001'")
		pl_attribute(RunAnimationSpeed,				float,					35.0f,		ReadWrite,	DirectValue,	"Run animation playback speed (walk animation, just faster)",										"Min='0.0001'")
		pl_attribute(RotationNode,					PLGeneral::String,		"",			ReadWrite,	DirectValue,	"If empty, take the rotation of the owner node for movement, else the rotation of the given node",	"")
		// Overwritten PLScene::SceneNodeModifier variables
		pl_attribute(Flags,							pl_flag_type(EFlags),	0,			ReadWrite,	GetSet,			"Flags",																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual void SetFlags(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsCharacterController(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsCharacterController();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bJumping;	/**< Are we currently jumping? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
