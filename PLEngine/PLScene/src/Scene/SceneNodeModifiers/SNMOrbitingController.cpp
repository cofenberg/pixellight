/*********************************************************\
 *  File: SNMOrbitingController.cpp                      *
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
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/OrbitingController.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMOrbitingController.h"


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
pl_implement_class(SNMOrbitingController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMOrbitingController::SetFlags(uint32 nValue)
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
SNMOrbitingController::SNMOrbitingController(SceneNode &cSceneNode) : SNMOrbiting(cSceneNode),
	EventHandlerUpdate(&SNMOrbitingController::NotifyUpdate, this),
	m_pController(new OrbitingController())
{
	// Connect to virtual input controller
	// [TODO] This is not quite the right place to do it, because we can not really know in here, what
	//        virtual controller is used by the application. Therefore, it should be the application that
	//        connects our controls to it's virtual controller, which will need some additional callback
	//        to connect to scene nodes that provide input controllers.
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if (pController) {
		m_pController->Connect("RotX",		pController->GetControl("RotX"));
		m_pController->Connect("RotY",		pController->GetControl("RotY"));
		m_pController->Connect("RotZ",		pController->GetControl("RotZ"));
		m_pController->Connect("TransX",	pController->GetControl("TransX"));
		m_pController->Connect("TransX",	pController->GetControl("MouseX"), -1.0f);
		m_pController->Connect("TransY",	pController->GetControl("TransY"));
		m_pController->Connect("TransY",	pController->GetControl("MouseY"), -1.0f);
		m_pController->Connect("TransZ",	pController->GetControl("TransZ"));
		m_pController->Connect("ZoomAxis",	pController->GetControl("MouseWheel"));
		m_pController->Connect("ZoomAxis",	pController->GetControl("TransZ"));
		m_pController->Connect("ZoomAxis",	pController->GetControl("MouseY"), -1.0f);
		m_pController->Connect("Rotate",	pController->GetControl("Button1"));
		m_pController->Connect("Pan",		pController->GetControl("Button3"));
		m_pController->Connect("Zoom",		pController->GetControl("Button2"));
		m_pController->Connect("SpeedUp",	pController->GetControl("Run"));
		m_pController->Connect("SlowDown",	pController->GetControl("Crouch"));
	}
}

/**
*  @brief
*    Destructor
*/
SNMOrbitingController::~SNMOrbitingController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNodeModifier functions            ]
//[-------------------------------------------------------]
Controller *SNMOrbitingController::GetInputController() const
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
void SNMOrbitingController::NotifyUpdate()
{
	// Check if input is active
	if (m_pController->GetActive()) {
		// Get the current speed
		float fCurrentSpeed = Timing::GetInstance()->GetTimeDifference();
		if (m_pController->SpeedUp.IsPressed())
			fCurrentSpeed *= 4.0f;
		else if (m_pController->SlowDown.IsPressed())
			fCurrentSpeed /= 4.0f;

		// Rotation
		if (m_pController->Rotate.IsPressed()) {
			const float fX = m_pController->RotX.GetValue()*fCurrentSpeed;
			const float fY = m_pController->RotY.GetValue()*fCurrentSpeed;
			const float fZ = m_pController->RotZ.GetValue()*fCurrentSpeed;
			if (fX || fY || fZ) {
				// Get a quaternion representation of the rotation delta
				Quaternion qRotInc;
				EulerAngles::ToQuaternion(-float(fX*Math::DegToRad),
										  -float(fY*Math::DegToRad),
										  -float(fZ*Math::DegToRad),
										  qRotInc);

				// Update rotation
				GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
			}
		}

		// Pan
		if (m_pController->Pan.IsPressed()) {
			const float fX = m_pController->TransX.GetValue()*fCurrentSpeed;
			const float fY = m_pController->TransY.GetValue()*fCurrentSpeed;
			const float fZ = m_pController->TransZ.GetValue()*fCurrentSpeed;
			if (fX || fY || fZ) {
				Vector3 vPan = Pan.Get();
				vPan.x += fX;
				vPan.y += fY;
				vPan.z += fZ;
				Pan.Set(vPan);
			}
		}

		// Zoom
		if (m_pController->Zoom.IsPressed()) {
			const float fZoomAxis = m_pController->ZoomAxis.GetValue()*fCurrentSpeed;
			if (fZoomAxis) {
				// Set new distance
				SetDistance(GetDistance() - fZoomAxis);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
