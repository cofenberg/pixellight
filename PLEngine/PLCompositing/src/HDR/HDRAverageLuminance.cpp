/*********************************************************\
 *  File: HDRAverageLuminance.cpp                        *
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
#include <PLMath/Math.h>
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/HDR/HDRAverageLuminance.h"
#include "HDRAverageLuminance_Cg.h"	// The shader programs


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
HDRAverageLuminance::HDRAverageLuminance(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pFullscreenQuad(NULL),
	m_bDownsampleLogFragmentShader(false),
	m_pDownsampleLogRenderTarget(NULL),
	m_bDownsampleFragmentShader(false),
	m_pDownsampleRenderTarget(NULL),
	m_bDownsampleExpFragmentShader(false),
	m_pAverageLuminanceTextureBuffer2D(NULL)
{
}

/**
*  @brief
*    Destructor
*/
HDRAverageLuminance::~HDRAverageLuminance()
{
	// Destroy the fullscreen quad
	if (m_pFullscreenQuad)
		delete m_pFullscreenQuad;

	// Destroy the downsample 2x2 log fragment shader and render target
	if (m_cDownsampleLogFragmentShader.GetResource())
		delete m_cDownsampleLogFragmentShader.GetResource();
	if (m_pDownsampleLogRenderTarget)
		delete m_pDownsampleLogRenderTarget;

	// Destroy the downsample 4x4 fragment shader and render target
	if (m_cDownsampleFragmentShader.GetResource())
		delete m_cDownsampleFragmentShader.GetResource();
	if (m_pDownsampleRenderTarget)
		delete m_pDownsampleRenderTarget;

	// Destroy the average luminance result step stuff
	if (m_cDownsampleExpFragmentShader.GetResource())
		delete m_cDownsampleExpFragmentShader.GetResource();
	if (m_pAverageLuminanceTextureBuffer2D)
		delete m_pAverageLuminanceTextureBuffer2D;
}

/**
*  @brief
*    Calculates the logarithmic average luminance
*/
void HDRAverageLuminance::CalculateAverageLuminance(TextureBufferRectangle &cOriginalTexture, const Color3 &cLuminanceConvert)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = (cOriginalTexture.GetFormat() == TextureBuffer::R16G16B16A16F) ? TextureBuffer::L16F : TextureBuffer::L32F;

	{ // First step: Downsample 2x2, calculate pixel luminance and log - I don't use a "bilinear filter" because this would mess up the incomming texel data "before" the log calculation was performed!
		// Get the fragment shader
		Shader *pFragmentShader = GetDownsampleLogFragmentShader();
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Get the size of the original HDR texture
			const Vector2i vRTSize = cOriginalTexture.GetSize()/2;
			if (vRTSize.x != 0 && vRTSize.y != 0) {
				// Render target size change?
				if (m_pDownsampleLogRenderTarget && (m_pDownsampleLogRenderTarget->GetSize() != vRTSize || m_pDownsampleLogRenderTarget->GetFormat() != nInternalFormat)) {
					// Destroy the downsample 2x2 log render target
					if (m_pDownsampleLogRenderTarget) {
						delete m_pDownsampleLogRenderTarget;
						m_pDownsampleLogRenderTarget = NULL;
					}
				}

				// Create the downsample 2x2 log render target right now?
				if (!m_pDownsampleLogRenderTarget)
					m_pDownsampleLogRenderTarget = m_pRenderer->CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
			}
			
			// Make the downsample 2x2 log render target to the current render target
			m_pRenderer->SetRenderTarget(m_pDownsampleLogRenderTarget);

			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

			{ // Set the "LuminanceConvert" fragment shader parameter
				static const String sLuminanceConvert = "LuminanceConvert";
				pFragmentShaderProgram->SetParameter3fv(sLuminanceConvert, cLuminanceConvert);
			}

			{ // Set the "Epsilon" fragment shader parameter
				static const String sEpsilon = "Epsilon";
				pFragmentShaderProgram->SetParameter1f(sEpsilon, 0.0001f);
			}

			{ // Set the "Texture" fragment shader parameter
				static const String sTexture = "Texture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, &cOriginalTexture);
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
			m_pFullscreenQuad->Draw(cOriginalTexture.GetSize());
		}
	}

	const uint32 TextureScaleFactor = 2;
	Vector2i vFinalTextureSize;
	TextureBufferRectangle *pFinalTextureBufferRectangle = NULL;

	{ // Second step: Reduce to <4>x<4>
		// Get the fragment shader
		Shader *pFragmentShader = GetDownsampleFragmentShader();
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Get the size of the original HDR texture
			const Vector2i vRTSize = m_pDownsampleLogRenderTarget->GetSize()/TextureScaleFactor;
			if (vRTSize.x != 0 && vRTSize.y != 0) {
				// Render target size change?
				if (m_pDownsampleRenderTarget && (m_pDownsampleRenderTarget->GetSize() != vRTSize || m_pDownsampleRenderTarget->GetFormat() != nInternalFormat)) {
					// Destroy the downsample 4x4 render target
					if (m_pDownsampleRenderTarget) {
						delete m_pDownsampleRenderTarget;
						m_pDownsampleRenderTarget = NULL;
					}
				}

				// Create the downsample 4x4 render target right now?
				if (!m_pDownsampleRenderTarget)
					m_pDownsampleRenderTarget = m_pRenderer->CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
			}

			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

			// Get the maximum size
			Vector2i vCurrentSize = m_pDownsampleLogRenderTarget->GetSize();
			uint32   nSize		  = Math::Max(vCurrentSize.x, vCurrentSize.y);

			// Downscale in multiple render passes, we render into m_pDownsampleRenderTarget and m_pDownsampleLogRenderTarget in a ping-pong way
			bool bRenderTarget = false;
			for (; nSize>TextureScaleFactor; nSize/=TextureScaleFactor, bRenderTarget=!bRenderTarget, vCurrentSize/=TextureScaleFactor) {
				// Get the render target we will render into
				SurfaceTextureBuffer *pRenderTargetTexture = bRenderTarget ? m_pDownsampleLogRenderTarget : m_pDownsampleRenderTarget;

				// Get the texture buffer we will downscale
				TextureBufferRectangle *pTextureBufferRectangle = (TextureBufferRectangle*)(bRenderTarget ? m_pDownsampleRenderTarget->GetTextureBuffer() : m_pDownsampleLogRenderTarget->GetTextureBuffer());

				// Set the current render target
				m_pRenderer->SetRenderTarget(pRenderTargetTexture);

				{ // Set the "Texture" fragment shader parameter
					static const String sTexture = "Texture";
					const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pTextureBufferRectangle);
					if (nStage >= 0) {
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
						m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
						m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);	// [TODO] Use bilinear filter
						m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);	// [TODO] Use bilinear filter
						m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				}

				// Backup texture width
				vFinalTextureSize			 = vCurrentSize/TextureScaleFactor;
				pFinalTextureBufferRectangle = (TextureBufferRectangle*)pRenderTargetTexture->GetTextureBuffer();

				// Draw the fullscreen quad
				m_pFullscreenQuad->Draw(vCurrentSize, vFinalTextureSize);
			}
		}
	}

	{ // Third step: Reduce <4>x<4> to <1>x<1> and calculate the exponent
		// Get the fragment shader
		Shader *pFragmentShader = GetDownsampleExpFragmentShader();
		if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
			// Render format change?
			if (m_pAverageLuminanceTextureBuffer2D && m_pAverageLuminanceTextureBuffer2D->GetFormat() != nInternalFormat) {
				// Destroy the result render target
				if (m_pAverageLuminanceTextureBuffer2D) {
					delete m_pAverageLuminanceTextureBuffer2D;
					m_pAverageLuminanceTextureBuffer2D = NULL;
				}
			}

			// Create the result render target right now?
			if (!m_pAverageLuminanceTextureBuffer2D)
				m_pAverageLuminanceTextureBuffer2D = m_pRenderer->CreateSurfaceTextureBuffer2D(Vector2i::One, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);

			// Make the result render target to the current render target
			m_pRenderer->SetRenderTarget(m_pAverageLuminanceTextureBuffer2D);

			// Set the fragment shader program
			ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
			m_pRenderer->SetFragmentShaderProgram(pFragmentShaderProgram);

			{ // Set the "Texture" fragment shader parameter
				static const String sTexture = "Texture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pFinalTextureBufferRectangle);
				if (nStage >= 0) {
					m_pRenderer->SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
					m_pRenderer->SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
					m_pRenderer->SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);	// [TODO] Use bilinear filter
					m_pRenderer->SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);	// [TODO] Use bilinear filter
					m_pRenderer->SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw the fullscreen quad
			m_pFullscreenQuad->Draw(vFinalTextureSize);
		}
	}
}

