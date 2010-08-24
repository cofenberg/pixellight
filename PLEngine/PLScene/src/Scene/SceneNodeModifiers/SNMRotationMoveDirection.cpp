/*********************************************************\
 *  File: SNMRotationMoveDirection.cpp                   *
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
#include <PLMath/Matrix3x3.h>
#include <PLMath/EulerAngles.h>
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMRotationMoveDirection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMRotationMoveDirection)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMRotationMoveDirection::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMRotation::SetFlags(nValue);

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
SNMRotationMoveDirection::SNMRotationMoveDirection(SceneNode &cSceneNode) : SNMRotation(cSceneNode),
	Offset(this),
	UpVector(this),
	EventHandlerUpdate(&SNMRotationMoveDirection::NotifyUpdate, this),
	m_vLastPos(GetSceneNode().GetTransform().GetPosition())
{
}

/**
*  @brief
*    Destructor
*/
SNMRotationMoveDirection::~SNMRotationMoveDirection()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMRotationMoveDirection::NotifyUpdate()
{
	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	// Do ONLY update the rotation if the position difference is large enough. If this
	// is not done, the node will 'ugly flacker' if the difference is quite small.
	const Vector3 vDiff = cSceneNode.GetTransform().GetPosition()-m_vLastPos;
	if (vDiff.DotProduct(vDiff) > Math::Epsilon) {
		// Set rotation
		Matrix3x3 mRot;
		mRot.LookAt(cSceneNode.GetTransform().GetPosition(), m_vLastPos, UpVector.Get());
		mRot.Transpose();
		if (Offset.Get().IsNull())
			cSceneNode.GetTransform().SetRotation(Quaternion(mRot));
		else {
			// Get a quaternion representation of the rotation offset
			Quaternion qRotOffset;
			EulerAngles::ToQuaternion(float(Offset.Get().x*Math::DegToRad), float(Offset.Get().y*Math::DegToRad), float(Offset.Get().z*Math::DegToRad), qRotOffset);

			// Set new rotation
			cSceneNode.GetTransform().SetRotation(Quaternion(mRot)*qRotOffset);
		}

		// We can also use Vector3::GetRotationTo(), but the results are not always good - in the worst case
		// we will get 'extreme ugly flacker'
//		if (Offset.Get().IsNull())
//			cSceneNode.SetRotation(Vector3::UnitZ.GetRotationTo(vDiff));
//		else {
			// Get a quaternion representation of the rotation offset
//			Quaternion qRotOffset;
//			EulerAngles::ToQuaternion(float(Offset.Get().x*Math::DegToRad), float(Offset.Get().y*Math::DegToRad), float(Offset.Get().z*Math::DegToRad), qRotOffset);

			// Set new rotation
//			cSceneNode.SetRotation(Vector3::UnitZ.GetRotationTo(vDiff)*Quaternion(mRot)*qRotOffset);
//		}

		// Backup the current position
		m_vLastPos = cSceneNode.GetTransform().GetPosition();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
