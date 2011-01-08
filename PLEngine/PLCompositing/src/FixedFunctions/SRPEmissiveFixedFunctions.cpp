/*********************************************************\
 *  File: SRPEmissiveFixedFunctions.cpp                  *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Texture/Texture.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/FixedFunctions/SRPEmissiveFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPEmissiveFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPEmissiveFixedFunctions::SRPEmissiveFixedFunctions() :
	TextureFiltering(this)
{
}

/**
*  @brief
*    Destructor
*/
SRPEmissiveFixedFunctions::~SRPEmissiveFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets correct texture filtering modes
*/
void SRPEmissiveFixedFunctions::SetupTextureFiltering(Renderer &cRenderer, uint32 nStage) const
{
	// Anisotropic filtering
	if (TextureFiltering > 1) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MaxAnisotropy, TextureFiltering);

	// Bilinear filtering
	} else if (TextureFiltering > 0) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::Linear);

	// No filtering
	} else {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
	}
}

/**
*  @brief
*    Draws recursive
*/
void SRPEmissiveFixedFunctions::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery) const
{
	// Get the fixed functions interface (when we're in here, we know that it must exist!)
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();

	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

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
				// Here we draw the stuff by hand in order to minimize state changes and other overhead
				const MeshHandler *pMeshHandler = pSceneNode->GetMeshHandler();
				if (pMeshHandler && pMeshHandler->GetVertexBuffer() && pMeshHandler->GetNumOfMaterials()) {
					// Get the used mesh
					const Mesh *pMesh = pMeshHandler->GetResource();
					if (pMesh) {
						// Get buffers
						const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
						if (pLODLevel && pLODLevel->GetIndexBuffer()) {
								  IndexBuffer     *pIndexBuffer  = pLODLevel->GetIndexBuffer();
							const Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

							// Draw mesh
							bool bFirst = true;
							for (uint32 nMat=0; nMat<pMeshHandler->GetNumOfMaterials(); nMat++) {
								// Get mesh material
								const Material *pMaterial = pMeshHandler->GetMaterial(nMat);
								if (pMaterial && !pMaterial->GetEffect()) {
									// Draw geometries
									for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
										// Is this geometry active and is it using the current used mesh material?
										const Geometry &cGeometry = lstGeometries[nGeo];
										if (cGeometry.IsActive() && nMat == cGeometry.GetMaterial()) {
											// Bind textures
											// Emissive map (stage 0)
											const Texture *pTexture = nullptr;
											const Parameter *pParameter = pMaterial->GetParameter(Material::EmissiveMap);
											if (pParameter)
												pTexture = pParameter->GetValueTexture();
											if (pTexture) {
												pTexture->Bind(0);
												SetupTextureFiltering(cRenderer, 0);

												// First draw call?
												if (bFirst) {
													bFirst = false;

													// Bind buffers
													cRenderer.SetIndexBuffer(pIndexBuffer);
													pFixedFunctions->SetVertexBuffer(pMeshHandler->GetVertexBuffer());

													// Setup cull mode
													static const String sTwoSided = "TwoSided";
													pParameter = pMaterial->GetParameter(sTwoSided);
													cRenderer.SetRenderState(RenderState::CullMode, (pParameter && pParameter->GetValue1f() == 1.0f) ? Cull::None : Cull::CCW);

													// Set emissive color - we do this in here by changing the ambient color for this material...
													static const String sEmissiveColor = "EmissiveColor";
													pParameter = pMaterial->GetParameter(sEmissiveColor);
													if (pParameter) {
														float fEmissiveColor[3] = { 1.0f, 1.0f, 1.0f };
														pParameter->GetValue3f(fEmissiveColor[0], fEmissiveColor[1], fEmissiveColor[2]);
														pFixedFunctions->SetColor(Color4(fEmissiveColor[0], fEmissiveColor[1], fEmissiveColor[2], 1.0f));
													} else {
														pFixedFunctions->SetColor(Color4::White);
													}
												}

												// Draw geometry
												cRenderer.DrawIndexedPrimitives(
													cGeometry.GetPrimitiveType(),
													0,
													pMeshHandler->GetVertexBuffer()->GetNumOfElements()-1,
													cGeometry.GetStartIndex(),
													cGeometry.GetIndexSize()
												);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPEmissiveFixedFunctions::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Fixed functions support required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Reset all render states to default
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::BlendEnable,		 true);
		cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

		// Set the initial world matrix
		pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, cCullQuery.GetSceneContainer().GetTransform().GetMatrix());

		// Draw recursive from front to back
		DrawRec(cRenderer, cCullQuery);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
