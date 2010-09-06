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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLMath/Matrix3x3.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/RenderStates.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
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
	m_pCurrentMaterial(NULL)
{
	// Init shader handler data
	MemoryManager::Set(m_bVertexShader,   0, sizeof(m_bVertexShader));
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGBuffer::~SRPDeferredGBuffer()
{
	// Destroy all used shaders
	DestroyShaders();

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
*    Returns an ambient/emissive vertex shader
*/
Shader *SRPDeferredGBuffer::GetVertexShader(Renderer &cRenderer, bool bDiffuseMap, bool bParallax, bool bDisplacementMap, bool bAmbientOcclusionMap, bool bNormalMap, bool bEmissiveMap, bool bReflection, bool bLightMap, bool bTwoSided, float fAlphaReference)
{
	// Take diffuse map into account? (if ambient color is black, we don't need it :)
	bool bAmbientColor = true;
	bDiffuseMap = (bAmbientColor && bDiffuseMap) || bEmissiveMap || fAlphaReference != 0.0f;
	if (!bAmbientColor)
		bLightMap = false; // No ambient color, no light map required :)

	// Tangent and binormal required?
	bool bTangentBinormal = bNormalMap || bParallax;

	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cVertexShader[bDiffuseMap][bParallax][bDisplacementMap][bAmbientOcclusionMap][bTangentBinormal][bEmissiveMap][bReflection][bLightMap][bTwoSided];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bVertexShader[bDiffuseMap][bParallax][bDisplacementMap][bAmbientOcclusionMap][bTangentBinormal][bEmissiveMap][bReflection][bLightMap][bTwoSided]) {
		const static String ShaderFilename = "Vertex/SRPDeferredGBuffer.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bTwoSided) {
			sDefines += "#define TWOSIDED\n";
			sName    += "[TwoSided]";
		}
		if (bDisplacementMap) {
			sDefines += "#define USE_DISPLACEMENTMAP\n";
			sName    += "[DisplacementMap]";
		}
		if (bAmbientOcclusionMap) {
			sDefines += "#define USE_AMBIENTOCCLUSIONMAP\n";
			sName    += "[AmbientOcclusionMap]";
		}
		if (bLightMap) {
			sDefines += "#define USE_LIGHTMAP\n";
			sName    += "[LightMap]";
		}
		if (bTangentBinormal) {
			sDefines += "#define TANGENT_BINORMAL\n";
			sName    += "[TangentBinormal]";
		}
		if (bReflection) {
			sDefines += "#define USE_REFLECTION\n";
			sName    += "[Reflection]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGBuffer_Cg_VS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGBuffer_Cg_VS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, false, "arbvp1", sDefines); // [TODO] Use "glslv" profile for vertex texture fetch... but it looks like this is messing up with for example "TANGENT" input semantics (in the future, I will use pur GLSL instead of Cg for this anyway :)
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bVertexShader[bDiffuseMap][bParallax][bDisplacementMap][bAmbientOcclusionMap][bTangentBinormal][bEmissiveMap][bReflection][bLightMap][bTwoSided] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns an ambient/emissive fragment shader
*/
Shader *SRPDeferredGBuffer::GetFragmentShader(Renderer &cRenderer, bool bDiffuseMap, bool bSpecular, bool bSpecularMap, bool bParallax, bool bAmbientOcclusionMap, bool bEmissiveMap, bool b2DReflection, bool bCubeReflection, bool bReflectivityMap, bool bLightMap, bool bAlphaTest, bool bNormalMap, bool bNormalMap_DXT5_xGxR, bool bDetailNormalMap, bool bDetailNormalMap_DXT5_xGxR, float fAlphaReference, bool bFresnelReflection, bool bGlow, bool bGlowMap, bool bGammaCorrection)
{
	// Check reflection settings
	if (b2DReflection && bCubeReflection)
		b2DReflection = bCubeReflection = false; // Invalid state!
	const bool bReflection = (bFresnelReflection || b2DReflection || bCubeReflection);

	// Normal mapping logic checks
	if (bNormalMap) {
		if (!bDetailNormalMap)
			bDetailNormalMap_DXT5_xGxR = false;
	} else {
		bNormalMap_DXT5_xGxR = bDetailNormalMap = bDetailNormalMap_DXT5_xGxR = false;
	}

	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bDiffuseMap][bSpecular][bSpecularMap][bParallax][bAmbientOcclusionMap][bEmissiveMap][b2DReflection][bCubeReflection][bReflectivityMap][bLightMap][bAlphaTest][bNormalMap][bNormalMap_DXT5_xGxR][bDetailNormalMap][bDetailNormalMap_DXT5_xGxR][bFresnelReflection][bGlow][bGlowMap][bReflection][bGammaCorrection];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bDiffuseMap][bSpecular][bSpecularMap][bParallax][bAmbientOcclusionMap][bEmissiveMap][b2DReflection][bCubeReflection][bReflectivityMap][bLightMap][bAlphaTest][bNormalMap][bNormalMap_DXT5_xGxR][bDetailNormalMap][bDetailNormalMap_DXT5_xGxR][bFresnelReflection][bGlow][bGlowMap][bReflection][bGammaCorrection]) {
		const static String ShaderFilename = "Fragment/SRPDeferredGBuffer.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bDiffuseMap) {
			sDefines += "#define USE_DIFFUSEMAP\n";
			sName    += "[DiffuseMap]";
			if (bAlphaTest) {
				sDefines += "#define USE_ALPHATEST\n";
				sName    += "[AlphaTest]";
			}
		}
		if (bSpecular) {
			sDefines += "#define USE_SPECULAR\n";
			sName    += "[Specular]";
			if (bSpecularMap) {
				sDefines += "#define USE_SPECULARMAP\n";
				sName    += "[SpecularMap]";
			}
		}
		if (bNormalMap) {
			sDefines += "#define USE_NORMALMAP\n";
			sName    += "[NormalMap]";
			if (bNormalMap_DXT5_xGxR) {
				sDefines += "#define NORMALMAP_DXT5_XGXR\n";
				sName    += "[NormalMap_DXT5_xGxR]";
			}
			if (bDetailNormalMap) {
				sDefines += "#define USE_DETAILNORMALMAP\n";
				sName    += "[DetailNormalMap]";
				if (bDetailNormalMap_DXT5_xGxR) {
					sDefines += "#define DETAILNORMALMAP_DXT5_XGXR\n";
					sName    += "[DetailNormalMap_DXT5_xGxR]";
				}
			}
		}
		if (bParallax) {
			sDefines += "#define USE_PARALLAXMAPPING\n";
			sName    += "[ParallaxMapping]";
		}
		if (bAmbientOcclusionMap) {
			sDefines += "#define USE_AMBIENTOCCLUSIONMAP\n";
			sName    += "[AmbientOcclusionMap]";
		}
		if (bLightMap) {
			sDefines += "#define USE_LIGHTMAP\n";
			sName    += "[LightMap]";
		}
		if (bEmissiveMap) {
			sDefines += "#define USE_EMISSIVEMAP\n";
			sName    += "[EmissiveMap]";
		}
		if (bGlow) {
			sDefines += "#define USE_GLOW\n";
			sName    += "[Glow]";
			if (bGlowMap) {
				sDefines += "#define USE_GLOWMAP\n";
				sName    += "[GlowMap]";
			}
		}
		if (bReflection) {
			sDefines += "#define USE_REFLECTION\n";
			sName    += "[Reflection]";
			if (bFresnelReflection) {
				sDefines += "#define USE_FRESNELREFLECTION\n";
				sName    += "[FresnelReflection]";
			}
			if (bReflectivityMap) {
				sDefines += "#define USE_REFLECTIVITYMAP\n";
				sName    += "[ReflectivityMap]";
			}
			if (b2DReflection) {
				sDefines += "#define USE_2DREFLECTIONMAP\n";
				sName    += "[ReflectionMap2D]";
			} else if (bCubeReflection) {
				sDefines += "#define USE_CUBEREFLECTIONMAP\n";
				sName    += "[ReflectionMapCube]";
			}
		}
		if (bGammaCorrection) {
			sDefines += "#define USE_GAMMACORRECTION\n";
			sName    += "[GammaCorrection]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGBuffer_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGBuffer_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "arbfp1", sDefines); // "glslf" would be nice, but then, the "discard" keyword seems to have no effect :/
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bDiffuseMap][bSpecular][bSpecularMap][bParallax][bAmbientOcclusionMap][bEmissiveMap][b2DReflection][bCubeReflection][bReflectivityMap][bLightMap][bAlphaTest][bNormalMap][bNormalMap_DXT5_xGxR][bDetailNormalMap][bDetailNormalMap_DXT5_xGxR][bFresnelReflection][bGlow][bGlowMap][bReflection][bGammaCorrection] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredGBuffer::DestroyShaders()
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
						if (pLODLevel && pLODLevel->GetIndexBuffer()) {
							// Draw the mesh
							DrawMesh(cRenderer, cCullQuery, *pVisNode, *pSceneNode, *pMeshHandler, *pMesh, *pLODLevel);

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
void SRPDeferredGBuffer::DrawMesh(Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, SceneNode &cSceneNode, const MeshHandler &cMeshHandler, const Mesh &cMesh, const MeshLODLevel &cMeshLODLevel)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Get buffers
		  IndexBuffer     *pIndexBuffer  = cMeshLODLevel.GetIndexBuffer();
	const Array<Geometry> &lstGeometries = *cMeshLODLevel.GetGeometries();

	// Bind buffers
	cRenderer.SetIndexBuffer(pIndexBuffer);
	// [TODO] Remove FixedFunctions usage by using the new shader interface
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions)
		pFixedFunctions->SetVertexBuffer(cMeshHandler.GetVertexBuffer());

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
						ShaderProgram *pVertexShaderProgram = cRenderer.GetVertexShaderProgram();
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
											if (pNormalMapTexture && (pNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR || pNormalMapTexture->GetCompressionHint() == Texture::LATC2_XYSwizzle))
												bNormalMap_DXT5_xGxR = true;	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
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
											if (pDetailNormalMapTexture && (pDetailNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR || pDetailNormalMapTexture->GetCompressionHint() == Texture::LATC2_XYSwizzle))
												bDetailNormalMap_DXT5_xGxR = true;	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
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

								// Use gamma correction?
								const bool bGammaCorrection = !(GetFlags() & NoGammaCorrection);

								// Get the shader with the given features
								Shader *pMeshVertexShader = GetVertexShader(cRenderer, pDiffuseMap != NULL || pReflectivityMap != NULL || pNormalMap != NULL, fParallax != 0.0f, pDisplacementMap != NULL, pAmbientOcclusionMap != NULL, pNormalMap != NULL, pEmissiveMap != NULL, bReflection, pLightMap != NULL, bTwoSided, fAlphaReference != 0.0f);
								if (pMeshVertexShader) {
									pVertexShaderProgram = pMeshVertexShader->GetShaderProgram();
									if (pVertexShaderProgram) {
										Shader *pMeshFragmentShader = GetFragmentShader(cRenderer, pDiffuseMap != NULL, bSpecular, pSpecularMap != NULL, fParallax != 0.0f, pAmbientOcclusionMap != NULL, pEmissiveMap != NULL, b2DReflectionMap && pReflectionMap, !b2DReflectionMap && pReflectionMap, pReflectivityMap != NULL, pLightMap != NULL, fAlphaReference != 0.0f, pNormalMap != NULL, bNormalMap_DXT5_xGxR, pDetailNormalMap != NULL, bDetailNormalMap_DXT5_xGxR, fAlphaReference, fIndexOfRefraction > 0.0f, fGlowFactor != 0.0f, pGlowMap != NULL, bGammaCorrection);
										if (pMeshFragmentShader) {
											ShaderProgram *pFragmentShaderProgram = pMeshFragmentShader->GetShaderProgram();
											if (pFragmentShaderProgram) {
											// Vertex shader program
												cRenderer.SetVertexShaderProgram(pVertexShaderProgram);

												// Set displacement map
												if (pDisplacementMap) {
													const int nStage = pVertexShaderProgram->SetParameterTextureBuffer(sDisplacementMap, pDisplacementMap);
													if (nStage >= 0) {
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
														SetupTextureFiltering(cRenderer, nStage);
													}

													// Set displacement scale bias
													static const String sDisplacementScaleBias = "DisplacementScaleBias";
													const Vector2 vDisplacementScaleBias(fDisplacementScale, fDisplacementBias);
													pVertexShaderProgram->SetParameter2fv(sDisplacementScaleBias, vDisplacementScaleBias);
												}

											// Fragment shader program
												cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

												{ // Set the "DiffuseColor" fragment shader parameter
													static const String sDiffuseColor = "DiffuseColor";
													pParameter = pMaterial->GetParameter(sDiffuseColor);
													if (pParameter) {
														float fDiffuseColor[3] = { 1.0f, 1.0f, 1.0f };
														pParameter->GetValue3f(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
														pFragmentShaderProgram->SetParameter3fv(sDiffuseColor, fDiffuseColor);
													} else {
														pFragmentShaderProgram->SetParameter3f(sDiffuseColor, 1.0f, 1.0f, 1.0f);
													}
												}

												// Diffuse
												if (pDiffuseMap) {
													// Set the "DiffuseMap" fragment shader parameter
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::DiffuseMap, pDiffuseMap);
													if (nStage >= 0) {
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
														SetupTextureFiltering(cRenderer, nStage);
													}

													// Set the "AlphaReference" fragment shader parameter
													if (fAlphaReference != 0.0f) {
														static const String sAlphaReference = "AlphaReference";
														pFragmentShaderProgram->SetParameter1f(sAlphaReference, fAlphaReference);
													}
												}

												// Specular
												if (bSpecular) {
													// Set specular exponent and specular color
													pFragmentShaderProgram->SetParameter3fv(sSpecularColor,    cSpecularColor);
													pFragmentShaderProgram->SetParameter1f (sSpecularExponent, fSpecularExponent);

													// Set the "SpecularMap" fragment shader parameter
													if (pSpecularMap) {
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::SpecularMap, pSpecularMap);
														if (nStage >= 0) {
															cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
															cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
															SetupTextureFiltering(cRenderer, nStage);
														}
													}
												}

												// Normal map
												if (pNormalMap) {
													{ // Set normal map
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::NormalMap, pNormalMap);
														if (nStage >= 0) {
															cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
															cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
															SetupTextureFiltering(cRenderer, nStage);
														}

														// Set normal map bumpiness
														pFragmentShaderProgram->SetParameter1f(sNormalMapBumpiness, fNormalMapBumpiness);
													}

													// Detail normal map
													if (pDetailNormalMap) {
														// Set detail normal map
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sDetailNormalMap, pDetailNormalMap);
														if (nStage >= 0) {
															cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
															cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
															SetupTextureFiltering(cRenderer, nStage);
														}

														// Set detail normal map bumpiness and uv scale
														pFragmentShaderProgram->SetParameter1f (sDetailNormalMapBumpiness, fDetailNormalMapBumpiness);
														pFragmentShaderProgram->SetParameter2fv(sDetailNormalMapUVScale,   vDetailNormalMapUVScale);
													}
												}

												// Set height map
												if (pHeightMap) {
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::HeightMap, pHeightMap);
													if (nStage >= 0) {
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
														SetupTextureFiltering(cRenderer, nStage);
													}

													// Set parallax scale bias
													static const String sParallaxScaleBias = "ParallaxScaleBias";
													const Vector2 vParallaxScaleBias(fParallax, -0.02f);
													pFragmentShaderProgram->SetParameter2fv(sParallaxScaleBias, vParallaxScaleBias);
												}

												// Set ambient occlusion map
												if (pAmbientOcclusionMap) {
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::AmbientOcclusionMap, pAmbientOcclusionMap);
													if (nStage >= 0) {
														// Setup sampler states
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
														SetupTextureFiltering(cRenderer, nStage);

														// Set ambient occlusion factor
														float fAmbientOcclusionFactor = 1.0f;
														static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
														pParameter = pMaterial->GetParameter(sAmbientOcclusionFactor);
														if (pParameter)
															pParameter->GetValue1f(fAmbientOcclusionFactor);
														pFragmentShaderProgram->SetParameter1f(sAmbientOcclusionFactor, fAmbientOcclusionFactor);
													}
												}

												// Set light map
												if (pLightMap) {
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::LightMap, pLightMap);
													if (nStage >= 0) {
														// Setup sampler states
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
														SetupTextureFiltering(cRenderer, nStage);

														// Set light map color
														float fLightMapColor[3] = { 1.0f, 1.0f, 1.0f };
														static const String sLightMapColor = "LightMapColor";
														pParameter = pMaterial->GetParameter(sLightMapColor);
														if (pParameter)
															pParameter->GetValue3f(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
														pFragmentShaderProgram->SetParameter3fv(sLightMapColor, fLightMapColor);
													}

													// Color target 3 has real information
													m_bColorTarget3Used = true;
												}

												// Set emissive map
												if (pEmissiveMap) {
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::EmissiveMap, pEmissiveMap);
													if (nStage >= 0) {
														// Setup sampler states
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
														SetupTextureFiltering(cRenderer, nStage);

														// Set emissive color
														float fEmissiveMapColor[3] = { 1.0f, 1.0f, 1.0f };
														static const String sEmissiveMapColor = "EmissiveMapColor";
														pParameter = pMaterial->GetParameter(sEmissiveMapColor);
														if (pParameter)
															pParameter->GetValue3f(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
														pFragmentShaderProgram->SetParameter3fv(sEmissiveMapColor, fEmissiveMapColor);
													}

													// Color target 3 has real information
													m_bColorTarget3Used = true;
												}

												// Set the "GlowFactor" fragment shader parameter
												if (fGlowFactor != 0.0f) {
													static const String sGlowFactor = "GlowFactor";
													pFragmentShaderProgram->SetParameter1f(sGlowFactor, fGlowFactor);

													// Set glow map
													if (pGlowMap) {
														static const String sGlowMap = "GlowMap";
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sGlowMap, pGlowMap);
														if (nStage >= 0) {
															// Setup sampler states
															cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
															cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
															SetupTextureFiltering(cRenderer, nStage);
														}
													}

													// The alpha channel of target 3 has real information
													m_bColorTarget3AlphaUsed = true;
												}

												// Set reflection parameters
												if (bReflection) {
													// Set the "ReflectionColor" fragment shader parameter
													pFragmentShaderProgram->SetParameter3fv(sReflectionColor, cReflectionColor);

													// Set the "Reflectivity" fragment shader parameter
													pFragmentShaderProgram->SetParameter1f(sReflectivity, fReflectivity);

													// Set the "ReflectivityMap" fragment shader parameter
													if (pReflectivityMap) {
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::ReflectivityMap, pReflectivityMap);
														if (nStage >= 0) {
															cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
															cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
															SetupTextureFiltering(cRenderer, nStage);
														}
													}

													// Use Fresnel reflection?
													if (fIndexOfRefraction > 0.0f) {
														// Calculate the eta value
														// [TODO] Make the "from material" also setable per material or global?
														static const float AirIndexOfRefaction = 1.0f;
														const float fEtaValue = AirIndexOfRefaction / fIndexOfRefraction; // "from material" -> "to material"

														// Set the "FresnelConstants" fragment shader parameter
														static const String sFresnelConstants = "FresnelConstants";
														const float fR0 = Math::Saturate(Math::Pow(1.0f - fEtaValue, 2.0f) / Math::Pow(1.0f + fEtaValue, 2.0f));
														pFragmentShaderProgram->SetParameter2f(sFresnelConstants, fR0, fFresnelReflectionPower);
													}

													// Set the "ReflectionMap" fragment shader parameter
													if (pReflectionMap) {
														const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(Material::ReflectionMap, pReflectionMap);
														if (nStage >= 0) {
															// Setup sampler states
															if (b2DReflectionMap) {
																cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
																cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
															} else {
																cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
																cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
															}
															SetupTextureFiltering(cRenderer, nStage);
														}

														{ // Set the "ViewSpaceToWorldSpace" fragment shader parameter
															// [TODO] Add *SNCamera::GetInvViewMatrix()?
															Matrix3x3 mRot;
															if (SNCamera::GetCamera()) mRot = SNCamera::GetCamera()->GetViewMatrix().GetInverted();
															else					   mRot = Matrix3x3::Identity;
															static const String sViewSpaceToWorldSpace = "ViewSpaceToWorldSpace";
															pFragmentShaderProgram->SetParameterFloat3x3(sViewSpaceToWorldSpace, mRot);
														}
													}
												}
											}
										}
									}
								}
							}

							// Vertex shader program
							if (pVertexShaderProgram) {
								// Two sided?
								if (bTwoSided) {
									static const String sNormalScale = "NormalScale";
									pVertexShaderProgram->SetParameter1f(sNormalScale, 1.0f);
								}

								// Set world view projection matrix
								static const String sWorldVP = "WorldVP";
								pVertexShaderProgram->SetParameterMatrixfv(sWorldVP, cVisNode.GetWorldViewProjectionMatrix());

								// Set world view matrix
								static const String sWorldV = "WorldV";
								pVertexShaderProgram->SetParameterMatrixfv(sWorldV, cVisNode.GetWorldViewMatrix());

								// Set object space eye position
								if (pHeightMap || pReflectionMap) {
									static const String sEyePos = "EyePos";
									pVertexShaderProgram->SetParameter3fv(sEyePos, cVisNode.GetInverseWorldMatrix()*(cVisContainer.GetWorldMatrix()*cCullQuery.GetCameraPosition()));
								}
							}
						}

						// Draw geometry
						cRenderer.DrawIndexedPrimitives(
							cGeometry.GetPrimitiveType(),
							0,
							cMeshHandler.GetVertexBuffer()->GetNumOfElements()-1,
							cGeometry.GetStartIndex(),
							cGeometry.GetIndexSize()
						);

						// If this is a two sided material, draw the primitives again - but with
						// flipped culling mode and vertex normals
						if (bTwoSided && pVertexShaderProgram) {
							// Setup cull mode - because two sided materials usually not used
							// often, we reset the state after we're done
							cRenderer.SetRenderState(RenderState::CullMode, Cull::CW);

							// Flip normals
							static const String sNormalScale = "NormalScale";
							pVertexShaderProgram->SetParameter1f(sNormalScale, -1.0f);

							// Draw geometry
							cRenderer.DrawIndexedPrimitives(
								cGeometry.GetPrimitiveType(),
								0,
								cMeshHandler.GetVertexBuffer()->GetNumOfElements()-1,
								cGeometry.GetStartIndex(),
								cGeometry.GetIndexSize()
							);

							// Reset cull mode
							pVertexShaderProgram->SetParameter1f(sNormalScale, 1.0f);
							cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
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
		m_nMaterialChanges		 = 0;
		m_pCurrentMaterial		 = NULL;
		m_bColorTarget3Used		 = false;
		m_bColorTarget3AlphaUsed = false;

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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
