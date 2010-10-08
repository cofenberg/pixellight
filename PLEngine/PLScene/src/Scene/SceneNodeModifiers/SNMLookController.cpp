/*********************************************************\
 *  File: SNMLookController.cpp                          *
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
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/LookController.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMLookController.h"


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
pl_implement_class(SNMLookController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMLookController::SetFlags(uint32 nValue)
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
SNMLookController::SNMLookController(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	EventHandlerUpdate(&SNMLookController::NotifyUpdate, this),
	Flags(this),
	m_pController(new LookController())
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|UseRotationKey);

	// Connect to virtual input controller
	// [TODO] This is not quite the right place to do it, because we can not really know in here, what
	//        virtual controller is used by the application. Therefore, it should be the application that
	//        connects our controls to it's virtual controller, which will need some additional callback
	//        to connect to scene nodes that provide input controllers.
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if (pController) {
		m_pController->Connect("RotX",   pController->GetControl("RotX"));
		m_pController->Connect("RotY",   pController->GetControl("RotY"));
		m_pController->Connect("RotZ",   pController->GetControl("RotZ"));
		m_pController->Connect("Rotate", pController->GetControl("Button1"));
	}
}

/**
*  @brief
*    Destructor
*/
SNMLookController::~SNMLookController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNodeModifier functions            ]
//[-------------------------------------------------------]
Controller *SNMLookController::GetInputController() const
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
void SNMLookController::NotifyUpdate()
{
	// Check if input is active and whether or not the rotation key required and pressed
	if (m_pController->GetActive() && (!(GetFlags() & UseRotationKey) || m_pController->Rotate.IsPressed())) {
		// Get rotation
		const float fX = m_pController->RotX.GetValue();
		const float fY = m_pController->RotY.GetValue();
		const float fZ = m_pController->RotZ.GetValue();
		if (fX || fY || fZ) {
			// Get the current time difference
			const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

			// Get a quaternion representation of the rotation delta
			Quaternion qRotInc;
			EulerAngles::ToQuaternion(float(fX*Math::DegToRad*fTimeDiff),
									  float(fY*Math::DegToRad*fTimeDiff),
									  float(fZ*Math::DegToRad*fTimeDiff),
									  qRotInc);

			// Update rotation
			GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
