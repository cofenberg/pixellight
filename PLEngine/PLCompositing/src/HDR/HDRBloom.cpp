/*********************************************************\
 *  File: HDRBloom.cpp                                   *
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
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/HDR/HDRBloom.h"
#include "HDRBloom_Cg.h"	// The shader programs


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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HDRBloom::HDRBloom(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pFullscreenQuad(NULL),
	m_bBloomFragmentShader(false),
	m_bResultIndex(0)
{
	// Init data
	m_pRenderTarget[0] = m_pRenderTarget[1] = NULL;
	MemoryManager::Set(m_bDownsampleFragmentShader, 0, sizeof(m_bDownsampleFragmentShader));
}

/**
*  @brief
*    Destructor
*/
HDRBloom::~HDRBloom()
{
	// Destroy all used shaders
	DestroyShaders();

	// Destroy the fullscreen quad
	if (m_pFullscreenQuad)
		delete m_pFullscreenQuad;

	// Destroy the render targets
	for (int i=0; i<2; i++) {
		if (m_pRenderTarget[i])
			delete m_pRenderTarget[i];
	}

	// Destroy the bloom fragment shader
	if (m_cBloomFragmentShader.GetResource())
		delete m_cBloomFragmentShader.GetResource();
}

/**
*  @brief
*    Calculates the bloom
*/
void HDRBloom::CalculateBloom(TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, bool bToneMapping, bool bAutomaticAverageLuminance, const Color3 &cLuminanceConvert,
							  float fKey, float fWhiteLevel, float fAverageLuminance, TextureBuffer *pHDRAverageLuminanceTextureBuffer, uint32 nBloomBlurPasses, float fDownscale)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = cOriginalTexture.GetFormat();

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
					m_pRenderTarget[i] = m_pRenderer->CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
			}
		}
	}

	{ // First step: Downscale, apply bright pass filter and tone mapping
		// Get the fragment shader
		Shader *pFragmentShader = GetDownsampleFragmentShader(bToneMapping, bAutomaticAverageLuminance);
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Make the render target 0 to the current render target
			m_pRenderer->SetRenderTarget(m_pRenderTarget[0]);
			m_bResultIndex = 0;

			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

			// Set tone mapping fragment shader parameters
			if (bToneMapping) {
				{ // Set the "LuminanceConvert" fragment shader parameter
					static const String sLuminanceConvert = "LuminanceConvert";
					pFragmentShaderProgram->SetParameter3fv(sLuminanceConvert, cLuminanceConvert);
				}

				{ // Set the "Key" fragment shader parameter
					static const String sKey = "Key";
					pFragmentShaderProgram->SetParameter1f(sKey, (fKey > 0.0f) ? fKey : 0.0f);
				}

				{ // Set the "WhiteLevel" fragment shader parameter
					static const String sWhiteLevel = "WhiteLevel";
					pFragmentShaderProgram->SetParameter1f(sWhiteLevel, (fWhiteLevel > 0.0f) ? fWhiteLevel : 0.0f);
				}

				// Set the "AverageLuminance" fragment shader parameter
				if (bAutomaticAverageLuminance) {
					static const String sAverageLuminanceTexture = "AverageLuminanceTexture";
					const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sAverageLuminanceTexture, pHDRAverageLuminanceTextureBuffer);
					if (nStage >= 0) {
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressU,  TextureAddressing::Wrap);
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressV,  TextureAddressing::Wrap);
						m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
						m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
						m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				} else {
					static const String sAverageLuminance = "AverageLuminance";
					pFragmentShaderProgram->SetParameter1f(sAverageLuminance, fAverageLuminance);
				}
			}

			{ // Set the "BrightThreshold" fragment shader parameter
				static const String sBrightThreshold = "BrightThreshold";
				pFragmentShaderProgram->SetParameter1f(sBrightThreshold, fBrightThreshold);
			}

			{ // Set the "Texture" fragment shader parameter
				static const String sTexture = "Texture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, &cOriginalTexture);
				if (nStage >= 0) {
					m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
					m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
					m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
					m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
					m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Create the fullscreen quad instance if required
			if (!m_pFullscreenQuad)
				m_pFullscreenQuad = new FullscreenQuad(*m_pRenderer);

			// Draw the fullscreen quad
			m_pFullscreenQuad->Draw(cOriginalTexture.GetSize());
		}
	}

	{ // Gaussian convolution filter to bloom
		// Get the fragment shader
		Shader *pFragmentShader = GetBloomFragmentShader();
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

			// Horizontal and vertical blur
			for (uint32 i=0; i<nBloomBlurPasses; i++) {
				// Make the render target 1 to the current render target
				m_pRenderer->SetRenderTarget(m_pRenderTarget[!m_bResultIndex]);

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
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
						m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
						m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
						m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				}

				// Draw the fullscreen quad
				m_pFullscreenQuad->Draw(m_pRenderTarget[0]->GetSize());

				// The result is now within the other render target
				m_bResultIndex = !m_bResultIndex;
			}
		}
	}
}

/**
*  @brief
*    Returns the rectangle texture buffer storing the bloom
*/
TextureBuffer *HDRBloom::GetTextureBuffer() const
{
	return m_pRenderTarget[m_bResultIndex] ? m_pRenderTarget[m_bResultIndex]->GetTextureBuffer() : NULL;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the downsample fragment shader
*/
Shader *HDRBloom::GetDownsampleFragmentShader(bool bToneMapping, bool bAutomaticAverageLuminance)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cDownsampleFragmentShader[bToneMapping][bAutomaticAverageLuminance];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bDownsampleFragmentShader[bToneMapping][bAutomaticAverageLuminance]) {
		const static String ShaderFilename = "Fragment/HDRBloom_Downsample.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bToneMapping) {
			sDefines += "#define TONE_MAPPING\n";
			sName    += "[ToneMapping]";
			if (bAutomaticAverageLuminance) {
				sDefines += "#define AUTOMATIC_AVERAGE_LUMINANCE\n";
				sName    += "[AutomaticAverageLuminance]";
			}
		}

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRBloom_Downsample_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRBloom_Downsample_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bDownsampleFragmentShader[bToneMapping][bAutomaticAverageLuminance] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the bloom fragment shader
*/
Shader *HDRBloom::GetBloomFragmentShader()
{
	// Get/construct the shader
	Shader *pShader = m_cBloomFragmentShader.GetResource();
	if (!pShader && !m_bBloomFragmentShader) {
		const static String ShaderFilename = "Fragment/HDRBloom_Bloom.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRBloom_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRBloom_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cBloomFragmentShader.SetResource(pShader);
		m_bBloomFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void HDRBloom::DestroyShaders()
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
	MemoryManager::Set(m_bDownsampleFragmentShader, 0, sizeof(m_bDownsampleFragmentShader));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
