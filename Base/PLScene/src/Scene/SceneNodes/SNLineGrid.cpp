/*********************************************************\
 *  File: SNLineGrid.cpp                                 *
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
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNLineGrid.h"


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
pl_implement_class(SNLineGrid)


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNLineGrid::SNLineGrid() :
	NumOfXLines(this),
	NumOfYLines(this),
	MainWidth(this),
	MainColor(this),
	MinorWidth(this),
	MinorColor(this),
	Flags(this),
	AABBMin(this),
	AABBMax(this)
{
	// Overwritten SceneNode variables
	SetAABoundingBox(AABoundingBox(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, 0.5f, 0.0f)));

	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawSolid | UseDrawTransparent));
}

/**
*  @brief
*    Destructor
*/
SNLineGrid::~SNLineGrid()
{
}

/**
*  @brief
*    Draws the grid
*/
void SNLineGrid::DrawGrid(Renderer &cRenderer, const VisNode &cVisNode)
{
	// Anything to do in here?
	if (!(GetFlags() & NoMainLines) || !(GetFlags() & NoMinorLines)) {
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();

		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		if (GetFlags() & NoDepthTest) {
			cRenderer.SetRenderState(RenderState::ZEnable,      false);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		}

		// Draw the main grid lines
		if (!(GetFlags() & NoMainLines)) {
			// Setup render states
			cRenderer.SetRenderState(RenderState::BlendEnable, MainColor.Get().a != 1.0f);

			// Draw the lines
			cDrawHelpers.DrawLine(MainColor.Get(), Vector3(-0.5f, 0.0f, 0.0f), Vector3(0.5f, 0.0f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MainWidth);
			cDrawHelpers.DrawLine(MainColor.Get(), Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MainWidth);
		}

		// Draw the minor grid lines
		if (!(GetFlags() & NoMinorLines)) {
			// Setup render states
			cRenderer.SetRenderState(RenderState::BlendEnable, MinorColor.Get().a != 1.0f);

			// Draw the main grid lines
			if (GetFlags() & NoMainLines) {
				// Draw the lines
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(-0.5f, 0.0f, 0.0f), Vector3(0.5f, 0.0f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
			}

			// Draw the lines along the x axis
			float fDelta = 0.5f/NumOfXLines;
			for (uint32 i=1; i<=NumOfXLines; i++) {
				const float fPosition = static_cast<float>(i*fDelta);
				// Positive axis
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(fPosition, -0.5f, 0.0f), Vector3(fPosition, 0.5f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
				// Negative axis
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(-fPosition, -0.5f, 0.0f), Vector3(-fPosition, 0.5f, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
			}

			// Draw the lines along the y axis
			fDelta = 0.5f/NumOfYLines;
			for (uint32 i=1; i<=NumOfYLines; i++) {
				const float fPosition = static_cast<float>(i*fDelta);
				// Positive axis
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(-0.5f, fPosition, 0.0f), Vector3(0.5f, fPosition, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
				// Negative axis
				cDrawHelpers.DrawLine(MinorColor.Get(), Vector3(-0.5f, -fPosition, 0.0f), Vector3(0.5f, -fPosition, 0.0f), cVisNode.GetWorldViewProjectionMatrix(), MinorWidth);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNLineGrid::DrawSolid(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Perform depth test?
	if (!(GetFlags() & NoDepthTest)) {
		// Call base implementation
		SceneNode::DrawSolid(cRenderer, pVisNode);

		// Draw the grid
		if (pVisNode)
			DrawGrid(cRenderer, *pVisNode);
	}
}

void SNLineGrid::DrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Perform depth test?
	if (GetFlags() & NoDepthTest) {
		// Call base implementation
		SceneNode::DrawTransparent(cRenderer, pVisNode);

		// Draw the grid
		if (pVisNode)
			DrawGrid(cRenderer, *pVisNode);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
