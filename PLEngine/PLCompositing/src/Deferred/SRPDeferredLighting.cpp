/*********************************************************\
 *  File: SRPDeferredLighting.cpp                        *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLMath/Matrix3x3.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferCube.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SNDirectionalLight.h>
#include <PLScene/Scene/SNProjectiveSpotLight.h>
#include <PLScene/Scene/SNProjectivePointLight.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include <PLScene/Compositing/ShadowMapManager.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredLighting.h"
#include "SRPDeferredLighting_Cg.h"	// The shader programs


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
pl_implement_class(SRPDeferredLighting)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SRPDeferredLighting::SetFlags(uint32 nValue)
{
	if (GetFlags() != nValue) {
		// Call base implementation
		SRPDeferred::SetFlags(nValue);

		// Destroy all currently used shaders, just to avoid old unused shaders flying around...
		// and in the case the quality mode was changed this is required.
		DestroyShaders();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredLighting::SRPDeferredLighting() :
	TextureFiltering(this),
	Flags(this),
	m_bVertexShader(false)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoShadowLOD|NoAmbientOcclusion);

	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredLighting::~SRPDeferredLighting()
{
	// Destroy all used shaders
	DestroyShaders();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets correct texture filtering modes
*/
void SRPDeferredLighting::SetupTextureFiltering(Renderer &cRenderer, uint32 nStage, uint32 nTextureFiltering) const
{
	// Anisotropic filtering
	if (nTextureFiltering > 1) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter,     TextureFiltering::None);	// GBuffer doesn't required mipmaps
		cRenderer.SetSamplerState(nStage, Sampler::MaxAnisotropy, nTextureFiltering);

	// Bilinear filtering
	} else if (nTextureFiltering > 0) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);	// GBuffer doesn't required mipmaps

	// No filtering
	} else {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);	// GBuffer doesn't required mipmaps
	}
}

/**
*  @brief
*    Returns the vertex shader
*/
Shader *SRPDeferredLighting::GetVertexShader(Renderer &cRenderer)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cVertexShader;
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bVertexShader) {
		const static String ShaderFilename = "Vertex/SRPDeferredLighting.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredLighting_Cg_VS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredLighting_Cg_VS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, false, "arbvp1", "");
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bVertexShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the fragment shader for the requested visualisation mode
*/
Shader *SRPDeferredLighting::GetFragmentShader(Renderer &cRenderer, bool bDirectional, bool bProjectivePoint, bool bSpot, bool bProjectiveSpot, bool bSpotCone, bool bSpotSmoothCone, bool bShadowMapping, bool bDiscard, bool bGammaCorrection)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bDirectional][bProjectivePoint][bSpot][bProjectiveSpot][bSpotCone][bSpotSmoothCone][bShadowMapping][bDiscard][bGammaCorrection];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bDirectional][bProjectivePoint][bSpot][bProjectiveSpot][bSpotCone][bSpotSmoothCone][bShadowMapping][bDiscard][bGammaCorrection]) {
		const static String ShaderFilename = "Fragment/SRPDeferredLighting.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bDirectional) {
			sDefines += "#define DIRECTIONAL\n";
			sName    += "[Directional]";
		} else {
			if (bProjectivePoint) {
				sDefines += "#define PROJECTIVE_POINT\n";
				sName    += "[ProjectivePoint]";
			} else {
				if (bSpot) {
					sDefines += "#define SPOT\n";
					sName    += "[Spot]";
					if (bProjectiveSpot) {
						sDefines += "#define PROJECTIVE_SPOT\n";
						sName    += "[ProjectiveSpot]";
					}
					if (bSpotCone) {
						sDefines += "#define SPOT_CONE\n";
						sName    += "[SpotCone]";
						if (bSpotSmoothCone) {
							sDefines += "#define SPOT_SMOOTHCONE\n";
							sName    += "[SpotSmoothCone]";
						}
					}
				}
			}
			if (bShadowMapping) {
				sDefines += "#define SHADOWMAPPING\n";
				sName    += "[ShadowMapping]";
				if (!(GetFlags() & NoSoftShadow)) {
					sDefines += "#define SOFTSHADOWMAPPING\n";
					sName    += "[SoftShadowMapping]";
				}
			}
		}
		if (GetFlags() & NoAlbedo) {
			sDefines += "#define NO_ALBEDO\n";
			sName    += "[NoAlbedo]";
		}
		if (GetFlags() & NoAmbientOcclusion) {
			sDefines += "#define NO_AMBIENTOCCLUSION\n";
			sName    += "[NoAmbientOcclusion]";
		}
		if (GetFlags() & NoSpecular) {
			sDefines += "#define NO_SPECULAR\n";
			sName    += "[NoSpecular]";
		}
		if (GetFlags() & NoSpecularColor) {
			sDefines += "#define NO_SPECULARCOLOR\n";
			sName    += "[NoSpecularColor]";
		}
		if (GetFlags() & NoSpecularExponent) {
			sDefines += "#define NO_SPECULAREXPONENT\n";
			sName    += "[NoSpecularExponent]";
		}
		if (bDiscard) {
			sDefines += "#define DISCARD\n";
			sName    += "[Discard]";
		}
		if (bGammaCorrection) {
			sDefines += "#define GAMMACORRECTION\n";
			sName    += "[GammaCorrection]";
		}

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredLighting_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredLighting_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "arbfp1", sDefines); // "glslf" would be nice, but then, the "discard" keyword seems to have no effect :/
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bDirectional][bProjectivePoint][bProjectiveSpot][bSpot][bSpotCone][bSpotSmoothCone][bShadowMapping][bDiscard][bGammaCorrection] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredLighting::DestroyShaders()
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
	m_bVertexShader = false;
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Draws recursive
*/
void SRPDeferredLighting::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery, SRPDeferredGBuffer &cSRPDeferredGBuffer)
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
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					DrawRec(cRenderer, *pVisCell->GetCullQuery(), cSRPDeferredGBuffer);
				}

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery())
					DrawRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery(), cSRPDeferredGBuffer);

			// Is this a light?
			} else if (pSceneNode->IsLight()) {
				if (((SNLight*)pSceneNode)->IsRenderLight()) {
					// Render the light
					RenderLight(cRenderer, cCullQuery, cSRPDeferredGBuffer, *((SNLight*)pSceneNode), *pVisNode);
				}

			// This must just be a quite boring scene node, ignore it
			} else {
			}
		}
	}
}

