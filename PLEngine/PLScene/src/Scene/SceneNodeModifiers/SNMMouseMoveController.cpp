/*********************************************************\
 *  File: SNMMouseMoveController.cpp                     *
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
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMouseMoveController.h"


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
pl_implement_class(SNMMouseMoveController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMMouseMoveController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMPosition::SetFlags(nValue);

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
SNMMouseMoveController::SNMMouseMoveController(SceneNode &cSceneNode) : SNMPosition(cSceneNode),
	Speed(this),
	XSpeed(this),
	YSpeed(this),
	WheelSpeed(this),
	Flags(this),
	EventHandlerUpdate(&SNMMouseMoveController::NotifyUpdate, this)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|LeftMouseButton|NoRightMouseButton);
}

/**
*  @brief
*    Destructor
*/
SNMMouseMoveController::~SNMMouseMoveController()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMMouseMoveController::NotifyUpdate()
{
	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if ((pController && pController->GetActive()) || !pController) {
		// Get mouse input device
		Mouse *pMouse = InputManager::GetInstance()->GetMouse();
		if (pMouse) {
			// The mouse wheel can be used to move forward/backward
			float fWheelDelta = pMouse->Wheel.GetValue()*WheelSpeed;
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

				// Get the scene node
				SceneNode &cSceneNode = GetSceneNode();

				// Get direction vectors
				Vector3 vDirVector = cSceneNode.GetTransform().GetRotation().GetZAxis();
				if (GetFlags() & FlipZAxis)
					vDirVector.Invert();

				// Get movement vector
				Vector3 vMovement = vDirVector*fWheelDelta*Timing::GetInstance()->GetTimeDifference();

				// 'Move' to the new position
				if (!vMovement.IsNull())
					cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition()+vMovement);
			}

			// Is any mouse button pressed we are interested in?
			if ((!(GetFlags() & LeftMouseButton)    ||  pMouse->Left .IsPressed()) &&
				(!(GetFlags() & RightMouseButton)   ||  pMouse->Right.IsPressed()) &&
				(!(GetFlags() & NoLeftMouseButton)  || !pMouse->Left .IsPressed()) &&
				(!(GetFlags() & NoRightMouseButton) || !pMouse->Right.IsPressed()))
			{
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

					// Get the scene node
					SceneNode &cSceneNode = GetSceneNode();

					// Get direction vectors
					Vector3 vDirVector     = cSceneNode.GetTransform().GetRotation().GetZAxis();
					Vector3 vDirLeftVector = cSceneNode.GetTransform().GetRotation().GetXAxis();
					Vector3 vDirUpVector   = cSceneNode.GetTransform().GetRotation().GetYAxis();
					if (GetFlags() & FlipZAxis)
						vDirVector.Invert();
					if (GetFlags() & FlipXAxis)
						vDirLeftVector.Invert();
					if (GetFlags() & FlipYAxis)
						vDirUpVector.Invert();

					// Get movement vector
					Vector3 vMovement;
					if (fDeltaX)
						vMovement += vDirLeftVector*fDeltaX;
					if (pMouse->Middle.IsPressed()) {
						// Perform zoom
						if (fDeltaY)
							vMovement += vDirVector*fDeltaY;
					} else {
						if (fDeltaY)
							vMovement += vDirUpVector*fDeltaY;
					}

					// Set movement speed
					float fCurrentSpeed = Speed;

					// Get keyboard input device
					Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
					if (pKeyboard) {
						// Speed up
						if (pKeyboard->KeyShift.IsPressed())
							fCurrentSpeed *= 4;

						// Slow down
						else if (pKeyboard->KeyControl.IsPressed())
							fCurrentSpeed /= 4;
					}

					// Calculate the final movement vector
					vMovement *= fCurrentSpeed*Timing::GetInstance()->GetTimeDifference();

					// 'Move' to the new position
					if (!vMovement.IsNull())
						cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition()-vMovement);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
