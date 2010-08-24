/*********************************************************\
 *  File: SNMMouseLookController.h                       *
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
#include "PLScene/Scene/SceneNodeModifiers/SNMRotation.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class Control;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple scene node mouse look controller modifier class
*
*  @note
*    - Normally only used for debugging
*    - 'SpaceMouse'-support
*/
class SNMMouseLookController : public SNMRotation {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			FlipXAxis          = 1<<2,	/**< Flip x mouse axis */
			FlipYAxis          = 1<<3,	/**< Flip y mouse axis */
			SwapXYAxis         = 1<<4,	/**< Swap x/y mouse axis */
			LeftMouseButton    = 1<<5,	/**< The left mouse button must be hold down to rotate */
			RightMouseButton   = 1<<6,	/**< The right mouse button must be hold down to rotate */
			NoLeftMouseButton  = 1<<7,	/**< The left mouse button is not allowed to be hold down to rotate */
			NoRightMouseButton = 1<<8	/**< The right mouse button is not allowed to be hold down to rotate */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMRotation::EFlags)
			pl_enum_value(FlipXAxis,			"Flip x mouse axis")
			pl_enum_value(FlipYAxis,			"Flip y mouse axis")
			pl_enum_value(SwapXYAxis,			"Swap x/y mouse axis")
			pl_enum_value(LeftMouseButton,		"The left mouse button must be hold down to rotate")
			pl_enum_value(RightMouseButton,		"The right mouse button must be hold down to rotate")
			pl_enum_value(NoLeftMouseButton,	"The left mouse button is not allowed to be hold down to rotate")
			pl_enum_value(NoRightMouseButton,	"The right mouse button is not allowed to be hold down to rotate")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMouseLookController, "PLScene", PLScene::SNMRotation, "Simple scene node mouse look controller modifier class")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(XSpeed,	float,					0.3f,								ReadWrite,	DirectValue,	"X-axis speed (Mouse and SpaceMouse)",	"")
		pl_attribute(YSpeed,	float,					0.3f,								ReadWrite,	DirectValue,	"Y-axis speed (Mouse and SpaceMouse)",	"")
		pl_attribute(ZSpeed,	float,					0.5f,								ReadWrite,	DirectValue,	"Z-axis speed (SpaceMouse only)",		"")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,		pl_flag_type(EFlags),	LeftMouseButton|NoRightMouseButton,	ReadWrite,	GetSet,			"Flags",								"")
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
		PLS_API SNMMouseLookController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMouseLookController();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();

		/**
		*  @brief
		*    Called when a mouse control event has occured
		*
		*  @param[in] pControl
		*    The control causing the event
		*/
		void NotifyMouseControl(PLInput::Control *pControl);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>					EventHandlerUpdate;
		PLCore::EventHandler<PLInput::Control*> EventHandlerMouseControl;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fMouseDeltaX;
		float m_fMouseDeltaY;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MOUSELOOKCONTROLLER_H__
