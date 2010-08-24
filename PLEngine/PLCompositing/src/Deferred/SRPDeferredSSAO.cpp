/*********************************************************\
 *  File: SRPDeferredSSAO.cpp                            *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredSSAO.h"
#include "SRPDeferredSSAO_Cg.h"	// The shader programs


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredSSAO)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredSSAO::SRPDeferredSSAO() :
	Contrast(this),
	BlurRadius(this),
	BlurSharpness(this),
	ResolutionScale(this),
	SceneScale(this),
	Flags(this),
	m_pRenderTargetAO(NULL),
	m_pRenderTargetXBlur(NULL)
{
	// Init shader handler data
	m_bBlurVertexShader = false;
	MemoryManager::Set(m_bBlurFragmentShader, 0, sizeof(m_bBlurFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredSSAO::~SRPDeferredSSAO()
{
	// Destroy all used shaders
	DestroyShaders();

	// Destroy the render targets required for blur
	if (m_pRenderTargetAO)
		delete m_pRenderTargetAO;
	if (m_pRenderTargetXBlur)
		delete m_pRenderTargetXBlur;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the blur vertex shader
*/
Shader *SRPDeferredSSAO::GetBlurVertexShader(Renderer &cRenderer)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cBlurVertexShader;
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bBlurVertexShader) {
		const static String ShaderFilename = "Vertex/SRPDeferredSSAO_Blur.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredSSAO_Cg_VS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredSSAO_Cg_VS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, false, "arbvp1", "");
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bBlurVertexShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the blur fragment shader
*/
Shader *SRPDeferredSSAO::GetBlurFragmentShader(Renderer &cRenderer, bool bXBlur)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cBlurFragmentShader[bXBlur];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bBlurFragmentShader[bXBlur]) {
		const static String ShaderFilename = "Fragment/SRPDeferredSSAO_Blur.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bXBlur) {
			sDefines += "#define XBLUR\n";
			sName    += "[XBlur]";
		}

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredSSAO_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredSSAO_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines); // We can't use for e.g. "arbfp1" because we're using loops heavily in here
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bBlurFragmentShader[bXBlur] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredSSAO::DestroyShaders()
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
	m_bBlurVertexShader = false;
	MemoryManager::Set(m_bBlurFragmentShader, 0, sizeof(m_bBlurFragmentShader));
}

