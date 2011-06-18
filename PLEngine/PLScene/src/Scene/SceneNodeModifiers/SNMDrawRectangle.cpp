/*********************************************************\
 *  File: SNMDrawRectangle.cpp                           *
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
#include <PLMath/Matrix4x4.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMDrawRectangle.h"


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
pl_implement_class(SNMDrawRectangle)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMDrawRectangle::SNMDrawRectangle(SceneNode &cSceneNode) : SNMDraw(cSceneNode),
	Width(this),
	Color(this),
	Flags(this),
	SlotOnDrawTransparent(this)
{
	// Set draw function flags
	cSceneNode.SetDrawFunctionFlags(static_cast<uint8>(cSceneNode.GetDrawFunctionFlags() | SceneNode::UseDrawTransparent));
}

/**
*  @brief
*    Destructor
*/
SNMDrawRectangle::~SNMDrawRectangle()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMDrawRectangle::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	if (bActivate)
		GetSceneNode().SignalDrawTransparent.Connect(SlotOnDrawTransparent);
	else
		GetSceneNode().SignalDrawTransparent.Disconnect(SlotOnDrawTransparent);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on scene node transparent draw
*/
void SNMDrawRectangle::OnDrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Visibility node required
	if (pVisNode) {
		// Get the vertices of the bounding box
		Array<Vector3> vVertex(8);
		GetSceneNode().GetAABoundingBox().GetVertices(vVertex.GetData());

		// Get viewport parameters
		const uint32 nX      = static_cast<uint32>(cRenderer.GetViewport().GetX());
		const uint32 nY      = static_cast<uint32>(cRenderer.GetViewport().GetY());
		const uint32 nWidth  = static_cast<uint32>(cRenderer.GetViewport().GetWidth());
		const uint32 nHeight = static_cast<uint32>(cRenderer.GetViewport().GetHeight());

		// Calculate the scissor rectangle
		Rectangle cRectangle;
		cRectangle.ScreenRectangle(vVertex, true, pVisNode->GetWorldViewProjectionMatrix(), nX, nY, nWidth, nHeight);

		// Is the rectangle visible?
		if (cRectangle.GetWidth() || cRectangle.GetHeight()) {
			// Setup render states
			cRenderer.GetRendererContext().GetEffectManager().Use();
			cRenderer.SetRenderState(RenderState::ZEnable,      GetFlags() & DepthTest);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
			cRenderer.SetRenderState(RenderState::BlendEnable,  Color.Get().a != 1.0f);

			// Begin 2D mode
			DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
			cDrawHelpers.Begin2DMode(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nWidth), static_cast<float>(nHeight));

				// Draw the rectangle
				cDrawHelpers.DrawLine(Color.Get(), Vector2(cRectangle.vMin.x, cRectangle.vMin.y), Vector2(cRectangle.vMax.x, cRectangle.vMin.y), Width);
				cDrawHelpers.DrawLine(Color.Get(), Vector2(cRectangle.vMin.x, cRectangle.vMax.y), Vector2(cRectangle.vMax.x, cRectangle.vMax.y), Width);
				cDrawHelpers.DrawLine(Color.Get(), Vector2(cRectangle.vMin.x, cRectangle.vMin.y), Vector2(cRectangle.vMin.x, cRectangle.vMax.y), Width);
				cDrawHelpers.DrawLine(Color.Get(), Vector2(cRectangle.vMax.x, cRectangle.vMin.y), Vector2(cRectangle.vMax.x, cRectangle.vMax.y), Width);

			// End 2D mode
			cDrawHelpers.End2DMode();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
