/*********************************************************\
 *  File: SRPDeferredGBuffer.cpp                         *
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
#include <float.h>
#include <PLMath/Matrix3x3.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/RenderStates.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "SRPDeferredGBuffer_Cg.h"	// The shader programs


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredGBuffer)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredGBuffer::SRPDeferredGBuffer() :
	ShaderLanguage(this),
	TextureFiltering(this),
	Flags(this),
	m_pRenderTarget(NULL),
	m_pColorTarget1(NULL),
	m_pColorTarget2(NULL),
	m_pColorTarget3(NULL),
	m_bColorTarget3Used(false),
	m_bColorTarget3AlphaUsed(false),
	m_pSurfaceBackup(NULL),
	m_pFullscreenQuad(NULL),
	m_pRenderStates(new RenderStates()),
	m_nMaterialChanges(0),
	m_pCurrentMaterial(NULL),
	m_pGeneratedProgramUserData(NULL),
	m_pProgramGenerator(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGBuffer::~SRPDeferredGBuffer()
{
	// Destroy render states 'translator'
	delete m_pRenderStates;

	// Destroy the render target of the GBuffer
	if (m_pRenderTarget)
		delete m_pRenderTarget;
	if (m_pColorTarget1)
		delete m_pColorTarget1;
	if (m_pColorTarget2)
		delete m_pColorTarget2;
	if (m_pColorTarget3)
		delete m_pColorTarget3;

	// Destroy the fullscreen quad
	if (m_pFullscreenQuad)
		delete m_pFullscreenQuad;

	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
}

/**
*  @brief
*    Returns a render target texture buffer of the GBuffer
*/
TextureBufferRectangle *SRPDeferredGBuffer::GetRenderTargetTextureBuffer(uint32 nIndex) const
{
	switch (nIndex)  {
		case 0:
			return m_pRenderTarget ? (TextureBufferRectangle*)m_pRenderTarget->GetTextureBuffer() : NULL;

		case 1:
			return m_pColorTarget1;

		case 2:
			return m_pColorTarget2;

		case 3:
			return m_pColorTarget3;

		default:
			return NULL;
	}
}

// [TODO] Remove this!
SurfaceTextureBuffer *SRPDeferredGBuffer::GetRenderTarget() const
{
	return m_pRenderTarget;
}

/**
*  @brief
*    Returns whether or not color target 3 has real information
*/
bool SRPDeferredGBuffer::IsColorTarget3Used() const
{
	return m_bColorTarget3Used;
}

/**
*  @brief
*    Returns whether or not the alpha channel target 3 has real information
*/
bool SRPDeferredGBuffer::IsColorTarget3AlphaUsed() const
{
	return m_bColorTarget3AlphaUsed;
}

