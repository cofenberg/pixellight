/*********************************************************\
 *  File: ShadowMapManager.cpp                           *
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


// [TODO] Heavy under construction


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Tools.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Intersect.h>
#include <PLMath/EulerAngles.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Shader/ShaderManager.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include "PLScene/Scene/SNLight.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SNProjectiveSpotLight.h"
#include "PLScene/Scene/SNPointLight.h"
#include "PLScene/Scene/SceneQueryHandler.h"
#include "PLScene/Visibility/SQCull.h"
#include "PLScene/Visibility/VisPortal.h"
#include "PLScene/Visibility/VisContainer.h"
#include "PLScene/Compositing/ShadowMap.h"
#include "PLScene/Compositing/ShadowMapManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
const String ShadowMapManager::m_sWorldVP = "WorldVP";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShadowMapManager::ShadowMapManager(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pLightCullQuery(new SceneQueryHandler()),
	m_pCurrentCubeShadowRenderTarget(NULL),
	m_pCurrentSpotShadowRenderTarget(NULL),
	m_nTextureFiltering(Anisotropic2),
	m_nMaterialChanges(0),
	m_pCurrentMaterial(NULL)
{
	// Init shader handler data
	MemoryManager::Set(m_bVertexShader,   0, sizeof(m_bVertexShader));
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));

	// Init shadow maps
	for (int i=0; i<CubeShadowRenderTargets; i++)
		m_pCubeShadowRenderTarget[i] = NULL;
	for (int i=0; i<SpotShadowRenderTargets; i++)
		m_pSpotShadowRenderTarget[i] = NULL;
}

/**
*  @brief
*    Destructor
*/
ShadowMapManager::~ShadowMapManager()
{
	// Destroy all used shaders
	DestroyShaders();

	// Cube shadow maps
	for (int i=0; i<CubeShadowRenderTargets; i++) {
		if (m_pCubeShadowRenderTarget[i]) {
			delete m_pCubeShadowRenderTarget[i];
			m_pCubeShadowRenderTarget[i] = NULL;
		}
	}
	m_pCurrentCubeShadowRenderTarget = NULL;

	// Spot shadow maps
	for (int i=0; i<SpotShadowRenderTargets; i++) {
		if (m_pSpotShadowRenderTarget[i]) {
			delete m_pSpotShadowRenderTarget[i];
			m_pSpotShadowRenderTarget[i] = NULL;
		}
	}
	m_pCurrentSpotShadowRenderTarget = NULL;

	// Destroy the cull query
	SceneQuery *pSceneQuery = m_pLightCullQuery->GetElement();
	if (pSceneQuery)
		pSceneQuery->GetSceneContainer().DestroyQuery(*pSceneQuery);

	delete m_pLightCullQuery;
}