/**
*  @brief
*    Renders a light
*/
void SRPDeferredLighting::RenderLight(Renderer &cRenderer, const SQCull &cCullQuery, SRPDeferredGBuffer &cSRPDeferredGBuffer, SNLight &cLight, const VisNode &cLightVisNode)
{
	// Skip black lights, they have no visible incluence!
	if (cLight.Color.Get() == Color3::Black)
		return;	// Get us out of here right now

	// Figure out the type of the given light
	const bool bPoint			= cLight.IsPointLight();
	const bool bProjectivePoint	= (GetFlags() & NoProjectivePointLights) ? false : (cLight.IsProjectivePointLight() && !(cLight.GetFlags() & SNProjectivePointLight::NoProjection));
	const bool bSpot			= cLight.IsSpotLight();
	const bool bProjectiveSpot	= (GetFlags() & NoProjectiveSpotLights) ? false : (cLight.IsProjectiveSpotLight() && !(cLight.GetFlags() & SNProjectiveSpotLight::NoProjection));
	const bool bDirectional		= cLight.IsDirectionalLight();

	// Get the light range
	const float fRange = bPoint ? ((SNPointLight&)cLight).GetRange() : 0.0f;

	// Skip none directional lights with a radius of <= 0, they have no visible incluence!
	if (!bDirectional && fRange <= 0.0f)
		return;	// Get us out of here right now

	// Calculate the scissor rectangle
	Rectangle cScissorRectangle;
	if (bDirectional) {
		// Directional lights influence the hole screen, as a result, the scissor rectangle is equal to the rectangle of the viewport
		cScissorRectangle = cRenderer.GetViewport();
	} else {
		// Get the vertices of the light scene node bounding box
		Array<Vector3> vVertex(8);
		cLight.GetAABoundingBox().GetVertices(vVertex.GetData());

		// Get viewport parameters
		const uint32 nX      = (uint32)cRenderer.GetViewport().GetX();
		const uint32 nY      = (uint32)cRenderer.GetViewport().GetY();
		const uint32 nWidth  = (uint32)cRenderer.GetViewport().GetWidth();
		const uint32 nHeight = (uint32)cRenderer.GetViewport().GetHeight();

		// Calculate the rectangle on the screen enclosing the given vertices
		cScissorRectangle.ScreenRectangle(vVertex, true, cLightVisNode.GetWorldViewProjectionMatrix(), nX, nY, nWidth, nHeight);
	}

	// Is the scissor rectangle visible?
	if (cScissorRectangle.GetWidth() || cScissorRectangle.GetHeight()) {
		// Set the scissor rectangle
		cRenderer.SetScissorRect(&cScissorRectangle);

		// Get the shadow map manager and update the shadow map
		bool bShadowMapping = false;
		ShadowMapManager *pShadowMapManager = NULL;
		if (!(GetFlags() & NoShadow) && (cLight.GetFlags() & SNLight::CastShadow)) {
			// Get the scene context
			SceneContext *pSceneContext = GetSceneContext();
			if (pSceneContext) {
				// Get the shadow map manager
				pShadowMapManager = &pSceneContext->GetShadowMapManager();
				if (pShadowMapManager) {
					// Update the shadow map for this light
					pShadowMapManager->UpdateShadowMap(cLight, cCullQuery, (GetFlags() & NoShadowLOD) ? 0.0f : cLightVisNode.GetSquaredDistanceToCamera());

					// Perform shadow mapping?
					if (pShadowMapManager->GetCubeShadowRenderTarget() || pShadowMapManager->GetSpotShadowRenderTarget())
						bShadowMapping = true;

					// [TODO] Remove this, to much state changes!
					// Sets the initial render states
					cRenderer.GetRendererContext().GetEffectManager().Use();
					cRenderer.SetRenderState(RenderState::CullMode,     Cull::None);
					cRenderer.SetRenderState(RenderState::ZEnable,      false);
					cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
					cRenderer.SetRenderState(RenderState::BlendEnable,	true);
					cRenderer.SetRenderState(RenderState::SrcBlendFunc,	BlendFunc::One);
					cRenderer.SetRenderState(RenderState::DstBlendFunc,	BlendFunc::One);

					// Set the color mask, we don't write out alpha
					cRenderer.SetColorMask(true, true, true, false);
				}
			}
		}

		// Use spot cone or even smooth spot cone for spot lights?
		bool bSpotCone       = false;
		bool bSpotSmoothCone = false;
		if (bSpot && !(cLight.GetFlags() & SNSpotLight::NoCone)) {
			// A spot cone is used
			bSpotCone = true;

			// The inner angle MUST be smaller than the outer one, else we do not use a smooth cone
			bSpotSmoothCone = ((SNSpotLight&)cLight).GetOuterAngle() > ((SNSpotLight&)cLight).GetInnerAngle();
		}

		// Get and set the vertex shader
		Shader *pVertexShader = GetVertexShader(cRenderer);
		if (pVertexShader && pVertexShader->GetShaderProgram()) {
			// Get and set the vertex shader program
			ShaderProgram *pVertexShaderProgram = pVertexShader->GetShaderProgram();
			cRenderer.SetVertexShaderProgram(pVertexShaderProgram);

			// Use gamma correction?
			const bool bGammaCorrection = !(GetFlags() & NoGammaCorrection);

			// Get and set the fragment shader
			Shader *pFragmentShader = GetFragmentShader(cRenderer, bDirectional, bProjectivePoint, bSpot, bProjectiveSpot, bSpotCone, bSpotSmoothCone, bShadowMapping, !(GetFlags() & NoDiscard), bGammaCorrection);
			if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
				// Get and set the fragment shader program
				ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
				cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

				// Get the size of the texture buffer
				const Vector2i vSize = cSRPDeferredGBuffer.GetRenderTargetTextureBuffer(0)->GetSize();

				{ // Set the "TextureSize" vertex shader parameter
					static const String sTextureSize = "TextureSize";
					pVertexShaderProgram->SetParameter2iv(sTextureSize, vSize);
				}

				// Directional light?
				if (bDirectional) {
					// Set normalized view space light direction vector
					Vector3 vLightDirection = cLightVisNode.GetWorldViewMatrix().GetZAxis();
					vLightDirection.Invert();
					vLightDirection.Normalize();
					static const String sLightDirection = "LightDirection";
					pFragmentShaderProgram->SetParameter3fv(sLightDirection, vLightDirection);
				} else {
					{ // Set the "LightPosition" fragment shader parameter
						static const String sLightPosition = "LightPosition";
						pFragmentShaderProgram->SetParameter3fv(sLightPosition, cLightVisNode.GetWorldViewMatrix().GetTranslation());
					}

					{ // Set the "LightRadius" fragment shader parameter
						static const String sLightRadius = "LightRadius";
						pFragmentShaderProgram->SetParameter1f(sLightRadius, fRange);
					}

					// Set cube map
					if (bProjectivePoint) {
						// The texture buffer we're going to project
						TextureBuffer *pCubeMap = NULL;

						// Get the projective material to use
						const Material *pProjectiveMaterial = ((SNProjectivePointLight&)cLight).GetProjectedMaterialHandler().GetResource();
						if (pProjectiveMaterial) {
							// Get the DiffuseMap-parameter of the projective material
							const Parameter *pParameter = pProjectiveMaterial->GetParameter(Material::DiffuseMap);
							if (pParameter) {
								// Get the texture we're going to project
								const Texture *pTexture = pParameter->GetValueTexture();
								if (pTexture)
									pCubeMap = pTexture->GetTextureBuffer();
							}
						}

						// Use the default cube map?
						if (!pCubeMap) {
							if (!m_cCubeMapHandler.GetResource())
								m_cCubeMapHandler.Load(cRenderer.GetRendererContext().GetTextureManager(), "Data/Textures/DefaultCubeMap.dds");
							if (m_cCubeMapHandler.GetResource())
								pCubeMap = m_cCubeMapHandler.GetResource()->GetTextureBuffer();
						}

						// Set the "ProjectivePointCubeMap" fragment shader parameter
						static const String sProjectivePointCubeMap = "ProjectivePointCubeMap";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sProjectivePointCubeMap, pCubeMap);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
							cRenderer.SetSamplerState(nStage, Sampler::AddressW, TextureAddressing::Wrap);
							SetupTextureFiltering(cRenderer, nStage, TextureFiltering);
						}

						{ // Set the "ViewSpaceToCubeMapSpace" fragment shader parameter
							Matrix3x3 mRot = cLightVisNode.GetWorldViewMatrix();
							mRot.Invert();
							static const String sViewSpaceToCubeMapSpace = "ViewSpaceToCubeMapSpace";
							pFragmentShaderProgram->SetParameterFloat3x3(sViewSpaceToCubeMapSpace, mRot);
						}
					} else {
						// Set spot light parameters
						if (bSpot) {
							{ // Set light direction in view space
								Vector3 vLightDirection = cLightVisNode.GetWorldViewMatrix().GetZAxis();
								vLightDirection.Normalize();
								static const String sLightDirection = "LightDirection";
								pFragmentShaderProgram->SetParameter3fv(sLightDirection, vLightDirection);
							}

							// Projective spot light
							if (bProjectiveSpot) {
								// The texture buffer we're going to project
								TextureBuffer *pSpotMap = NULL;

								// Get the projective material to use
								const Material *pProjectiveMaterial = ((SNProjectiveSpotLight&)cLight).GetProjectedMaterialHandler().GetResource();
								if (pProjectiveMaterial) {
									// Get the DiffuseMap-parameter of the projective material
									const Parameter *pParameter = pProjectiveMaterial->GetParameter(Material::DiffuseMap);
									if (pParameter) {
										// Get the texture we're going to project
										const Texture *pTexture = pParameter->GetValueTexture();
										if (pTexture)
											pSpotMap = pTexture->GetTextureBuffer();
									}
								}

								// Use the default spot map?
								if (!pSpotMap) {
									if (!m_cSpotMapHandler.GetResource())
										m_cSpotMapHandler.Load(cRenderer.GetRendererContext().GetTextureManager(), "Data/Textures/PLLogo.dds");
									if (m_cSpotMapHandler.GetResource())
										pSpotMap = m_cSpotMapHandler.GetResource()->GetTextureBuffer();
								}

								// Set the "ProjectiveSpotMap" fragment shader parameter
								static const String sProjectiveSpotMap = "ProjectiveSpotMap";
								const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sProjectiveSpotMap, pSpotMap);
								if (nStage >= 0) {
									// Do NOT use wrapping for projective textures! :)
									cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Border);
									cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Border);
									SetupTextureFiltering(cRenderer, nStage, TextureFiltering);
								}

								{ // Set the "ProjectiveSpotMap" fragment shader parameter
									static const String sViewSpaceToSpotMapSpace = "ViewSpaceToSpotMapSpace";

									// This matrix brings us from clip space [-1...1] to texture space [0...1] (scale & bias)
									static const Matrix4x4 mClipSpaceToTextureSpace(0.5f, 0.0f, 0.0f, 0.5f,
																					0.0f, 0.5f, 0.0f, 0.5f,
																					0.0f, 0.0f, 0.5f, 0.5f,
																					0.0f, 0.0f, 0.0f, 1.0f);

									// Clip space [-1...1] to texture space [0...1]
									Matrix4x4 mTransform = mClipSpaceToTextureSpace;

									// View space to clip space [-1...1]
									mTransform *= ((SNProjectiveSpotLight&)cLight).GetProjectionMatrix();

									// Set the fragment shader parameter
									pFragmentShaderProgram->SetParameterMatrixfv(sViewSpaceToSpotMapSpace, mTransform*cLightVisNode.GetWorldViewMatrix().GetInverted());
								}
							}

							// Set spot light cone parameters
							if (bSpotCone) {
								static const String sSpotConeCos = "SpotConeCos";
								if (bSpotSmoothCone) {
									// Set spot light cone outer and inner angle in view space
									pFragmentShaderProgram->SetParameter2f(sSpotConeCos, float(Math::Cos(((SNSpotLight&)cLight).GetOuterAngle()*Math::DegToRad*0.5f)),
																						 float(Math::Cos(((SNSpotLight&)cLight).GetInnerAngle()*Math::DegToRad*0.5f)));

								} else {
									// Set spot light cone outer angle in view space
									pFragmentShaderProgram->SetParameter1f(sSpotConeCos, float(Math::Cos(((SNSpotLight&)cLight).GetOuterAngle()*Math::DegToRad*0.5f)));
								}
							}
						}
					}

					// Shadow mapping
					if (bShadowMapping) {
						// Get the shadow map
						TextureBuffer *pShadowMap = NULL;
						if (bSpot) {
							if (pShadowMapManager->GetSpotShadowRenderTarget())
								pShadowMap = pShadowMapManager->GetSpotShadowRenderTarget()->GetTextureBuffer();
						} else {
							if (pShadowMapManager->GetCubeShadowRenderTarget())
								pShadowMap = pShadowMapManager->GetCubeShadowRenderTarget()->GetTextureBuffer();
						}

						// Set shadow map
						if (pShadowMap) {
							static const String sShadowMap = "ShadowMap";
							const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sShadowMap, pShadowMap);
							if (nStage >= 0) {
								// Clamp, if this is not done, we may see some artefacts
								cRenderer.SetSamplerState(nStage, Sampler::AddressU,  TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::AddressV,  TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::AddressW,  TextureAddressing::Clamp);

								// No mipmapping, please
								cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
								cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
								cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);

								// Set the "ViewSpaceToShadowMapSpace" fragment shader parameter
								if (bSpot) {
									static const String sViewSpaceToShadowMapSpace = "ViewSpaceToShadowMapSpace";

									// This matrix brings us from clip space [-1...1] to texture space [0...1] (scale & bias)
									static const Matrix4x4 mClipSpaceToTextureSpace(0.5f, 0.0f, 0.0f, 0.5f,
																					0.0f, 0.5f, 0.0f, 0.5f,
																					0.0f, 0.0f, 0.5f, 0.5f,
																					0.0f, 0.0f, 0.0f, 1.0f);

									// Clip space [-1...1] to texture space [0...1]
									Matrix4x4 mTransform = mClipSpaceToTextureSpace;

									// View space to clip space [-1...1]
									mTransform *= ((SNSpotLight&)cLight).GetProjectionMatrix();

									// Scene node space to view space
									mTransform *= ((SNSpotLight&)cLight).GetViewMatrix();

									// Set the fragment shader parameter
									pFragmentShaderProgram->SetParameterMatrixfv(sViewSpaceToShadowMapSpace, mTransform*cLight.GetTransform().GetMatrix()*cLightVisNode.GetWorldViewMatrix().GetInverted());
								} else {
									{ // Set the "ViewSpaceToShadowCubeMapSpace" fragment shader parameter
										Matrix3x3 mRot = cLight.GetTransform().GetMatrix()*cLightVisNode.GetWorldViewMatrix().GetInverted();
										static const String sViewSpaceToShadowCubeMapSpace = "ViewSpaceToShadowCubeMapSpace";
										pFragmentShaderProgram->SetParameterFloat3x3(sViewSpaceToShadowCubeMapSpace, mRot);
									}

									{ // Set the "InvLightRadius" fragment shader parameter
										static const String sInvLightRadius = "InvLightRadius";
										pFragmentShaderProgram->SetParameter1f(sInvLightRadius, 1.0f/fRange);
									}
								}

								// Set texel size
								if (!(GetFlags() & NoSoftShadow)) {
									float fSize = 0.0f;
									if (pShadowMap->GetType() == TextureBuffer::TypeTextureBuffer2D)
										fSize = (float)((TextureBuffer2D*)pShadowMap)->GetSize().x;
									else if (pShadowMap->GetType() == TextureBuffer::TypeTextureBufferCube)
										fSize = (float)((TextureBufferCube*)pShadowMap)->GetSize();
									if (fSize) {
										static const String sTexelSize = "TexelSize";
										pFragmentShaderProgram->SetParameter1f(sTexelSize, 0.5f/fSize);
									}
								}
							}
						}
					}
				}

				{ // Set the "LightColor" fragment shader parameter
					static const String sLightColor = "LightColor";
					pFragmentShaderProgram->SetParameter3fv(sLightColor, cLight.Color.Get());
				}

				{ // Focal length
					// Calculate the focal length
					const float fFovY         = float((SNCamera::GetCamera() ? SNCamera::GetCamera()->GetFOV() : 45.0f) * Math::DegToRad);
					const float fFocalLengthY = 1.0f / Math::Tan(fFovY * 0.5f);
					const float fFocalLengthX = fFocalLengthY * ((vSize.y * (SNCamera::GetCamera() ? SNCamera::GetCamera()->GetAspect() : 1.0f)) / vSize.x);

					// InvFocalLen
					static const String sInvFocalLen = "InvFocalLen";
					pFragmentShaderProgram->SetParameter2f(sInvFocalLen, 1.0f/fFocalLengthX, 1.0f/fFocalLengthY);
				}

				// Set render target texture 0
				if (!(GetFlags() & NoAlbedo) || !(GetFlags() & NoAmbientOcclusion)) {
					// Get the texture buffer to use
					TextureBufferRectangle *pTextureBuffer = cSRPDeferredGBuffer.GetRenderTargetTextureBuffer(0);
					if (pTextureBuffer) {
						static const String sRenderTargetTexture0 = "RenderTargetTexture0";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sRenderTargetTexture0, pTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}
				}

				{ // Set render target texture 1
					// Get the texture buffer to use
					TextureBufferRectangle *pTextureBuffer = cSRPDeferredGBuffer.GetRenderTargetTextureBuffer(1);
					if (pTextureBuffer) {
						static const String sRenderTargetTexture1 = "RenderTargetTexture1";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sRenderTargetTexture1, pTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}
				}

				// Set render target texture 2
				if (!(GetFlags() & NoSpecular)) {
					// Get the texture buffer to use
					TextureBufferRectangle *pTextureBuffer = cSRPDeferredGBuffer.GetRenderTargetTextureBuffer(2);
					if (pTextureBuffer) {
						static const String sRenderTargetTexture2 = "RenderTargetTexture2";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sRenderTargetTexture2, pTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}
				}

				// Make the vertex buffer of this deferred scene renderer pass the the current one
				// [TODO] Remove FixedFunctions usage by using the new shader interface
				FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
				if (pFixedFunctions)
					pFixedFunctions->SetVertexBuffer(GetVertexBuffer());

				// Draw the fullscreen quad
				cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredLighting::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
	SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
	if (pSRPDeferredGBuffer && pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0)) {
		// Reset all render states to default
		cRenderer.GetRendererContext().GetEffectManager().Use();

		// Setup renderer
		const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
		cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);
		cRenderer.SetRenderState(RenderState::FixedFillMode,	 Fill::Solid);
		cRenderer.SetRenderState(RenderState::CullMode,			 Cull::None);
		cRenderer.SetRenderState(RenderState::ZEnable,			 false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);

		// Set blend mode
		cRenderer.SetRenderState(RenderState::BlendEnable,	true);
		cRenderer.SetRenderState(RenderState::SrcBlendFunc,	BlendFunc::One);
		cRenderer.SetRenderState(RenderState::DstBlendFunc,	BlendFunc::One);

		// Set the color mask, we don't write out alpha
		cRenderer.SetColorMask(true, true, true, false);

		// Draw recursive from front to back
		DrawRec(cRenderer, cCullQuery, *pSRPDeferredGBuffer);

		// Restore fixed fill mode render state
		cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);

		// Restore color mask
		cRenderer.SetColorMask(true, true, true, true);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
