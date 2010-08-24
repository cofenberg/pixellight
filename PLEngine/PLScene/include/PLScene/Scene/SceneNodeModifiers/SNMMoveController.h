/*********************************************************\
 *  File: SNMMoveController.h                            *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MOVECONTROLLER_H__
#define __PLSCENE_SCENENODEMODIFIER_MOVECONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMPosition.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple scene node move controller modifier class
*
*  @remarks
*    Use a/w/d/s or cursor keys to walk. 'PageUp/PageDown' to move upwards/downwards.
*    Hold the 'shift'-key to speed up, hold the 'strg'-key to slow down.
*
*  @note
*    - Normally only used for debugging
*    - 'SpaceMouse'-support
*/
class SNMMoveController : public SNMPosition {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			FlipXAxis = 1<<2,	/**< Flip x axis */
			FlipYAxis = 1<<3,	/**< Flip y axis */
			FlipZAxis = 1<<4	/**< Flip z axis */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMPosition::EFlags)
			pl_enum_value(FlipXAxis,	"Flip x axis")
			pl_enum_value(FlipYAxis,	"Flip y axis")
			pl_enum_value(FlipZAxis,	"Flip z axis")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMoveController, "PLScene", PLScene::SNMPosition, "Simple scene node move controller modifier class")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(Speed,							float,					1.0f,		ReadWrite,	DirectValue,	"Speed",								"Min='0.0001'")
		pl_attribute(SpaceMouseTranslationFactor,	float,					0.0025f,	ReadWrite,	DirectValue,	"Space mouse translation scale factor",	"Min='0.0001'")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,							pl_flag_type(EFlags),	0,			ReadWrite,	GetSet,			"Flags",								"")
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
		PLS_API SNMMoveController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMoveController();


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


#endif // __PLSCENE_SCENENODEMODIFIER_MOVECONTROLLER_H__
