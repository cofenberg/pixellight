/*********************************************************\
 *  File: SNMCameraZoom.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Timing.h>
#include "PLScene/Scene/SNCamera.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMCameraZoom.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMCameraZoom)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMCameraZoom::SNMCameraZoom(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	ZoomDegree(this),
	ZoomFactor(this),
	ZoomSpeed(this),
	EventHandlerUpdate(&SNMCameraZoom::NotifyUpdate, this),
	m_fOriginalFOV(cSceneNode.IsCamera() ? ((SNCamera&)cSceneNode).GetFOV() : 0.0f),
	m_fCurrentZoomFactor(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMCameraZoom::~SNMCameraZoom()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMCameraZoom::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
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
		// Smooth camera zoom?
		if (ZoomSpeed) {
			// Get the current time difference
			const float fTimeDiff = Timing::GetInstance()->GetTimeDifference()*ZoomSpeed;

			// Update the current zoom factor
			if (m_fCurrentZoomFactor < ZoomFactor) {
				// Increase the current zoom factor
				m_fCurrentZoomFactor += fTimeDiff;
				if (m_fCurrentZoomFactor > ZoomFactor)
					m_fCurrentZoomFactor = ZoomFactor;
			} else {
				// Decrease the current zoom factor
				m_fCurrentZoomFactor -= fTimeDiff;
				if (m_fCurrentZoomFactor < ZoomFactor)
					m_fCurrentZoomFactor = ZoomFactor;
			}
		} else {
			// Set to target zoom factor at once
			m_fCurrentZoomFactor = ZoomFactor;
		}

		// Set the current FOV of the owner camera
		((SNCamera&)cSceneNode).SetFOV(m_fOriginalFOV - m_fCurrentZoomFactor*ZoomDegree);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
