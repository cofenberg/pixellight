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
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
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
	Speed(this),
	EventHandlerUpdate(&SNMMoveController::NotifyUpdate, this),
	m_pController(new MoveController())
{
	// Connect to virtual input controller
	// [TODO] This is not quite the right place to do it, because we can not really know in here, what
	//        virtual controller is used by the application. Therefore, it should be the application that
	//        connects our controls to it's virtual controller, which will need some additional callback
	//        to connect to scene nodes that provide input controllers.
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if (pController) {
		m_pController->Connect("TransX",		pController->GetControl("TransX"));
		m_pController->Connect("TransY",		pController->GetControl("TransY"));
		m_pController->Connect("TransZ",		pController->GetControl("TransZ"));
		m_pController->Connect("Forward",		pController->GetControl("Forward"));
		m_pController->Connect("Backward",		pController->GetControl("Backward"));
		m_pController->Connect("StrafeLeft",	pController->GetControl("StrafeLeft"));
		m_pController->Connect("StrafeRight",	pController->GetControl("StrafeRight"));
		m_pController->Connect("Up",			pController->GetControl("Up"));
		m_pController->Connect("Down",			pController->GetControl("Down"));
		m_pController->Connect("Run",			pController->GetControl("Run"));
		m_pController->Connect("Crouch",		pController->GetControl("Crouch"));
	}
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
		// Movement vector
		Vector3 vMovement;

		// Forward/backward
		if (m_pController->Forward.IsPressed())
			vMovement += vDirVector;
		if (m_pController->Backward.IsPressed())
			vMovement -= vDirVector;
		vMovement += vDirVector*m_pController->TransZ.GetValue();

		// Left/right
		if (m_pController->StrafeLeft.IsPressed())
			vMovement += vDirLeftVector;
		if (m_pController->StrafeRight.IsPressed())
			vMovement -= vDirLeftVector;
		vMovement += vDirLeftVector*m_pController->TransX.GetValue();

		// Upward/downward
		if (m_pController->Up.IsPressed())
			vMovement += vDirUpVector;
		if (m_pController->Down.IsPressed())
			vMovement -= vDirUpVector;
		vMovement += vDirUpVector*m_pController->TransY.GetValue();

		// Set movement speed
		float fCurrentSpeed = Speed;

		// Speed up
		if (m_pController->Run.IsPressed())
			fCurrentSpeed *= 4;

		// Slow down
		else if (m_pController->Crouch.IsPressed())
			fCurrentSpeed /= 4;

		// Calculate movement
		vMovement *= fCurrentSpeed*Timing::GetInstance()->GetTimeDifference();

		// 'Move' to the new position
		if (!vMovement.IsNull())
			cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition() + vMovement);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
