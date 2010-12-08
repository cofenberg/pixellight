/*********************************************************\
 *  File: SNMCameraZoomController.h                      *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_CAMERAZOOMCONTROLLER_H__
#define __PLSCENE_SCENENODEMODIFIER_CAMERAZOOMCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodeModifiers/SNMCameraZoom.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class CameraZoomController;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node modifier class implementing camera zoom input control
*
*  @remarks
*    When using the unchanged virtual standard controller:
*    Hold the right mouse button to zoom.
*/
class SNMCameraZoomController : public SNMCameraZoom {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMCameraZoomController, "PLScene", PLScene::SNMCameraZoom, "Scene node modifier class implementing camera zoom input control")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(InputSemantic,	PLGeneral::String,	"",	ReadWrite,	DirectValue,	"Semantic of this input controller (e.g. \"Camera\")",	"")
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
		PLS_API SNMCameraZoomController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMCameraZoomController();


	//[-------------------------------------------------------]
	//[ Public virtual SceneNodeModifier functions            ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLInput::Controller *GetInputController() const;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void InformedOnInit();
		PLS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a control event has occured
		*
		*  @param[in] pControl
		*    The control causing the event
		*/
		void NotifyControl(PLInput::Control *pControl);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLInput::Control*> EventHandlerControl;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		CameraZoomController *m_pController;	/**< Camera zoom input controller instance, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_CAMERAZOOMCONTROLLER_H__
