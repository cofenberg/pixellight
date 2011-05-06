/*********************************************************\
 *  File: SNMLookController.cpp                          *
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMLookController::SNMLookController(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	InputSemantic(this),
	Flags(this),
	EventHandlerUpdate(&SNMLookController::NotifyUpdate, this),
	m_pController(new LookController())
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|UseRotationKey);
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
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMLookController::InformedOnInit()
{
	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneNode().GetSceneContext()->EventInputControllerFound.Emit(m_pController, InputSemantic);
}

void SNMLookController::OnActivate(bool bActivate)
{
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
void SNMLookController::NotifyUpdate()
{
	// [HACK][TODO] Currently it's not possible to define/script a control logic within the control connection to, for instance
	// "pass through" a rotation value from a space mouse, but "passing" movements from the mouse only if, for example, the left
	// mouse button is currently pressed (so we don't look around the every time when moving the mouse to, for instance, move
	// the mouse cursor to an ingame GUI widget). Because it's REALLY comfortable to use the space mouse, I added this hack so
	// the space mouse (provides us with absolute values!) can be used as expected during the last steps of the input system refactoring.
	const bool bSpaceMouseRotationHack = ((GetFlags() & UseRotationKey) && (!m_pController->RotX.IsValueRelative() || !m_pController->RotY.IsValueRelative()));

	// Check if input is active and whether or not the rotation key required and pressed
	if (m_pController->GetActive() && (!(GetFlags() & UseRotationKey) || m_pController->Rotate.IsPressed() || bSpaceMouseRotationHack)) {
		// Get rotation
		float fX = m_pController->RotX.GetValue();
		float fY = m_pController->RotY.GetValue();
		float fZ = m_pController->RotZ.GetValue();
		if (fX || fY || fZ) {
			// Get the current time difference
			const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

			// Do we need to take the current time difference into account?
			if (!m_pController->RotX.IsValueRelative())
				fX *= fTimeDiff;
			if (!m_pController->RotY.IsValueRelative())
				fY *= fTimeDiff;
			if (!m_pController->RotZ.IsValueRelative())
				fZ *= fTimeDiff;

			// Get a quaternion representation of the rotation delta
			Quaternion qRotInc;
			EulerAngles::ToQuaternion(static_cast<float>(fX*Math::DegToRad),
									  static_cast<float>(fY*Math::DegToRad),
									  static_cast<float>(fZ*Math::DegToRad),
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
