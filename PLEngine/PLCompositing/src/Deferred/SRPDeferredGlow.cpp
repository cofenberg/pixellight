/*********************************************************\
 *  File: SRPDeferredGlow.cpp                            *
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
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredGlow.h"
#include "SRPDeferredGlow_Cg.h"	// The shader programs


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
pl_implement_class(SRPDeferredGlow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredGlow::SRPDeferredGlow() :
	GlowFactor(this),
	GlowBlurPasses(this),
	GlowDownscale(this),
	Flags(this),
	m_bDownsampleFragmentShader(false),
	m_bGlowFragmentShader(false),
	m_bResultIndex(0)
{
	// Init data
	m_pRenderTarget[0] = m_pRenderTarget[1] = NULL;
	MemoryManager::Set(m_bResultFragmentShader, 0, sizeof(m_bResultFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGlow::~SRPDeferredGlow()
{
	// Destroy the render targets
	for (int i=0; i<2; i++) {
		if (m_pRenderTarget[i])
			delete m_pRenderTarget[i];
	}

	// Destroy the downsample fragment shader
	if (m_cDownsampleFragmentShader.GetResource())
		delete m_cDownsampleFragmentShader.GetResource();

	// Destroy the glow fragment shader
	if (m_cGlowFragmentShader.GetResource())
		delete m_cGlowFragmentShader.GetResource();

	// Destroy the result fragment shader
	for (int i=0; i<2; i++) {
		if (m_cResultFragmentShader[i].GetResource())
			delete m_cResultFragmentShader[i].GetResource();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates the glow
*/
void SRPDeferredGlow::CalculateGlow(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, uint32 nBlurPasses, float fDownscale)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = cOriginalTexture.GetFormat();

	// Get the renderer instance
	Renderer &cRenderer = cOriginalTexture.GetRenderer();

	// Backup current render target
	Surface *pSurfaceBackup = cRenderer.GetRenderTarget();

	{ // Create/update the two render targets
		// Get the size of the original HDR texture
		const Vector2i vRTSize = cOriginalTexture.GetSize()/fDownscale;
		if (vRTSize.x != 0 && vRTSize.y != 0) {
			for (int i=0; i<2; i++) {
				// Render target size change?
				if (m_pRenderTarget[i] && (m_pRenderTarget[i]->GetSize() != vRTSize || m_pRenderTarget[i]->GetFormat() != nInternalFormat)) {
					// Destroy the downsample render target
					if (m_pRenderTarget[i]) {
						delete m_pRenderTarget[i];
						m_pRenderTarget[i] = NULL;
					}
				}

				// Create the downsample render target right now?
				if (!m_pRenderTarget[i])
					m_pRenderTarget[i] = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
			}
		}
	}

	{ // First step: Downscale
		// Get the fragment shader
		Shader *pFragmentShader = GetDownsampleFragmentShader(cRenderer);
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Make the render target 0 to the current render target
			cRenderer.SetRenderTarget(m_pRenderTarget[0]);
			m_bResultIndex = 0;

			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

			{ // Set the "Texture" fragment shader parameter
				static const String sTexture = "Texture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, &cOriginalTexture);
				if (nStage >= 0) {
					cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw the fullscreen quad
			cFullscreenQuad.Draw(cOriginalTexture.GetSize());
		}
	}

	{ // Gaussian convolution filter to glow
		// Get the fragment shader
		Shader *pFragmentShader = GetGlowFragmentShader(cRenderer);
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

			// Horizontal and vertical blur
			for (uint32 i=0; i<nBlurPasses; i++) {
				// Make the render target 1 to the current render target
				cRenderer.SetRenderTarget(m_pRenderTarget[!m_bResultIndex]);

				{ // Set the "UVScale" fragment shader parameter
					static const String sUVScale = "UVScale";
					if (i%2 != 0)
						pFragmentShaderProgram->SetParameter2f(sUVScale, 0.0f, 1.0f);
					else
						pFragmentShaderProgram->SetParameter2f(sUVScale, 1.0f, 0.0f);
				}

				{ // Set the "Texture" fragment shader parameter
					static const String sTexture = "Texture";
					const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, m_pRenderTarget[m_bResultIndex]->GetTextureBuffer());
					if (nStage >= 0) {
						cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
						cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
						cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				}

				// Draw the fullscreen quad
				cFullscreenQuad.Draw(m_pRenderTarget[0]->GetSize());

				// The result is now within the other render target
				m_bResultIndex = !m_bResultIndex;
			}
		}
	}

	// Restore the previous render target
	cRenderer.SetRenderTarget(pSurfaceBackup);
}

