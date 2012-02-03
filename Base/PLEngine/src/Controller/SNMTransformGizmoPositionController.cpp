/*********************************************************\
 *  File: SNMTransformGizmoPositionController.cpp        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Timing.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLCore/Frontend/FrontendApplication.h>
#include <PLMath/Ray.h>
#include <PLMath/Intersect.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Devices/Mouse.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLEngine/Controller/SNMTransformGizmoPositionController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMTransformGizmoPositionController)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMTransformGizmoPositionController::SNMTransformGizmoPositionController(SceneNode &cSceneNode) : SNMTransformGizmoPosition(cSceneNode)
{
}

/**
*  @brief
*    Destructor
*/
SNMTransformGizmoPositionController::~SNMTransformGizmoPositionController()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SNMTransformGizmo functions  ]
//[-------------------------------------------------------]
void SNMTransformGizmoPositionController::UpdateSelection(Renderer &cRenderer, const VisNode &cVisNode)
{
	// Get the frontend instance
	Frontend &cFrontend = static_cast<FrontendApplication*>(CoreApplication::GetApplication())->GetFrontend();

	// Check whether or not the mouse is currently over the frontend
	if (cFrontend.IsMouseOver()) {
		// Get current mouse cursor position inside the widget
		const int nMousePosX = cFrontend.GetMousePositionX();
		const int nMousePosY = cFrontend.GetMousePositionY();

		// Calculate the clip space to object space matrix
		Matrix4x4 mClipSpaceToObjectSpace = m_mObjectSpaceToClipSpace;
		mClipSpaceToObjectSpace.Invert();

		// Check where the mouse is over
		// Get the ray starting from the camera position in direction of the mouse position
		Vector3 v2DPos(static_cast<float>(nMousePosX), static_cast<float>(nMousePosY), 0.0001f);
		Vector3 vCamPos = v2DPos.To3DCoordinate(mClipSpaceToObjectSpace, cRenderer.GetViewport());
		v2DPos.z = 0.9999f;
		Vector3 vEndPos = v2DPos.To3DCoordinate(mClipSpaceToObjectSpace, cRenderer.GetViewport());

		// Determine the current selected axis by using a picking ray
		Ray cRay;
		cRay.Set(vCamPos, vEndPos);
		m_nSelected = DetermineSelected(cRay);
	} else {
		m_nSelected = 0;
	}
}

void SNMTransformGizmoPositionController::PerformTransform()
{
	// Get the mouse device, there's no point in abstracting this in here because the transform gizmos are used through a mouse
	Mouse *pMouse = InputManager::GetInstance()->GetMouse();
	if (pMouse) {
		// General transform speed
		static const float TransformSpeed = 0.5f;

		// Get the current time difference
		const float fTimeDifference = Timing::GetInstance()->GetTimeDifference()*TransformSpeed;

		// Get timed transform speed along each mouse axis, this speed is "eaten up" as soon as it's used
		float fTransformSpeedX = fTimeDifference*pMouse->X.GetValue();
		float fTransformSpeedY = fTimeDifference*pMouse->Y.GetValue();

		// Get the current position of the owner scene node
		Vector3 vPosition = GetSceneNode().GetPosition();

		// Update position
		if (m_nSelected & XAxis) {
			vPosition.x -= fTransformSpeedX;
			fTransformSpeedX = 0.0f;
		}
		if (m_nSelected & YAxis) {
			vPosition.y -= fTransformSpeedY;
			fTransformSpeedY = 0.0f;
		}
		if (m_nSelected & ZAxis)
			vPosition.z -= fTransformSpeedX ? fTransformSpeedX : fTransformSpeedY;

		// Set the new position of the owner scene node
		GetSceneNode().MoveTo(vPosition);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine

