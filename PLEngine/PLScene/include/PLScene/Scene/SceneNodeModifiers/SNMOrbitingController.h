/*********************************************************\
 *  File: SNMOrbitingController.h                        *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MOUSEORBITINGCONTROLLER_H__
#define __PLSCENE_SCENENODEMODIFIER_MOUSEORBITINGCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMOrbiting.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node modifier class rotating a scene node towards a target scene node using an input controller
*
*  @remarks
*    Hold the 'shift'-key to speed up, hold the 'strg'-key to slow down.
*
*  @note
*    - Normally only used for debugging
*    - 'SpaceMouse'-support
*/
class SNMOrbitingController : public SNMOrbiting {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			FlipXAxis				 = 1<<2,	/**< Flip x mouse axis */
			FlipYAxis				 = 1<<3,	/**< Flip y mouse axis */
			SwapXYAxis				 = 1<<4,	/**< Swap x/y mouse axis */
			RotateNoMouseButton		 = 1<<5,	/**< No mouse button must be hold down to rotate */
			RotateLeftMouseButton	 = 1<<6,	/**< The left mouse button must be hold down to rotate */
			RotateRightMouseButton	 = 1<<7,	/**< The right mouse button must be hold down to rotate */
			RotateMiddleMouseButton	 = 1<<8,	/**< The left mouse button must be hold down to rotate */
			ZoomNoMouseButton		 = 1<<9,	/**< No mouse button must be hold down to zoom */
			ZoomLeftMouseButton		 = 1<<10,	/**< The left mouse button must be hold down to zoom */
			ZoomRightMouseButton	 = 1<<11,	/**< The right mouse button must be hold down to zoom */
			ZoomMiddleMouseButton	 = 1<<12,	/**< The left mouse button must be hold down to zoom */
			ZoomMouseWheel			 = 1<<13,	/**< The mouse wheel can be used to zoom */
			PanNoMouseButton		 = 1<<14,	/**< No mouse button must be hold down to pan */
			PanLeftMouseButton		 = 1<<15,	/**< The left mouse button must be hold down to pan */
			PanRightMouseButton		 = 1<<16,	/**< The right mouse button must be hold down to pan */
			PanMiddleMouseButton	 = 1<<17	/**< The left mouse button must be hold down to pan */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMOrbiting::EFlags)
			pl_enum_value(FlipXAxis,				"Flip x mouse axis")
			pl_enum_value(FlipYAxis,				"Flip y mouse axis")
			pl_enum_value(SwapXYAxis,				"Swap x/y mouse axis")
			pl_enum_value(RotateNoMouseButton,		"No mouse button must be hold down to rotate")
			pl_enum_value(RotateLeftMouseButton,	"The left mouse button must be hold down to rotate")
			pl_enum_value(RotateRightMouseButton,	"The right mouse button must be hold down to rotate")
			pl_enum_value(RotateMiddleMouseButton,	"The left mouse button must be hold down to rotate")
			pl_enum_value(ZoomNoMouseButton,		"No mouse button must be hold down to zoom")
			pl_enum_value(ZoomLeftMouseButton,		"The left mouse button must be hold down to zoom")
			pl_enum_value(ZoomRightMouseButton,		"The right mouse button must be hold down to zoom")
			pl_enum_value(ZoomMiddleMouseButton,	"The left mouse button must be hold down to zoom")
			pl_enum_value(ZoomMouseWheel,			"The mouse wheel can be used to zoom")
			pl_enum_value(PanNoMouseButton,			"No mouse button must be hold down to pan")
			pl_enum_value(PanLeftMouseButton,		"The left mouse button must be hold down to pan")
			pl_enum_value(PanRightMouseButton,		"The right mouse button must be hold down to pan")
			pl_enum_value(PanMiddleMouseButton,		"The left mouse button must be hold down to pan")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMOrbitingController, "PLScene", PLScene::SNMOrbiting, "Scene node modifier class rotating a scene node towards a target scene node using an input controller")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(XSpeed,		float,					0.3f,																			ReadWrite,	DirectValue,	"Mouse look x axis speed",					"")
		pl_attribute(YSpeed,		float,					0.3f,																			ReadWrite,	DirectValue,	"Mouse look y axis speed",					"")
		pl_attribute(RotationSpeed,	float,					1.0f,																			ReadWrite,	DirectValue,	"Rotation speed",							"")
		pl_attribute(PanSpeed,		float,					1.0f,																			ReadWrite,	DirectValue,	"Pan speed",								"")
		pl_attribute(ZoomSpeed,		float,					1.0f,																			ReadWrite,	DirectValue,	"Zoom speed",								"")
		pl_attribute(WheelSpeed,	float,					0.1f,																			ReadWrite,	DirectValue,	"Mouse wheel speed for distance control",	"")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	RotateLeftMouseButton|ZoomRightMouseButton|ZoomMouseWheel|PanMiddleMouseButton,	ReadWrite,	GetSet,			"Flags",									"")
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
		PLS_API SNMOrbitingController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMOrbitingController();


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


#endif // __PLSCENE_SCENENODEMODIFIER_MOUSEORBITINGCONTROLLER_H__
