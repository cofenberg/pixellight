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
	m_pProgramGenerator(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGBuffer::~SRPDeferredGBuffer()
{
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

	// Destroy all mesh batches
	{ // Currently free ones
		Iterator<MeshBatch*> cIterator = m_lstFreeMeshBatches.GetIterator();
		while (cIterator.HasNext())
			delete cIterator.Next();
		m_lstFreeMeshBatches.Clear();
	}
	{ // Currently used ones
		Iterator<MeshBatch*> cIterator = m_lstMeshBatches.GetIterator();
		while (cIterator.HasNext())
			delete cIterator.Next();
		m_lstMeshBatches.Clear();
	}
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
*    Collect mesh batches recursive
*/
void SRPDeferredGBuffer::CollectMeshBatchesRec(const SQCull &cCullQuery)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

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
				if (pVisCell && pVisCell->GetCullQuery())
					CollectMeshBatchesRec(*pVisCell->GetCullQuery());

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Collect this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery())
					CollectMeshBatchesRec(*((const VisContainer*)pVisNode)->GetCullQuery());

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
							// Loop through all mesh geometries
							const Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
							for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
								// Is this geometry active and is it using the current used mesh material?
								const Geometry &cGeometry = lstGeometries[nGeo];
								if (cGeometry.IsActive()) {
									// Get the material the mesh geometry is using
									const Material *pMaterial = pMeshHandler->GetMaterial(cGeometry.GetMaterial());
									if (pMaterial) {
										// Transparent material?
										static const String sOpacity = "Opacity";
										const Parameter *pParameter = pMaterial->GetParameter(sOpacity);
										if (!pParameter || pParameter->GetValue1f() >= 1.0f) {
											// Get a free mesh batch
											MeshBatch &cMeshBatch = GetFreeMeshBatch();
											m_lstMeshBatches.Add(&cMeshBatch);

											// Fill the mesh batch
											cMeshBatch.pMaterial			= pMaterial;
											cMeshBatch.pVertexBuffer		= pMeshHandler->GetVertexBuffer();
											cMeshBatch.pIndexBuffer			= pLODLevel->GetIndexBuffer();
											cMeshBatch.pCullQuery			= &cCullQuery;
											cMeshBatch.pGeometry			= &cGeometry;
											cMeshBatch.pVisNode				= pVisNode;
											cMeshBatch.sScissorRectangle	= cVisContainer.GetProjection().cRectangle;

											// Add material
											if (!m_lstMaterials.IsElement(pMaterial))
												m_lstMaterials.Add(pMaterial);
										}
									}
								}
							}

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
*    Makes a material to the currently used one
*/
SRPDeferredGBuffer::GeneratedProgramUserData *SRPDeferredGBuffer::MakeMaterialCurrent(Renderer &cRenderer, const Material &cMaterial)
{
	const Parameter *pParameter = NULL;

	// Two sided?
	bool bTwoSided = false;
	{
		static const String sTwoSided = "TwoSided";
		pParameter = cMaterial.GetParameter(sTwoSided);
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
		pParameter = cMaterial.GetParameter(sDisplacementScale);
		if (pParameter)
			pParameter->GetValue1f(fDisplacementScale);

		// Get displacement bias
		static const String sDisplacementBias  = "DisplacementBias";
		pParameter = cMaterial.GetParameter(sDisplacementBias);
		if (pParameter)
			pParameter->GetValue1f(fDisplacementBias);

		// Get displacement map
		if (fDisplacementScale != 0.0f) {
			pDisplacementMap = cMaterial.GetParameterTextureBuffer(sDisplacementMap);
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
		pParameter = cMaterial.GetParameter(sIndexOfRefraction);
		if (pParameter)
			fIndexOfRefraction = pParameter->GetValue1f();
		if (fIndexOfRefraction > 0.0f) {
			// FresnelReflectionPower
			static const String sFresnelReflectionPower = "FresnelReflectionPower";
			pParameter = cMaterial.GetParameter(sFresnelReflectionPower);
			if (pParameter) {
				fFresnelReflectionPower = pParameter->GetValue1f();

				// Ensure that the value is always >0 to avoid NAN production
				if (fFresnelReflectionPower < FLT_MIN)
					fFresnelReflectionPower = FLT_MIN;
			}
		}
	}

	// Get (2D/cube) reflection map
	TextureBuffer *pReflectionMap = (GetFlags() & NoReflectionMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::ReflectionMap);
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
		pParameter = cMaterial.GetParameter(sReflectionColor);
		if (pParameter)
			cReflectionColor = pParameter->GetValue3fv();

		// Get reflectivity map
		if (!(GetFlags() & NoReflectivityMap))
			pReflectivityMap = cMaterial.GetParameterTextureBuffer(Material::ReflectivityMap);

		// Get reflectivity 
		pParameter = cMaterial.GetParameter(sReflectivity);
		if (pParameter)
			fReflectivity = pParameter->GetValue1f();
	}

	// Get parallax mapping settings
	float fParallax = 0.04f;
	TextureBuffer *pHeightMap = NULL;
	if (!(GetFlags() & NoParallaxMapping)) {
		// Get parallax
		static const String sParallax = "Parallax";
		pParameter = cMaterial.GetParameter(sParallax);
		if (pParameter)
			pParameter->GetValue1f(fParallax);

		// Get height map
		if (fParallax != 0.0f)
			pHeightMap = cMaterial.GetParameterTextureBuffer(Material::HeightMap);
	}
	// No height map = no parallax mapping possible
	if (!pHeightMap)
		fParallax = 0.0f;

	// Get glow
	float		   fGlowFactor = 0.0f;
	TextureBuffer *pGlowMap    = NULL;
	if (!(GetFlags() & NoGlow)) {
		static const String sGlow = "Glow";
		pParameter = cMaterial.GetParameter(sGlow);
		if (pParameter) {
			fGlowFactor = pParameter->GetValue1f();

			// Get glow map
			if (fGlowFactor != 0.0f) {
				static const String sGlowMap = "GlowMap";
				pGlowMap = (GetFlags() & NoGlowMap) ? NULL : cMaterial.GetParameterTextureBuffer(sGlowMap);
			}
		}
	}

	// Get ambient occlusion map
	TextureBuffer *pAmbientOcclusionMap = (GetFlags() & NoAmbientOcclusionMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::AmbientOcclusionMap);

	// Get diffuse map and alpha reference
	float fAlphaReference = 0.0f;
	TextureBuffer *pDiffuseMap = (GetFlags() & NoDiffuseMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::DiffuseMap);

	// Enable/disable alpha test (fragments are thrown away inside the fragment shader using the 'discard' keyword)
	if (pDiffuseMap && pDiffuseMap->GetComponentsPerPixel() == 4) {
		// Get alpha reference
		static const String sAlphaReference = "AlphaReference";
		pParameter = cMaterial.GetParameter(sAlphaReference);
		fAlphaReference = pParameter ? pParameter->GetValue1f() : 0.5f;
	}

	// Get specular settings
	static const String sSpecularColor = "SpecularColor";
	bool bSpecular = false;
	Color3 cSpecularColor = Color3::White;
	if (!(GetFlags() & NoSpecular)) {
		// First, get specular color - if it's 0, we don't have any specular at all
		pParameter = cMaterial.GetParameter(sSpecularColor);
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
			pSpecularMap = cMaterial.GetParameterTextureBuffer(Material::SpecularMap);

		// Get specular exponent
		pParameter = cMaterial.GetParameter(sSpecularExponent);
		if (pParameter)
			pParameter->GetValue1f(fSpecularExponent);
	}

	// Get normal map
	TextureBuffer *pNormalMap = (GetFlags() & NoNormalMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::NormalMap);
	float fNormalMapBumpiness = 1.0f;
	bool bNormalMap_DXT5_xGxR = false;
	bool bNormalMap_LATC2     = false;
	static const String sNormalMapBumpiness = "NormalMapBumpiness";
	if (pNormalMap) {
		// Get normal map bumpiness
		const Parameter *pNormalMapParameter = cMaterial.GetParameter(sNormalMapBumpiness);
		if (pNormalMapParameter)
			fNormalMapBumpiness = pNormalMapParameter->GetValue1f();
		if (fNormalMapBumpiness != 0.0f) {
			// DXT5 xGxR normal map?
			pNormalMapParameter = cMaterial.GetParameter(Material::NormalMap);
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
	TextureBuffer *pDetailNormalMap = (!pNormalMap || (GetFlags() & NoDetailNormalMap)) ? NULL : cMaterial.GetParameterTextureBuffer(sDetailNormalMap);
	float fDetailNormalMapBumpiness = 1.0f;
	Vector2 vDetailNormalMapUVScale(4.0f, 4.0f);
	bool bDetailNormalMap_DXT5_xGxR = false;
	bool bDetailNormalMap_LATC2     = false;
	static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
	static const String sDetailNormalMapUVScale   = "DetailNormalMapUVScale";
	if (pDetailNormalMap) {
		// Get detail normal map bumpiness
		const Parameter *pDetailNormalMapParameter = cMaterial.GetParameter(sDetailNormalMapBumpiness);
		if (pDetailNormalMapParameter)
			fDetailNormalMapBumpiness = pDetailNormalMapParameter->GetValue1f();
		if (fDetailNormalMapBumpiness != 0.0f) {
			// Get detail normal map uv scale
			pDetailNormalMapParameter = cMaterial.GetParameter(sDetailNormalMapUVScale);
			if (pDetailNormalMapParameter)
				vDetailNormalMapUVScale = pDetailNormalMapParameter->GetValue2fv();

			// DXT5 xGxR detail normal map?
			pDetailNormalMapParameter = cMaterial.GetParameter(sDetailNormalMap);
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
	TextureBuffer *pLightMap = (GetFlags() & NoLightMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::LightMap);

	// Get emissive map
	TextureBuffer *pEmissiveMap = (GetFlags() & NoEmissiveMap) ? NULL : cMaterial.GetParameterTextureBuffer(Material::EmissiveMap);

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
	GeneratedProgramUserData *pGeneratedProgramUserData = NULL;
	if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
		// Set pointers to uniforms & attributes of a generated program if they are not set yet
		pGeneratedProgramUserData = (GeneratedProgramUserData*)pGeneratedProgram->pUserData;
		if (!pGeneratedProgramUserData) {
			pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
			Program *pProgram = pGeneratedProgram->pProgram;
			// Vertex shader attributes
			static const String sVertexPosition = "VertexPosition";
			pGeneratedProgramUserData->pVertexPosition	= pProgram->GetAttribute(sVertexPosition);
			static const String sVertexTexCoord0 = "VertexTexCoord0";
			pGeneratedProgramUserData->pVertexTexCoord0	= pProgram->GetAttribute(sVertexTexCoord0);
			static const String sVertexTexCoord1 = "VertexTexCoord1";
			pGeneratedProgramUserData->pVertexTexCoord1	= pProgram->GetAttribute(sVertexTexCoord1);
			static const String sVertexNormal = "VertexNormal";
			pGeneratedProgramUserData->pVertexNormal	= pProgram->GetAttribute(sVertexNormal);
			static const String sVertexTangent = "VertexTangent";
			pGeneratedProgramUserData->pVertexTangent	= pProgram->GetAttribute(sVertexTangent);
			static const String sVertexBinormal = "VertexBinormal";
			pGeneratedProgramUserData->pVertexBinormal	= pProgram->GetAttribute(sVertexBinormal);
			// Vertex shader uniforms
			static const String sNormalScale = "NormalScale";
			pGeneratedProgramUserData->pNormalScale					= pProgram->GetUniform(sNormalScale);
			static const String sEyePos = "EyePos";
			pGeneratedProgramUserData->pEyePos						= pProgram->GetUniform(sEyePos);
			static const String sWorldVP = "WorldVP";
			pGeneratedProgramUserData->pWorldVP						= pProgram->GetUniform(sWorldVP);
			static const String sWorldV = "WorldV";
			pGeneratedProgramUserData->pWorldV						= pProgram->GetUniform(sWorldV);
			static const String sDisplacementMap = "DisplacementMap";
			pGeneratedProgramUserData->pDisplacementMap				= pProgram->GetUniform(sDisplacementMap);
			static const String sDisplacementScaleBias = "DisplacementScaleBias";
			pGeneratedProgramUserData->pDisplacementScaleBias		= pProgram->GetUniform(sDisplacementScaleBias);
			// Fragment shader uniforms
			static const String sDiffuseColor = "DiffuseColor";
			pGeneratedProgramUserData->pDiffuseColor				= pProgram->GetUniform(sDiffuseColor);
			static const String sDiffuseMap = "DiffuseMap";
			pGeneratedProgramUserData->pDiffuseMap					= pProgram->GetUniform(sDiffuseMap);
			static const String sAlphaReference = "AlphaReference";
			pGeneratedProgramUserData->pAlphaReference				= pProgram->GetUniform(sAlphaReference);
			static const String sSpecularColor = "SpecularColor";
			pGeneratedProgramUserData->pSpecularColor				= pProgram->GetUniform(sSpecularColor);
			static const String sSpecularExponent = "SpecularExponent";
			pGeneratedProgramUserData->pSpecularExponent			= pProgram->GetUniform(sSpecularExponent);
			static const String sSpecularMap = "SpecularMap";
			pGeneratedProgramUserData->pSpecularMap					= pProgram->GetUniform(sSpecularMap);
			static const String sNormalMap = "NormalMap";
			pGeneratedProgramUserData->pNormalMap					= pProgram->GetUniform(sNormalMap);
			static const String sNormalMapBumpiness = "NormalMapBumpiness";
			pGeneratedProgramUserData->pNormalMapBumpiness			= pProgram->GetUniform(sNormalMapBumpiness);
			static const String sDetailNormalMap = "DetailNormalMap";
			pGeneratedProgramUserData->pDetailNormalMap				= pProgram->GetUniform(sDetailNormalMap);
			static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
			pGeneratedProgramUserData->pDetailNormalMapBumpiness	= pProgram->GetUniform(sDetailNormalMapBumpiness);
			static const String sDetailNormalMapUVScale = "DetailNormalMapUVScale";
			pGeneratedProgramUserData->pDetailNormalMapUVScale		= pProgram->GetUniform(sDetailNormalMapUVScale);
			static const String sHeightMap = "HeightMap";
			pGeneratedProgramUserData->pHeightMap					= pProgram->GetUniform(sHeightMap);
			static const String sParallaxScaleBias = "ParallaxScaleBias";
			pGeneratedProgramUserData->pParallaxScaleBias			= pProgram->GetUniform(sParallaxScaleBias);
			static const String sAmbientOcclusionMap = "AmbientOcclusionMap";
			pGeneratedProgramUserData->pAmbientOcclusionMap			= pProgram->GetUniform(sAmbientOcclusionMap);
			static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
			pGeneratedProgramUserData->pAmbientOcclusionFactor		= pProgram->GetUniform(sAmbientOcclusionFactor);
			static const String sLightMap = "LightMap";
			pGeneratedProgramUserData->pLightMap					= pProgram->GetUniform(sLightMap);
			static const String sLightMapColor = "LightMapColor";
			pGeneratedProgramUserData->pLightMapColor				= pProgram->GetUniform(sLightMapColor);
			static const String sEmissiveMap = "EmissiveMap";
			pGeneratedProgramUserData->pEmissiveMap					= pProgram->GetUniform(sEmissiveMap);
			static const String sEmissiveMapColor = "EmissiveMapColor";
			pGeneratedProgramUserData->pEmissiveMapColor			= pProgram->GetUniform(sEmissiveMapColor);
			static const String sGlowFactor = "GlowFactor";
			pGeneratedProgramUserData->pGlowFactor					= pProgram->GetUniform(sGlowFactor);
			static const String sGlowMap = "GlowMap";
			pGeneratedProgramUserData->pGlowMap						= pProgram->GetUniform(sGlowMap);
			static const String sReflectionColor = "ReflectionColor";
			pGeneratedProgramUserData->pReflectionColor				= pProgram->GetUniform(sReflectionColor);
			static const String sReflectivity = "Reflectivity";
			pGeneratedProgramUserData->pReflectivity				= pProgram->GetUniform(sReflectivity);
			static const String sReflectivityMap = "ReflectivityMap";
			pGeneratedProgramUserData->pReflectivityMap				= pProgram->GetUniform(sReflectivityMap);
			static const String sFresnelConstants = "FresnelConstants";
			pGeneratedProgramUserData->pFresnelConstants			= pProgram->GetUniform(sFresnelConstants);
			static const String sReflectionMap = "ReflectionMap";
			pGeneratedProgramUserData->pReflectionMap				= pProgram->GetUniform(sReflectionMap);
			static const String sViewSpaceToWorldSpace = "ViewSpaceToWorldSpace";
			pGeneratedProgramUserData->pViewSpaceToWorldSpace		= pProgram->GetUniform(sViewSpaceToWorldSpace);
		}

		// Set displacement map
		if (pGeneratedProgramUserData->pDisplacementMap) {
			const int nTextureUnit = pGeneratedProgramUserData->pDisplacementMap->Set(pDisplacementMap);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
				SetupTextureFiltering(cRenderer, nTextureUnit);
			}

			// Set displacement scale bias
			if (pGeneratedProgramUserData->pDisplacementScaleBias)
				pGeneratedProgramUserData->pDisplacementScaleBias->Set(fDisplacementScale, fDisplacementBias);
		}

		// Set the "DiffuseColor" fragment shader parameter
		if (pGeneratedProgramUserData->pDiffuseColor) {
			static const String sDiffuseColor = "DiffuseColor";
			pParameter = cMaterial.GetParameter(sDiffuseColor);
			if (pParameter) {
				float fDiffuseColor[3] = { 1.0f, 1.0f, 1.0f };
				pParameter->GetValue3f(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
				pGeneratedProgramUserData->pDiffuseColor->Set(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
			} else {
				pGeneratedProgramUserData->pDiffuseColor->Set(1.0f, 1.0f, 1.0f);
			}
		}

		// Diffuse
		if (pGeneratedProgramUserData->pDiffuseMap) {
			// Set the "DiffuseMap" fragment shader parameter
			const int nTextureUnit = pGeneratedProgramUserData->pDiffuseMap->Set(pDiffuseMap);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
				SetupTextureFiltering(cRenderer, nTextureUnit);
			}

			// Set the "AlphaReference" fragment shader parameter
			if (pGeneratedProgramUserData->pAlphaReference)
				pGeneratedProgramUserData->pAlphaReference->Set(fAlphaReference);
		}

		// Specular
		if (bSpecular) {
			// Set specular exponent and specular color
			if (pGeneratedProgramUserData->pSpecularColor)
				pGeneratedProgramUserData->pSpecularColor->Set(cSpecularColor);
			if (pGeneratedProgramUserData->pSpecularExponent)
				pGeneratedProgramUserData->pSpecularExponent->Set(fSpecularExponent);

			// Set the "SpecularMap" fragment shader parameter
			if (pGeneratedProgramUserData->pSpecularMap) {
				const int nTextureUnit = pGeneratedProgramUserData->pSpecularMap->Set(pSpecularMap);
				if (nTextureUnit >= 0) {
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
					SetupTextureFiltering(cRenderer, nTextureUnit);
				}
			}
		}

		// Normal map
		if (pGeneratedProgramUserData->pNormalMap) {
			{ // Set normal map
				const int nTextureUnit = pGeneratedProgramUserData->pNormalMap->Set(pNormalMap);
				if (nTextureUnit >= 0) {
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
					SetupTextureFiltering(cRenderer, nTextureUnit);
				}

				// Set normal map bumpiness
				if (pGeneratedProgramUserData->pNormalMapBumpiness)
					pGeneratedProgramUserData->pNormalMapBumpiness->Set(fNormalMapBumpiness);
			}

			// Detail normal map
			if (pGeneratedProgramUserData->pDetailNormalMap) {
				{ // Set detail normal map
					const int nTextureUnit = pGeneratedProgramUserData->pDetailNormalMap->Set(pDetailNormalMap);
					if (nTextureUnit >= 0) {
						cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
						cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
						SetupTextureFiltering(cRenderer, nTextureUnit);
					}
				}

				// Set detail normal map bumpiness and uv scale
				if (pGeneratedProgramUserData->pDetailNormalMapBumpiness)
					pGeneratedProgramUserData->pDetailNormalMapBumpiness->Set(fDetailNormalMapBumpiness);
				if (pGeneratedProgramUserData->pDetailNormalMapUVScale)
					pGeneratedProgramUserData->pDetailNormalMapUVScale->Set(vDetailNormalMapUVScale);
			}
		}

		// Set height map
		if (pGeneratedProgramUserData->pHeightMap) {
			const int nTextureUnit = pGeneratedProgramUserData->pHeightMap->Set(pHeightMap);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
				SetupTextureFiltering(cRenderer, nTextureUnit);
			}

			// Set parallax scale bias
			if (pGeneratedProgramUserData->pParallaxScaleBias)
				pGeneratedProgramUserData->pParallaxScaleBias->Set(fParallax, -0.02f);
		}

		// Set ambient occlusion map
		if (pGeneratedProgramUserData->pAmbientOcclusionMap) {
			const int nTextureUnit = pGeneratedProgramUserData->pAmbientOcclusionMap->Set(pAmbientOcclusionMap);
			if (nTextureUnit >= 0) {
				// Setup sampler states
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
				SetupTextureFiltering(cRenderer, nTextureUnit);

				// Set ambient occlusion factor
				if (pGeneratedProgramUserData->pAmbientOcclusionFactor) {
					float fAmbientOcclusionFactor = 1.0f;
					static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
					pParameter = cMaterial.GetParameter(sAmbientOcclusionFactor);
					if (pParameter)
						pParameter->GetValue1f(fAmbientOcclusionFactor);
					pGeneratedProgramUserData->pAmbientOcclusionFactor->Set(fAmbientOcclusionFactor);
				}
			}
		}

		// Set light map
		if (pGeneratedProgramUserData->pLightMap) {
			const int nTextureUnit = pGeneratedProgramUserData->pLightMap->Set(pLightMap);
			if (nTextureUnit >= 0) {
				// Setup sampler states
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
				SetupTextureFiltering(cRenderer, nTextureUnit);

				// Set light map color
				if (pGeneratedProgramUserData->pLightMapColor) {
					float fLightMapColor[3] = { 1.0f, 1.0f, 1.0f };
					static const String sLightMapColor = "LightMapColor";
					pParameter = cMaterial.GetParameter(sLightMapColor);
					if (pParameter)
						pParameter->GetValue3f(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
					pGeneratedProgramUserData->pLightMapColor->Set(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
				}
			}

			// Color target 3 has real information
			m_bColorTarget3Used = true;
		}

		// Set emissive map
		if (pGeneratedProgramUserData->pEmissiveMap) {
			const int nTextureUnit = pGeneratedProgramUserData->pEmissiveMap->Set(pEmissiveMap);
			if (nTextureUnit >= 0) {
				// Setup sampler states
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
				SetupTextureFiltering(cRenderer, nTextureUnit);

				// Set emissive color
				if (pGeneratedProgramUserData->pEmissiveMapColor) {
					float fEmissiveMapColor[3] = { 1.0f, 1.0f, 1.0f };
					static const String sEmissiveMapColor = "EmissiveMapColor";
					pParameter = cMaterial.GetParameter(sEmissiveMapColor);
					if (pParameter)
						pParameter->GetValue3f(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
					pGeneratedProgramUserData->pEmissiveMapColor->Set(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
				}
			}

			// Color target 3 has real information
			m_bColorTarget3Used = true;
		}

		// Set the "GlowFactor" fragment shader parameter
		if (fGlowFactor != 0.0f) {
			if (pGeneratedProgramUserData->pGlowFactor)
				pGeneratedProgramUserData->pGlowFactor->Set(fGlowFactor);

			// Set glow map
			if (pGeneratedProgramUserData->pGlowMap) {
				const int nTextureUnit = pGeneratedProgramUserData->pGlowMap->Set(pGlowMap);
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
			if (pGeneratedProgramUserData->pReflectionColor)
				pGeneratedProgramUserData->pReflectionColor->Set(cReflectionColor);

			// Set the "Reflectivity" fragment shader parameter
			if (pGeneratedProgramUserData->pReflectivity)
				pGeneratedProgramUserData->pReflectivity->Set(fReflectivity);

			// Set the "ReflectivityMap" fragment shader parameter
			if (pGeneratedProgramUserData->pReflectivityMap) {
				const int nTextureUnit = pGeneratedProgramUserData->pReflectivityMap->Set(pReflectivityMap);
				if (nTextureUnit >= 0) {
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
					SetupTextureFiltering(cRenderer, nTextureUnit);
				}
			}

			// Use Fresnel reflection?
			if (pGeneratedProgramUserData->pFresnelConstants) {
				// Calculate the eta value
				// [TODO] Make the "from material" also setable per material or global?
				static const float AirIndexOfRefaction = 1.0f;
				const float fEtaValue = AirIndexOfRefaction / fIndexOfRefraction; // "from material" -> "to material"

				// Set the "FresnelConstants" fragment shader parameter
				static const String sFresnelConstants = "FresnelConstants";
				const float fR0 = Math::Saturate(Math::Pow(1.0f - fEtaValue, 2.0f) / Math::Pow(1.0f + fEtaValue, 2.0f));
				pGeneratedProgramUserData->pFresnelConstants->Set(fR0, fFresnelReflectionPower);
			}

			// Set the "ReflectionMap" fragment shader parameter
			if (pGeneratedProgramUserData->pReflectionMap) {
				const int nTextureUnit = pGeneratedProgramUserData->pReflectionMap->Set(pReflectionMap);
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
				if (pGeneratedProgramUserData->pViewSpaceToWorldSpace) {
					// [TODO] Add *SNCamera::GetInvViewMatrix()?
					Matrix3x3 mRot;
					if (SNCamera::GetCamera()) mRot = SNCamera::GetCamera()->GetViewMatrix().GetInverted();
					else					   mRot = Matrix3x3::Identity;
					pGeneratedProgramUserData->pViewSpaceToWorldSpace->Set(mRot);
				}
			}
		}
	}

	// Done
	return pGeneratedProgramUserData;
}

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
*    Draws a mesh batch
*/
void SRPDeferredGBuffer::DrawMeshBatch(Renderer &cRenderer, GeneratedProgramUserData &cGeneratedProgramUserData, MeshBatch &cMeshBatch) const
{
	// Get the mesh batch vertex buffer
	VertexBuffer *pVertexBuffer = cMeshBatch.pVertexBuffer;

	{ // Set per mesh batch program parameters
		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		if (cGeneratedProgramUserData.pVertexPosition)
			cGeneratedProgramUserData.pVertexPosition->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
		if (cGeneratedProgramUserData.pVertexTexCoord0)
			cGeneratedProgramUserData.pVertexTexCoord0->Set(pVertexBuffer, PLRenderer::VertexBuffer::TexCoord);
		if (cGeneratedProgramUserData.pVertexTexCoord1)
			cGeneratedProgramUserData.pVertexTexCoord1->Set(pVertexBuffer, PLRenderer::VertexBuffer::TexCoord, 1);
		if (cGeneratedProgramUserData.pVertexNormal)
			cGeneratedProgramUserData.pVertexNormal->Set(pVertexBuffer, PLRenderer::VertexBuffer::Normal);
		if (cGeneratedProgramUserData.pVertexTangent)
			cGeneratedProgramUserData.pVertexTangent->Set(pVertexBuffer, PLRenderer::VertexBuffer::Tangent);
		if (cGeneratedProgramUserData.pVertexBinormal)
			cGeneratedProgramUserData.pVertexBinormal->Set(pVertexBuffer, PLRenderer::VertexBuffer::Binormal);

		// Get the mesh batch visibility node
		const VisNode *pVisNode = cMeshBatch.pVisNode;

		// Two sided lighting?
		if (cGeneratedProgramUserData.pNormalScale)
			cGeneratedProgramUserData.pNormalScale->Set(1.0f);

		// Set world view projection matrix
		if (cGeneratedProgramUserData.pWorldVP)
			cGeneratedProgramUserData.pWorldVP->Set(pVisNode->GetWorldViewProjectionMatrix());

		// Set world view matrix
		if (cGeneratedProgramUserData.pWorldV)
			cGeneratedProgramUserData.pWorldV->Set(pVisNode->GetWorldViewMatrix());

		// Set object space eye position
		if (cGeneratedProgramUserData.pEyePos)
			cGeneratedProgramUserData.pEyePos->Set(pVisNode->GetInverseWorldMatrix()*(cMeshBatch.pCullQuery->GetVisContainer().GetWorldMatrix()*cMeshBatch.pCullQuery->GetCameraPosition()));
	}

	// Bind index buffer
	cRenderer.SetIndexBuffer(cMeshBatch.pIndexBuffer);

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cMeshBatch.sScissorRectangle);

	// Get the mesh patch geometry
	const Geometry *pGeometry = cMeshBatch.pGeometry;

	// Draw the geometry
	cRenderer.DrawIndexedPrimitives(
		pGeometry->GetPrimitiveType(),
		0,
		pVertexBuffer->GetNumOfElements()-1,
		pGeometry->GetStartIndex(),
		pGeometry->GetIndexSize()
	);

	// If this is a two sided material, draw the primitives again - but with
	// flipped culling mode and vertex normals
	if (cGeneratedProgramUserData.pNormalScale) {
		// Flip normals
		cGeneratedProgramUserData.pNormalScale->Set(-1.0f);

		// Flip the backface culling
		const uint32 nCullModeBackup = cRenderer.GetRenderState(RenderState::CullMode);
		cRenderer.SetRenderState(RenderState::CullMode, Cull::CW);

		// Draw geometry - again
		cRenderer.DrawIndexedPrimitives(
			pGeometry->GetPrimitiveType(),
			0,
			pVertexBuffer->GetNumOfElements()-1,
			pGeometry->GetStartIndex(),
			pGeometry->GetIndexSize()
		);

		// Restore the previous cull mode
		cRenderer.SetRenderState(RenderState::CullMode, nCullModeBackup);
	}
}

/**
*  @brief
*    Returns a free mesh batch
*/
SRPDeferredGBuffer::MeshBatch &SRPDeferredGBuffer::GetFreeMeshBatch()
{
	if (m_lstFreeMeshBatches.IsEmpty())
		return *(new MeshBatch);
	else {
		MeshBatch *pMeshBatch = m_lstFreeMeshBatches.Get(0);
		m_lstFreeMeshBatches.RemoveAtIndex(0);
		return *pMeshBatch;
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
			m_bColorTarget3Used			= false;
			m_bColorTarget3AlphaUsed	= false;

			// Collect recursive
			CollectMeshBatchesRec(cCullQuery);

			{ // Loop through all currently used materials
				Iterator<const Material*> cMaterialIterator = m_lstMaterials.GetIterator();
				while (cMaterialIterator.HasNext()) {
					// Get the current material
					const Material *pMaterial = cMaterialIterator.Next();

					// Make the material to the currently used one
					GeneratedProgramUserData *pGeneratedProgramUserData = MakeMaterialCurrent(cRenderer, *pMaterial);
					if (pGeneratedProgramUserData) {
						// Draw all mesh batches using this material
						Iterator<MeshBatch*> cMeshBatchIterator = m_lstMeshBatches.GetIterator();
						while (cMeshBatchIterator.HasNext()) {
							// Get the current mesh batch
							MeshBatch *pMeshBatch = cMeshBatchIterator.Next();

							// Same material?
							if (pMeshBatch->pMaterial == pMaterial) {
								// Draw the mesh batch
								DrawMeshBatch(cRenderer, *pGeneratedProgramUserData, *pMeshBatch);
							}
						}
					}
				}
				{ // Free the mesh batches
					Iterator<MeshBatch*> cMeshBatchIterator = m_lstMeshBatches.GetIterator();
					while (cMeshBatchIterator.HasNext())
						m_lstFreeMeshBatches.Add(cMeshBatchIterator.Next());
					m_lstMeshBatches.Clear();
				}
				m_lstMaterials.Clear();
			}

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
