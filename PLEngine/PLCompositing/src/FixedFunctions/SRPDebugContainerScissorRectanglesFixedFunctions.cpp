/*********************************************************\
 *  File: SRPDebugContainerScissorRectanglesFixedFunctions.cpp *
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
#include <PLGeneral/Tools/Tools.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/FixedFunctions/SRPDebugContainerScissorRectanglesFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDebugContainerScissorRectanglesFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDebugContainerScissorRectanglesFixedFunctions::SRPDebugContainerScissorRectanglesFixedFunctions()
{
}

/**
*  @brief
*    Destructor
*/
SRPDebugContainerScissorRectanglesFixedFunctions::~SRPDebugContainerScissorRectanglesFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws recursive
*/
void SRPDebugContainerScissorRectanglesFixedFunctions::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery, const Color4 &cColor) const
{
	// Draw the scissor rectangle
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();
	const Rectangle    &cRect         = cVisContainer.GetProjection().cRectangle;
	// [TODO] Draw helpers update (currently not working...)
	cRenderer.GetDrawHelpers().DrawQuad(cColor,
										Vector3(cRect.vMin.x, cRect.vMin.y, 0.0f),
										Vector3(cRect.vMax.x, cRect.vMin.y, 0.0f),
										Vector3(cRect.vMax.x, cRect.vMax.y, 0.0f),
										Vector3(cRect.vMin.x, cRect.vMax.y, 0.0f),
										Matrix4x4::Identity, 1.0f);

	// Recursive
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();
		if (pSceneNode) {
			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisContainer *pVisCell = static_cast<const VisPortal*>(pVisNode)->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					DrawRec(cRenderer, *pVisCell->GetCullQuery(), cColor);
				}

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (static_cast<const VisContainer*>(pVisNode)->GetCullQuery())
					DrawRec(cRenderer, *static_cast<const VisContainer*>(pVisNode)->GetCullQuery(), cColor);

			// This must just be a quite boring scene node :)
			} else {
				// Nothing to do here
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDebugContainerScissorRectanglesFixedFunctions::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Setup renderer states
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::ZEnable,			 false);
	cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);
	cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);
	cRenderer.SetRenderState(RenderState::LineWidth,		 Tools::FloatToUInt32(2.0f));

	// Set the initial world matrix
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions)
		pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, Matrix4x4::Identity);

	// Draw recursive from front to back
	const uint32 nFixedFillModeT = cRenderer.GetRenderState(RenderState::FixedFillMode);
	cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Line);

	// Begin 2D mode
	DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
	cDrawHelpers.Begin2DMode(0.0f, 0.0f, 0.0f, 0.0f);

		// Draw recursive
		DrawRec(cRenderer, cCullQuery, Color4(0.8f, 0.8f, 1.0f, 1.0f));

	// End 2D mode
	cDrawHelpers.End2DMode();

	// Restore fixed fill mode render state
	cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeT);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
