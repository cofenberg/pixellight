/*********************************************************\
 *  File: SRPDebugWireframesFixedFunctions.cpp           *
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
#include <PLCore/Tools/Tools.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/FixedFunctions/SRPDebugWireframesFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDebugWireframesFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDebugWireframesFixedFunctions::SRPDebugWireframesFixedFunctions()
{
}

/**
*  @brief
*    Destructor
*/
SRPDebugWireframesFixedFunctions::~SRPDebugWireframesFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws recursive
*/
void SRPDebugWireframesFixedFunctions::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery) const
{
	// Get the fixed functions interface (when we're in here, we know that it must exist!)
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();

	// Get scene container
	SceneContainer &cSceneContainer = cCullQuery.GetSceneContainer();
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	// Draw the container scene node
	if (cSceneContainer.GetMeshHandler())
		DrawMesh(cRenderer, cVisContainer, *cSceneContainer.GetMeshHandler());

	// Render all visible scene nodes of this scene container
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();
		if (pSceneNode) {
			// Set the current world matrix
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, pVisNode->GetWorldMatrix());

			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisContainer *pVisCell = static_cast<const VisPortal*>(pVisNode)->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					DrawRec(cRenderer, *pVisCell->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

				// Draw the portal itself
				if (pSceneNode->GetMeshHandler())
					DrawMesh(cRenderer, *pVisNode, *pSceneNode->GetMeshHandler());

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (static_cast<const VisContainer*>(pVisNode)->GetCullQuery())
					DrawRec(cRenderer, *static_cast<const VisContainer*>(pVisNode)->GetCullQuery());

				// Set the previous scissor rectangle
				cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

			// This must just be a quite boring scene node :)
			} else {
				if (pSceneNode->GetMeshHandler())
					DrawMesh(cRenderer, *pVisNode, *pSceneNode->GetMeshHandler());
			}
		}
	}
}

/**
*  @brief
*    Draws a mesh
*/
void SRPDebugWireframesFixedFunctions::DrawMesh(Renderer &cRenderer, const VisNode &cVisNode, const MeshHandler &cMeshHandler) const
{
	// Check for draw distance limitation
	if ((MaxDrawDistance <= 0.0f || cVisNode.GetSquaredDistanceToCamera() <= MaxDrawDistance*MaxDrawDistance) && cMeshHandler.GetVertexBuffer()) {
		// Get the mesh
		const Mesh *pMesh = cMeshHandler.GetResource();
		if (pMesh) {
			// Get buffers
			const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
			if (pLODLevel && pLODLevel->GetIndexBuffer()) {
					  IndexBuffer	  *pIndexBuffer  = pLODLevel->GetIndexBuffer();
				const Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

				// Bind buffers
				cRenderer.SetIndexBuffer(pIndexBuffer);
				FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
				if (pFixedFunctions)
					pFixedFunctions->SetVertexBuffer(cMeshHandler.GetVertexBuffer());

				// Draw geometries
				for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
					// Is this geometry active?
					const Geometry &cGeometry = lstGeometries[nGeo];
					if (cGeometry.IsActive()) {
						// Draw geometry
						cRenderer.DrawIndexedPrimitives(
							cGeometry.GetPrimitiveType(),
							0,
							cMeshHandler.GetVertexBuffer()->GetNumOfElements()-1,
							cGeometry.GetStartIndex(),
							cGeometry.GetIndexSize()
						);
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDebugWireframesFixedFunctions::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Check current fill mode
	if (cRenderer.GetRenderState(RenderState::FixedFillMode) == Fill::Solid) {
		// Fixed functions support required
		FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
		if (pFixedFunctions) {
			// Setup renderer states
			cRenderer.GetRendererContext().GetEffectManager().Use();
			const bool bUseDepth = (GetFlags() & UseDepth) != 0;
			cRenderer.SetRenderState(RenderState::CullMode,			 CullMode.Get());
			cRenderer.SetRenderState(RenderState::ZEnable,			 bUseDepth);
			cRenderer.SetRenderState(RenderState::ZWriteEnable,		 bUseDepth);
			cRenderer.SetRenderState(RenderState::BlendEnable,		 (LineColor.Get().a < 1.0f));
			cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);
			cRenderer.SetRenderState(RenderState::LineWidth,		 Tools::FloatToUInt32(LineWidth));
			pFixedFunctions->SetColor(LineColor.Get());

			// Set polygon offset to avoid nasty line artifacts
			cRenderer.SetRenderState(RenderState::SlopeScaleDepthBias,	Tools::FloatToUInt32(SlopeScaleDepthBias.Get()));
			cRenderer.SetRenderState(RenderState::DepthBias,			Tools::FloatToUInt32(DepthBias.Get()));

			// Set the initial world matrix
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, cCullQuery.GetSceneContainer().GetTransform().GetMatrix());

			// Draw recursive from front to back
			const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
			cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Line);
			DrawRec(cRenderer, cCullQuery);
			cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
