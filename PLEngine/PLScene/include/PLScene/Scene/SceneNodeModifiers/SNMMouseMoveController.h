/*********************************************************\
 *  File: SNMMouseMoveController.h                       *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MOUSELOOKCONTROLLER_H__
#define __PLSCENE_SCENENODEMODIFIER_MOUSELOOKCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMTransform.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple scene node mouse move controller modifier class
*
*  @note
*    - Normally only used for debugging
*/
class SNMMouseMoveController : public SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			FlipXAxis          =   4,	/**< Flip x mouse axis */
			FlipYAxis          =   8,	/**< Flip y mouse axis */
			FlipZAxis          =  16,	/**< Flip z mouse axis */
			SwapXYAxis         =  32,	/**< Swap x/y mouse axis */
			LeftMouseButton    =  64,	/**< The left mouse button must be hold down to move */
			RightMouseButton   = 128,	/**< The right mouse button must be hold down to move */
			NoLeftMouseButton  = 256,	/**< The left mouse button is not allowed to be hold down to move */
			NoRightMouseButton = 512	/**< The right mouse button is not allowed to be hold down to move */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNodeModifier::EFlags)
			pl_enum_value(FlipXAxis,			"Flip x mouse axis")
			pl_enum_value(FlipYAxis,			"Flip y mouse axis")
			pl_enum_value(FlipZAxis,			"Flip z mouse axis")
			pl_enum_value(SwapXYAxis,			"Swap x/y mouse axis")
			pl_enum_value(LeftMouseButton,		"The left mouse button must be hold down to move")
			pl_enum_value(RightMouseButton,		"The right mouse button must be hold down to move")
			pl_enum_value(NoLeftMouseButton,	"The left mouse button is not allowed to be hold down to move")
			pl_enum_value(NoRightMouseButton,	"The right mouse button is not allowed to be hold down to move")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMouseMoveController, "PLScene", PLScene::SNMTransform, "Simple scene node mouse move controller modifier class")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(Speed,			float,					1.0f,								ReadWrite,	DirectValue,	"Speed",										"Min='0.0001'")
		pl_attribute(XSpeed,		float,					0.3f,								ReadWrite,	DirectValue,	"Mouse move x axis speed",						"")
		pl_attribute(YSpeed,		float,					0.5f,								ReadWrite,	DirectValue,	"Mouse move y axis speed",						"")
		pl_attribute(WheelSpeed,	float,					0.1f,								ReadWrite,	DirectValue,	"Mouse wheel speed to move forward/backward",	"")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	LeftMouseButton|NoRightMouseButton,	ReadWrite,	GetSet,			"Flags",										"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);


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
		PLS_API SNMMouseMoveController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMouseMoveController();


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


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MOUSELOOKCONTROLLER_H__
