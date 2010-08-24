/*********************************************************\
 *  File: SNMCameraZoom.cpp                              *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Devices/Mouse.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SNCamera.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMCameraZoom.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMCameraZoom)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMCameraZoom::SetFlags(uint32 nValue)
{
	// Call base implementation
	SceneNodeModifier::SetFlags(nValue);

	// Connect/disconnect event handler
	if (IsActive())
		GetSceneNode().EventUpdate.Connect(&EventHandlerUpdate);
	else
		GetSceneNode().EventUpdate.Disconnect(&EventHandlerUpdate);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMCameraZoom::SNMCameraZoom(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Zoom(this),
	ZoomSpeed(this),
	EventHandlerUpdate(&SNMCameraZoom::NotifyUpdate, this),
	m_fOriginalFOV(0.0f),
	m_fZoomFactor(0.0f)
{
	// Get the original FOV of the owner camera
	if (cSceneNode.IsCamera())
		m_fOriginalFOV = ((SNCamera&)cSceneNode).GetFOV();
}

/**
*  @brief
*    Destructor
*/
SNMCameraZoom::~SNMCameraZoom()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMCameraZoom::NotifyUpdate()
{
	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();
	if (cSceneNode.IsCamera()) {
		// Get the current time difference
		const float fTimeDiff = Timing::GetInstance()->GetTimeDifference()*ZoomSpeed;

		// Zoom mode active?
		bool bZoom = false;

		// Check if input is active
		// [TODO] Don't use devices directly, use a virtual controller instead
		Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
		if ((pController && pController->GetActive()) || !pController) {
			// Get mouse input device
			Mouse *pMouse = InputManager::GetInstance()->GetMouse();
			if (pMouse && pMouse->Right.IsPressed())
				bZoom = true;
		}

		// Update the zoom factor
		if (bZoom) {
			m_fZoomFactor += fTimeDiff;
			if (m_fZoomFactor > 1.0f)
				m_fZoomFactor = 1.0f;
		} else {
			m_fZoomFactor -= fTimeDiff;
			if (m_fZoomFactor < 0.0f)
				m_fZoomFactor = 0.0f;
		}

		// Set the current FOV of the owner camera
		((SNCamera&)cSceneNode).SetFOV(m_fOriginalFOV - m_fZoomFactor*Zoom);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
