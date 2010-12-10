/*********************************************************\
 *  File: SRPFunctionsPost.cpp                           *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/SRPFunctionsPost.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPFunctionsPost)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPFunctionsPost::SRPFunctionsPost()
{
}

/**
*  @brief
*    Destructor
*/
SRPFunctionsPost::~SRPFunctionsPost()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws recursive
*/
void SRPFunctionsPost::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery) const
{
	// Get scene container
	SceneContainer     &cSceneContainer = cCullQuery.GetSceneContainer();
	const VisContainer &cVisContainer   = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	// Draw the container scene node
	if (cSceneContainer.GetDrawFunctionFlags() & SceneNode::UseDrawPost)
		cSceneContainer.DrawPost(cRenderer, &cVisContainer);

	// Render all visible scene nodes of this scene container
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();
		if (pSceneNode) {
			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisContainer *pVisCell = ((const VisPortal*)pVisNode)->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					DrawRec(cRenderer, *pVisCell->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

				// Draw the portal itself
				if (pSceneNode->GetDrawFunctionFlags() & SceneNode::UseDrawPost)
					pSceneNode->DrawPost(cRenderer, pVisNode);

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
				if (pSceneNode->GetDrawFunctionFlags() & SceneNode::UseDrawPost)
					pSceneNode->DrawPost(cRenderer, pVisNode);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPFunctionsPost::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Enable scissor test
	cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

	// [TODO] Remove FixedFunctions usage, currently it's just in here for backward compatibility - Ensure the correct projection and view matrix is set
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, cCullQuery.GetProjectionMatrix());
		pFixedFunctions->SetTransformState(FixedFunctions::Transform::View,       cCullQuery.GetViewMatrix());
	}

	// Draw recursive from front to back
	DrawRec(cRenderer, cCullQuery);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
