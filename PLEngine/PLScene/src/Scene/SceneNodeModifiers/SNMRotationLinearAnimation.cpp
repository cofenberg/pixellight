/*********************************************************\
 *  File: SNMRotationLinearAnimation.cpp                 *
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
#include "PLScene/Scene/SceneNodeModifiers/SNMRotationLinearAnimation.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMRotationLinearAnimation)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMRotationLinearAnimation::SetFlags(uint32 nValue)
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
SNMRotationLinearAnimation::SNMRotationLinearAnimation(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	Velocity(this),
	EventHandlerUpdate(&SNMRotationLinearAnimation::NotifyUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMRotationLinearAnimation::~SNMRotationLinearAnimation()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMRotationLinearAnimation::NotifyUpdate()
{
	// Is the velocity not null?
	if (!Velocity.Get().IsNull()) {
		// Get rotation increase in Euler angles (degree)
		Vector3 vRot = Velocity.Get();
		vRot *= Timing::GetInstance()->GetTimeDifference();

		// Get a quaternion representation of the rotation increase
		Quaternion qRot;
		EulerAngles::ToQuaternion(float(vRot.x*Math::DegToRad), float(vRot.y*Math::DegToRad), float(vRot.z*Math::DegToRad), qRot);

		// Apply the rotation increase
		GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRot);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
