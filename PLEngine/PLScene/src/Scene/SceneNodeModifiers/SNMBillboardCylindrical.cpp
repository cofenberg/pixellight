/*********************************************************\
 *  File: SNMBillboardCylindrical.cpp                    *
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
#include "PLScene/Scene/SceneNodeModifiers/SNMBillboardCylindrical.h"


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
pl_implement_class(SNMBillboardCylindrical)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMBillboardCylindrical::SNMBillboardCylindrical(SceneNode &cSceneNode) : SNMBillboard(cSceneNode),
	UpVector(this),
	EventHandlerAddedToVisibilityTree(&SNMBillboardCylindrical::NotifyAddedToVisibilityTree, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMBillboardCylindrical::~SNMBillboardCylindrical()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMBillboardCylindrical::OnActivate(bool bActivate)
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
void SNMBillboardCylindrical::BuildTransformMatrix(const Matrix4x4 &mView, const Matrix4x4 &mWorld, Matrix3x4 &mTransform)
{
		  float x      = UpVector.Get().x;
		  float y      = UpVector.Get().y;
		  float z      = UpVector.Get().z;
	const float fTheta = float(-180.0f*Math::ATan2(mView.xz, mView.zz)/Math::Pi);
		  float d      = x*x + y*y + z*z;
	const float ct     = (float)Math::Cos(Math::DegToRad*fTheta);
	const float st     = (float)Math::Sin(Math::DegToRad*fTheta);

	// Normalize
	if (d > 0.0f) {
		d = 1.0f/d;
		x *= d;
		y *= d;
		z *= d;
	}

	// Get position
	Vector3 vPosition;
	vPosition *= mWorld;

	// Get scale
	const Vector3 &vScale = GetSceneNode().GetTransform().GetScale();

	// Construct the new world transform matrix (WITHOUT position!)
	mTransform.xx = vScale.x*(x*x + ct*(1.0f - x*x));         mTransform.xy = vScale.y*(x*y + ct*(0.0f - x*y) + st*-z); mTransform.xz = vScale.z*(x*z + ct*(0.0f - x*z) + st*y);
	mTransform.yx = vScale.x*(y*x + ct*(0.0f - y*x) + st*z);  mTransform.yy = vScale.y*(y*y + ct*(1.0f - y*y));         mTransform.yz = vScale.z*(y*z + ct*(0.0f - y*z) + st*-x);
	mTransform.zx = vScale.x*(z*x + ct*(0.0f - z*x) + st*-y); mTransform.zy = vScale.y*(z*y + ct*(0.0f - z*y) + st*x);  mTransform.zz = vScale.z*(z*z + ct*(1.0f - z*z));

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
void SNMBillboardCylindrical::NotifyAddedToVisibilityTree(VisNode &cVisNode)
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
