/*********************************************************\
 *  File: SRPDebugHierarchiesFixedFunctions.cpp          *
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
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneHierarchy.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/FixedFunctions/SRPDebugHierarchiesFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDebugHierarchiesFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDebugHierarchiesFixedFunctions::SRPDebugHierarchiesFixedFunctions()
{
}

/**
*  @brief
*    Destructor
*/
SRPDebugHierarchiesFixedFunctions::~SRPDebugHierarchiesFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws recursive
*/
void SRPDebugHierarchiesFixedFunctions::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	{ // Render all visible scene nodes of this scene container
		Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetEndIterator();
		while (cIterator.HasPrevious()) {
			// Get visibility node and scene node
			const VisNode   *pVisNode   = cIterator.Previous();
				  SceneNode *pSceneNode = pVisNode->GetSceneNode();
			if (pSceneNode) {
				// Is this scene node a portal?
				if (pVisNode->IsPortal()) {
					// Get the target cell visibility container
					const VisContainer *pVisCell = ((const VisPortal*)pVisNode)->GetTargetVisContainer();
					if (pVisCell) {
						// Draw the target cell
						if (pVisCell->GetCullQuery())
							DrawRec(cRenderer, *pVisCell->GetCullQuery());

						// Set the previous scissor rectangle
						cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
					}

				// Is this scene node a container? We do not need to check for cells because we will
				// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
				} else if (pVisNode->IsContainer()) {
					// Draw this container without special processing
					if (((const VisContainer*)pVisNode)->GetCullQuery())
						DrawRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

				// This must just be a quite boring scene node :)
				} else {
					// Ignore it :)
				}
			}
		}
	}

	// Set the current world matrix
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions)
		pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, cVisContainer.GetWorldMatrix());

	// Draw the hierachie of the scene container
	cCullQuery.GetSceneContainer().GetHierarchyInstance()->Draw(cRenderer, LineColor.Get(), cVisContainer.GetWorldViewProjectionMatrix(), 1.0f);
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDebugHierarchiesFixedFunctions::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Reset all render states to default
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::ZEnable,			 false);
	cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);
	cRenderer.SetRenderState(RenderState::BlendEnable,		 (LineColor.Get().a < 1.0f));
	cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);
	cRenderer.SetRenderState(RenderState::LineWidth,		 Tools::FloatToUInt32(LineWidth));

	// Draw recursive from back to front
	DrawRec(cRenderer, cCullQuery);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
