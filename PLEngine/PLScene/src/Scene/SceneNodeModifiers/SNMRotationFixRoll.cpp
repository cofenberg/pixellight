/*********************************************************\
 *  File: SNMRotationFixRoll.cpp                         *
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
#include <PLMath/Matrix3x3.h>
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMRotationFixRoll.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMRotationFixRoll)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMRotationFixRoll::SetFlags(uint32 nValue)
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
SNMRotationFixRoll::SNMRotationFixRoll(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	UpVector(this),
	Speed(this),
	EventHandlerUpdate(&SNMRotationFixRoll::NotifyUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMRotationFixRoll::~SNMRotationFixRoll()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMRotationFixRoll::NotifyUpdate()
{
	// Get the scene node
	SceneNode &cSceneNode = GetSceneNode();

	/*
	// This will 'flat' the rotation for example for an up-vector of '0 1 0' on the xz-plane
	Vector3    vLocalY = cSceneNode.GetRotation()*UpVector.Get();
	Quaternion qQuat   = vLocalY.GetRotationTo(UpVector.Get());
	cSceneNode.SetRotation(qQuat*cSceneNode.GetRotation());
	*/
	Matrix3x3 mRot;
	mRot.LookAt(cSceneNode.GetTransform().GetPosition(), cSceneNode.GetTransform().GetPosition()-cSceneNode.GetTransform().GetRotation().GetZAxis(), UpVector.Get());
	Quaternion qQ = mRot;
	qQ.UnitInvert();
	if (Speed > 0.0f)
		qQ.Slerp(cSceneNode.GetTransform().GetRotation(), qQ, Timing::GetInstance()->GetTimeDifference()*Speed);
	cSceneNode.GetTransform().SetRotation(qQ);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
