/*********************************************************\
 *  File: SNMLookController.h                            *
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


#ifndef __PLENGINE_CONTROLLER_SNMLOOKCONTROLLER_H__
#define __PLENGINE_CONTROLLER_SNMLOOKCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeModifiers/SNMTransform.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class LookController;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node rotation input controller modifier class without 3D restriction
*
*  @note
*    - Primary intended for rapid prototyping
*    - Unrestricted 3D rotation via rotation quaternion
*    - Combine this modifier with for example "PLScene::SNMRotationFixRoll" to restrict the
*      rotation or directly use the specialized "PLEngine::SNMEgoLookController"-modifier
*/
class SNMLookController : public PLScene::SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (PLScene::SceneNodeModifier flags extension)
		*/
		enum EFlags {
			UseRotationKey = 1<<2	/**< If this flag is set, it's required to keep the rotation key pressed in order to rotate */
		};
		pl_enum(EFlags)
			pl_enum_base(PLScene::SNMTransform::EFlags)
			pl_enum_value(UseRotationKey, "If this flag is set, it's required to keep the rotation key pressed in order to rotate without 3D restriction")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNMLookController, "PLEngine", PLScene::SNMTransform, "Scene node rotation input controller modifier class")
		// Attributes
		pl_attribute(InputSemantic,	PLCore::String,			"",				ReadWrite,	DirectValue,	"Semantic of this input controller (e.g. \"Camera\")",	"")
			// Overwritten PLScene::SceneNodeModifier attributes
		pl_attribute(Flags,			pl_flag_type(EFlags),	UseRotationKey,	ReadWrite,	GetSet,			"Flags",												"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,	"Called when the scene node modifier needs to be updated",	"")
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
		PL_API SNMLookController(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNMLookController();


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNodeModifier functions   ]
	//[-------------------------------------------------------]
	public:
		PL_API virtual PLInput::Controller *GetInputController() const override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void InformedOnInit() override;
		PL_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Protected virtual SNMLookController functions         ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		PL_API virtual void OnUpdate();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		LookController *m_pController;	/**< Look input controller instance, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CONTROLLER_SNMLOOKCONTROLLER_H__
