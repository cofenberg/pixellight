/*********************************************************\
 *  File: SNClipPrimitivePlane.cpp                       *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLVolume/Scene/SNClipPrimitivePlane.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNClipPrimitivePlane)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNClipPrimitivePlane::SNClipPrimitivePlane() :
	AABBMin(this),
	AABBMax(this)
{
	// Overwritten PLScene::SceneNode variables
	// -> In general a plane is infinite, but technically this scene node must have a limited dimension we can work with
	SetAABoundingBox(AABoundingBox(Vector3(-10.0f, -10.0f, -10.0f), Vector3(10.0f, 10.0f, 10.0f)));
}

/**
*  @brief
*    Destructor
*/
SNClipPrimitivePlane::~SNClipPrimitivePlane()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNode functions           ]
//[-------------------------------------------------------]
void SNClipPrimitivePlane::DrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNClipPrimitive::DrawDebug(cRenderer, pVisNode);

	// Draw the plane visualization?
	// -> Plane in scene node space, xy-plane clipping everything <0 on the z-axis
	if (pVisNode && !(GetDebugFlags() & DebugNoVisualization)) {
		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		cRenderer.SetRenderState(RenderState::BlendEnable,  true);

		// Invert clipping?
		const bool bInvertClipping = (GetFlags() & InvertClipping) != 0;

		// Draw the plane twice, so we can better see the clipping direction
		const float Scale = 10.0f;
		// When looking along +z
		// -> Positive
		cRenderer.GetDrawHelpers().DrawQuad(bInvertClipping ? DebugColorNegative.Get() : DebugColorPositive.Get(), Vector3(-Scale, Scale, 0.0f), Vector3(Scale, Scale, 0.0f), Vector3(-Scale, -Scale, 0.0f), Vector3(Scale, -Scale, 0.0f), pVisNode->GetWorldViewProjectionMatrix());
		// When looking along -z
		// -> Negative
		cRenderer.GetDrawHelpers().DrawQuad(bInvertClipping ? DebugColorPositive.Get() : DebugColorNegative.Get(), Vector3(Scale, Scale, 0.0f), Vector3(-Scale, Scale, 0.0f), Vector3(Scale, -Scale, 0.0f), Vector3(-Scale, -Scale, 0.0f), pVisNode->GetWorldViewProjectionMatrix());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
