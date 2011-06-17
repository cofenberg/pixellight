/*********************************************************\
 *  File: SNMOrbitingController.cpp                      *
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
#include <PLMath/EulerAngles.h>
#include "PLScene/Scene/SceneContext.h"
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMOrbitingController::SNMOrbitingController(SceneNode &cSceneNode) : SNMOrbiting(cSceneNode),
	InputSemantic(this),
	EventHandlerUpdate(&SNMOrbitingController::OnUpdate, this),
	m_pController(new OrbitingController())
{
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
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMOrbitingController::InformedOnInit()
{
	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneNode().GetSceneContext()->EventInputControllerFound(m_pController, InputSemantic);
}

void SNMOrbitingController::OnActivate(bool bActivate)
{
	// Call base implementation
	SNMOrbiting::OnActivate(bActivate);

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
*    Called when the scene node modifier needs to be updated
*/
void SNMOrbitingController::OnUpdate()
{
	// Check if input is active
	if (m_pController->GetActive()) {
		// Get the current speed
		float fSpeed = 1.0f;
		if (m_pController->Run.IsPressed())
			fSpeed *= 4.0f;
		else if (m_pController->Crouch.IsPressed())
			fSpeed /= 4.0f;
		const float fTimedSpeed = fSpeed*Timing::GetInstance()->GetTimeDifference();

		// Rotation
		if (m_pController->Rotate.IsPressed()) {
			float fX = m_pController->RotX.GetValue();
			float fY = m_pController->RotY.GetValue();
			float fZ = m_pController->RotZ.GetValue();
			if (fX || fY || fZ) {
				// Do we need to take the current time difference into account?
				fX *= m_pController->RotX.IsValueRelative() ? fSpeed : fTimedSpeed;
				fY *= m_pController->RotY.IsValueRelative() ? fSpeed : fTimedSpeed;
				fZ *= m_pController->RotZ.IsValueRelative() ? fSpeed : fTimedSpeed;

				// Get a quaternion representation of the rotation delta
				Quaternion qRotInc;
				EulerAngles::ToQuaternion(-static_cast<float>(fX*Math::DegToRad),
										  -static_cast<float>(fY*Math::DegToRad),
										  -static_cast<float>(fZ*Math::DegToRad),
										  qRotInc);

				// Update rotation
				GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
			}
		}

		// Pan
		if (m_pController->Pan.IsPressed()) {
			float fX = m_pController->PanX.GetValue();
			float fY = m_pController->PanY.GetValue();
			float fZ = m_pController->PanZ.GetValue();
			if (fX || fY || fZ) {
				// Do we need to take the current time difference into account?
				fX *= m_pController->PanX.IsValueRelative() ? fSpeed : fTimedSpeed;
				fY *= m_pController->PanY.IsValueRelative() ? fSpeed : fTimedSpeed;
				fZ *= m_pController->PanZ.IsValueRelative() ? fSpeed : fTimedSpeed;

				// Set pan
				Vector3 vPan = Pan.Get();
				vPan.x += fX;
				vPan.y += fY;
				vPan.z += fZ;
				Pan.Set(vPan);
			}
		}

		// Zoom
		if (m_pController->Zoom.IsPressed()) {
			float fZoomAxis = m_pController->ZoomAxis.GetValue();
			if (fZoomAxis) {
				// Do we need to take the current time difference into account?
				fZoomAxis *= m_pController->ZoomAxis.IsValueRelative() ? fSpeed : fTimedSpeed;

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
