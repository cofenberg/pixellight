/*********************************************************\
 *  File: HDRLightAdaptation.cpp                         *
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
#include <PLMath/Rectangle.h>
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/HDR/HDRLightAdaptation.h"


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
HDRLightAdaptation::HDRLightAdaptation(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pFullscreenQuad(NULL),
	m_bFragmentShader(false),
	m_bPreviousIndex(0)
{
	m_pLightAdaptationTextureBuffer2D[0] = m_pLightAdaptationTextureBuffer2D[1] = NULL;
}

/**
*  @brief
*    Destructor
*/
HDRLightAdaptation::~HDRLightAdaptation()
{
	// Destroy the fullscreen quad
	if (m_pFullscreenQuad)
		delete m_pFullscreenQuad;

	// Destroy the fragment shader and render target
	if (m_cFragmentShader.GetResource())
		delete m_cFragmentShader.GetResource();
	for (int i=0; i<2; i++) {
		if (m_pLightAdaptationTextureBuffer2D[i])
			delete m_pLightAdaptationTextureBuffer2D[i];
	}
}

/**
*  @brief
*    Calculates the light adaptation
*/
void HDRLightAdaptation::CalculateLightAdaptation(PLRenderer::TextureBuffer &cAverageLuminanceTextureBuffer2D, float fTauTimeDifference)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = (cAverageLuminanceTextureBuffer2D.GetFormat() == TextureBuffer::R16G16B16A16F) ? TextureBuffer::L16F : TextureBuffer::L32F;

	// Get the fragment shader
	Shader *pFragmentShader = GetFragmentShader();
	if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
		// Swap previous/current texture buffer
		m_bPreviousIndex = !m_bPreviousIndex;
		const bool bCurrentIndex = !m_bPreviousIndex;

		// Render format change?
		if (m_pLightAdaptationTextureBuffer2D[bCurrentIndex] && m_pLightAdaptationTextureBuffer2D[bCurrentIndex]->GetFormat() != nInternalFormat) {
			// Destroy the result render target
			if (m_pLightAdaptationTextureBuffer2D[bCurrentIndex]) {
				delete m_pLightAdaptationTextureBuffer2D[bCurrentIndex];
				m_pLightAdaptationTextureBuffer2D[bCurrentIndex] = NULL;
			}
		}

		// Create the result render target right now?
		if (!m_pLightAdaptationTextureBuffer2D[bCurrentIndex])
			m_pLightAdaptationTextureBuffer2D[bCurrentIndex] = m_pRenderer->CreateSurfaceTextureBuffer2D(Vector2i::One, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);

		// Make the result render target to the current render target
		m_pRenderer->SetRenderTarget(m_pLightAdaptationTextureBuffer2D[bCurrentIndex]);

		// Set the fragment shader program
		ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
		m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

		{ // Set the "Factor" fragment shader parameter
			static const String sFactor = "Factor";
			pFragmentShaderProgram->SetParameter1f(sFactor, 1.0f - Math::Exp(-fTauTimeDifference));
		}

		{ // Set the "PreviousTexture" fragment shader parameter
			static const String sPreviousTexture = "PreviousTexture";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sPreviousTexture, m_pLightAdaptationTextureBuffer2D[m_bPreviousIndex] ? m_pLightAdaptationTextureBuffer2D[m_bPreviousIndex]->GetTextureBuffer() : &cAverageLuminanceTextureBuffer2D);
			if (nStage >= 0) {
				m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
				m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
				m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
				m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
				m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		{ // Set the "CurrentTexture" fragment shader parameter
			static const String sCurrentTexture = "CurrentTexture";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sCurrentTexture, &cAverageLuminanceTextureBuffer2D);
			if (nStage >= 0) {
				m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
				m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
				m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
				m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
				m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Create the fullscreen quad instance if required
		if (!m_pFullscreenQuad)
			m_pFullscreenQuad = new FullscreenQuad(*m_pRenderer);

		// Draw the fullscreen quad
		m_pFullscreenQuad->Draw(Vector2i::One);
	}
}

/**
*  @brief
*    Returns the 1x1 2D texture buffer storing the light adaptation
*/
TextureBuffer *HDRLightAdaptation::GetTextureBuffer() const
{
	return m_pLightAdaptationTextureBuffer2D[!m_bPreviousIndex] ? m_pLightAdaptationTextureBuffer2D[!m_bPreviousIndex]->GetTextureBuffer() : NULL;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader
*/
Shader *HDRLightAdaptation::GetFragmentShader()
{
	// Get/construct the shader
	Shader *pShader = m_cFragmentShader.GetResource();
	if (!pShader && !m_bFragmentShader) {
		const static String ShaderFilename = "Fragment/HDRLightAdaptation.cg";
		{ // Load the shader
			#include "HDRLightAdaptation_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRLightAdaptation_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRLightAdaptation_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cFragmentShader.SetResource(pShader);
		m_bFragmentShader = true;
	}

	// Return the shader
	return pShader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
