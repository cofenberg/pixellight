/*********************************************************\
 *  File: SNMMouseOrbitingController.cpp                 *
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
#include <PLMath/EulerAngles.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Devices/Mouse.h>
#include <PLInput/Input/Devices/Keyboard.h>
#include <PLInput/Input/Devices/SpaceMouse.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMouseOrbitingController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMouseOrbitingController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMMouseOrbitingController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMOrbiting::SetFlags(nValue);

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
SNMMouseOrbitingController::SNMMouseOrbitingController(SceneNode &cSceneNode) : SNMOrbiting(cSceneNode),
	XSpeed(this),
	YSpeed(this),
	RotationSpeed(this),
	PanSpeed(this),
	ZoomSpeed(this),
	WheelSpeed(this),
	Flags(this),
	EventHandlerUpdate(&SNMMouseOrbitingController::NotifyUpdate, this)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|RotateLeftMouseButton|ZoomRightMouseButton|ZoomMouseWheel|PanMiddleMouseButton);
}

/**
*  @brief
*    Destructor
*/
SNMMouseOrbitingController::~SNMMouseOrbitingController()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMMouseOrbitingController::NotifyUpdate()
{
	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if ((pController && pController->GetActive()) || !pController) {
		// Get mouse input device
		Mouse *pMouse = InputManager::GetInstance()->GetMouse();
		if (pMouse) {
			// The mouse wheel can be used to control the distance to the target
			if (GetFlags() & ZoomMouseWheel) {
				float fWheelDelta = pMouse->Wheel.GetValue() * WheelSpeed;
				if (fWheelDelta) {
					// Get keyboard input device
					Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
					if (pKeyboard) {
						// Speed up
						if (pKeyboard->KeyShift.IsPressed())
							fWheelDelta *= 4;

						// Slow down
						else if (pKeyboard->KeyControl.IsPressed())
							fWheelDelta /= 4;
					}

					// Set new distance
					SetDistance(GetDistance() - fWheelDelta);
				}
			}

			// Check mouse buttons
			bool bLeftButton   = pMouse->Left.IsPressed();
			bool bRightButton  = pMouse->Right.IsPressed();
			bool bMiddleButton = pMouse->Middle.IsPressed();
			if (bLeftButton && bRightButton) {
				// Emulate third mouse button
				bLeftButton		= false;
				bRightButton	= false;
				bMiddleButton	= true;
			}

			// Is any rotation mouse button pressed we are interested in?
			const bool bRotate = (RotationSpeed && (
								   ((GetFlags() & RotateLeftMouseButton)   && bLeftButton) ||
								   ((GetFlags() & RotateRightMouseButton)  && bRightButton) ||
								   ((GetFlags() & RotateMiddleMouseButton) && bMiddleButton) ||
								   ((GetFlags() & RotateNoMouseButton)) ) );

			// Is any pan mouse button pressed we are interested in?
			const bool bPan = (PanSpeed && (
								   ((GetFlags() & PanLeftMouseButton)   && bLeftButton) ||
								   ((GetFlags() & PanRightMouseButton)  && bRightButton) ||
								   ((GetFlags() & PanMiddleMouseButton) && bMiddleButton) ||
								   ((GetFlags() & PanNoMouseButton)) ) );

			// Is any zoom mouse button pressed we are interested in?
			const bool bZoom = (ZoomSpeed && (
								   ((GetFlags() & ZoomLeftMouseButton)   && bLeftButton) ||
								   ((GetFlags() & ZoomRightMouseButton)  && bRightButton) ||
								   ((GetFlags() & ZoomMiddleMouseButton) && bMiddleButton) ||
								   ((GetFlags() & ZoomNoMouseButton)) ) );

			// Rotate and/or pan and/or zoom?
			if (bRotate || bPan || bZoom) {
				// Get mouse movement
				float fDeltaX = pMouse->X.GetValue()*XSpeed;
				float fDeltaY = pMouse->Y.GetValue()*YSpeed;
				if (fDeltaX || fDeltaY) {
					// Flip axis
					if (GetFlags() & FlipXAxis)
						fDeltaX = -fDeltaX;
					if (GetFlags() & FlipYAxis)
						fDeltaY = -fDeltaY;

					// Swap x/y axis
					if (GetFlags() & SwapXYAxis) {
						const float fTemp = fDeltaX;
						fDeltaX = fDeltaY;
						fDeltaY = fTemp;
					}

					// Get keyboard input device
					Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
					if (pKeyboard) {
						// Speed up
						if (pKeyboard->KeyShift.IsPressed()) {
							fDeltaX *= 4;
							fDeltaY *= 4;

						// Slow down
						} else if (pKeyboard->KeyControl.IsPressed()) {
							fDeltaX /= 4;
							fDeltaY /= 4;
						}
					}

					// Rotate?
					if (bRotate) {
						// Get a quaternion representation of the rotation delta
						Quaternion qRotInc;
						EulerAngles::ToQuaternion(-float(fDeltaY*Math::DegToRad*RotationSpeed),
												   float(fDeltaX*Math::DegToRad*RotationSpeed),
												   0.0f, qRotInc);

						// Update rotation
						GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
					}

					// Pan?
					if (bPan) {
						Vector3 vPan = Pan.Get();
						if (fDeltaX)
							vPan.x -= fDeltaX*PanSpeed;
						if (fDeltaY)
							vPan.y -= fDeltaY*PanSpeed;
						Pan.Set(vPan);
					}

					// Zoom?
					if (bZoom) {
						// Set new distance
						SetDistance(GetDistance() - fDeltaY);
					}
				}
			}
		}

		// Get SpaceMouse device
		SpaceMouse *pSpaceMouse = (SpaceMouse*)InputManager::GetInstance()->GetDevice("SpaceMouse0");
		if (pSpaceMouse) {
			const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

			// Get rotation
				  float fX = pSpaceMouse->RotX.GetValue() * RotationSpeed * fTimeDiff;
				  float fY = pSpaceMouse->RotY.GetValue() * RotationSpeed * fTimeDiff;
			const float fZ = pSpaceMouse->RotZ.GetValue() * RotationSpeed * fTimeDiff;

			// Flip axis
			if (GetFlags() & FlipXAxis)
				fX = -fX;
			if (GetFlags() & FlipYAxis)
				fY = -fY;

			// Swap x/y axis
			if (GetFlags() & SwapXYAxis) {
				const float fTemp = fX;
				fX = fY;
				fY = fTemp;
			}

			// Get keyboard input device
			Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
			if (pKeyboard) {
				// Speed up
				if (pKeyboard->KeyShift.IsPressed()) {
					fX *= 4;
					fY *= 4;

				// Slow down
				} else if (pKeyboard->KeyControl.IsPressed()) {
					fX /= 4;
					fY /= 4;
				}
			}

			// Get a quaternion representation of the rotation delta
			Quaternion qRotInc;
			EulerAngles::ToQuaternion( float(fX*Math::DegToRad),
									   float(fZ*Math::DegToRad),
									   float(fY*Math::DegToRad),
									   qRotInc);

			// Update rotation
			GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);

			// Get translation
			float fTranslationX = pSpaceMouse->TransX.GetValue() * PanSpeed * fTimeDiff;
			float fTranslationY = pSpaceMouse->TransY.GetValue() * PanSpeed * fTimeDiff;
			float fTranslationZ = pSpaceMouse->TransZ.GetValue() * PanSpeed * fTimeDiff;

			// Do pan or zoom
			if (pSpaceMouse->Button1.IsPressed() || pSpaceMouse->Button2.IsPressed()) {
				// Flip axis
				if (GetFlags() & FlipXAxis)
					fTranslationX = -fTranslationX;
				if (GetFlags() & FlipYAxis)
					fTranslationY = -fTranslationY;

				// Swap x/y axis
				if (GetFlags() & SwapXYAxis) {
					const float fTemp = fTranslationX;
					fTranslationX = fTranslationY;
					fTranslationY = fTemp;
				}

				// Check keyboard input device
				if (pKeyboard) {
					// Speed up
					if (pKeyboard->KeyShift.IsPressed()) {
						fTranslationX *= 4;
						fTranslationY *= 4;

					// Slow down
					} else if (pKeyboard->KeyControl.IsPressed()) {
						fTranslationX /= 4;
						fTranslationY /= 4;
					}
				}

				// Set new offset
				Vector3 vPan = Pan.Get();
				vPan.x += fTranslationX;
				vPan.y += fTranslationY;
				Pan.Set(vPan);
			} else {
				// Set new distance
				SetDistance(GetDistance() + fTranslationZ);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
