/*********************************************************\
 *  File: SNMPhysicsCharacterController.h                *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsCharacter.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SNMMeshUpdate;
}
namespace PLPhysics {
	class PhysicsCharacterController;
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
*    Basic PL physics character controller scene node modifier class
*
*  @remarks
*    When using the unchanged virtual standard controller:
*    Use a/w/d/s or cursor keys to walk, q/e to rotate and 'space' to jump. 'PageUp/PageDown'
*    to move upwards/downwards. Hold the 'shift'-key to speed up, hold the 'strg'-key to slow down.
*
*  @note
*    - Adds automatically a "PLScene::SNMMeshUpdate" scene node modifier (if there's not yet one) in order to frequently update the mesh
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
			NoJump  = 1<<3,	/**< Do not allow jumping */
			NoRun   = 1<<4,	/**< Do not allow running */
			NoCreep = 1<<5	/**< Do not allow creeping */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMPhysicsCharacter::EFlags)
			pl_enum_value(NoJump,	"Do not allow jumping")
			pl_enum_value(NoRun,	"Do not allow running")
			pl_enum_value(NoCreep,	"Do not allow creeping")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsCharacterController, "PLPhysics", PLPhysics::SNMPhysicsCharacter, "Basic PL physics character controller scene node modifier class")
		// Attributes
		pl_attribute(InputSemantic,			PLGeneral::String,		"",		ReadWrite,	DirectValue,	"Semantic of this input controller (e.g. \"Camera\")",												"")
		pl_attribute(YRotVelocity,			float,					0.0f,	ReadWrite,	DirectValue,	"Y rotation velocity, if 0, there's no rotation control",											"")
		pl_attribute(IdleAnimation,			PLGeneral::String,		"",		ReadWrite,	DirectValue,	"Idle animation",																					"")
		pl_attribute(IdleAnimationSpeed,	float,					24.0f,	ReadWrite,	DirectValue,	"Idle animation playback speed",																	"Min='0.0001'")
		pl_attribute(WalkAnimation,			PLGeneral::String,		"",		ReadWrite,	DirectValue,	"Walk animation",																					"")
		pl_attribute(WalkAnimationSpeed,	float,					24.0f,	ReadWrite,	DirectValue,	"Walk animation playback speed",																	"Min='0.0001'")
		pl_attribute(RunAnimationSpeed,		float,					35.0f,	ReadWrite,	DirectValue,	"Run animation playback speed (walk animation, just faster)",										"Min='0.0001'")
		pl_attribute(RotationNode,			PLGeneral::String,		"",		ReadWrite,	DirectValue,	"If empty, take the rotation of the owner node for movement, else the rotation of the given node",	"")
			// Overwritten PLScene::SceneNodeModifier attributes
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																							"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
	pl_class_end


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
	//[ Public virtual PLScene::SceneNodeModifier functions   ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual PLInput::Controller *GetInputController() const;


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void InformedOnInit();
		PLPHYSICS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void NotifyUpdate();

		/**
		*  @brief
		*    Returns a "PLScene::SNMMeshUpdate" instance from the owner scene node
		*
		*  @return
		*    A "PLScene::SNMMeshUpdate" instance
		*
		*  @note
		*    - If not already there, this method creates an instance of the "PLScene::SNMMeshUpdate" scene node modifier which frequently updates the mesh
		*/
		PLScene::SNMMeshUpdate *GetSNMMeshUpdate() const;


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool						m_bJumping;		/**< Are we currently jumping? */
		PhysicsCharacterController *m_pController;	/**< Physics character input controller instance, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_CHARACTERCONTROLLER_H__
