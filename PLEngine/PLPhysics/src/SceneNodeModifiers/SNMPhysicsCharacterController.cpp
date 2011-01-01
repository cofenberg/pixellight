/*********************************************************\
 *  File: SNMPhysicsCharacterController.cpp              *
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
#include <PLRenderer/Animation/Animation.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshAnimationManager.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/SNMesh.h>
#include "PLPhysics/SceneNodeModifiers/PhysicsCharacterController.h"
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsCharacterController::SNMPhysicsCharacterController(SceneNode &cSceneNode) : SNMPhysicsCharacter(cSceneNode),
	InputSemantic(this),
	YRotVelocity(this),
	IdleAnimation(this),
	IdleAnimationSpeed(this),
	WalkAnimation(this),
	WalkAnimationSpeed(this),
	RunAnimationSpeed(this),
	RotationNode(this),
	Flags(this),
	EventHandlerUpdate(&SNMPhysicsCharacterController::NotifyUpdate, this),
	m_bJumping(false),
	m_pController(new PhysicsCharacterController())
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsCharacterController::~SNMPhysicsCharacterController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNodeModifier functions   ]
//[-------------------------------------------------------]
Controller *SNMPhysicsCharacterController::GetInputController() const
{
	return m_pController;
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMPhysicsCharacterController::InformedOnInit()
{
	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneNode().GetSceneContext()->EventInputControllerFound.Emit(m_pController, InputSemantic);
}

void SNMPhysicsCharacterController::OnActivate(bool bActivate)
{
	// Call base implementation
	SNMPhysicsCharacter::OnActivate(bActivate);

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
*    Called when the scene node needs to be updated
*/
void SNMPhysicsCharacterController::NotifyUpdate()
{
	// Current time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference()*10;

	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	// Revert animation?
	bool bRevert = false;

	// Movement
	Vector3 vMovement;

	// Check if input is active
	if (m_pController->GetActive()) {
		// Get direction vectors from the owner node or a special rotation node
		const SceneNode *pRotationNode = &cSceneNode;
		if (RotationNode.Get().GetLength() && cSceneNode.GetContainer()) {
			const SceneNode *pSceneNode = cSceneNode.GetContainer()->Get(RotationNode.Get());
			if (pSceneNode)
				pRotationNode = pSceneNode;
		}
		const Quaternion &qRot = pRotationNode->GetTransform().GetRotation();
		const Vector3 vDirLeftVector = qRot.GetXAxis();
		const Vector3 vDirUpVector   = qRot.GetYAxis();
		const Vector3 vDirVector     = qRot.GetZAxis();

		// Forward/backward
		if (m_pController->Forward.IsPressed())
			vMovement += vDirVector;
		if (m_pController->Backward.IsPressed()) {
			vMovement -= vDirVector;
			bRevert = true;
		}
		// For relative input values, we need to cancel out the time difference applied within the base method "SetMovement()"
		if (!m_pController->TransZ.IsValueRelative() || !fTimeDiff)
			vMovement += vDirVector*m_pController->TransZ.GetValue();
		else
			vMovement += vDirVector*(1.0f/fTimeDiff)*m_pController->TransZ.GetValue();

		// Strafe left/right
		if (m_pController->StrafeLeft.IsPressed())
			vMovement += vDirLeftVector;
		if (m_pController->StrafeRight.IsPressed())
			vMovement -= vDirLeftVector;
		// For relative input values, we need to cancel out the time difference applied within the base method "SetMovement()"
		if (!m_pController->TransX.IsValueRelative() || !fTimeDiff)
			vMovement += vDirLeftVector*m_pController->TransX.GetValue();
		else
			vMovement += vDirLeftVector*(1.0f/fTimeDiff)*m_pController->TransX.GetValue();

		// Upward/downward
		if (GetFlags() & YMovement) {
			if (m_pController->Up.IsPressed())
				vMovement += vDirUpVector;
			if (m_pController->Down.IsPressed())
				vMovement -= vDirUpVector;

			// For relative input values, we need to cancel out the time difference applied within the base method "SetMovement()"
			if (!m_pController->TransY.IsValueRelative() || !fTimeDiff)
				vMovement += vDirUpVector*m_pController->TransY.GetValue();
			else
				vMovement += vDirUpVector*(1.0f/fTimeDiff)*m_pController->TransY.GetValue();
		}
	}

	// Set new movement vector
	SetMovement(vMovement);

	// Playback idle animation?
	bool bIdle = vMovement.IsNull();

	// Check if input is active
	if (m_pController->GetActive()) {
		// Rotation
		if (YRotVelocity) {
			float fYRotationChange = 0.0f;
			if (m_pController->Left.IsPressed()) {
				fYRotationChange += fTimeDiff*YRotVelocity;
				bRevert = true;
			}
			if (m_pController->Right.IsPressed())
				fYRotationChange -= fTimeDiff*YRotVelocity;
			fYRotationChange += m_pController->RotY.GetValue()*fTimeDiff*YRotVelocity;
			if (fYRotationChange) {
				Vector3 vRot = cSceneNode.GetRotation();
				vRot.y += fYRotationChange;
				cSceneNode.SetRotation(vRot);
				bIdle = false;
			}
		}

		// Jump
		if (!(GetFlags() & NoJump) && JumpForce && m_pController->Jump.IsPressed()) {
			if (!m_bJumping) {
				Jump();
				bIdle = false;
				m_bJumping = true;
			}
		} else {
			m_bJumping = false;
		}

		// Toggle running mode
		SetRunning(!(GetFlags() & NoRun) && m_pController->Run.IsPressed());

		// Toggle creeping mode
		SetCreeping(!(GetFlags() & NoCreep) && m_pController->Crouch.IsPressed());
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

					// Is the animation currently running?
					if (pAni->IsRunning()) {
						// Ensure that there's a "PLScene::SNMMeshUpdate" instance within the owner scene node which takes care of the frequent mesh update
						GetSNMMeshUpdate();
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Returns a "PLScene::SNMMeshUpdate" instance from the owner scene node
*/
SNMMeshUpdate *SNMPhysicsCharacterController::GetSNMMeshUpdate() const
{
	// Is there already an instance of the "PLScene::SNMMeshUpdate" scene node modifier?
	const static String sSNMMeshUpdate = "PLScene::SNMMeshUpdate";
	SNMMeshUpdate *pSNMMeshUpdate = (SNMMeshUpdate*)GetSceneNode().GetModifier(sSNMMeshUpdate);
	if (!pSNMMeshUpdate)
		pSNMMeshUpdate = (SNMMeshUpdate*)GetSceneNode().AddModifier(sSNMMeshUpdate, "Flags=\"Automatic\"");

	// Return the SNMMeshUpdate instance
	return pSNMMeshUpdate;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
