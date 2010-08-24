/*********************************************************\
 *  File: SNMMouseLookController.cpp                     *
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
#include <PLInput/Input/Devices/SpaceMouse.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMouseLookController.h"


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
pl_implement_class(SNMMouseLookController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMMouseLookController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMRotation::SetFlags(nValue);

	// Get mouse input device
	Mouse *pMouse = InputManager::GetInstance()->GetMouse();
	if (pMouse) {
		// Connect/disconnect event handler
		if (IsActive()) {
			GetSceneNode().EventUpdate.Connect(&EventHandlerUpdate);
			pMouse->OnControl.Connect(&EventHandlerMouseControl);

			// Reset mouse deltas
			m_fMouseDeltaX = m_fMouseDeltaY = 0.0f;
		} else {
			GetSceneNode().EventUpdate.Disconnect(&EventHandlerUpdate);
			pMouse->OnControl.Disconnect(&EventHandlerMouseControl);
		}
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMouseLookController::SNMMouseLookController(SceneNode &cSceneNode) : SNMRotation(cSceneNode),
	EventHandlerUpdate		(&SNMMouseLookController::NotifyUpdate,		  this),
	EventHandlerMouseControl(&SNMMouseLookController::NotifyMouseControl, this),
	XSpeed(this),
	YSpeed(this),
	ZSpeed(this),
	Flags(this),
	m_fMouseDeltaX(0.0f),
	m_fMouseDeltaY(0.0f)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|LeftMouseButton|NoRightMouseButton);
}

/**
*  @brief
*    Destructor
*/
SNMMouseLookController::~SNMMouseLookController()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMMouseLookController::NotifyUpdate()
{
	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if ((pController && pController->GetActive()) || !pController) {
		// Get mouse input device
		Mouse *pMouse = InputManager::GetInstance()->GetMouse();
		if (pMouse) {
			// Is any mouse button pressed we are interested in?
			if ((!(GetFlags() & LeftMouseButton)    ||  pMouse->Left .IsPressed()) &&
				(!(GetFlags() & RightMouseButton)   ||  pMouse->Right.IsPressed()) &&
				(!(GetFlags() & NoLeftMouseButton)  || !pMouse->Left .IsPressed()) &&
				(!(GetFlags() & NoRightMouseButton) || !pMouse->Right.IsPressed())) {
				// Get mouse movement
				float fDeltaX = m_fMouseDeltaX*XSpeed;
				float fDeltaY = m_fMouseDeltaY*YSpeed;
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

					// Get a quaternion representation of the rotation delta
					Quaternion qRotInc;
					EulerAngles::ToQuaternion(float(fDeltaY*Math::DegToRad), -float(fDeltaX*Math::DegToRad), 0.0f, qRotInc);

					// Update rotation
					GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
				}
			}
		}

		// Reset mouse deltas
		m_fMouseDeltaX = m_fMouseDeltaY = 0.0f;

		// Get SpaceMouse device
		SpaceMouse *pSpaceMouse = (SpaceMouse*)InputManager::GetInstance()->GetDevice("SpaceMouse0");
		if (pSpaceMouse) {
			// Get rotation
			float fX = pSpaceMouse->RotX.GetValue() * XSpeed * Timing::GetInstance()->GetTimeDifference();
			float fY = pSpaceMouse->RotY.GetValue() * YSpeed * Timing::GetInstance()->GetTimeDifference();
			float fZ = pSpaceMouse->RotZ.GetValue() * ZSpeed * Timing::GetInstance()->GetTimeDifference();

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

			// Get a quaternion representation of the rotation delta
			Quaternion qRotInc;
			EulerAngles::ToQuaternion(-float(fX*Math::DegToRad),
									  -float(fZ*Math::DegToRad),
									   float(fY*Math::DegToRad),
									   qRotInc);

			// Update rotation
			GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
		}
	}
}

/**
*  @brief
*    Called when a mouse control event has occured
*/
void SNMMouseLookController::NotifyMouseControl(Control *pControl)
{
	// Is the owner scene node active?
	if (GetSceneNode().IsActive()) {
		// Update mouse deltas
		if (pControl->GetName() == "X")
			m_fMouseDeltaX += ((Axis*)pControl)->GetValue();
		else if (pControl->GetName() == "Y")
			m_fMouseDeltaY += ((Axis*)pControl)->GetValue();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
