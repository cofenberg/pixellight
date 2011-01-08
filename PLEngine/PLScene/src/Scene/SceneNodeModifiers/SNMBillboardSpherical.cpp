/*********************************************************\
 *  File: SNMBillboardSpherical.cpp                      *
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
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix4x4.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMBillboardSpherical.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMBillboardSpherical)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMBillboardSpherical::SNMBillboardSpherical(SceneNode &cSceneNode) : SNMBillboard(cSceneNode),
	EventHandlerAddedToVisibilityTree(&SNMBillboardSpherical::NotifyAddedToVisibilityTree, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMBillboardSpherical::~SNMBillboardSpherical()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMBillboardSpherical::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	if (bActivate) {
		// Connect event handler
		GetSceneNode().EventAddedToVisibilityTree.Connect(&EventHandlerAddedToVisibilityTree);
	} else {
		// Disconnect event handler
		GetSceneNode().EventAddedToVisibilityTree.Disconnect(&EventHandlerAddedToVisibilityTree);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Builds a transform matrix
*/
void SNMBillboardSpherical::BuildTransformMatrix(const Matrix4x4 &mView, const Matrix4x4 &mWorld, Matrix3x4 &mTransform)
{
	// Get position
	Vector3 vPosition;
	vPosition *= mWorld;

	// Get scale
	const Vector3 &vScale = GetSceneNode().GetTransform().GetScale();
	
	// Construct the new world transform matrix, (WITHOUT position!) the rotation part is just the transposed rotation part of the given view matrix
	mTransform.xx = vScale.x*mView.xx; mTransform.xy = vScale.y*mView.yx; mTransform.xz = vScale.z*mView.zx;
	mTransform.yx = vScale.x*mView.xy; mTransform.yy = vScale.y*mView.yy; mTransform.yz = vScale.z*mView.zy;
	mTransform.zx = vScale.x*mView.xz; mTransform.zy = vScale.y*mView.yz; mTransform.zz = vScale.z*mView.zz;

	/*
	// [TODO] Currently, this doesn't look correct - do we really need/want a possible rotation offset?
	// Apply rotation (can be seen as offset in here)
	if (GetSceneNode().GetTransform().GetRotation() != Quaternion::Identity) {
		Matrix3x4 mRotation;
		GetSceneNode().GetTransform().GetRotation().ToRotationMatrix(mRotation);
		mTransform = mRotation*mTransform;
	}
	*/

	// Finally, set the position
	mTransform.xw = vPosition.x;
	mTransform.yw = vPosition.y;
	mTransform.zw = vPosition.z;
}

/**
*  @brief
*    Called when the owner scene node was added to a visibility tree
*/
void SNMBillboardSpherical::NotifyAddedToVisibilityTree(VisNode &cVisNode)
{
	// Get the new world transform matrix
	Matrix3x4 mTransform;
	BuildTransformMatrix(cVisNode.GetViewMatrix(), cVisNode.GetWorldMatrix(), mTransform);

	// Set the new world transform matrix of the visibility node
	cVisNode.SetWorldMatrix(mTransform);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
