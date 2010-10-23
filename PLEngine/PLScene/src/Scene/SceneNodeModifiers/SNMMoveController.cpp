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
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/MoveController.h"
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
	SNMTransform::SetFlags(nValue);

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
SNMMoveController::SNMMoveController(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	EventHandlerUpdate(&SNMMoveController::NotifyUpdate, this),
	InputSemantic(this),
	Speed(this),
	m_pController(new MoveController())
{
	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneNode().GetSceneContext()->EventInputControllerFound.Emit(m_pController, InputSemantic);
}

/**
*  @brief
*    Destructor
*/
SNMMoveController::~SNMMoveController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNodeModifier functions   ]
//[-------------------------------------------------------]
Controller *SNMMoveController::GetInputController() const
{
	return m_pController;
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
	const Vector3 vDirLeftVector = qRot.GetXAxis();
	const Vector3 vDirUpVector   = qRot.GetYAxis();
	const Vector3 vDirVector     = qRot.GetZAxis();

	// Check if input is active
	if (m_pController->GetActive()) {
		// Set movement speed and don't forget to apply the current time difference
		float fCurrentSpeed = Speed*Timing::GetInstance()->GetTimeDifference();

		// Speed up
		if (m_pController->Run.IsPressed())
			fCurrentSpeed *= 4;

		// Slow down
		else if (m_pController->Crouch.IsPressed())
			fCurrentSpeed /= 4;

		// Movement vector
		Vector3 vMovement;

		// Forward/backward
		if (m_pController->Forward.IsPressed())
			vMovement += vDirVector*fCurrentSpeed;
		if (m_pController->Backward.IsPressed())
			vMovement -= vDirVector*fCurrentSpeed;
		vMovement += vDirVector*(m_pController->TransZ.IsValueRelative() ? m_pController->TransZ.GetValue() : m_pController->TransZ.GetValue()*fCurrentSpeed);

		// Left/right
		if (m_pController->StrafeLeft.IsPressed())
			vMovement += vDirLeftVector*fCurrentSpeed;
		if (m_pController->StrafeRight.IsPressed())
			vMovement -= vDirLeftVector*fCurrentSpeed;
		vMovement += vDirLeftVector*(m_pController->TransX.IsValueRelative() ? m_pController->TransX.GetValue() : m_pController->TransX.GetValue()*fCurrentSpeed);

		// Upward/downward
		if (m_pController->Up.IsPressed())
			vMovement += vDirUpVector*fCurrentSpeed;
		if (m_pController->Down.IsPressed())
			vMovement -= vDirUpVector*fCurrentSpeed;
		vMovement += vDirUpVector*(m_pController->TransY.IsValueRelative() ? m_pController->TransY.GetValue() : m_pController->TransY.GetValue()*fCurrentSpeed);

		// 'Move' to the new position
		if (!vMovement.IsNull())
			cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition() + vMovement);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