/**
*  @brief
*    Returns the rectangle texture buffer storing the glow
*/
TextureBuffer *SRPDeferredGlow::GetTextureBuffer() const
{
	return m_pRenderTarget[m_bResultIndex] ? m_pRenderTarget[m_bResultIndex]->GetTextureBuffer() : NULL;
}

/**
*  @brief
*    Returns the downsample fragment shader
*/
Shader *SRPDeferredGlow::GetDownsampleFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cDownsampleFragmentShader;
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bDownsampleFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredGlow_Downsample.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGlow_Downsample_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGlow_Downsample_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		cShaderHandler.SetResource(pShader);
		m_bDownsampleFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the glow fragment shader
*/
Shader *SRPDeferredGlow::GetGlowFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	Shader *pShader = m_cGlowFragmentShader.GetResource();
	if (!pShader && !m_bGlowFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredGlow_Glow.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGlow_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGlow_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cGlowFragmentShader.SetResource(pShader);
		m_bGlowFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the result fragment shader
*/
Shader *SRPDeferredGlow::GetResultFragmentShader(Renderer &cRenderer, bool bDiscard)
{
	// Get/construct the shader
	Shader *pShader = m_cResultFragmentShader[bDiscard].GetResource();
	if (!pShader && !m_bResultFragmentShader[bDiscard]) {
		const static String ShaderFilename = "Fragment/SRPDeferredGlow_Result.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bDiscard) {
			sDefines += "#define DISCARD\n";
			sName    += "[Discard]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGlow_Result_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGlow_Result_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);  // Currently, within "glslf" the "discard" keyword seems to have no effect, but arbfp1 will mess up everything :/
		}
		m_cResultFragmentShader[bDiscard].SetResource(pShader);
		m_bResultFragmentShader[bDiscard] = true;
	}

	// Return the shader
	return pShader;
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredGlow::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass and check whether or not color target 3 has real information in it
	SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
	if (pSRPDeferredGBuffer && pSRPDeferredGBuffer->IsColorTarget3Used() && pSRPDeferredGBuffer->IsColorTarget3AlphaUsed()) {
		// Get the fullscreen quad instance
		FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
		if (pFullscreenQuad) {
			// Get the texture buffer to use
			TextureBufferRectangle *pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
			if (pTextureBuffer) {
				// Reset all render states to default
				cRenderer.GetRendererContext().GetEffectManager().Use();

				// Calculate the glow texture buffer
				if (GlowDownscale < 1.0f)
					GlowDownscale = 1.0f;
				CalculateGlow(*pFullscreenQuad, *pTextureBuffer, 0.0f, GlowBlurPasses, GlowDownscale);

				// Get glow texture buffer
				pTextureBuffer = (TextureBufferRectangle*)GetTextureBuffer();
				if (pTextureBuffer) {
					// Get and set the fragment shader
					Shader *pFragmentShader = GetResultFragmentShader(cRenderer, !(GetFlags() & NoDiscard));
					if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
						// Get and set the fragment shader program
						ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
						cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

						{ // Set the "GlowFactor" fragment shader parameter
							static const String sGlowFactor = "GlowFactor";
							pFragmentShaderProgram->SetParameter1f(sGlowFactor, GlowFactor);
						}

						{ // Set the "Texture" fragment shader parameter
							static const String sTexture = "Texture";
							const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pTextureBuffer);
							if (nStage >= 0) {
								cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
								cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
								cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
							}
						}

						// Set blend mode
						if (!(GetFlags() & NoBlending)) {
							cRenderer.SetRenderState(RenderState::BlendEnable,	true);
							cRenderer.SetRenderState(RenderState::SrcBlendFunc,	BlendFunc::One);
							cRenderer.SetRenderState(RenderState::DstBlendFunc,	BlendFunc::One);
						}

						// Draw the fullscreen quad
						pFullscreenQuad->Draw(pTextureBuffer->GetSize());
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
