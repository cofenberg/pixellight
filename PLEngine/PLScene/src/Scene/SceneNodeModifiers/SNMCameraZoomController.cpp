/*********************************************************\
 *  File: SNMCameraZoomController.cpp                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/CameraZoomController.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMCameraZoomController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMCameraZoomController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMCameraZoomController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMCameraZoom::SetFlags(nValue);

	// Activate/deactivate the input controller
	m_pController->SetActive(IsActive());
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMCameraZoomController::SNMCameraZoomController(SceneNode &cSceneNode) : SNMCameraZoom(cSceneNode),
	EventHandlerControl(&SNMCameraZoomController::NotifyControl, this),
	m_pController(new CameraZoomController())
{
	// Connect input control event handler
	m_pController->OnControl.Connect(&EventHandlerControl);

	// Connect to virtual input controller
	// [TODO] This is not quite the right place to do it, because we can not really know in here, what
	//        virtual controller is used by the application. Therefore, it should be the application that
	//        connects our controls to it's virtual controller, which will need some additional callback
	//        to connect to scene nodes that provide input controllers.
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if (pController)
		m_pController->Connect("Zoom", pController->GetControl("Button2"));
}

/**
*  @brief
*    Destructor
*/
SNMCameraZoomController::~SNMCameraZoomController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNodeModifier functions            ]
//[-------------------------------------------------------]
Controller *SNMCameraZoomController::GetInputController() const
{
	return m_pController;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a control event has occured
*/
void SNMCameraZoomController::NotifyControl(Control *pControl)
{
	if (pControl == &m_pController->Zoom)
		ZoomFactor = ((Button*)pControl)->IsPressed() ? 1.0f : 0.0f;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
