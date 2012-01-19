/*********************************************************\
 *  File: SNMTransformGizmo.cpp                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLMath/Rectangle.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/Renderer.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMTransformGizmo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMTransformGizmo)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the current selected axis (see ESelected flags)
*/
uint32 SNMTransformGizmo::GetSelected() const
{
	return m_nSelected;
}

/**
*  @brief
*    Sets the current selected axis (see ESelected flags)
*/
void SNMTransformGizmo::SetSelected(uint32 nSelected)
{
	m_nSelected = nSelected;
}

/**
*  @brief
*    Returns whether the transform gizmo is currently in transform mode or not
*/
bool SNMTransformGizmo::IsTransformMode() const
{
	return m_bTransform;
}

/**
*  @brief
*    Sets whether the transform gizmo is currently in transform mode or not
*/
void SNMTransformGizmo::SetTransformMode(bool bTransformMode)
{
	m_bTransform = bTransformMode;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMTransformGizmo::SNMTransformGizmo(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	SlotOnDrawTransparent(this),
	SlotOnUpdate(this),
	m_nSelected(0),
	m_bTransform(false)
{
	// Set draw function flags
	cSceneNode.SetDrawFunctionFlags(static_cast<uint8>(cSceneNode.GetDrawFunctionFlags() | SceneNode::UseDrawTransparent));
}

/**
*  @brief
*    Destructor
*/
SNMTransformGizmo::~SNMTransformGizmo()
{
}

/**
*  @brief
*    Sets a scaled world matrix
*/
float SNMTransformGizmo::SetScaledWorldMatrix(Renderer &cRenderer, Matrix4x4 &mWorld)
{
	const float fWidthDelta  = 100.0f/cRenderer.GetViewport().GetWidth();
	const float fHeightDelta = 100.0f/cRenderer.GetViewport().GetHeight();

	float fScale = fWidthDelta;
	if (fHeightDelta < fScale)
		fScale = fHeightDelta;

	// Apply scale
	Matrix3x4 mScale;
	mScale.SetScaleMatrix(fScale, fScale, fScale);
	mWorld *= mScale;

	// Return scale
	return fScale;
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMTransformGizmo::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate) {
			GetSceneNode().SignalDrawTransparent.Connect(SlotOnDrawTransparent);
			pSceneContext->EventUpdate.Connect(SlotOnUpdate);
		} else {
			GetSceneNode().SignalDrawTransparent.Disconnect(SlotOnDrawTransparent);
			pSceneContext->EventUpdate.Disconnect(SlotOnUpdate);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on scene node transparent draw
*/
void SNMTransformGizmo::OnDrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Update gizmo
	if (!m_bTransform)
		UpdateSelection(cRenderer, *pVisNode);

	// Draw gizmo
	DrawGizmo(cRenderer, pVisNode);
}

/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMTransformGizmo::OnUpdate()
{
	// Update gizmo
	if (m_bTransform)
		PerformTransform();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
