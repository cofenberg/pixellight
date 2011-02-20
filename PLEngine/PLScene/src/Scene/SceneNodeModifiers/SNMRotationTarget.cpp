/*********************************************************\
 *  File: SNMRotationTarget.cpp                          *
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
#include <PLGeneral/Container/Stack.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/EulerAngles.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMRotationTarget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMRotationTarget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMRotationTarget::SNMRotationTarget(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	Target(this),
	Offset(this),
	UpVector(this),
	EventHandlerPositionUpdate(&SNMRotationTarget::NotifyPositionUpdate, this),
	EventHandlerDrawDebug	  (&SNMRotationTarget::NotifyDrawDebug,		 this)
{
}

/**
*  @brief
*    Destructor
*/
SNMRotationTarget::~SNMRotationTarget()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMRotationTarget::OnActivate(bool bActivate)
{
	// Update the rotation also on position change: If this is not done in here, too, the camera may 'shiver'
	// if it's rotation is changed 'before' it's position is updated

	// Connect/disconnect event handlers
	SceneNode &cSceneNode = GetSceneNode();
	if (bActivate) {
		// Connect event handlers
		cSceneNode.EventDrawDebug.Connect(&EventHandlerDrawDebug);
		cSceneNode.GetTransform().EventPosition.Connect(&EventHandlerPositionUpdate);
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Connect(&EventHandlerPositionUpdate);
	} else {
		// Disconnect event handlers
		cSceneNode.EventDrawDebug.Disconnect(&EventHandlerDrawDebug);
		cSceneNode.GetTransform().EventPosition.Disconnect(&EventHandlerPositionUpdate);
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Disconnect(&EventHandlerPositionUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the target position within the container space of the owner node
*/
bool SNMRotationTarget::GetTargetPosition(Vector3 &vPos) const
{
	// Target scene node given?
	if (Target.Get().GetLength()) {
		// Get the target scene node
		const SceneNode *pTarget;
		if (GetSceneNode().GetContainer())
			pTarget = GetSceneNode().GetContainer()->Get(Target.Get());
		else {
			// This must be the root :()
			pTarget = static_cast<const SceneContainer&>(GetSceneNode()).Get(Target.Get());
		}
		if (pTarget) {
			// Set the position of the attached node
			vPos = pTarget->GetTransform().GetPosition();

			// Are we in luck and the target is within the same container as the owner node?
			if (GetSceneNode().GetContainer() != pTarget->GetContainer()) {
				// Nope, we have to translate the position into the correct space :(
				SceneContainer *pContainer = pTarget->GetContainer();
				while (pContainer) {
					vPos *= pContainer->GetTransform().GetMatrix();
					pContainer = pContainer->GetContainer();
				}

				// To container space of the owner node
				pContainer = GetSceneNode().GetContainer();
				Stack<SceneContainer*> lstStack;
				while (pContainer) {
					lstStack.Push(pContainer);
					pContainer = pContainer->GetContainer();
				}
				while (lstStack.GetNumOfElements()) {
					pContainer = lstStack.Top();
					lstStack.Pop();
					vPos *= pContainer->GetTransform().GetInverseMatrix();
				}
			}

			// Done
			return true;
		}
	}

	// Error - no valid target scene node, no target rotation :(
	return false;
}

/**
*  @brief
*    Called on scene node debug draw
*/
void SNMRotationTarget::NotifyDrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Get the position of the target scene node
	Vector3 vTargetPos;
	if (GetTargetPosition(vTargetPos)) {
		vTargetPos *= GetSceneNode().GetTransform().GetInverseMatrix();

		// Draw a line to the target
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		cRenderer.GetDrawHelpers().DrawLine(Color4(0.0f, 1.0f, 1.0f, 1.0f), Vector3::Zero, vTargetPos, pVisNode->GetWorldViewProjectionMatrix(), 1.0f);
	}
}

/**
*  @brief
*    Called on scene node position change or update request
*/
void SNMRotationTarget::NotifyPositionUpdate()
{
	// Get the position of the target scene node
	Vector3 vTargetPos;
	if (GetTargetPosition(vTargetPos)) {
		// Get a quaternion representation of the rotation offset
		Quaternion qRotOffset;
		EulerAngles::ToQuaternion(static_cast<float>(Offset.Get().x*Math::DegToRad), static_cast<float>(Offset.Get().y*Math::DegToRad), static_cast<float>(Offset.Get().z*Math::DegToRad), qRotOffset);

		// Set rotation
		Matrix3x3 mRot;
		mRot.LookAt(vTargetPos, GetSceneNode().GetTransform().GetPosition(), UpVector.Get());
		GetSceneNode().GetTransform().SetRotation(Quaternion(mRot).GetUnitInverted()*qRotOffset);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