/**
*  @brief
*    Updates the shadow map
*/
void ShadowMapManager::UpdateShadowMap(SNLight &cLight, const SQCull &cCullQuery, float fSquaredDistanceToCamera)
{
	if ((cLight.GetFlags() & SNLight::CastShadow) && cLight.IsPointLight()) {
		Renderer &cRenderer = *m_pRenderer;

		// Squared distance to camera must be >= 0
		fSquaredDistanceToCamera = Math::Abs(fSquaredDistanceToCamera);

		// Get/create render targets depending on the light type
		if (cLight.IsSpotLight()) {
			// Get texture size
			uint16 nTextureSize = 1024;
			m_pCurrentSpotShadowRenderTarget = &m_pSpotShadowRenderTarget[0];
			const float fRange = ((SNSpotLight&)cLight).GetRange();
			float fMinimumDistanceToCamera = fSquaredDistanceToCamera-(fRange*fRange);
			if (fMinimumDistanceToCamera > 20.0f*20.0f) {
				nTextureSize = 64;
				m_pCurrentSpotShadowRenderTarget = &m_pSpotShadowRenderTarget[4];
			} else if (fMinimumDistanceToCamera > 15.0f*15.0f) {
				nTextureSize = 128;
				m_pCurrentSpotShadowRenderTarget = &m_pSpotShadowRenderTarget[3];
			} else if (fMinimumDistanceToCamera > 10.0f*10.0f) {
				nTextureSize = 256;
				m_pCurrentSpotShadowRenderTarget = &m_pSpotShadowRenderTarget[2];
			} else if (fMinimumDistanceToCamera > 5.0f*5.0f) {
				nTextureSize = 512;
				m_pCurrentSpotShadowRenderTarget = &m_pSpotShadowRenderTarget[1];
			}

			// Get/create the texture
			if (!*m_pCurrentSpotShadowRenderTarget)
				*m_pCurrentSpotShadowRenderTarget = cRenderer.CreateSurfaceTextureBuffer2D(Vector2i(nTextureSize, nTextureSize), TextureBuffer::D24, SurfaceTextureBuffer::Depth|SurfaceTextureBuffer::NoMultisampleAntialiasing);
		} else if (cLight.IsPointLight()) {
			// Get texture size
			uint16 nTextureSize = 512;
			m_pCurrentCubeShadowRenderTarget = &m_pCubeShadowRenderTarget[0];
			const float fRange = ((SNPointLight&)cLight).GetRange();
			float fMinimumDistanceToCamera = fSquaredDistanceToCamera-(fRange*fRange);
			if (fMinimumDistanceToCamera > 20.0f*20.0f) {
				nTextureSize = 32;
				m_pCurrentCubeShadowRenderTarget = &m_pCubeShadowRenderTarget[4];
			} else if (fMinimumDistanceToCamera > 15.0f*15.0f) {
				nTextureSize = 64;
				m_pCurrentCubeShadowRenderTarget = &m_pCubeShadowRenderTarget[3];
			} else if (fMinimumDistanceToCamera > 10.0f*10.0f) {
				nTextureSize = 128;
				m_pCurrentCubeShadowRenderTarget = &m_pCubeShadowRenderTarget[2];
			} else if (fMinimumDistanceToCamera > 5.0f*5.0f) {
				nTextureSize = 256;
				m_pCurrentCubeShadowRenderTarget = &m_pCubeShadowRenderTarget[1];
			}

			// Get/create the texture
			if (!*m_pCurrentCubeShadowRenderTarget)
				*m_pCurrentCubeShadowRenderTarget = cRenderer.CreateSurfaceTextureBufferCube(nTextureSize, TextureBuffer::R8G8B8A8, SurfaceTextureBuffer::Depth|SurfaceTextureBuffer::NoMultisampleAntialiasing);
		}

		// Render
		if ((m_pCurrentCubeShadowRenderTarget && *m_pCurrentCubeShadowRenderTarget) ||
			(m_pCurrentSpotShadowRenderTarget && *m_pCurrentSpotShadowRenderTarget)) {
			// Setup render states
			cRenderer.GetRendererContext().GetEffectManager().Use();

			// Create cull query if required
			const SQCull *pRootQuery = cCullQuery.GetVisRootContainer() ? cCullQuery.GetVisRootContainer()->GetCullQuery() : NULL;
			if (pRootQuery) {
				SQCull *pLightCullQuery = (SQCull*)m_pLightCullQuery->GetElement();
				if (!pLightCullQuery) {
					pLightCullQuery = (SQCull*)pRootQuery->GetSceneContainer().CreateQuery("PLScene::SQCull");
					if (pLightCullQuery) {
						m_pLightCullQuery->SetElement(pLightCullQuery);

						// Set the cull mode
						pLightCullQuery->SetMode(SQCull::Frustum);

						// We do not need to inform any scene query listeners
						pLightCullQuery->SetFlags(0);
					}
				}
				// [TODO] No fixed functions in here
				FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
				if (pFixedFunctions) {
					if (pLightCullQuery) {
						// Backup the color mask
						bool bRed, bGreen, bBlue, bAlpha;
						cRenderer.GetColorMask(bRed, bGreen, bBlue, bAlpha);

						// Get current render target
						Surface *pSurfaceBackup = cRenderer.GetRenderTarget();
						const Matrix4x4 mProjBackup = pFixedFunctions->GetTransformState(FixedFunctions::Transform::Projection);
						const Matrix4x4 mViewBackup = pFixedFunctions->GetTransformState(FixedFunctions::Transform::View);
						cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

						// Set polygon offset to avoid nasty shadow artefacts
						cRenderer.SetRenderState(RenderState::SlopeScaleDepthBias,	Tools::FloatToUInt32(2.0f));
						cRenderer.SetRenderState(RenderState::DepthBias,			Tools::FloatToUInt32(10.0f));

						// Spot or point light?
						if (cLight.IsSpotLight()) {
							SNSpotLight &cSpotLight = (SNSpotLight&)cLight;
							pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, cSpotLight.GetProjectionMatrix());
							pFixedFunctions->SetTransformState(FixedFunctions::Transform::View,       cSpotLight.GetViewMatrix());

							// Setup render query
							pLightCullQuery->SetCameraContainer(cLight.GetContainer()->IsCell() ? cLight.GetContainer() : NULL);
							pLightCullQuery->SetCameraPosition(cLight.GetTransform().GetPosition());
							pLightCullQuery->SetViewFrustum(cSpotLight.GetFrustum());
							pLightCullQuery->SetViewMatrix(cSpotLight.GetViewMatrix());
							pLightCullQuery->SetViewProjectionMatrix(cSpotLight.GetProjectionMatrix()*cSpotLight.GetViewMatrix());

							// Set the new render target
							if (cRenderer.SetRenderTarget(*m_pCurrentSpotShadowRenderTarget)) {
								// Perform the visibility determination
								pLightCullQuery->PerformQuery();

								// Clear the frame buffer
								cRenderer.Clear(Clear::ZBuffer);

								// Reset current material
								m_nMaterialChanges = 0;
								m_pCurrentMaterial = NULL;

								// Disable color writes
								cRenderer.SetColorMask(false, false, false, false);

								// Render distance recursive
								RenderDistanceRec(cRenderer, *pLightCullQuery, cLight);
							}
						} else {
							SNPointLight &cPointLight = (SNPointLight&)cLight;

							// For each of the 6 cube faces...
							Vector3 vRot;
							for (uint8 nFace=0; nFace<6; nFace++) {
								// Get rotation
								switch (nFace) {
									// x-positive
									case 0:
										vRot.SetXYZ(  0.0f,  90.0f, 180.0f);
										break;

									// x-negative
									case 1:
										vRot.SetXYZ(  0.0f, -90.0f, 180.0f);
										break;

									// y-positive
									case 2:
										vRot.SetXYZ(-90.0f, 180.0f, 180.0f);
										break;

									// y-negative
									case 3:
										vRot.SetXYZ( 90.0f, 180.0f, 180.0f);
										break;

									// z-positive
									case 4:
										vRot.SetXYZ(  0.0f, 180.0f, 180.0f);
										break;

									// z-negative
									case 5:
										vRot.SetXYZ(  0.0f,   0.0f, 180.0f);
										break;
								}
								Quaternion qRot;
								EulerAngles::ToQuaternion(float(vRot.x*Math::DegToRad), float(vRot.y*Math::DegToRad), float(vRot.z*Math::DegToRad), qRot);

								// Calculate and set projection matrix
								Matrix4x4 mProj;
								mProj.PerspectiveFov(float(90.0f*Math::DegToRad), 1.0f, 0.01f, cPointLight.GetRange());
								pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, mProj);

								// Calculate and set view matrix
								Matrix3x4 mView;
								mView.View(qRot, cLight.GetTransform().GetPosition());
								pFixedFunctions->SetTransformState(FixedFunctions::Transform::View, mView);

								// Calculate the view frustum
								Frustum cFrustum;
								cFrustum.CreateViewPlanes(mProj, mView);

								// Setup render query
								pLightCullQuery->SetCameraContainer(cLight.GetContainer()->IsCell() ? cLight.GetContainer() : NULL);
								pLightCullQuery->SetCameraPosition(cLight.GetTransform().GetPosition());
								pLightCullQuery->SetViewFrustum(cFrustum);
								pLightCullQuery->SetViewMatrix(mView);
								pLightCullQuery->SetViewProjectionMatrix(mProj*mView);

								// Set the new render target
								if (cRenderer.SetRenderTarget(*m_pCurrentCubeShadowRenderTarget, nFace)) {
									// Perform the visibility determination
									pLightCullQuery->PerformQuery();

									// Clear the frame buffer
									cRenderer.Clear(Clear::Color|Clear::ZBuffer, PLGraphics::Color4::White);

									// Reset current material
									m_nMaterialChanges = 0;
									m_pCurrentMaterial = NULL;

									// Enable color writes - this shadow map technique requires it!
									cRenderer.SetColorMask();

									// Render distance recursive
									RenderDistanceRec(cRenderer, *pLightCullQuery, cLight);
								}
							}
						}

						// Reset renderer target
						cRenderer.SetRenderTarget(pSurfaceBackup);
						pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, mProjBackup);
						pFixedFunctions->SetTransformState(FixedFunctions::Transform::View,       mViewBackup);

						// Restore the color mask
						cRenderer.SetColorMask(bRed, bGreen, bBlue, bAlpha);
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Returns the render target for the cube shadow map
*/
SurfaceTextureBuffer *ShadowMapManager::GetCubeShadowRenderTarget() const
{
	return m_pCurrentCubeShadowRenderTarget ? *m_pCurrentCubeShadowRenderTarget : NULL;
}

/**
*  @brief
*    Returns the render target for the spot shadow map
*/
SurfaceTextureBuffer *ShadowMapManager::GetSpotShadowRenderTarget() const
{
	return m_pCurrentSpotShadowRenderTarget ? *m_pCurrentSpotShadowRenderTarget : NULL;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets correct texture filtering modes
*/
void ShadowMapManager::SetupTextureFiltering(Renderer &cRenderer, uint32 nStage) const
{
	if (m_nTextureFiltering > 1) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MaxAnisotropy, m_nTextureFiltering);
	} else {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::Linear);
	}
}

/**
*  @brief
*    Returns a vertex shader
*/
Shader *ShadowMapManager::GetVertexShader(Renderer &cRenderer, bool bDiffuseMap)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cVertexShader[bDiffuseMap];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bVertexShader[bDiffuseMap]) {
		const static String ShaderFilename = "Vertex/Distance.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bDiffuseMap) {
			sDefines += "#define USE_DIFFUSEMAP\n";
			sName    += "[DiffuseMap]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		// Load the shader
		{
			#include "ShadowMapManager_VertexShader.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszShadowMapManager_VertexShader) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszShadowMapManager_VertexShader, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, false, "arbvp1", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bVertexShader[bDiffuseMap] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns a fragment shader
*/
Shader *ShadowMapManager::GetFragmentShader(Renderer &cRenderer, bool bAlphaTest)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bAlphaTest];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bAlphaTest]) {
		const static String ShaderFilename = "Fragment/Distance.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bAlphaTest) {
			sDefines += "#define ALPHATEST\n";
			sName    += "[AlphaTest]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		// Load the shader
		{
			#include "ShadowMapManager_FragmentShader.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszShadowMapManager_FragmentShader) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszShadowMapManager_FragmentShader, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "arbfp1", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bAlphaTest] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void ShadowMapManager::DestroyShaders()
{
	{
		Iterator<ShaderHandler*> cIterator = m_lstShaders.GetIterator();
		while (cIterator.HasNext()) {
			ShaderHandler *pShaderHandler = cIterator.Next();
			if (pShaderHandler->GetResource())
				delete pShaderHandler->GetResource();
			delete pShaderHandler;
		}
	}
	m_lstShaders.Clear();

	// Init shader handler data
	MemoryManager::Set(m_bVertexShader,   0, sizeof(m_bVertexShader));
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Renders distance recursive
*/
void ShadowMapManager::RenderDistanceRec(Renderer &cRenderer, const SQCull &cCullQuery, SNLight &cLight)
{
	// Get scene container
//	SceneContainer     &cSceneContainer = cCullQuery.GetSceneContainer();
	const VisContainer &cVisContainer   = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	// Draw the container scene node (maybe there are for instance some debug information to draw)
	// [TODO]
//	cSceneContainer.DrawSolid(cRenderer);

	// Render all visible scene nodes of this scene container
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();

		// Can this scene node product shadows? LOOK OUT: This may result in that objects behind portals don't
		// cast shadows if the light source is on the other side of the portal! (may or may not be desired!)
		if (pSceneNode && (pSceneNode->GetFlags() & SceneNode::CastShadow)) {
			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisContainer *pVisCell = ((const VisPortal*)pVisNode)->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					RenderDistanceRec(cRenderer, *pVisCell->GetCullQuery(), cLight);

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

				// Draw the portal itself (maybe there are for instance some debug information to draw)
				// [TODO]
	//			pSceneNode->DrawSolid(cRenderer);

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery()) {
					RenderDistanceRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery(), cLight);

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// Is this a light, if so, ignore it
			} else if (pSceneNode->IsLight()) {

			// This must just be a quite boring scene node :)
			} else {
				// First of all, check sphere/axis aligned bounding box intersection of the used light and the scene node
				// [TODO] Make this portal safe
				//	Intersect::SphereSphere(cLight.GetContainerBoundingSphere(), pSceneNode->GetContainerBoundingSphere()) &&
				//	Intersect::SphereAABox(cLight.GetContainerBoundingSphere(), pSceneNode->GetContainerAABoundingBox())) {
				if (true) {
					// If this is a spot light, we can do another intersection test
					// [TODO] Make this portal safe
					if (true) {
//					if (!cLight.IsSpotLight() ||
//						Intersect::PlaneSetAABox(((SNSpotLight&)cLight).GetFrustum(), pSceneNode->GetContainerAABoundingBox().vMin, pSceneNode->GetContainerAABoundingBox().vMax)) {
						// Here we draw the stuff by hand in order to minimize state changes and other overhead
						MeshHandler *pMeshHandler = pSceneNode->GetMeshHandler();
						if (pMeshHandler && pMeshHandler->GetVertexBuffer()) {
							Material *pMaterial = pMeshHandler->GetMaterial(0);
							if (pMaterial) {
								Mesh *pMesh = pMeshHandler->GetResource();
								if (pMesh) {
									// Get buffers
									MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
									if (pLODLevel) {
										// Get index buffer
										IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
										if (pIndexBuffer) {
											const Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

											// Mark this scene node as drawn
											pSceneNode->SetDrawn();

											// Bind buffers
											cRenderer.SetIndexBuffer(pIndexBuffer);

											// [TODO] Remove FixedFunctions usage by using the new shader interface
											FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
											if (pFixedFunctions)
												pFixedFunctions->SetVertexBuffer(pMeshHandler->GetVertexBuffer());

											// Draw mesh
											for (uint32 nMat=0; nMat<pMeshHandler->GetNumOfMaterials(); nMat++) {
												// Get mesh material
												pMaterial = pMeshHandler->GetMaterial(nMat);
												if (pMaterial) {
													// Draw geometries
													bool bFirstMaterialUsage = true;
													for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
														// Is this geometry active and is it using the current used mesh material?
														const Geometry &cGeometry = lstGeometries[nGeo];
														if (cGeometry.IsActive() && nMat == cGeometry.GetMaterial()) {
															// Transparent material?
															static const String sOpacity = "Opacity";
															const Parameter *pParameter = pMaterial->GetParameter(sOpacity);
															if (!pParameter || pParameter->GetValue1f() >= 1.0f) {
																// First material usage?
																if (bFirstMaterialUsage) {
																	ShaderProgram *pVertexShaderProgram = NULL;
																	bFirstMaterialUsage = false;

																	// Material change?
																	if (m_pCurrentMaterial != pMaterial) {
																		m_nMaterialChanges++;
																		m_pCurrentMaterial = pMaterial;

																		// Two sided?
																		static const String sTwoSided = "TwoSided";
																		pParameter = pMaterial->GetParameter(sTwoSided);
																		const bool bTwoSided = (pParameter && pParameter->GetValue1f() == 1.0f);

																		// Setup cull mode
																		cRenderer.SetRenderState(RenderState::CullMode, bTwoSided ? Cull::None : Cull::CCW);

																		// Get diffuse map and alpha reference
																		float fAlphaReference = 0.0f;
																		TextureBuffer *pDiffuseMap = pMaterial->GetParameterTextureBuffer(Material::DiffuseMap);
																		// Enable/disable alpha test
																		if (pDiffuseMap && pDiffuseMap->GetComponentsPerPixel() == 4) {
																			// Get alpha reference
																			static const String sAlphaReference = "AlphaReference";
																			pParameter = pMaterial->GetParameter(sAlphaReference);
																			fAlphaReference = pParameter ? pParameter->GetValue1f() : 0.5f;
																		}

																		// Get the shader with the given features
																		Shader *pMeshVertexShader = GetVertexShader(cRenderer, fAlphaReference != 0.0f);
																		if (pMeshVertexShader) {
																			pVertexShaderProgram = pMeshVertexShader->GetShaderProgram();
																			if (pVertexShaderProgram) {
																				Shader *pMeshFragmentShader = GetFragmentShader(cRenderer, fAlphaReference != 0.0f);
																				if (pMeshFragmentShader) {
																					ShaderProgram *pFragmentShaderProgram = pMeshFragmentShader->GetShaderProgram();
																					if (pFragmentShaderProgram) {
																					// Vertex shader program
																						cRenderer.SetVertexShaderProgram(pVertexShaderProgram);

																					// Fragment shader program
																						cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

																						// Set diffuse map
																						if (fAlphaReference != 0.0f) {
																							const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::DiffuseMap, pDiffuseMap);
																							if (nStage >= 0) {
																								cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
																								cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
																								SetupTextureFiltering(cRenderer, nStage);
																							}

																							// Set the "AlphaReference" fragment shader parameter
																							static const String sAlphaReference = "AlphaReference";
																							pFragmentShaderProgram->SetParameter1f(sAlphaReference, fAlphaReference);
																						}
																					}
																				}
																			}
																		}
																	} else {
																		pVertexShaderProgram = cRenderer.GetVertexShaderProgram();
																	}

																	// Vertex shader program
																	if (pVertexShaderProgram) {
																		// Set world view projection matrix
																		static const String sWorldVP = "WorldVP";
																		pVertexShaderProgram->SetParameterMatrixfv(sWorldVP, pVisNode->GetWorldViewProjectionMatrix());

																		// Set 4x4 world view matrix
																		static const String sWorldV = "WorldV";
																		pVertexShaderProgram->SetParameterMatrixfv(sWorldV, pVisNode->GetWorldViewMatrix());

																		// Set world space inverse light radius
																		const float fRange = cLight.IsPointLight() ? ((SNPointLight&)cLight).GetRange() : 0.0f;
																		static const String sInvRadius = "InvRadius";
																		pVertexShaderProgram->SetParameter1f(sInvRadius, 1.0f/fRange);
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
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLGeneral::ElementManager functions   ]
//[-------------------------------------------------------]
ShadowMap *ShadowMapManager::CreateElement(const String &sName)
{
	return new ShadowMap(sName, this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
