/*********************************************************\
 *  File: SNMMoveController.cpp                          *
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
#include <PLInput/Input/Devices/Keyboard.h>
#include <PLInput/Input/Devices/SpaceMouse.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMoveController.h"


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
pl_implement_class(SNMMoveController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMMoveController::SetFlags(uint32 nValue)
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
SNMMoveController::SNMMoveController(SceneNode &cSceneNode) : SNMPosition(cSceneNode),
	Speed(this),
	SpaceMouseTranslationFactor(this),
	Flags(this),
	EventHandlerUpdate(&SNMMoveController::NotifyUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMMoveController::~SNMMoveController()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMMoveController::NotifyUpdate()
{
	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	// Get direction vectors
	const Quaternion &qRot = cSceneNode.GetTransform().GetRotation();
	Vector3 vDirLeftVector = qRot.GetXAxis();
	Vector3 vDirUpVector   = qRot.GetYAxis();
	Vector3 vDirVector     = qRot.GetZAxis();
	if (GetFlags() & FlipXAxis)
		vDirLeftVector.Invert();
	if (GetFlags() & FlipYAxis)
		vDirUpVector.Invert();
	if (GetFlags() & FlipZAxis)
		vDirVector.Invert();

	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if ((pController && pController->GetActive()) || !pController) {
		// Movement vector
		Vector3 vMovement;

		// Get keyboard input device
		Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
		if (pKeyboard) {
			// Forward/backward
			if (pKeyboard->KeyW.IsPressed() || pKeyboard->KeyUp.IsPressed())
				vMovement -= vDirVector;
			if (pKeyboard->KeyS.IsPressed() || pKeyboard->KeyDown.IsPressed())
				vMovement += vDirVector;

			// Left/right
			if (pKeyboard->KeyA.IsPressed() || pKeyboard->KeyLeft.IsPressed())
				vMovement -= vDirLeftVector;
			if (pKeyboard->KeyD.IsPressed() || pKeyboard->KeyRight.IsPressed())
				vMovement += vDirLeftVector;

			// Upward/downward
			if (pKeyboard->KeyPageUp.IsPressed())
				vMovement -= vDirUpVector;
			if (pKeyboard->KeyPageDown.IsPressed())
				vMovement += vDirUpVector;
		}

		// Get SpaceMouse device
		SpaceMouse *pSpaceMouse = (SpaceMouse*)InputManager::GetInstance()->GetDevice("SpaceMouse0");
		if (pSpaceMouse) {
			// Get translation
			const float fX = pSpaceMouse->TransX.GetValue() * SpaceMouseTranslationFactor;
			const float fY = pSpaceMouse->TransY.GetValue() * SpaceMouseTranslationFactor;
			const float fZ = pSpaceMouse->TransZ.GetValue() * SpaceMouseTranslationFactor;

			// Set new offset
			vMovement += vDirLeftVector * fX;
			vMovement += vDirUpVector   * fZ;
			vMovement += vDirVector     * fY;
		}

		// Set movement speed
		float fCurrentSpeed = Speed;

		// Check keyboard input device
		if (pKeyboard) {
			// Speed up
			if (pKeyboard->KeyShift.IsPressed())
				fCurrentSpeed *= 4;

			// Slow down
			else if (pKeyboard->KeyControl.IsPressed())
				fCurrentSpeed /= 4;
		}

		// Calculate movement
		vMovement *= fCurrentSpeed*Timing::GetInstance()->GetTimeDifference();

		// 'Move' to the new position
		if (!vMovement.IsNull())
			cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition()-vMovement);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
