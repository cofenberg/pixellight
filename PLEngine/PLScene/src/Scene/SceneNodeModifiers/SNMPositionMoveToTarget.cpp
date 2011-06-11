/*********************************************************\
 *  File: SNMPositionMoveToTarget.cpp                    *
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
#include <PLGeneral/Container/Stack.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMPositionMoveToTarget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPositionMoveToTarget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPositionMoveToTarget::SNMPositionMoveToTarget(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	Target(this),
	Speed(this),
	EventHandlerUpdate(&SNMPositionMoveToTarget::OnUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMPositionMoveToTarget::~SNMPositionMoveToTarget()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMPositionMoveToTarget::OnActivate(bool bActivate)
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
*    Returns the target position within the container space of the owner node
*/
bool SNMPositionMoveToTarget::GetTargetPosition(Vector3 &vPos) const
{
	// Get the target scene node
	const SceneNode *pTarget;
	if (GetSceneNode().GetContainer())
		pTarget = GetSceneNode().GetContainer()->GetByName(Target.Get());
	else {
		// This must be the root :()
		pTarget = static_cast<const SceneContainer&>(GetSceneNode()).GetByName(Target.Get());
	}
	if (!pTarget)
		return false; // Error - no valid target scene node, no target rotation :(

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

/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMPositionMoveToTarget::OnUpdate()
{
	// Get the position of the target scene node
	Vector3 vTargetPos;
	if (GetTargetPosition(vTargetPos)) {
		// Get the scene node
		SceneNode &cSceneNode = GetSceneNode();

		// 'Move' the scene node a bit towards the new desired position...
		const float fFactor = Timing::GetInstance()->GetTimeDifference()*Speed;
		cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition() + (vTargetPos - cSceneNode.GetTransform().GetPosition())*fFactor);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
