/*********************************************************\
 *  File: SNMPositionLinearAnimation.cpp                 *
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
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMPositionLinearAnimation.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPositionLinearAnimation)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPositionLinearAnimation::SNMPositionLinearAnimation(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	AutoVector(this),
	Vector(this),
	Speed(this),
	EventHandlerUpdate(&SNMPositionLinearAnimation::OnUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMPositionLinearAnimation::~SNMPositionLinearAnimation()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMPositionLinearAnimation::OnActivate(bool bActivate)
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
void SNMPositionLinearAnimation::OnUpdate()
{
	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	// Get movement vector
	Vector3 vVector;
	switch (AutoVector) {
		case None:
			vVector = Vector.Get();
			break;

		case XAxis:
			vVector = cSceneNode.GetTransform().GetRotation().GetXAxis();
			break;

		case YAxis:
			vVector = cSceneNode.GetTransform().GetRotation().GetYAxis();
			break;

		case ZAxis:
			vVector = cSceneNode.GetTransform().GetRotation().GetZAxis();
			break;
	}

	// Apply vector, speed and time difference
	const Vector3 vPosInc = vVector*Speed*Timing::GetInstance()->GetTimeDifference();

	// 'Move' to the new position
	if (!vPosInc.IsNull())
		cSceneNode.MoveTo(cSceneNode.GetTransform().GetPosition()-vPosInc);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