/**
*  @brief
*    Returns the 1x1 2D texture buffer storing the logarithmic average luminance
*/
TextureBuffer *HDRAverageLuminance::GetTextureBuffer() const
{
	return m_pAverageLuminanceTextureBuffer2D ? m_pAverageLuminanceTextureBuffer2D->GetTextureBuffer() : NULL;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the downsample 2x2 log fragment shader
*/
Shader *HDRAverageLuminance::GetDownsampleLogFragmentShader()
{
	// Get/construct the shader
	Shader *pShader = m_cDownsampleLogFragmentShader.GetResource();
	if (!pShader && !m_bDownsampleLogFragmentShader) {
		const static String ShaderFilename = "Fragment/HDRAverageLuminance_DownsampleLog.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRAverageLuminance_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRAverageLuminance_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf", "", "DownsampleLog");
		}
		m_cDownsampleLogFragmentShader.SetResource(pShader);
		m_bDownsampleLogFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the downsample 4x4 fragment shader
*/
Shader *HDRAverageLuminance::GetDownsampleFragmentShader()
{
	// Get/construct the shader
	Shader *pShader = m_cDownsampleFragmentShader.GetResource();
	if (!pShader && !m_bDownsampleFragmentShader) {
		const static String ShaderFilename = "Fragment/HDRAverageLuminance_Downsample.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRAverageLuminance_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRAverageLuminance_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf", "", "Downsample");
		}
		m_cDownsampleFragmentShader.SetResource(pShader);
		m_bDownsampleFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the downsample 4x4 exp fragment shader
*/
Shader *HDRAverageLuminance::GetDownsampleExpFragmentShader()
{
	// Get/construct the shader
	Shader *pShader = m_cDownsampleExpFragmentShader.GetResource();
	if (!pShader && !m_bDownsampleExpFragmentShader) {
		const static String ShaderFilename = "Fragment/HDRAverageLuminance_DownsampleExp.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszHDRAverageLuminance_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszHDRAverageLuminance_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf", "", "DownsampleExp");
		}
		m_cDownsampleExpFragmentShader.SetResource(pShader);
		m_bDownsampleExpFragmentShader = true;
	}

	// Return the shader
	return pShader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
