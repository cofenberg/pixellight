/*********************************************************\
 *  File: SRPDirectionalLightingShaders.cpp              *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/RenderStates.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SNLight.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisContainer.h>
#include "PLCompositing/Shaders/General/SRPDirectionalLightingShaders.h"


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
pl_implement_class(SRPDirectionalLightingShaders)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDirectionalLightingShaders::SRPDirectionalLightingShaders() :
	ShaderLanguage(this),
	Flags(this),
	m_pProgramGenerator(NULL),
	m_pRenderStates(new RenderStates()),
	m_bGlowEnabled(false),
	m_fDOFNearBlurDepth(0.0f),
	m_fDOFFocalPlaneDepth(0.0f),
	m_fDOFFarBlurDepth(0.0f),
	m_fDOFBlurrinessCutoff(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SRPDirectionalLightingShaders::~SRPDirectionalLightingShaders()
{
	// Destroy render states 'translator'
	delete m_pRenderStates;

	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
}

/**
*  @brief
*    Returns the directional light scene node used for rendering the scene the last time
*/
SNDirectionalLight *SRPDirectionalLightingShaders::GetUsedLight() const
{
	return (SNDirectionalLight*)m_cLightNodeHandler.GetElement();
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SRPDirectionalLighting functions ]
//[-------------------------------------------------------]
void SRPDirectionalLightingShaders::DrawMesh(Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, SceneNode &cSceneNode, const MeshHandler &cMeshHandler, const Mesh &cMesh, const MeshLODLevel &cMeshLODLevel, VertexBuffer &cVertexBuffer)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Get buffers
		  IndexBuffer     *pIndexBuffer  = cMeshLODLevel.GetIndexBuffer();
	const Array<Geometry> &lstGeometries = *cMeshLODLevel.GetGeometries();

	// Bind buffers
	cRenderer.SetIndexBuffer(pIndexBuffer);

	// Is lighting enabled for this scene node?
	const bool bLightingEnabled = !(cSceneNode.GetFlags() & SceneNode::NoLighting) && (m_cLightColor != Color3::Black);

	// Get available vertex buffer attributes
	// Binormal and tangent make only sense in this usage when there's also a normal, we need all three vectors!
	const bool bHasVertexTexCoord0 = (cVertexBuffer.GetVertexAttribute(VertexBuffer::TexCoord, 0) != NULL);	// e.g. for diffuse maps
	const bool bHasVertexTexCoord1 = (cVertexBuffer.GetVertexAttribute(VertexBuffer::TexCoord, 1) != NULL);	// e.g. for light maps
	const bool bHasVertexNormal    = (cVertexBuffer.GetVertexAttribute(VertexBuffer::Normal) != NULL);
		  bool bHasVertexTangent   = bHasVertexNormal && (cVertexBuffer.GetVertexAttribute(VertexBuffer::Tangent) != NULL);
	const bool bHasVertexBinormal  = bHasVertexTangent && (cVertexBuffer.GetVertexAttribute(VertexBuffer::Binormal) != NULL);
	if (!bHasVertexBinormal)
		bHasVertexTangent = false;

	// For better readability, define whether or not normal mapping is possible with the given vertex data
	const bool bNormalMappingPossible = bHasVertexBinormal;	// We don't need to check for all three vectors in here :D

	// Draw mesh
	for (uint32 nMat=0; nMat<cMeshHandler.GetNumOfMaterials(); nMat++) {
		// Get mesh material
		const Material *pMaterial = cMeshHandler.GetMaterial(nMat);
		if (pMaterial) {
			// Draw geometries
			bool bTwoSided = false;
			for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
				// Is this geometry active and is it using the current used mesh material?
				const Geometry &cGeometry = lstGeometries[nGeo];
				if (cGeometry.IsActive() && nMat == cGeometry.GetMaterial()) {
					// Transparent material?
					static const String sOpacity = "Opacity";
					const Parameter *pParameter = pMaterial->GetParameter(sOpacity);
					if ((GetFlags() & TransparentPass) ? (pParameter && pParameter->GetValue1f() < 1.0f) : (!pParameter || pParameter->GetValue1f() >= 1.0f)) {
						GeneratedProgramUserData *pGeneratedProgramUserData = NULL;

						// Reset the program flags
						m_cProgramFlags.Reset();

						// Get glow
						float		   fGlow    = 0.0f;
						TextureBuffer *pGlowMap = NULL;
						if (m_bGlowEnabled) {
							static const String sGlow = "Glow";
							pParameter = pMaterial->GetParameter(sGlow);
							if (pParameter) {
								fGlow = pParameter->GetValue1f();

								// Get glow map
								if (fGlow) {
									static const String sGlowMap = "GlowMap";
									pGlowMap = (GetFlags() & NoGlowMap) ? NULL : pMaterial->GetParameterTextureBuffer(sGlowMap);
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_GLOW)
								}
							}
						}

						// Transparent stuff only: Write into the alpha channel only for glowing stuff
						if (GetFlags() & TransparentPass)
							cRenderer.SetColorMask(true, true, true, (m_cProgramFlags.GetFragmentShaderFlags() & FS_GLOW) != 0);

						// Get opacity
						const float fOpacity = pParameter ? pParameter->GetValue1f() : 1.0f;
						if (fOpacity < 1) {
							// Get and set source blend function
							uint32 nValue = BlendFunc::SrcAlpha;
							static const String sSrcBlendFunc = "SrcBlendFunc";
							pParameter = pMaterial->GetParameter(sSrcBlendFunc);
							if (pParameter) {
								m_pRenderStates->SetAttribute("SrcBlendFunc", pParameter->GetParameterString());
								nValue = m_pRenderStates->Get(RenderState::SrcBlendFunc);
							}
							cRenderer.SetRenderState(RenderState::SrcBlendFunc, nValue);

							// Get and set destination blend function
							nValue = BlendFunc::InvSrcAlpha;
							static const String sDstBlendFunc = "DstBlendFunc";
							pParameter = pMaterial->GetParameter(sDstBlendFunc);
							if (pParameter) {
								m_pRenderStates->SetAttribute("DstBlendFunc", pParameter->GetParameterString());
								nValue = m_pRenderStates->Get(RenderState::DstBlendFunc);
							}
							cRenderer.SetRenderState(RenderState::DstBlendFunc, nValue);
						}

						// Normal
						if (bHasVertexNormal) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_NORMAL)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMAL)
						}

						{ // Two sided
							static const String sTwoSided = "TwoSided";
							pParameter = pMaterial->GetParameter(sTwoSided);
							bTwoSided = (pParameter && pParameter->GetValue1f() == 1.0f);
							if (bTwoSided) {
								// We need to take care of two sided lighting
								if (bHasVertexNormal) {
									// Perform backface culling: For proper two sided lighting, we draw the
									// geometry twice, the second time with flipped vertex normals
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TWOSIDEDLIGHTING)
									cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
								} else {
									// No lighting means that we can go the easy way: Just don't perform backface culling
									cRenderer.SetRenderState(RenderState::CullMode, Cull::None);
								}
							} else {
								// Usual backface culling
								cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
							}
						}

						// Use gamma correction?
						if (!(GetFlags() & NoGammaCorrection))
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_GAMMACORRECTION)

						// Diffuse map and alpha reference
						float fAlphaReference = 0.0f;
						TextureBuffer *pDiffuseMap = (!bHasVertexTexCoord0 || (GetFlags() & NoDiffuseMap)) ? NULL : pMaterial->GetParameterTextureBuffer(Material::DiffuseMap);
						if (pDiffuseMap) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIFFUSEMAP)

							// Get alpha reference
							if (pDiffuseMap->GetComponentsPerPixel() == 4) {
								static const String sAlphaReference = "AlphaReference";
								pParameter = pMaterial->GetParameter(sAlphaReference);
								fAlphaReference = pParameter ? pParameter->GetValue1f() : 0.5f;
								if (fAlphaReference != 0.0f) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_ALPHATEST)

									// We need to take care of glow even if this material currently does not glow
									if (m_bGlowEnabled && (m_fDOFBlurrinessCutoff || m_bGlowEnabled))
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_GLOW)
								}
							}
						}

						// Diffuse ramp map
						static const String sDiffuseRampMap = "DiffuseRampMap";
						TextureBuffer *pDiffuseRampMap = (!bLightingEnabled || (GetFlags() & NoDiffuseRampMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sDiffuseRampMap);
						if (pDiffuseRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIFFUSERAMPMAP)

						// Ambient map and light map require texture coordinate set 1
						TextureBuffer *pAmbientOcclusionMap = NULL;
						TextureBuffer *pLightMap			= NULL;
						if (bHasVertexTexCoord1) {
							// Get ambient occlusion map
							if (!(GetFlags() & NoAmbientOcclusionMap)) {
								pAmbientOcclusionMap = pMaterial->GetParameterTextureBuffer(Material::AmbientOcclusionMap);
								if (pAmbientOcclusionMap) {
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD1)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_AMBIENTOCCLUSIONMAP)
								}
							}

							// Get light map
							if (!(GetFlags() & NoLightMap)) {
								pLightMap = pMaterial->GetParameterTextureBuffer(Material::LightMap);
								if (pLightMap) {
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD1)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_LIGHTMAP)
								}
							}
						}

						// Get emissive map
						TextureBuffer *pEmissiveMap = (!bHasVertexTexCoord0 || (GetFlags() & NoEmissiveMap)) ? NULL : pMaterial->GetParameterTextureBuffer(Material::EmissiveMap);
						if (pEmissiveMap) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_EMISSIVEMAP)
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
							if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBuffer2D) {
								b2DReflectionMap = true;
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_2DREFLECTIONMAP)
							} else if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBufferCube) {
								b2DReflectionMap = false;
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_CUBEREFLECTIONMAP)
							} else
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
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_VIEWSPACEPOSITION)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTION)
							if (fIndexOfRefraction > 0.0f)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_FRESNELREFLECTION)

							// ReflectionColor
							pParameter = pMaterial->GetParameter(sReflectionColor);
							if (pParameter)
								cReflectionColor = pParameter->GetValue3fv();

							// Get reflectivity map
							if (!(GetFlags() & NoReflectivityMap)) {
								pReflectivityMap = pMaterial->GetParameterTextureBuffer(Material::ReflectivityMap);
								if (pReflectivityMap)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTIVITYMAP)
							}

							// Get reflectivity 
							pParameter = pMaterial->GetParameter(sReflectivity);
							if (pParameter)
								fReflectivity = pParameter->GetValue1f();
						}

						// Get normal map
						TextureBuffer *pNormalMap = (!bNormalMappingPossible || (GetFlags() & NoNormalMap)) ? NULL : pMaterial->GetParameterTextureBuffer(Material::NormalMap);
						float fNormalMapBumpiness = 1.0f;
						static const String sNormalMapBumpiness = "NormalMapBumpiness";
						if (pNormalMap) {
							// Get normal map bumpiness
							const Parameter *pNormalMapParameter = pMaterial->GetParameter(sNormalMapBumpiness);
							if (pNormalMapParameter)
								fNormalMapBumpiness = pNormalMapParameter->GetValue1f();
							if (fNormalMapBumpiness != 0.0f) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_TANGENT_BINORMAL)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_TANGENT_BINORMAL)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP)

								// DXT5 xGxR normal map?
								pNormalMapParameter = pMaterial->GetParameter(Material::NormalMap);
								if (pNormalMapParameter) {
									const Texture *pNormalMapTexture = pNormalMapParameter->GetValueTexture();
									if (pNormalMapTexture) {
										if (pNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR || pNormalMapTexture->GetCompressionHint() == Texture::LATC2_XYSwizzle)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP_DXT5_XGXR)	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
										else if (pNormalMapTexture->GetCompressionHint() == Texture::LATC2)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP_LATC2)
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
						static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
						static const String sDetailNormalMapUVScale   = "DetailNormalMapUVScale";
						if (pDetailNormalMap) {
							// Get detail normal map bumpiness
							const Parameter *pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMapBumpiness);
							if (pDetailNormalMapParameter)
								fDetailNormalMapBumpiness = pDetailNormalMapParameter->GetValue1f();
							if (fDetailNormalMapBumpiness != 0.0f) {
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP)

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
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP_DXT5_XGXR)	// We can use one and the same shader for DXT5_xGxR and LATC2_XYSwizzle :D
										else if (pDetailNormalMapTexture->GetCompressionHint() == Texture::LATC2)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP_LATC2)
									}
								}
							} else {
								// The detail normal map has no longer an influence!
								pDetailNormalMap = NULL;
							}
						}

						// Get parallax mapping settings
						float fParallax = 0.04f;
						TextureBuffer *pHeightMap = NULL;
						if (pNormalMap && !(GetFlags() & NoParallaxMapping)) {
							// Get parallax
							static const String sParallax = "Parallax";
							pParameter = pMaterial->GetParameter(sParallax);
							if (pParameter)
								pParameter->GetValue1f(fParallax);

							// Get height map
							if (fParallax != 0.0f)
								pHeightMap = pMaterial->GetParameterTextureBuffer(Material::HeightMap);

							// No height map = no parallax mapping possible
							if (pHeightMap) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_PARALLAXMAPPING)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_PARALLAXMAPPING)
							}
						}

						// Lighting and specular
						static const String sSpecularColor    = "SpecularColor";
						static const String sSpecularExponent = "SpecularExponent";
						Color3 cSpecularColor = Color3::White;
						TextureBuffer *pSpecularMap = NULL;
						float fSpecularExponent = 45.0f;
						if (bLightingEnabled) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_VIEWSPACEPOSITION)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_LIGHTING)

							// Specular
							if (!(GetFlags() & NoSpecular)) {
								// First, get specular color - if it's 0, we don't have any specular at all
								pParameter = pMaterial->GetParameter(sSpecularColor);
								if (pParameter)
									cSpecularColor = pParameter->GetValue3fv();
								if (cSpecularColor != 0.0f) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULAR)

									// Get specular exponent
									pParameter = pMaterial->GetParameter(sSpecularExponent);
									if (pParameter)
										pParameter->GetValue1f(fSpecularExponent);

									// Get the specular map
									if (!(GetFlags() & NoSpecularMap)) {
										pSpecularMap = pMaterial->GetParameterTextureBuffer(Material::SpecularMap);
										if (pSpecularMap)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULARMAP)
									}
								}
							}
						}

						// Specular ramp map
						static const String sSpecularRampMap = "SpecularRampMap";
						TextureBuffer *pSpecularRampMap = (!(m_cProgramFlags.GetFragmentShaderFlags() & FS_SPECULAR) || (GetFlags() & NoSpecularRampMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sSpecularRampMap);
						if (pSpecularRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULARRAMPMAP)

						// Edge ramp map
						static const String sEdgeRampMap = "EdgeRampMap";
						TextureBuffer *pEdgeRampMap = (!bLightingEnabled || (GetFlags() & NoEdgeRampMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sEdgeRampMap);
						if (pEdgeRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_EDGERAMPMAP)

						// Glow or DOF - or nothing of both?
						if (m_cProgramFlags.GetFragmentShaderFlags() & FS_GLOW) {
							if (pGlowMap) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_GLOWMAP)
							}
						} else {
							// Use DOF?
							if (m_fDOFBlurrinessCutoff) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_VIEWSPACEPOSITION)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_DOF)
							}
						}

						// Fragment shader needs texture coordinate flags, too
						if (m_cProgramFlags.GetVertexShaderFlags() & VS_TEXCOORD0)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_TEXCOORD0)
						if (m_cProgramFlags.GetVertexShaderFlags() & VS_TEXCOORD1)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_TEXCOORD1)

						// Get a program instance from the program generator using the given program flags
						ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);

						// Make our program to the current one
						if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
							// Set pointers to uniforms & attributes of a generated program if they are not set yet
							static const String sDiffuseColor			= "DiffuseColor";
							static const String sLightMapColor			= "LightMapColor";
							static const String sAmbientOcclusionFactor = "AmbientOcclusionFactor";
							static const String sEmissiveMapColor		= "EmissiveMapColor";
							pGeneratedProgramUserData = (GeneratedProgramUserData*)pGeneratedProgram->pUserData;
							if (!pGeneratedProgramUserData) {
								pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
								Program *pProgram = pGeneratedProgram->pProgram;
								// Vertex shader attributes
								static const String sVertexPosition = "VertexPosition";
								pGeneratedProgramUserData->pVertexPosition					= pProgram->GetAttribute(sVertexPosition);
								static const String sVertexTexCoord0 = "VertexTexCoord0";
								pGeneratedProgramUserData->pVertexTexCoord0					= pProgram->GetAttribute(sVertexTexCoord0);
								static const String sVertexTexCoord1 = "VertexTexCoord1";
								pGeneratedProgramUserData->pVertexTexCoord1					= pProgram->GetAttribute(sVertexTexCoord1);
								static const String sVertexNormal = "VertexNormal";
								pGeneratedProgramUserData->pVertexNormal					= pProgram->GetAttribute(sVertexNormal);
								static const String sVertexTangent = "VertexTangent";
								pGeneratedProgramUserData->pVertexTangent					= pProgram->GetAttribute(sVertexTangent);
								static const String sVertexBinormal = "VertexBinormal";
								pGeneratedProgramUserData->pVertexBinormal					= pProgram->GetAttribute(sVertexBinormal);
								// Vertex shader uniforms
								static const String sNormalScale = "NormalScale";
								pGeneratedProgramUserData->pNormalScale						= pProgram->GetUniform(sNormalScale);
								static const String sObjectSpaceToViewSpaceMatrix = "ObjectSpaceToViewSpaceMatrix";
								pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix	= pProgram->GetUniform(sObjectSpaceToViewSpaceMatrix);
								static const String sObjectSpaceToClipSpaceMatrix = "ObjectSpaceToClipSpaceMatrix";
								pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix	= pProgram->GetUniform(sObjectSpaceToClipSpaceMatrix);
								static const String sEyePos = "EyePos";
								pGeneratedProgramUserData->pEyePos							= pProgram->GetUniform(sEyePos);
								// Fragment shader uniforms
								static const String sAmbientColor = "AmbientColor";
								pGeneratedProgramUserData->pAmbientColor					= pProgram->GetUniform(sAmbientColor);
								pGeneratedProgramUserData->pDiffuseColor					= pProgram->GetUniform(sDiffuseColor);
								pGeneratedProgramUserData->pDiffuseMap						= pProgram->GetUniform(Material::DiffuseMap);
								static const String sAlphaReference = "AlphaReference";
								pGeneratedProgramUserData->pAlphaReference					= pProgram->GetUniform(sAlphaReference);
								pGeneratedProgramUserData->pDiffuseRampMap					= pProgram->GetUniform(sDiffuseRampMap);
								pGeneratedProgramUserData->pAmbientOcclusionMap				= pProgram->GetUniform(Material::AmbientOcclusionMap);
								pGeneratedProgramUserData->pAmbientOcclusionFactor			= pProgram->GetUniform(sAmbientOcclusionFactor);
								pGeneratedProgramUserData->pLightMap						= pProgram->GetUniform(Material::LightMap);
								pGeneratedProgramUserData->pLightMapColor					= pProgram->GetUniform(sLightMapColor);
								pGeneratedProgramUserData->pEmissiveMap						= pProgram->GetUniform(Material::EmissiveMap);
								pGeneratedProgramUserData->pEmissiveMapColor				= pProgram->GetUniform(sEmissiveMapColor);
								pGeneratedProgramUserData->pReflectionColor					= pProgram->GetUniform(sReflectionColor);
								pGeneratedProgramUserData->pReflectivity					= pProgram->GetUniform(sReflectivity);
								pGeneratedProgramUserData->pReflectivityMap					= pProgram->GetUniform(Material::ReflectivityMap);
								static const String sFresnelConstants = "FresnelConstants";
								pGeneratedProgramUserData->pFresnelConstants				= pProgram->GetUniform(sFresnelConstants);
								pGeneratedProgramUserData->pReflectionMap					= pProgram->GetUniform(Material::ReflectionMap);
								static const String sViewSpaceToWorldSpace = "ViewSpaceToWorldSpace";
								pGeneratedProgramUserData->pViewSpaceToWorldSpace			= pProgram->GetUniform(sViewSpaceToWorldSpace);
								pGeneratedProgramUserData->pNormalMap						= pProgram->GetUniform(Material::NormalMap);
								pGeneratedProgramUserData->pNormalMapBumpiness				= pProgram->GetUniform(sNormalMapBumpiness);
								pGeneratedProgramUserData->pDetailNormalMap					= pProgram->GetUniform(sDetailNormalMap);
								pGeneratedProgramUserData->pDetailNormalMapBumpiness		= pProgram->GetUniform(sDetailNormalMapBumpiness);
								pGeneratedProgramUserData->pDetailNormalMapUVScale			= pProgram->GetUniform(sDetailNormalMapUVScale);
								pGeneratedProgramUserData->pHeightMap						= pProgram->GetUniform(Material::HeightMap);
								static const String sParallaxScaleBias = "ParallaxScaleBias";
								pGeneratedProgramUserData->pParallaxScaleBias				= pProgram->GetUniform(sParallaxScaleBias);
								static const String sLightDirection = "LightDirection";
								pGeneratedProgramUserData->pLightDirection					= pProgram->GetUniform(sLightDirection);
								static const String sLightColor = "LightColor";
								pGeneratedProgramUserData->pLightColor						= pProgram->GetUniform(sLightColor);
								pGeneratedProgramUserData->pSpecularColor					= pProgram->GetUniform(sSpecularColor);
								pGeneratedProgramUserData->pSpecularExponent				= pProgram->GetUniform(sSpecularExponent);
								pGeneratedProgramUserData->pSpecularMap						= pProgram->GetUniform(Material::SpecularMap);
								pGeneratedProgramUserData->pSpecularRampMap					= pProgram->GetUniform(sSpecularRampMap);
								pGeneratedProgramUserData->pEdgeRampMap						= pProgram->GetUniform(sEdgeRampMap);
								static const String sGlow = "Glow";
								pGeneratedProgramUserData->pGlow							= pProgram->GetUniform(sGlow);
								static const String sGlowMap = "GlowMap";
								pGeneratedProgramUserData->pGlowMap							= pProgram->GetUniform(sGlowMap);
								static const String sDOFParams = "DOFParams";
								pGeneratedProgramUserData->pDOFParams						= pProgram->GetUniform(sDOFParams);
							}

							// Ambient color
							if (pGeneratedProgramUserData->pAmbientColor)
								pGeneratedProgramUserData->pAmbientColor->Set(AmbientColor.Get());

							// Diffuse color
							if (pGeneratedProgramUserData->pDiffuseColor) {
								pParameter = pMaterial->GetParameter(sDiffuseColor);
								if (pParameter) {
									float fDiffuseColor[3] = { 1.0f, 1.0f, 1.0f };
									pParameter->GetValue3f(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
									pGeneratedProgramUserData->pDiffuseColor->Set(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2], fOpacity);
								} else {
									pGeneratedProgramUserData->pDiffuseColor->Set(1.0f, 1.0f, 1.0f, fOpacity);
								}
							}

							// Diffuse map
							if (pGeneratedProgramUserData->pDiffuseMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pDiffuseMap->Set(pDiffuseMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
									SetupTextureFiltering(cRenderer, nTextureUnit);

									// Set the "AlphaReference" fragment shader parameter
									if (pGeneratedProgramUserData->pAlphaReference)
										pGeneratedProgramUserData->pAlphaReference->Set(fAlphaReference);
								}
							}

							// Diffuse ramp map
							if (pGeneratedProgramUserData->pDiffuseRampMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pDiffuseRampMap->Set(pDiffuseRampMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
									// No filtering, please
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
								}
							}

							// Ambient occlusion map
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
										pParameter = pMaterial->GetParameter(sAmbientOcclusionFactor);
										if (pParameter)
											pParameter->GetValue1f(fAmbientOcclusionFactor);
										pGeneratedProgramUserData->pAmbientOcclusionFactor->Set(fAmbientOcclusionFactor);
									}
								}
							}

							// Light map
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
										pParameter = pMaterial->GetParameter(sLightMapColor);
										if (pParameter)
											pParameter->GetValue3f(fLightMapColor[0], fLightMapColor[1], fLightMapColor[2]);
										pGeneratedProgramUserData->pLightMapColor->Set3(fLightMapColor);
									}
								}
							}

							// Emissive map
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
										pParameter = pMaterial->GetParameter(sEmissiveMapColor);
										if (pParameter)
											pParameter->GetValue3f(fEmissiveMapColor[0], fEmissiveMapColor[1], fEmissiveMapColor[2]);
										pGeneratedProgramUserData->pEmissiveMapColor->Set3(fEmissiveMapColor);
									}
								}
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
									const float fR0 = Math::Saturate(Math::Pow(1.0f - fEtaValue, 2.0f) / Math::Pow(1.0f + fEtaValue, 2.0f));

									// Set uniform
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
								}

								// Set the "ViewSpaceToWorldSpace" fragment shader parameter
								if (pGeneratedProgramUserData->pViewSpaceToWorldSpace && SNCamera::GetCamera()) {
									// [TODO] Add *SNCamera::GetInvViewMatrix()?
									Matrix3x3 mRot = SNCamera::GetCamera()->GetViewMatrix().GetInverted();
									pGeneratedProgramUserData->pViewSpaceToWorldSpace->Set(mRot);
								}
							}

							// Normal map
							if (pNormalMap) {
								// Set normal map
								if (pGeneratedProgramUserData->pNormalMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pNormalMap->Set(pNormalMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);

										// Set normal map bumpiness
										if (pGeneratedProgramUserData->pNormalMapBumpiness)
											pGeneratedProgramUserData->pNormalMapBumpiness->Set(fNormalMapBumpiness);
									}
								}

								// Set detail normal map
								if (pGeneratedProgramUserData->pDetailNormalMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pDetailNormalMap->Set(pDetailNormalMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);

										// Set detail normal map bumpiness and uv scale
										if (pGeneratedProgramUserData->pDetailNormalMapBumpiness)
											pGeneratedProgramUserData->pDetailNormalMapBumpiness->Set(fDetailNormalMapBumpiness);
										if (pGeneratedProgramUserData->pDetailNormalMapUVScale)
											pGeneratedProgramUserData->pDetailNormalMapUVScale->Set(vDetailNormalMapUVScale);
									}
								}
							}

							// Parallax mapping
							if (pGeneratedProgramUserData->pHeightMap) {
								// Height map (for parallax mapping)
								const int nTextureUnit = pGeneratedProgramUserData->pHeightMap->Set(pHeightMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
									SetupTextureFiltering(cRenderer, nTextureUnit);

									// Set parallax scale bias
									if (pGeneratedProgramUserData->pParallaxScaleBias)
										pGeneratedProgramUserData->pParallaxScaleBias->Set(fParallax, -0.02f);
								}
							}

							// Lighting
							if (bLightingEnabled) {
								// Set view space light direction and light color
								if (pGeneratedProgramUserData->pLightDirection)
									pGeneratedProgramUserData->pLightDirection->Set(m_vLightDirection);
								if (pGeneratedProgramUserData->pLightColor)
									pGeneratedProgramUserData->pLightColor->Set(m_cLightColor);

								// Specular
								if (m_cProgramFlags.GetFragmentShaderFlags() & FS_SPECULAR) {
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

									// Specular ramp map
									if (pGeneratedProgramUserData->pSpecularRampMap) {
										const int nTextureUnit = pGeneratedProgramUserData->pSpecularRampMap->Set(pSpecularRampMap);
										if (nTextureUnit >= 0) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
											// No filtering, please
											cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
										}
									}
								}

								// Set edge ramp map
								if (pGeneratedProgramUserData->pEdgeRampMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pEdgeRampMap->Set(pEdgeRampMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
										// No filtering, please
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
									}
								}
							}

							// Glow
							if (m_cProgramFlags.GetFragmentShaderFlags() & FS_GLOW) {
								// Set glow parameter - note, internally we flip the value because
								// it's more handy because alpha is 1 by default = no glow
								if (pGeneratedProgramUserData->pGlow)
									pGeneratedProgramUserData->pGlow->Set(1.0f - fGlow);

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
							} else {
								// DOF
								if (pGeneratedProgramUserData->pDOFParams)
									pGeneratedProgramUserData->pDOFParams->Set(m_fDOFNearBlurDepth, m_fDOFFocalPlaneDepth, m_fDOFFarBlurDepth, m_fDOFBlurrinessCutoff);
							}
						}
						if (pGeneratedProgramUserData) {
							// Set object space to clip space matrix uniform
							if (pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix)
								pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix->Set(cVisNode.GetWorldViewProjectionMatrix());

							// Set object space to view space matrix uniform
							if (pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix)
								pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix->Set(cVisNode.GetWorldViewMatrix());

							// Parallax mapping - set object space eye position
							if (pGeneratedProgramUserData->pHeightMap && pGeneratedProgramUserData->pEyePos)
								pGeneratedProgramUserData->pEyePos->Set(cVisNode.GetInverseWorldMatrix()*(cVisContainer.GetWorldMatrix()*cCullQuery.GetCameraPosition()));

							// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
							if (pGeneratedProgramUserData->pVertexPosition)
								pGeneratedProgramUserData->pVertexPosition->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);
							if (pGeneratedProgramUserData->pVertexTexCoord0)
								pGeneratedProgramUserData->pVertexTexCoord0->Set(&cVertexBuffer, PLRenderer::VertexBuffer::TexCoord, 0);
							if (pGeneratedProgramUserData->pVertexTexCoord1)
								pGeneratedProgramUserData->pVertexTexCoord1->Set(&cVertexBuffer, PLRenderer::VertexBuffer::TexCoord, 1);
							if (pGeneratedProgramUserData->pVertexNormal) {
								pGeneratedProgramUserData->pVertexNormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Normal);
								if (m_cProgramFlags.GetFragmentShaderFlags() & FS_NORMALMAP) {
									if (pGeneratedProgramUserData->pVertexTangent)
										pGeneratedProgramUserData->pVertexTangent->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Tangent);
									if (pGeneratedProgramUserData->pVertexBinormal)
										pGeneratedProgramUserData->pVertexBinormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Binormal);
								}
							}

							// Two sided lighting?
							if (pGeneratedProgramUserData->pNormalScale)
								pGeneratedProgramUserData->pNormalScale->Set(1.0f);

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
							if (pGeneratedProgramUserData->pNormalScale) {
								// Flip normals
								pGeneratedProgramUserData->pNormalScale->Set(-1.0f);

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
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDirectionalLightingShaders::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
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
		String sDiffuseOnly_VS;
		String sDiffuseOnly_FS;
		if (sShaderLanguage == "GLSL") {
			#include "SRPDirectionalLightingShaders_GLSL.h"
			sDiffuseOnly_VS = sDiffuseOnly_GLSL_VS;
			sDiffuseOnly_FS = sDiffuseOnly_GLSL_FS;
		} else if (sShaderLanguage == "Cg") {
			#include "SRPDirectionalLightingShaders_Cg.h"
			sDiffuseOnly_VS = sDiffuseOnly_Cg_VS;
			sDiffuseOnly_FS = sDiffuseOnly_Cg_FS;
		}

		// Create the program generator
		if (sDiffuseOnly_VS.GetLength() && sDiffuseOnly_FS.GetLength())
			m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDiffuseOnly_VS, "arbvp1", sDiffuseOnly_FS, "arbfp1", true);
	}

	// If there's no program generator, we don't need to continue
	if (m_pProgramGenerator) {
		// By default, glow is disabled
		m_bGlowEnabled = false;

		// Get depth of field settings from the 'SNMPostProcessDepthOfField' modifier of the used camera
		m_fDOFNearBlurDepth    = 0.0f;
		m_fDOFFocalPlaneDepth  = 0.0f;
		m_fDOFFarBlurDepth     = 0.0f;
		m_fDOFBlurrinessCutoff = 0.0f;
		bool bWriteAlpha = false;
		SNCamera *pCamera = SNCamera::GetCamera();
		if (pCamera) {
			// DOF enabled?
			if (!(GetFlags() & NoDOF)) {
				// Is there an active DOF post process modifier?
				SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcessDepthOfField");
				if (pModifier && pModifier->IsActive()) {
					if (pModifier->GetAttribute("EffectWeight")->GetFloat() > 0.0f) {
						m_fDOFNearBlurDepth    = pModifier->GetAttribute("NearBlurDepth")   ->GetFloat();
						m_fDOFFocalPlaneDepth  = pModifier->GetAttribute("FocalPlaneDepth") ->GetFloat();
						m_fDOFFarBlurDepth     = pModifier->GetAttribute("FarBlurDepth")    ->GetFloat();
						m_fDOFBlurrinessCutoff = pModifier->GetAttribute("BlurrinessCutoff")->GetFloat();
						bWriteAlpha = (m_fDOFBlurrinessCutoff != 0.0f);
					}
				}
			}

			// Glow enabled?
			if (!m_fDOFBlurrinessCutoff && !(GetFlags() & NoGlow)) {
				// Is there an active glow post process modifier?
				SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcessGlow");
				if (pModifier && pModifier->IsActive())
					m_bGlowEnabled = bWriteAlpha = true;
			}
		}

		// Reset all render states to default
		cRenderer.GetRendererContext().GetEffectManager().Use();

		// Is this a transparent renderer pass?
		if (GetFlags() & TransparentPass) {
			cRenderer.SetRenderState(RenderState::BlendEnable,  true);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		} else {
			// Maybe the z-buffer was already filled by another scene renderer pass? Let the user decide...
			cRenderer.SetRenderState(RenderState::ZWriteEnable, !(GetFlags() & NoZWrite));
		}

		// Backup the color mask
		bool bRed, bGreen, bBlue, bAlpha;
		cRenderer.GetColorMask(bRed, bGreen, bBlue, bAlpha);

		// Setup the color mask and enable scissor test
		cRenderer.SetColorMask(true, true, true, true);
		cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

		// Search for the first (= nearest) visible directional light scene node - but only if lighting is enabled
		const VisNode *pVisNode = (GetFlags() & NoLighting) ? NULL : GetFirstDirectionalLight(cCullQuery);
		if (pVisNode && pVisNode->GetSceneNode() && pVisNode->GetSceneNode()->IsLight()) {
			// Get the view space light direction vector and the light color
			m_vLightDirection = -pVisNode->GetWorldViewMatrix().GetZAxis().GetNormalized();
			m_cLightColor     = ((SNLight*)pVisNode->GetSceneNode())->Color.Get()*LightingIntensity;
			m_cLightNodeHandler.SetElement(pVisNode->GetSceneNode());
		} else {
			// Sorry, there's no visible directional light scene node
			m_vLightDirection = Vector3::NegativeUnitY;
			m_cLightColor     = Color3::Black;
			m_cLightNodeHandler.SetElement();
		}

		// Draw recursive from front to back
		DrawRec(cRenderer, cCullQuery);

		// Restore the color mask
		cRenderer.SetColorMask(bRed, bGreen, bBlue, bAlpha);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