/**
*  @brief
*    Returns a shared fullscreen quad instance
*/
FullscreenQuad *SRPDeferredGBuffer::GetFullscreenQuad() const
{
	return m_pFullscreenQuad;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets correct texture filtering modes
*/
void SRPDeferredGBuffer::SetupTextureFiltering(Renderer &cRenderer, uint32 nStage) const
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
void SRPDeferredGBuffer::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Set cull mode
	cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);

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

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery()) {
					DrawRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// This must just be a quite boring scene node :)
			} else {
				// Here we draw the stuff by hand in order to minimize state changes and other overhead
				const MeshHandler *pMeshHandler = pSceneNode->GetMeshHandler();
				if (pMeshHandler && pMeshHandler->GetVertexBuffer() && pMeshHandler->GetNumOfMaterials()) {
					// Get the used mesh
					const Mesh *pMesh = pMeshHandler->GetResource();
					if (pMesh) {
						// Get the mesh LOD level to use
						const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
						if (pLODLevel && pLODLevel->GetIndexBuffer() && pMeshHandler->GetVertexBuffer()) {
							// Draw the mesh
							DrawMesh(cRenderer, cCullQuery, *pVisNode, *pSceneNode, *pMeshHandler, *pMesh, *pLODLevel, *pMeshHandler->GetVertexBuffer());

							// Mark this scene node as drawn
							pSceneNode->SetDrawn();
						}
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Draws a mesh
*/
void SRPDeferredGBuffer::DrawMesh(Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, SceneNode &cSceneNode, const MeshHandler &cMeshHandler, const Mesh &cMesh, const MeshLODLevel &cMeshLODLevel, VertexBuffer &cVertexBuffer)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Get buffers
		  IndexBuffer     *pIndexBuffer  = cMeshLODLevel.GetIndexBuffer();
	const Array<Geometry> &lstGeometries = *cMeshLODLevel.GetGeometries();

	// Bind buffers
	cRenderer.SetIndexBuffer(pIndexBuffer);

	// Draw mesh
	for (uint32 nMat=0; nMat<cMeshHandler.GetNumOfMaterials(); nMat++) {
		// Get mesh material
		const Material *pMaterial = cMeshHandler.GetMaterial(nMat);
		if (pMaterial) {
			// Draw geometries
			bool bFirstMaterialUsage = true;
			bool bTwoSided           = false;
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
							bFirstMaterialUsage = false;

							{ // Two sided?
								static const String sTwoSided = "TwoSided";
								pParameter = pMaterial->GetParameter(sTwoSided);
								bTwoSided = (pParameter && pParameter->GetValue1f() == 1.0f);
							}

							// Get displacement mapping settings
							float fDisplacementScale = 0.1f;
							float fDisplacementBias  = 0.0f;
							TextureBuffer *pDisplacementMap = NULL;
							static const String sDisplacementMap = "DisplacementMap";
							if (!(GetFlags() & NoDisplacementMapping)) {
								// Get displacement scale
								static const String sDisplacementScale = "DisplacementScale";
								pParameter = pMaterial->GetParameter(sDisplacementScale);
								if (pParameter)
									pParameter->GetValue1f(fDisplacementScale);

								// Get displacement bias
								static const String sDisplacementBias  = "DisplacementBias";
								pParameter = pMaterial->GetParameter(sDisplacementBias);
								if (pParameter)
									pParameter->GetValue1f(fDisplacementBias);

								// Get displacement map
								if (fDisplacementScale != 0.0f) {
									pDisplacementMap = pMaterial->GetParameterTextureBuffer(sDisplacementMap);
									if (pDisplacementMap && pDisplacementMap->GetType() != TextureBuffer::TypeTextureBuffer2D)
										pDisplacementMap = NULL;
								}
							}

							// Get index of refraction and fresnel reflection power
							float fIndexOfRefraction      = 0.0f;
							float fFresnelReflectionPower = 5.0f;
							if (!(GetFlags() & NoFresnelReflection)) {
								// IndexOfRefraction
								static const String sIndexOfRefraction = "IndexOfRefraction";
								pParameter = pMaterial->GetParameter(sIndexOfRefraction);
								if (pParameter)
									fIndexOfRefraction = pParameter->GetValue1f();
								if (fIndexOfRefraction > 0.0f) {
									// FresnelReflectionPower
									static const String sFresnelReflectionPower = "FresnelReflectionPower";
									pParameter = pMaterial->GetParameter(sFresnelReflectionPower);
									if (pParameter) {
										fFresnelReflectionPower = pParameter->GetValue1f();

										// Ensure that the value is always >0 to avoid NAN production
										if (fFresnelReflectionPower < FLT_MIN)
											fFresnelReflectionPower = FLT_MIN;
									}
								}
							}

							// Get (2D/cube) reflection map
							TextureBuffer *pReflectionMap = (GetFlags() & NoReflectionMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::ReflectionMap);
							bool b2DReflectionMap = true;
							if (pReflectionMap) {
								if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBuffer2D)
									b2DReflectionMap = true;
								else if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBufferCube)
									b2DReflectionMap = false;
								else
									pReflectionMap   = NULL; // NOT supported!
							}

							// Figure out whether or not there's reflection on this material
							const bool bReflection = (fIndexOfRefraction > 0.0f) || pReflectionMap;

							// Get reflection parameters
							TextureBuffer *pReflectivityMap = NULL;
							float fReflectivity = 1.0f;
							Color3 cReflectionColor = Color3::White;
							static const String sReflectionColor = "ReflectionColor";
							static const String sReflectivity = "Reflectivity";
							if (bReflection) {
								// ReflectionColor
								pParameter = pMaterial->GetParameter(sReflectionColor);
								if (pParameter)
									cReflectionColor = pParameter->GetValue3fv();

								// Get reflectivity map
								if (!(GetFlags() & NoReflectivityMap))
									pReflectivityMap = pMaterial->GetParameterTextureBuffer(Material::ReflectivityMap);

								// Get reflectivity 
								pParameter = pMaterial->GetParameter(sReflectivity);
								if (pParameter)
									fReflectivity = pParameter->GetValue1f();
							}

							// Get parallax mapping settings
							float fParallax = 0.04f;
							TextureBuffer *pHeightMap = NULL;
							if (!(GetFlags() & NoParallaxMapping)) {
								// Get parallax
								static const String sParallax = "Parallax";
								pParameter = pMaterial->GetParameter(sParallax);
								if (pParameter)
									pParameter->GetValue1f(fParallax);

								// Get height map
								if (fParallax != 0.0f)
									pHeightMap = pMaterial->GetParameterTextureBuffer(Material::HeightMap);
							}
							// No height map = no parallax mapping possible
							if (!pHeightMap)
								fParallax = 0.0f;

							// Material change?
							if (m_pCurrentMaterial != pMaterial) {
								m_nMaterialChanges++;
								m_pCurrentMaterial = pMaterial;

								// Get glow
								float		   fGlowFactor = 0.0f;
								TextureBuffer *pGlowMap    = NULL;
								if (!(GetFlags() & NoGlow)) {
									static const String sGlow = "Glow";
									pParameter = pMaterial->GetParameter(sGlow);
									if (pParameter) {
										fGlowFactor = pParameter->GetValue1f();

										// Get glow map
										if (fGlowFactor != 0.0f) {
											static const String sGlowMap = "GlowMap";
											pGlowMap = (GetFlags() & NoGlowMap) ? NULL : pMaterial->GetParameterTextureBuffer(sGlowMap);
										}
									}
								}

								// Get ambient occlusion map
								TextureBuffer *pAmbientOcclusionMap = (GetFlags() & NoAmbientOcclusionMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::AmbientOcclusionMap);

								// Get diffuse map and alpha reference
								float fAlphaReference = 0.0f;
								TextureBuffer *pDiffuseMap = (GetFlags() & NoDiffuseMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::DiffuseMap);

								// Enable/disable alpha test (fragments are thrown away inside the fragment shader using the 'discard' keyword)
								if (pDiffuseMap && pDiffuseMap->GetComponentsPerPixel() == 4) {
									// Get alpha reference
									static const String sAlphaReference = "AlphaReference";
									pParameter = pMaterial->GetParameter(sAlphaReference);
									fAlphaReference = pParameter ? pParameter->GetValue1f() : 0.5f;
								}

								// Get specular settings
								static const String sSpecularColor = "SpecularColor";
								bool bSpecular = false;
								Color3 cSpecularColor = Color3::White;
								if (!(GetFlags() & NoSpecular)) {
									// First, get specular color - if it's 0, we don't have any specular at all
									pParameter = pMaterial->GetParameter(sSpecularColor);
									if (pParameter)
										cSpecularColor = pParameter->GetValue3fv();
									bSpecular = (cSpecularColor != 0.0f);
								}
								static const String sSpecularExponent = "SpecularExponent";
								TextureBuffer *pSpecularMap = NULL;
								float fSpecularExponent = 45.0f;
								if (bSpecular) {
									// Get the specular map
									if (!(GetFlags() & NoSpecularMap))
										pSpecularMap = pMaterial->GetParameterTextureBuffer(Material::SpecularMap);

									// Get specular exponent
									pParameter = pMaterial->GetParameter(sSpecularExponent);
									if (pParameter)
										pParameter->GetValue1f(fSpecularExponent);
								}

								// Get normal map
								TextureBuffer *pNormalMap = (GetFlags() & NoNormalMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::NormalMap);
								float fNormalMapBumpiness = 1.0f;
								bool bNormalMap_DXT5_xGxR = false;
								bool bNormalMap_LATC2     = false;
								static const String sNormalMapBumpiness = "NormalMapBumpiness";
								if (pNormalMap) {
									// Get normal map bumpiness
									const Parameter *pNormalMapParameter = pMaterial->GetParameter(sNormalMapBumpiness);
									if (pNormalMapParameter)
										fNormalMapBumpiness = pNormalMapParameter->GetValue1f();
									if (fNormalMapBumpiness != 0.0f) {
										// DXT5 xGxR normal map?
										pNormalMapParameter = pMaterial->GetParameter(Material::NormalMap);
										if (pNormalMapParameter) {
											const Texture *pNormalMapTexture = pNormalMapParameter->GetValueTexture();
											if (pNormalMapTexture) {
												if (pNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR || pNormalMapTexture->GetCompressionHint() == Texture::LATC2_XYSwizzle)
													bNormalMap_DXT5_xGxR = true;	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
												else if (pNormalMapTexture->GetCompressionHint() == Texture::LATC2)
													bNormalMap_LATC2 = true;
											}
										}
									} else {
										// The normal map has no longer an influence!
										pNormalMap = NULL;
									}
								}

								// Get detail normal map
								static const String sDetailNormalMap = "DetailNormalMap";
								TextureBuffer *pDetailNormalMap = (!pNormalMap || (GetFlags() & NoDetailNormalMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sDetailNormalMap);
								float fDetailNormalMapBumpiness = 1.0f;
								Vector2 vDetailNormalMapUVScale(4.0f, 4.0f);
								bool bDetailNormalMap_DXT5_xGxR = false;
								bool bDetailNormalMap_LATC2     = false;
								static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
								static const String sDetailNormalMapUVScale   = "DetailNormalMapUVScale";
								if (pDetailNormalMap) {
									// Get detail normal map bumpiness
									const Parameter *pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMapBumpiness);
									if (pDetailNormalMapParameter)
										fDetailNormalMapBumpiness = pDetailNormalMapParameter->GetValue1f();
									if (fDetailNormalMapBumpiness != 0.0f) {
										// Get detail normal map uv scale
										pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMapUVScale);
										if (pDetailNormalMapParameter)
											vDetailNormalMapUVScale = pDetailNormalMapParameter->GetValue2fv();

										// DXT5 xGxR detail normal map?
										pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMap);
										if (pDetailNormalMapParameter) {
											const Texture *pDetailNormalMapTexture = pDetailNormalMapParameter->GetValueTexture();
											if (pDetailNormalMapTexture) {
												if (pDetailNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR || pDetailNormalMapTexture->GetCompressionHint() == Texture::LATC2_XYSwizzle)
													bDetailNormalMap_DXT5_xGxR = true;	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
												else if (pDetailNormalMapTexture->GetCompressionHint() == Texture::LATC2)
													bDetailNormalMap_LATC2 = true;
											}
										}
									} else {
										// The detail normal map has no longer an influence!
										pDetailNormalMap = NULL;
									}
								}

								// Get light map
								TextureBuffer *pLightMap = (GetFlags() & NoLightMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::LightMap);

								// Get emissive map
								TextureBuffer *pEmissiveMap = (GetFlags() & NoEmissiveMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::EmissiveMap);

								// Reset the program flags
								m_cProgramFlags.Reset();

								// Set vertex program flags
								if (bTwoSided)
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TWOSIDED)
								if ( pDisplacementMap != NULL)
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_DISPLACEMENTMAP)
								if (pAmbientOcclusionMap != NULL || pLightMap != NULL)
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_SECONDTEXTURECOORDINATE)
								if (pNormalMap != NULL || fParallax != 0.0f)
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TANGENT_BINORMAL)
								if (bReflection)
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_VIEWSPACEPOSITION)
								
								// Set fragment program flags
								if (pDiffuseMap != NULL) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIFFUSEMAP)
									if (fAlphaReference != 0.0f)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_ALPHATEST)
								}
								if (bSpecular) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULAR)
									if (pSpecularMap != NULL)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULARMAP)
								}
								if (pNormalMap != NULL) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP)
									if (bNormalMap_DXT5_xGxR)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP_DXT5_XGXR)
									else if (bNormalMap_LATC2)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP_LATC2)
									if (pDetailNormalMap != NULL) {
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP)
										if (bDetailNormalMap_DXT5_xGxR)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP_DXT5_XGXR)
										else if (bDetailNormalMap_LATC2)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP_LATC2)
									}
								}
								if (fParallax != 0.0f)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_PARALLAXMAPPING)
								if (pAmbientOcclusionMap != NULL)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_AMBIENTOCCLUSIONMAP)
								if (pLightMap != NULL)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_LIGHTMAP)
								if (pEmissiveMap != NULL)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_EMISSIVEMAP)
								if (fGlowFactor != 0.0f) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_GLOW)
									if (pGlowMap != NULL)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_GLOWMAP)
								}
								if ((fIndexOfRefraction > 0.0f || (b2DReflectionMap && pReflectionMap) || (!b2DReflectionMap && pReflectionMap))) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTION)
									if (fIndexOfRefraction > 0.0f)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_FRESNELREFLECTION)
									if (pReflectivityMap != NULL)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTIVITYMAP)
									if (b2DReflectionMap && pReflectionMap)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_2DREFLECTIONMAP)
									else if (!b2DReflectionMap && pReflectionMap)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_CUBEREFLECTIONMAP)
								}
								// Use gamma correction?
								if (!(GetFlags() & NoGammaCorrection))
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_GAMMACORRECTION)

								// Get a program instance from the program generator using the given program flags
								ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);

								// Make our program to the current one
								if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
									// Set pointers to uniforms & attributes of a generated program if they are not set yet
									m_pGeneratedProgramUserData = (GeneratedProgramUserData*)pGeneratedProgram->pUserData;
									if (!m_pGeneratedProgramUserData) {
										pGeneratedProgram->pUserData = m_pGeneratedProgramUserData = new GeneratedProgramUserData;
										Program *pProgram = pGeneratedProgram->pProgram;
										// Vertex shader attributes
										static const String sVertexPosition = "VertexPosition";
										m_pGeneratedProgramUserData->pVertexPosition	= pProgram->GetAttribute(sVertexPosition);
										static const String sVertexTexCoord0 = "VertexTexCoord0";
										m_pGeneratedProgramUserData->pVertexTexCoord0	= pProgram->GetAttribute(sVertexTexCoord0);
										static const String sVertexTexCoord1 = "VertexTexCoord1";
										m_pGeneratedProgramUserData->pVertexTexCoord1	= pProgram->GetAttribute(sVertexTexCoord1);
										static const String sVertexNormal = "VertexNormal";
										m_pGeneratedProgramUserData->pVertexNormal	= pProgram->GetAttribute(sVertexNormal);
										static const String sVertexTangent = "VertexTangent";
										m_pGeneratedProgramUserData->pVertexTangent	= pProgram->GetAttribute(sVertexTangent);
										static const String sVertexBinormal = "VertexBinormal";
										m_pGeneratedProgramUserData->pVertexBinormal	= pProgram->GetAttribute(sVertexBinormal);
										// Vertex shader uniforms
										static const String sNormalScale = "NormalScale";
										m_pGeneratedProgramUserData->pNormalScale				= pProgram->GetUniform(sNormalScale);
										static const String sEyePos = "EyePos";
										m_pGeneratedProgramUserData->pEyePos					= pProgram->GetUniform(sEyePos);
										static const String sWorldVP = "WorldVP";
										m_pGeneratedProgramUserData->pWorldVP					= pProgram->GetUniform(sWorldVP);
										static const String sWorldV = "WorldV";
										m_pGeneratedProgramUserData->pWorldV					= pProgram->GetUniform(sWorldV);
										static const String sDisplacementMap = "DisplacementMap";
										m_pGeneratedProgramUserData->pDisplacementMap			= pProgram->GetUniform(sDisplacementMap);
										static const String sDisplacementScaleBias = "DisplacementScaleBias";
										m_pGeneratedProgramUserData->pDisplacementScaleBias	= pProgram->GetUniform(sDisplacementScaleBias);
										// Fragment shader uniforms
										static const String sDiffuseColor = "DiffuseColor";
										m_pGeneratedProgramUserData->pDiffuseColor				= pProgram->GetUniform(sDiffuseColor);
										static const String sDiffuseMap = "DiffuseMap";
										m_pGeneratedProgramUserData->pDiffuseMap				= pProgram->GetUniform(sDiffuseMap);
										static const String sAlphaReference = "AlphaReference";
										m_pGeneratedProgramUserData->pAlphaReference			= pProgram->GetUniform(sAlphaReference);
										static const String sSpecularColor = "SpecularColor";
										m_pGeneratedProgramUserData->pSpecularColor				= pProgram->GetUniform(sSpecularColor);
										static const String sSpecularExponent = "SpecularExponent";
										m_pGeneratedProgramUserData->pSpecularExponent			= pProgram->GetUniform(sSpecularExponent);
										static const String sSpecularMap = "SpecularMap";
										m_pGeneratedProgramUserData->pSpecularMap				= pProgram->GetUniform(sSpecularMap);
										static const String sNormalMap = "NormalMap";
										m_pGeneratedProgramUserData->pNormalMap					= pProgram->GetUniform(sNormalMap);
										static const String sNormalMapBumpiness = "NormalMapBumpiness";
										m_pGeneratedProgramUserData->pNormalMapBumpiness		= pProgram->GetUniform(sNormalMapBumpiness);
										static const String sDetailNormalMap = "DetailNormalMap";
										m_pGeneratedProgramUserData->pDetailNormalMap			= pProgram->GetUniform(sDetailNormalMap);
										static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
										m_pGeneratedProgramUserData->pDetailNormalMapBumpiness	= pProgram->GetUniform(sDetailNormalMapBumpiness);
										static const String sDetailNormalMapUVScale = "DetailNormalMapUVScale";
										m_pGeneratedProgramUserData->pDetailNormalMapUVScale	= pProgram->GetUniform(sDetailNormalMapUVScale);
										static const String sHeightMap = "HeightMap";
										m_pGeneratedProgramUserData->pHeightMap					= pProgram->GetUniform(sHeightMap);
										static const String sParallaxScaleBias = "ParallaxScaleBias";
										m_pGeneratedProgramUserData->pParallaxScaleBias			= pProgram->GetUniform(sParallaxScaleBias);
										static const String sAmbientOcclusionMap = "AmbientOcclusionMap";
										m_pGeneratedProgramUserData->pAmbientOcclusionMap		= pProgram->GetUniform(sAmbientOcclusionMap);
										static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
										m_pGeneratedProgramUserData->pAmbientOcclusionFactor	= pProgram->GetUniform(sAmbientOcclusionFactor);
										static const String sLightMap = "LightMap";
										m_pGeneratedProgramUserData->pLightMap					= pProgram->GetUniform(sLightMap);
										static const String sLightMapColor = "LightMapColor";
										m_pGeneratedProgramUserData->pLightMapColor				= pProgram->GetUniform(sLightMapColor);
										static const String sEmissiveMap = "EmissiveMap";
										m_pGeneratedProgramUserData->pEmissiveMap				= pProgram->GetUniform(sEmissiveMap);
										static const String sEmissiveMapColor = "EmissiveMapColor";
										m_pGeneratedProgramUserData->pEmissiveMapColor			= pProgram->GetUniform(sEmissiveMapColor);
										static const String sGlowFactor = "GlowFactor";
										m_pGeneratedProgramUserData->pGlowFactor				= pProgram->GetUniform(sGlowFactor);
										static const String sGlowMap = "GlowMap";
										m_pGeneratedProgramUserData->pGlowMap					= pProgram->GetUniform(sGlowMap);
										static const String sReflectionColor = "ReflectionColor";
										m_pGeneratedProgramUserData->pReflectionColor			= pProgram->GetUniform(sReflectionColor);
										static const String sReflectivity = "Reflectivity";
										m_pGeneratedProgramUserData->pReflectivity				= pProgram->GetUniform(sReflectivity);
										static const String sReflectivityMap = "ReflectivityMap";
										m_pGeneratedProgramUserData->pReflectivityMap			= pProgram->GetUniform(sReflectivityMap);
										static const String sFresnelConstants = "FresnelConstants";
										m_pGeneratedProgramUserData->pFresnelConstants			= pProgram->GetUniform(sFresnelConstants);
										static const String sReflectionMap = "ReflectionMap";
										m_pGeneratedProgramUserData->pReflectionMap				= pProgram->GetUniform(sReflectionMap);
										static const String sViewSpaceToWorldSpace = "ViewSpaceToWorldSpace";
										m_pGeneratedProgramUserData->pViewSpaceToWorldSpace		= pProgram->GetUniform(sViewSpaceToWorldSpace);
									}

									// Set displacement map
									if (m_pGeneratedProgramUserData->pDisplacementMap) {
										const int nTextureUnit = m_pGeneratedProgramUserData->pDisplacementMap->Set(pDisplacementMap);
										if (nTextureUnit >= 0) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
											SetupTextureFiltering(cRenderer, nTextureUnit);
										}

										// Set displacement scale bias
										if (m_pGeneratedProgramUserData->pDisplacementScaleBias)
											m_pGeneratedProgramUserData->pDisplacementScaleBias->Set(fDisplacementScale, fDisplacementBias);
									}

									// Set the "DiffuseColor" fragment shader parameter
									if (m_pGeneratedProgramUserData->pDiffuseColor) {
										static const String sDiffuseColor = "DiffuseColor";
										pParameter = pMaterial->GetParameter(sDiffuseColor);
										if (pParameter) {
											float fDiffuseColor[3] = { 1.0f, 1.0f, 1.0f };
											pParameter->GetValue3f(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
											m_pGeneratedProgramUserData->pDiffuseColor->Set(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
										} else {
											m_pGeneratedProgramUserData->pDiffuseColor->Set(1.0f, 1.0f, 1.0f);
										}
									}

									// Diffuse
									if (m_pGeneratedProgramUserData->pDiffuseMap) {
										// Set the "DiffuseMap" fragment shader parameter
										const int nTextureUnit = m_pGeneratedProgramUserData->pDiffuseMap->Set(pDiffuseMap);
										if (nTextureUnit >= 0) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
											SetupTextureFiltering(cRenderer, nTextureUnit);
										}

										// Set the "AlphaReference" fragment shader parameter
										if (m_pGeneratedProgramUserData->pAlphaReference)
											m_pGeneratedProgramUserData->pAlphaReference->Set(fAlphaReference);
									}

									// Specular
									if (bSpecular) {
										// Set specular exponent and specular color
										if (m_pGeneratedProgramUserData->pSpecularColor)
											m_pGeneratedProgramUserData->pSpecularColor->Set(cSpecularColor);
										if (m_pGeneratedProgramUserData->pSpecularExponent)
											m_pGeneratedProgramUserData->pSpecularExponent->Set(fSpecularExponent);

										// Set the "SpecularMap" fragment shader parameter
										if (m_pGeneratedProgramUserData->pSpecularMap) {
											const int nTextureUnit = m_pGeneratedProgramUserData->pSpecularMap->Set(pSpecularMap);
											if (nTextureUnit >= 0) {
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}
										}
									}

									// Normal map
									if (m_pGeneratedProgramUserData->pNormalMap) {
										{ // Set normal map
											const int nTextureUnit = m_pGeneratedProgramUserData->pNormalMap->Set(pNormalMap);
											if (nTextureUnit >= 0) {
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}

											// Set normal map bumpiness
											if (m_pGeneratedProgramUserData->pNormalMapBumpiness)
												m_pGeneratedProgramUserData->pNormalMapBumpiness->Set(fNormalMapBumpiness);
										}

										// Detail normal map
										if (m_pGeneratedProgramUserData->pDetailNormalMap) {
											{ // Set detail normal map
												const int nTextureUnit = m_pGeneratedProgramUserData->pDetailNormalMap->Set(pDetailNormalMap);
												if (nTextureUnit >= 0) {
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
													SetupTextureFiltering(cRenderer, nTextureUnit);
												}
											}

											// Set detail normal map bumpiness and uv scale
											if (m_pGeneratedProgramUserData->pDetailNormalMapBumpiness)
												m_pGeneratedProgramUserData->pDetailNormalMapBumpiness->Set(fDetailNormalMapBumpiness);
											if (m_pGeneratedProgramUserData->pDetailNormalMapUVScale)
												m_pGeneratedProgramUserData->pDetailNormalMapUVScale->Set(vDetailNormalMapUVScale);
										}
									}

									// Set height map
									if (m_pGeneratedProgramUserData->pHeightMap) {
										const int nTextureUnit = m_pGeneratedProgramUserData->pHeightMap->Set(pHeightMap);
										if (nTextureUnit >= 0) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
											SetupTextureFiltering(cRenderer, nTextureUnit);
										}

										// Set parallax scale bias
										if (m_pGeneratedProgramUserData->pParallaxScaleBias)
											m_pGeneratedProgramUserData->pParallaxScaleBias->Set(fParallax, -0.02f);
									}

									// Set ambient occlusion map
									if (m_pGeneratedProgramUserData->pAmbientOcclusionMap) {
										const int nTextureUnit = m_pGeneratedProgramUserData->pAmbientOcclusionMap->Set(pAmbientOcclusionMap);
										if (nTextureUnit >= 0) {
											// Setup sampler states
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
											SetupTextureFiltering(cRenderer, nTextureUnit);

											// Set ambient occlusion factor
											if (m_pGeneratedProgramUserData->pAmbientOcclusionFactor) {
												float fAmbientOcclusionFactor = 1.0f;
												static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
												pParameter = pMaterial->GetParameter(sAmbientOcclusionFactor);
												if (pParameter)
													pParameter->GetValue1f(fAmbientOcclusionFactor);
												m_pGeneratedProgramUserData->pAmbientOcclusionFactor->Set(fAmbientOcclusionFactor);
											}
										}
									}

									// Set light map
									if (m_pGeneratedProgramUserData->pLightMap) {
										const int nTextureUnit = m_pGeneratedProgramUserData->pLightMap->Set(pLightMap);
										if (nTextureUnit >= 0) {
											// Setup sampler states
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
											SetupTextureFiltering(cRenderer, nTextureUnit);

											// Set light map color
											if (m_pGeneratedProgramUserData->pLightMapColor) {
												float fLightMapColor[3] = { 1.0f, 1.0f, 1.0f };
												static const String sLightMapColor = "LightMapColor";
												pParameter = pMaterial->GetParameter(sLightMapColor);
												if (pParameter)
													pParameter->GetValue3f(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
												m_pGeneratedProgramUserData->pLightMapColor->Set(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
											}
										}

										// Color target 3 has real information
										m_bColorTarget3Used = true;
									}

									// Set emissive map
									if (m_pGeneratedProgramUserData->pEmissiveMap) {
										const int nTextureUnit = m_pGeneratedProgramUserData->pEmissiveMap->Set(pEmissiveMap);
										if (nTextureUnit >= 0) {
											// Setup sampler states
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
											SetupTextureFiltering(cRenderer, nTextureUnit);

											// Set emissive color
											if (m_pGeneratedProgramUserData->pEmissiveMapColor) {
												float fEmissiveMapColor[3] = { 1.0f, 1.0f, 1.0f };
												static const String sEmissiveMapColor = "EmissiveMapColor";
												pParameter = pMaterial->GetParameter(sEmissiveMapColor);
												if (pParameter)
													pParameter->GetValue3f(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
												m_pGeneratedProgramUserData->pEmissiveMapColor->Set(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
											}
										}

										// Color target 3 has real information
										m_bColorTarget3Used = true;
									}

									// Set the "GlowFactor" fragment shader parameter
									if (fGlowFactor != 0.0f) {
										if (m_pGeneratedProgramUserData->pGlowFactor)
											m_pGeneratedProgramUserData->pGlowFactor->Set(fGlowFactor);

										// Set glow map
										if (m_pGeneratedProgramUserData->pGlowMap) {
											const int nTextureUnit = m_pGeneratedProgramUserData->pGlowMap->Set(pGlowMap);
											if (nTextureUnit >= 0) {
												// Setup sampler states
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}
										}

										// The alpha channel of target 3 has real information
										m_bColorTarget3AlphaUsed = true;
									}

									// Set reflection parameters
									if (bReflection) {
										// Set the "ReflectionColor" fragment shader parameter
										if (m_pGeneratedProgramUserData->pReflectionColor)
											m_pGeneratedProgramUserData->pReflectionColor->Set(cReflectionColor);

										// Set the "Reflectivity" fragment shader parameter
										if (m_pGeneratedProgramUserData->pReflectivity)
											m_pGeneratedProgramUserData->pReflectivity->Set(fReflectivity);

										// Set the "ReflectivityMap" fragment shader parameter
										if (m_pGeneratedProgramUserData->pReflectivityMap) {
											const int nTextureUnit = m_pGeneratedProgramUserData->pReflectivityMap->Set(pReflectivityMap);
											if (nTextureUnit >= 0) {
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}
										}

										// Use Fresnel reflection?
										if (m_pGeneratedProgramUserData->pFresnelConstants) {
											// Calculate the eta value
											// [TODO] Make the "from material" also setable per material or global?
											static const float AirIndexOfRefaction = 1.0f;
											const float fEtaValue = AirIndexOfRefaction / fIndexOfRefraction; // "from material" -> "to material"

											// Set the "FresnelConstants" fragment shader parameter
											static const String sFresnelConstants = "FresnelConstants";
											const float fR0 = Math::Saturate(Math::Pow(1.0f - fEtaValue, 2.0f) / Math::Pow(1.0f + fEtaValue, 2.0f));
											m_pGeneratedProgramUserData->pFresnelConstants->Set(fR0, fFresnelReflectionPower);
										}

										// Set the "ReflectionMap" fragment shader parameter
										if (m_pGeneratedProgramUserData->pReflectionMap) {
											const int nTextureUnit = m_pGeneratedProgramUserData->pReflectionMap->Set(pReflectionMap);
											if (nTextureUnit >= 0) {
												// Setup sampler states
												if (b2DReflectionMap) {
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
												} else {
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
													cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
												}
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}

											// Set the "ViewSpaceToWorldSpace" fragment shader parameter
											if (m_pGeneratedProgramUserData->pViewSpaceToWorldSpace) {
												// [TODO] Add *SNCamera::GetInvViewMatrix()?
												Matrix3x3 mRot;
												if (SNCamera::GetCamera()) mRot = SNCamera::GetCamera()->GetViewMatrix().GetInverted();
												else					   mRot = Matrix3x3::Identity;
												m_pGeneratedProgramUserData->pViewSpaceToWorldSpace->Set(mRot);
											}
										}
									}
								}
							}

							// Vertex shader program
							if (m_pGeneratedProgramUserData) {
								// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
								if (m_pGeneratedProgramUserData->pVertexPosition)
									m_pGeneratedProgramUserData->pVertexPosition->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);
								if (m_pGeneratedProgramUserData->pVertexTexCoord0)
									m_pGeneratedProgramUserData->pVertexTexCoord0->Set(&cVertexBuffer, PLRenderer::VertexBuffer::TexCoord);
								if (m_pGeneratedProgramUserData->pVertexTexCoord1)
									m_pGeneratedProgramUserData->pVertexTexCoord1->Set(&cVertexBuffer, PLRenderer::VertexBuffer::TexCoord, 1);
								if (m_pGeneratedProgramUserData->pVertexNormal)
									m_pGeneratedProgramUserData->pVertexNormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Normal);
								if (m_pGeneratedProgramUserData->pVertexTangent)
									m_pGeneratedProgramUserData->pVertexTangent->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Tangent);
								if (m_pGeneratedProgramUserData->pVertexBinormal)
									m_pGeneratedProgramUserData->pVertexBinormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Binormal);

								// Two sided lighting?
								if (m_pGeneratedProgramUserData->pNormalScale)
									m_pGeneratedProgramUserData->pNormalScale->Set(1.0f);

								// Set world view projection matrix
								if (m_pGeneratedProgramUserData->pWorldVP)
									m_pGeneratedProgramUserData->pWorldVP->Set(cVisNode.GetWorldViewProjectionMatrix());

								// Set world view matrix
								if (m_pGeneratedProgramUserData->pWorldV)
									m_pGeneratedProgramUserData->pWorldV->Set(cVisNode.GetWorldViewMatrix());

								// Set object space eye position
								if (m_pGeneratedProgramUserData->pEyePos)
									m_pGeneratedProgramUserData->pEyePos->Set(cVisNode.GetInverseWorldMatrix()*(cVisContainer.GetWorldMatrix()*cCullQuery.GetCameraPosition()));
							}
						}

						// Draw the geometry
						cRenderer.DrawIndexedPrimitives(
							cGeometry.GetPrimitiveType(),
							0,
							cVertexBuffer.GetNumOfElements()-1,
							cGeometry.GetStartIndex(),
							cGeometry.GetIndexSize()
						);

						// If this is a two sided material, draw the primitives again - but with
						// flipped culling mode and vertex normals
						if (m_pGeneratedProgramUserData && m_pGeneratedProgramUserData->pNormalScale) {
							// Flip normals
							m_pGeneratedProgramUserData->pNormalScale->Set(-1.0f);

							// Flip the backface culling
							const uint32 nCullModeBackup = cRenderer.GetRenderState(RenderState::CullMode);
							cRenderer.SetRenderState(RenderState::CullMode, Cull::CW);

							// Draw geometry - again
							cRenderer.DrawIndexedPrimitives(
								cGeometry.GetPrimitiveType(),
								0,
								cVertexBuffer.GetNumOfElements()-1,
								cGeometry.GetStartIndex(),
								cGeometry.GetIndexSize()
							);

							// Restore the previous cull mode
							cRenderer.SetRenderState(RenderState::CullMode, nCullModeBackup);
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
void SRPDeferredGBuffer::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the shader language to use
	String sShaderLanguage = ShaderLanguage;
	if (!sShaderLanguage.GetLength())
		sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

	// Create the program generator if there's currently no instance of it
	if (!m_pProgramGenerator || m_pProgramGenerator->GetShaderLanguage() != sShaderLanguage) {
		// If there's an previous instance of the program generator, destroy it first
		if (m_pProgramGenerator) {
			delete m_pProgramGenerator;
			m_pProgramGenerator = NULL;
		}

		// Choose the shader source codes depending on the requested shader language
		String sDeferredGBuffer_VS;
		String sDeferredGBuffer_FS;
		if (sShaderLanguage == "GLSL") {
			#include "SRPDeferredGBuffer_GLSL.h"
			sDeferredGBuffer_VS = sDeferredGBuffer_GLSL_VS;
			sDeferredGBuffer_FS = sDeferredGBuffer_GLSL_FS;
		} else if (sShaderLanguage == "Cg") {
			#include "SRPDeferredGBuffer_Cg.h"
			sDeferredGBuffer_VS = sDeferredGBuffer_Cg_VS;
			sDeferredGBuffer_FS = sDeferredGBuffer_Cg_FS;
		}

		// Create the program generator
		if (sDeferredGBuffer_VS.GetLength() && sDeferredGBuffer_FS.GetLength())
			m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredGBuffer_VS, "arbvp1", sDeferredGBuffer_FS, "arbfp1", true);
	}

	// If there's no program generator, we don't need to continue
	if (m_pProgramGenerator) {
		// Create the fullscreen quad instance if required
		if (!m_pFullscreenQuad)
			m_pFullscreenQuad = new FullscreenQuad(cRenderer);

		// Get the size of the current render target
		const Vector2i vRTSize = cRenderer.GetRenderTarget()->GetSize();
		if (vRTSize.x != 0 && vRTSize.y != 0) {
			// Get the internal texture format to use
			const TextureBuffer::EPixelFormat nInternalFormat = (GetFlags() & Float32) ? TextureBuffer::R32G32B32A32F : TextureBuffer::R16G16B16A16F;

			// Render target size change?
			if (m_pRenderTarget && (m_pRenderTarget->GetSize() != vRTSize || m_pRenderTarget->GetFormat() != nInternalFormat)) {
				// Destroy the render target of the GBuffer
				if (m_pRenderTarget) {
					delete m_pRenderTarget;
					m_pRenderTarget = NULL;
				}
				if (m_pColorTarget1) {
					delete m_pColorTarget1;
					m_pColorTarget1 = NULL;
				}
				if (m_pColorTarget2) {
					delete m_pColorTarget2;
					m_pColorTarget2 = NULL;
				}
				if (m_pColorTarget3) {
					delete m_pColorTarget3;
					m_pColorTarget3 = NULL;
				}
			}

			// Create the render target of the GBuffer right now?
			if (!m_pRenderTarget) {
				m_pRenderTarget = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing, 4);
				{ // Create color target 1, 2 and 3
					Image cImage;
					ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
					pImageBuffer->CreateImage(DataFloat, ColorRGBA, Vector3i(vRTSize.x, vRTSize.y, 1));
					// [TODO] Currently, I just assume a real rectangle instance... find a better way!
					m_pColorTarget1 = (TextureBufferRectangle*)cRenderer.CreateTextureBufferRectangle(cImage, nInternalFormat, TextureBuffer::RenderTarget);
					m_pColorTarget2 = (TextureBufferRectangle*)cRenderer.CreateTextureBufferRectangle(cImage, nInternalFormat, TextureBuffer::RenderTarget);
					m_pColorTarget3 = (TextureBufferRectangle*)cRenderer.CreateTextureBufferRectangle(cImage, nInternalFormat, TextureBuffer::RenderTarget);
				}
			}
		}

		// Is there a render target?
		if (m_pRenderTarget) {
			// Backup the current render target, pass on the depth buffer of the surface texture buffer and set the new render target
			m_pSurfaceBackup = cRenderer.GetRenderTarget();
			if (m_pSurfaceBackup->GetType() == Surface::TextureBuffer)
				m_pRenderTarget->TakeDepthBufferFromSurfaceTextureBuffer((SurfaceTextureBuffer&)*m_pSurfaceBackup);
			cRenderer.SetRenderTarget(m_pRenderTarget);
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget1, 1);
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget2, 2);
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget3, 3);

			// Reset all render states to default
			cRenderer.GetRendererContext().GetEffectManager().Use();

			// Clear the GBuffer content
			if (GetFlags() & NoStencil) {
				// Do only clear the color buffer
				cRenderer.Clear(Clear::Color, Color4(0.0f, 0.0f, 0.0f, 0.0f));
			} else {
				// Clear color buffer and stencil buffer
				cRenderer.Clear(Clear::Color | Clear::Stencil, Color4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1);

				// Enable stencil test - if something is written, the pixel is tagged with 0
				cRenderer.SetRenderState(RenderState::StencilEnable, true);
				cRenderer.SetRenderState(RenderState::StencilRef,    0);
				cRenderer.SetRenderState(RenderState::StencilPass,   StencilOp::Replace);
			}

			// Backup the color mask
			bool bRed, bGreen, bBlue, bAlpha;
			cRenderer.GetColorMask(bRed, bGreen, bBlue, bAlpha);

			// Setup the color mask and enable scissor test
			cRenderer.SetColorMask(true, true, true, true);
			cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

			// Reset current states
			m_nMaterialChanges			= 0;
			m_pCurrentMaterial			= NULL;
			m_pGeneratedProgramUserData	= NULL;
			m_bColorTarget3Used			= false;
			m_bColorTarget3AlphaUsed	= false;

			// Draw recursive from front to back
			DrawRec(cRenderer, cCullQuery);

			// Restore the color mask
			cRenderer.SetColorMask(bRed, bGreen, bBlue, bAlpha);

			// Give back the depth buffer of the surface texture buffer and restore the previously set render target
			if (m_pSurfaceBackup->GetType() == Surface::TextureBuffer)
				((SurfaceTextureBuffer*)m_pSurfaceBackup)->TakeDepthBufferFromSurfaceTextureBuffer(*m_pRenderTarget);
			cRenderer.SetRenderTarget(m_pSurfaceBackup);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
