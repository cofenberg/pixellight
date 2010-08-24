/*********************************************************\
 *  File: SNMPhysicsCharacterController.cpp              *
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
#include <PLRenderer/Animation/Animation.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshAnimationManager.h>
#include "PLScene/Scene/SceneContext.h"
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/SNMesh.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsCharacterController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsCharacterController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMPhysicsCharacterController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMPhysicsCharacter::SetFlags(nValue);

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
SNMPhysicsCharacterController::SNMPhysicsCharacterController(SceneNode &cSceneNode) : SNMPhysicsCharacter(cSceneNode),
	YRotVelocity(this),
	SpaceMouseTranslationFactor(this),
	IdleAnimation(this),
	IdleAnimationSpeed(this),
	WalkAnimation(this),
	WalkAnimationSpeed(this),
	RunAnimationSpeed(this),
	RotationNode(this),
	Flags(this),
	EventHandlerUpdate(&SNMPhysicsCharacterController::NotifyUpdate, this),
	m_bJumping(false)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsCharacterController::~SNMPhysicsCharacterController()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMPhysicsCharacterController::NotifyUpdate()
{
	// Current time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference()*10;

	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	// Get direction vectors from the owner node or a special rotation node
	const SceneNode *pRotationNode = &cSceneNode;
	if (RotationNode.Get().GetLength() && cSceneNode.GetContainer()) {
		const SceneNode *pSceneNode = cSceneNode.GetContainer()->Get(RotationNode.Get());
		if (pSceneNode)
			pRotationNode = pSceneNode;
	}
	const Quaternion &qRot = pRotationNode->GetTransform().GetRotation();
	Vector3 vDirLeftVector = qRot.GetXAxis();
	Vector3 vDirUpVector   = qRot.GetYAxis();
	Vector3 vDirVector     = qRot.GetZAxis();
	if (GetFlags() & FlipZAxis)
		vDirVector.Invert();
	if (GetFlags() & FlipXAxis)
		vDirLeftVector.Invert();

	// Revert animation?
	bool bRevert = false;

	// Movement
	Vector3 vMovement;

	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	Controller *pController = (Controller*)GetSceneNode().GetSceneContext()->GetDefaultInputController();
	if ((pController && pController->GetActive()) || !pController) {
		// Get keyboard input device
		Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
		if (pKeyboard) {
			// Forward/backward
			if (pKeyboard->KeyW.IsPressed() || pKeyboard->KeyUp   .IsPressed())
				vMovement += vDirVector;
			if (pKeyboard->KeyS.IsPressed() || pKeyboard->KeyDown .IsPressed()) {
				vMovement -= vDirVector;
				bRevert = true;
			}

			// Left/right
			if (pKeyboard->KeyA.IsPressed() || pKeyboard->KeyLeft .IsPressed())
				vMovement += vDirLeftVector;
			if (pKeyboard->KeyD.IsPressed() || pKeyboard->KeyRight.IsPressed())
				vMovement -= vDirLeftVector;

			// Upward/downward
			if (GetFlags() & YMovement) {
				if (pKeyboard->KeyPageUp.IsPressed())
					vMovement += vDirUpVector;
				if (pKeyboard->KeyPageDown.IsPressed())
					vMovement -= vDirUpVector;
			}
		}

		// Get SpaceMouse device
		SpaceMouse *pSpaceMouse = (SpaceMouse*)InputManager::GetInstance()->GetDevice("SpaceMouse0");
		if (pSpaceMouse) {
			// Set new offset
			vMovement -= vDirLeftVector*(pSpaceMouse->TransX.GetValue()*SpaceMouseTranslationFactor);
			if (GetFlags() & YMovement)
				vMovement -= vDirUpVector*(pSpaceMouse->TransZ.GetValue()*SpaceMouseTranslationFactor);
			vMovement -= vDirVector*(pSpaceMouse->TransY.GetValue()*SpaceMouseTranslationFactor);
		}
	}

	// Set new movement vector
	SetMovement(vMovement);

	// Playback idle animation?
	bool bIdle = vMovement.IsNull();

	// Check if input is active
	// [TODO] Don't use devices directly, use a virtual controller instead
	if ((pController && pController->GetActive()) || !pController) {
		// Get keyboard input device
		Keyboard *pKeyboard = InputManager::GetInstance()->GetKeyboard();
		if (pKeyboard) {
			// Rotation
			if (YRotVelocity && (pKeyboard->KeyQ.IsPressed() || pKeyboard->KeyE.IsPressed())) {
				Vector3 vRot = cSceneNode.GetRotation();
				if (pKeyboard->KeyQ.IsPressed()) {
					vRot.y += fTimeDiff*YRotVelocity;
					bRevert = true;
				}
				if (pKeyboard->KeyE.IsPressed())
					vRot.y -= fTimeDiff*YRotVelocity;
				cSceneNode.SetRotation(vRot);
				bIdle = false;
			}

			// Jump
			if (!(GetFlags() & NoJump) && JumpForce && pKeyboard->KeySpace.IsPressed()) {
				if (!m_bJumping) {
					Jump();
					bIdle = false;
					m_bJumping = true;
				}
			} else {
				m_bJumping = false;
			}

			// Toggle running mode
			SetRunning(!(GetFlags() & NoRun) && pKeyboard->KeyShift.IsPressed());

			// Toggle creeping mode
			SetCreeping(!(GetFlags() & NoCreep) && pKeyboard->KeyControl.IsPressed());
		}
	}

	// Setup character animation
	MeshHandler *pMeshHandler = ((SNMesh&)cSceneNode).GetMeshHandler();
	if (pMeshHandler) {
		MeshAnimationManager *pAniManager = pMeshHandler->GetMeshAnimationManager();
		if (!pAniManager)
			pAniManager = pMeshHandler->CreateMeshAnimationManager();
		if (pAniManager) {
			if (bIdle) {
				if (IdleAnimation.Get().GetLength() && !pAniManager->Get(IdleAnimation.Get())) {
					pAniManager->Clear();
					// Start 'idle'-animation
					AnimationInfo *pAniInfo = pMeshHandler->GetAnimationInfo(IdleAnimation.Get());
					Animation     *pAni     = pAniManager->Create(IdleAnimation.Get());
					if (pAniInfo && pAni) {
						pAni->Start(*pAniInfo, true);
						pAni->SetSpeed(IdleAnimationSpeed);
					}
				}
			} else {
				Animation *pAni = pAniManager->Get(WalkAnimation.Get());
				if (!pAni && WalkAnimation.Get().GetLength()) {
					pAniManager->Clear();
					// Start 'walk'-animation
					AnimationInfo *pAniInfo = pMeshHandler->GetAnimationInfo(WalkAnimation.Get());
					if (pAniInfo) {
						pAni = pAniManager->Create(WalkAnimation.Get());
						if (pAni)
							pAni->Start(*pAniInfo, true);
					}
				}
				if (pAni) {
					if (bRevert)
						pAni->SetSpeed(IsRunning() ? -RunAnimationSpeed : -WalkAnimationSpeed);
					else
						pAni->SetSpeed(IsRunning() ?  RunAnimationSpeed.GetFloat() :  WalkAnimationSpeed);
					pAni->SetWeight(IsRunning() ? 1.5f : 1.0f);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