/**
*  @brief
*    Draws the blur
*/
void SRPDeferredSSAO::DrawBlur(TextureBufferRectangle &cInputTextureBuffer, TextureBufferRectangle &cNormalDepthTextureBuffer, bool bXBlur)
{
	// Get the renderer instance
	Renderer &cRenderer = cNormalDepthTextureBuffer.GetRenderer();

	// Get and set the vertex shader
	Shader *pVertexShader = GetBlurVertexShader(cRenderer);
	if (pVertexShader && pVertexShader->GetShaderProgram()) {
		// Get and set the vertex shader program
		ShaderProgram *pVertexShaderProgram = pVertexShader->GetShaderProgram();
		cRenderer.SetVertexShaderProgram(pVertexShaderProgram);

		// Get and set the fragment shader
		Shader *pFragmentShader = GetBlurFragmentShader(cRenderer, bXBlur);
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Get and set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

			{ // Set the "TextureSize" vertex shader parameter
				static const String sTextureSize = "TextureSize";
				pVertexShaderProgram->SetParameter2iv(sTextureSize, cNormalDepthTextureBuffer.GetSize());
			}

			{ // Set the "InputTextureSize" vertex shader parameter
				static const String sInputTextureSize = "InputTextureSize";
				pVertexShaderProgram->SetParameter2iv(sInputTextureSize, cInputTextureBuffer.GetSize());
			}

			{// Set the "g_BlurRadius" fragment shader parameter
				static const String g_BlurRadius = "g_BlurRadius";
				pFragmentShaderProgram->SetParameter1f(g_BlurRadius, BlurRadius);
			}

			{	// Set the "g_BlurFalloff" fragment shader parameter
				float fSigma = (BlurRadius + 1)/2;
				static const String g_BlurFalloff = "g_BlurFalloff";
				pFragmentShaderProgram->SetParameter1f(g_BlurFalloff, 1.0f / (2*fSigma*fSigma));
			}

			{ // Set the "g_Sharpness" fragment shader parameter
				static const String g_Sharpness = "g_Sharpness";
				float fValue = BlurSharpness / SceneScale;
				pFragmentShaderProgram->SetParameter1f(g_Sharpness, fValue*fValue);
			}

			{ // Set the "InputTexture" vertex shader parameter
				static const String sInputTexture = "InputTexture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sInputTexture, &cInputTextureBuffer);
				if (nStage >= 0) {
					cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
					cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
					if (cInputTextureBuffer.GetSize() != cNormalDepthTextureBuffer.GetSize()) {
						cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
						cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
						cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					} else {
						cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				}
			}

			{ // Set the "NormalDepthTexture" vertex shader parameter
				static const String sNormalDepthTexture = "NormalDepthTexture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sNormalDepthTexture, &cNormalDepthTextureBuffer);
				if (nStage >= 0) {
					cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
					cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
					cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
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


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredSSAO::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Ensure that the resolution scale is really between 0-1, if this is <= 0, just skip this scene renderer pass!
	if (ResolutionScale > 0.0f) {
		if (ResolutionScale > 1.0f)
			ResolutionScale = 1.0f;

		// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
		SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
		if (pSRPDeferredGBuffer && pSRPDeferredGBuffer->GetRenderTarget()) {
			// Get the fullscreen quad instance
			FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
			if (pFullscreenQuad) {
				// RG components of RT1 store the normal vector, B component of RT1 stores the linear view space depth
				TextureBufferRectangle *pNormalDepthTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
				if (pNormalDepthTextureBuffer) {
					// Reset all render states to default
					cRenderer.GetRendererContext().GetEffectManager().Use();

					// Get and prepare the render target of the GBuffer (we store the AO result within the alpha channel of the GBuffer RT0)
					SurfaceTextureBuffer *pGBufferRenderTarget = pSRPDeferredGBuffer->GetRenderTarget();
					const uint8 nGBufferRenderTargetMaxColorTargetsBackup = pGBufferRenderTarget->GetMaxColorTargets();
					pGBufferRenderTarget->SetMaxColorTargets(1); // We only render into one target right now!

					// Backup current render target
					Surface *pSurfaceBackup = cRenderer.GetRenderTarget();

					// Disable scissor test
					cRenderer.SetRenderState(RenderState::ScissorTestEnable, false);

					// Backup the color mask
					bool bRed, bGreen, bBlue, bAlpha;
					cRenderer.GetColorMask(bRed, bGreen, bBlue, bAlpha);

					// Ambient occlusion with blur?
					if (GetFlags() & NoBlur) {
						// Nope, just blank pixel chaos ambient occlusion

						// [TODO] ResolutionScale support

						// Set the new render target
						cRenderer.SetRenderTarget(pGBufferRenderTarget);

						// Set the color mask - we will ONLY write into the alpha channel, do NOT overwrite the other channels!
						cRenderer.SetColorMask(false, false, false, true);

						// Setup renderer
						const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
						cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
						cRenderer.SetRenderState(RenderState::CullMode,      Cull::None);
						cRenderer.SetRenderState(RenderState::ZEnable,       false);
						cRenderer.SetRenderState(RenderState::ZWriteEnable,  false);

						// Draws the AO
						DrawAO(*pFullscreenQuad, *pNormalDepthTextureBuffer);

						// Restore fixed fill mode render state
						cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
					} else {
						// Jap, we want to have smooth ambient occlusion

						// Get the size of the GBuffer render target
						const Vector2i vRTSize = pGBufferRenderTarget->GetSize();
						if (vRTSize.x != 0 && vRTSize.y != 0) {
							// Get the texture format. A simple 1 byte per pixel format is good enough,
							// a fancy 16 or even 32 bit floating point format doesn't bring a visible improvement.
//							const TextureBuffer::EPixelFormat nInternalFormat = TextureBuffer::L32F;
							const TextureBuffer::EPixelFormat nInternalFormat = TextureBuffer::L8;

							// Get the size of the AO render target
							const Vector2i vAOSize = vRTSize*ResolutionScale;

							// Render target size or internal format change?
							if (m_pRenderTargetAO && (m_pRenderTargetAO->GetSize() != vAOSize || m_pRenderTargetAO->GetFormat() != nInternalFormat)) {
								delete m_pRenderTargetAO;
								m_pRenderTargetAO = NULL;
							}
							if (m_pRenderTargetXBlur && (m_pRenderTargetXBlur->GetSize() != vRTSize || m_pRenderTargetXBlur->GetFormat() != nInternalFormat)) {
								delete m_pRenderTargetXBlur;
								m_pRenderTargetXBlur = NULL;
							}

							// Create/update the render targets required for AO blur - if necessary
							if (!m_pRenderTargetAO)
								m_pRenderTargetAO = cRenderer.CreateSurfaceTextureBufferRectangle(vAOSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
							if (!m_pRenderTargetXBlur)
								m_pRenderTargetXBlur = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);

							// Render the AO with blur
							if (m_pRenderTargetAO && m_pRenderTargetXBlur) {
								const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);

								{ // Render AO
									// Set the new render target and color mask
									cRenderer.SetRenderTarget(m_pRenderTargetAO);
									cRenderer.SetColorMask(true, true, true, true);

									// Setup renderer
									cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
									cRenderer.SetRenderState(RenderState::CullMode,      Cull::None);
									cRenderer.SetRenderState(RenderState::ZEnable,       false);
									cRenderer.SetRenderState(RenderState::ZWriteEnable,  false);

									// Draws the AO
									DrawAO(*pFullscreenQuad, *pNormalDepthTextureBuffer);
								}

								{ // X blur
									// Set the new render target and color mask
									cRenderer.SetRenderTarget(m_pRenderTargetXBlur);
									cRenderer.SetColorMask(true, true, true, true);

									// Setup renderer
									cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
									cRenderer.SetRenderState(RenderState::CullMode,      Cull::None);
									cRenderer.SetRenderState(RenderState::ZEnable,       false);
									cRenderer.SetRenderState(RenderState::ZWriteEnable,  false);

									// Draws the blur
									DrawBlur((TextureBufferRectangle&)*m_pRenderTargetAO->GetTextureBuffer(), *pNormalDepthTextureBuffer, true);
								}

								{ // Y blur, the result is written into the alpha channel of the GBuffer RT0
									// Set the new render target
									cRenderer.SetRenderTarget(pGBufferRenderTarget);

									// Set the color mask - we will ONLY write into the alpha channel, do NOT overwrite the other channels!
									cRenderer.SetColorMask(false, false, false, true);

									// Setup renderer
									cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
									cRenderer.SetRenderState(RenderState::CullMode,      Cull::None);
									cRenderer.SetRenderState(RenderState::ZEnable,       false);
									cRenderer.SetRenderState(RenderState::ZWriteEnable,  false);

									// Draws the blur
									DrawBlur((TextureBufferRectangle&)*m_pRenderTargetXBlur->GetTextureBuffer(), *pNormalDepthTextureBuffer, false);
								}

								// Restore fixed fill mode render state
								cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
							}
						}
					}

					// Restore the color mask
					cRenderer.SetColorMask(bRed, bGreen, bBlue, bAlpha);

					// Restore the previously set render target and GBuffer render target settings
					cRenderer.SetRenderTarget(pSurfaceBackup);
					pGBufferRenderTarget->SetMaxColorTargets(nGBufferRenderTargetMaxColorTargetsBackup);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
