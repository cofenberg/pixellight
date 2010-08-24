/*********************************************************\
 *  File: SRPDeferredDOF.cpp                             *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include <PLScene/Compositing/General/SRPBegin.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredDOF.h"
#include "SRPDeferredDOF_Cg.h"	// The shader programs


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
pl_implement_class(SRPDeferredDOF)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredDOF::SRPDeferredDOF() :
	EffectWeight(this),
	NearPlaneDepth(this),
	FocalPlaneDepth(this),
	FarPlaneDepth(this),
	BlurrinessCutoff(this),
	BlurPasses(this),
	BlurDownscale(this),
	Flags(this),
	m_bDepthBlurFragmentShader(false),
	m_bDownsampleFragmentShader(false),
	m_bBlurFragmentShader(false),
	m_bResultFragmentShader(false),
	m_bResultIndex(0)
{
	// Init data
	MemoryManager::Set(m_bShowFragmentShader, 0, sizeof(m_bShowFragmentShader));
	m_pRenderTarget[0] = m_pRenderTarget[1] = NULL;
}

/**
*  @brief
*    Destructor
*/
SRPDeferredDOF::~SRPDeferredDOF()
{
	// Destroy the render targets
	for (int i=0; i<2; i++) {
		if (m_pRenderTarget[i])
			delete m_pRenderTarget[i];
	}

	// Destroy the depth blur fragment shader
	if (m_cDepthBlurFragmentShader.GetResource())
		delete m_cDepthBlurFragmentShader.GetResource();

	// Destroy the downsample fragment shader
	if (m_cDownsampleFragmentShader.GetResource())
		delete m_cDownsampleFragmentShader.GetResource();

	// Destroy the blur fragment shader
	if (m_cBlurFragmentShader.GetResource())
		delete m_cBlurFragmentShader.GetResource();

	// Destroy the result fragment shader
	if (m_cResultFragmentShader.GetResource())
		delete m_cResultFragmentShader.GetResource();

	// Destroy the show fragment shader
	for (int i=0; i<2; i++) {
		if (m_cShowFragmentShader[i].GetResource())
			delete m_cShowFragmentShader[i].GetResource();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates the depth blur
*/
void SRPDeferredDOF::CalculateDepthBlur(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cRGBTexture, TextureBufferRectangle &cNormalDepthTexture,
										float fNearPlaneDepth, float fFocalPlaneDepth, float fFarPlaneDepth, float fBlurrinessCutoff)
{
	// Get the renderer instance
	Renderer &cRenderer = cRGBTexture.GetRenderer();

	// Get the fragment shader
	Shader *pFragmentShader = GetDepthBlurFragmentShader(cRenderer);
	if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
		// Set the fragment shader program
		ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
		cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

		{ // Set the "DOFParams" fragment shader parameter and ensure that all values are correct
			static const String sDOFParams = "DOFParams";

			// fFocalPlaneDepth - fNearPlaneDepth is not allowed to be 0!
			if (fNearPlaneDepth > fFocalPlaneDepth)
				fNearPlaneDepth = fFocalPlaneDepth;
			if (fFocalPlaneDepth - fNearPlaneDepth < FLT_MIN)
				fNearPlaneDepth -= FLT_MIN;

			// fFarPlaneDepth - fFocalPlaneDepth is not allowed to be 0!
			if (fFarPlaneDepth < fFocalPlaneDepth)
				fFarPlaneDepth = fFocalPlaneDepth;
			if (fFarPlaneDepth - fFocalPlaneDepth < FLT_MIN)
				fFarPlaneDepth += FLT_MIN;

			// Set parameter
			pFragmentShaderProgram->SetParameter4f(sDOFParams, fNearPlaneDepth, fFocalPlaneDepth, fFarPlaneDepth, fBlurrinessCutoff);
		}

		{ // Set the "RGBTexture" fragment shader parameter
			static const String sRGBTexture = "RGBTexture";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sRGBTexture, &cRGBTexture);
			if (nStage >= 0) {
				cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		{ // Set the "NormalDepth" fragment shader parameter
			static const String sNormalDepth = "NormalDepth";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sNormalDepth, &cNormalDepthTexture);
			if (nStage >= 0) {
				cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Draw the fullscreen quad
		cFullscreenQuad.Draw(cRGBTexture.GetSize());
	}
}

/**
*  @brief
*    Calculates the blur
*/
void SRPDeferredDOF::CalculateBlur(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, uint32 nBlurPasses, float fDownscale)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = cOriginalTexture.GetFormat();

	// Get the renderer instance
	Renderer &cRenderer = cOriginalTexture.GetRenderer();

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

	{ // Gaussian convolution filter to blur
		// Get the fragment shader
		Shader *pFragmentShader = GetBlurFragmentShader(cRenderer);
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
}

/**
*  @brief
*    Shows data
*/
void SRPDeferredDOF::Show(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cTexture, uint32 nType)
{
	// Get the renderer instance
	Renderer &cRenderer = cTexture.GetRenderer();

	// Get the fragment shader
	Shader *pFragmentShader = GetShowFragmentShader(cRenderer, nType);
	if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
		// Set the fragment shader program
		ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
		cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

		{ // Set the "Texture" fragment shader parameter
			static const String sTexture = "Texture";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, &cTexture);
			if (nStage >= 0) {
				cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Draw the fullscreen quad
		cFullscreenQuad.Draw(cTexture.GetSize());
	}
}

/**
*  @brief
*    Returns the rectangle texture buffer storing the blur
*/
TextureBuffer *SRPDeferredDOF::GetBlurTextureBuffer() const
{
	return m_pRenderTarget[m_bResultIndex] ? m_pRenderTarget[m_bResultIndex]->GetTextureBuffer() : NULL;
}

/**
*  @brief
*    Returns the depth blur fragment shader
*/
Shader *SRPDeferredDOF::GetDepthBlurFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	Shader *pShader = m_cDepthBlurFragmentShader.GetResource();
	if (!pShader && !m_bDepthBlurFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredDOF_DepthBlur.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDOF_DepthBlur_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDOF_DepthBlur_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cDepthBlurFragmentShader.SetResource(pShader);
		m_bDepthBlurFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the downsample fragment shader
*/
Shader *SRPDeferredDOF::GetDownsampleFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cDownsampleFragmentShader;
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bDownsampleFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredBlur_Downsample.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDOF_Downsample_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDOF_Downsample_Cg_FS, nNumOfBytes, false, ".cg");
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
*    Returns the blur fragment shader
*/
Shader *SRPDeferredDOF::GetBlurFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	Shader *pShader = m_cBlurFragmentShader.GetResource();
	if (!pShader && !m_bBlurFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredDOF_Blur.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDOF_Blur_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDOF_Blur_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cBlurFragmentShader.SetResource(pShader);
		m_bBlurFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the result fragment shader
*/
Shader *SRPDeferredDOF::GetResultFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	Shader *pShader = m_cResultFragmentShader.GetResource();
	if (!pShader && !m_bResultFragmentShader) {
		const static String ShaderFilename = "Fragment/SRPDeferredDOF_Result.cg";
		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDOF_Result_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDOF_Result_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(ShaderFilename, cFile, true, "glslf");
		}
		m_cResultFragmentShader.SetResource(pShader);
		m_bResultFragmentShader = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Returns the show fragment shader
*/
Shader *SRPDeferredDOF::GetShowFragmentShader(Renderer &cRenderer, uint32 nType)
{
	// Get/construct the shader
	Shader *pShader = m_cShowFragmentShader[nType].GetResource();
	if (!pShader && !m_bShowFragmentShader[nType]) {
		const static String ShaderFilename = "Fragment/SRPDeferredDOF_Show.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		switch (nType) {
			case 0:
				sDefines += "#define DEPTH_BLUR\n";
				sName    += "[DepthBlur]";
				break;

			case 1:
				sDefines += "#define BLUR\n";
				sName    += "[Blur]";
				break;
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDOF_Show_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDOF_Show_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		m_cShowFragmentShader[nType].SetResource(pShader);
		m_bShowFragmentShader[nType] = true;
	}

	// Return the shader
	return pShader;
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredDOF::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get DOF settings
	float fEffectWeight		= EffectWeight;
	float fNearPlaneDepth   = NearPlaneDepth;
	float fFocalPlaneDepth  = FocalPlaneDepth;
	float fFarPlaneDepth    = FarPlaneDepth;
	float fBlurrinessCutoff = BlurrinessCutoff;
	bool  bDOFActive        = true;

	// Get depth of field settings from the 'SNMPostProcessDepthOfField' modifier of the used camera?
	if (!(GetFlags() & IgnoreCameraSettings)) {
		bDOFActive = false;
		SNCamera *pCamera = SNCamera::GetCamera();
		if (pCamera) {
			SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcessDepthOfField");
			if (pModifier && pModifier->IsActive()) {
				fEffectWeight = pModifier->GetAttribute("EffectWeight")->GetFloat();
				if (fEffectWeight > 0.0f) {
					fNearPlaneDepth   = pModifier->GetAttribute("NearBlurDepth")   ->GetFloat();
					fFocalPlaneDepth  = pModifier->GetAttribute("FocalPlaneDepth") ->GetFloat();
					fFarPlaneDepth    = pModifier->GetAttribute("FarBlurDepth")    ->GetFloat();
					fBlurrinessCutoff = pModifier->GetAttribute("BlurrinessCutoff")->GetFloat();
					bDOFActive        = true;
				}
			}
		}
	}

	// DOF active?
	if (bDOFActive) {
		// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
		SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
		if (pSRPDeferredGBuffer) {
			// Get the normal/depth texture buffer to use
			TextureBufferRectangle *pNormalDepthTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
			if (pNormalDepthTextureBuffer) {
				// Get the fullscreen quad instance
				FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
				if (pFullscreenQuad) {
					// Get the "PLScene::SRPBegin" instance
					SRPBegin *pSRPBegin = (SRPBegin*)GetFirstInstanceOfSceneRendererPassClass("PLScene::SRPBegin");
					if (pSRPBegin) {
						// We need up-to-date front render target content, so swap the render targets
						pSRPBegin->SwapRenderTargets();

						// Get the front render target of SRPBegin, this holds the current content
						SurfaceTextureBuffer *pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
						if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer()) {
							// Reset all render states to default
							cRenderer.GetRendererContext().GetEffectManager().Use();
							cRenderer.SetColorMask();

							// Calculate the depth blur
							CalculateDepthBlur(*pFullscreenQuad, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), *pNormalDepthTextureBuffer, fNearPlaneDepth, fFocalPlaneDepth, fFarPlaneDepth, fBlurrinessCutoff);
							if (GetFlags() & ShowDepthBlur) {
								// Show depth blur data
								pSRPBegin->SwapRenderTargets();
								pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
								if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer())
									Show(*pFullscreenQuad, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), 0);
							} else {
								// Calculate the blur texture buffer
								if (BlurDownscale < 1.0f)
									BlurDownscale = 1.0f;
								CalculateBlur(*pFullscreenQuad, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), 0.0f, BlurPasses, BlurDownscale);

								// We need up-to-date front render target content, so swap the render targets
								pSRPBegin->SwapRenderTargets();

								// Get blur texture buffer
								TextureBufferRectangle *pTextureBuffer = (TextureBufferRectangle*)GetBlurTextureBuffer();
								if (pTextureBuffer) {
									// Show blur data?
									if (GetFlags() & ShowBlur) {
										Show(*pFullscreenQuad, *pTextureBuffer, 1);
									} else {
										pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
										if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer()) {
											// Get and set the fragment shader
											Shader *pFragmentShader = GetResultFragmentShader(cRenderer);
											if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
												// Get and set the fragment shader program
												ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
												cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

												{ // Set the "EffectWeight" fragment shader parameter
													static const String sEffectWeight = "EffectWeight";
													pFragmentShaderProgram->SetParameter1f(sEffectWeight, fEffectWeight);
												}

												{ // Set the "BlurDownscale" fragment shader parameter
													static const String sBlurDownscale = "BlurDownscale";
													pFragmentShaderProgram->SetParameter1f(sBlurDownscale, BlurDownscale);
												}

												{ // Set the "BlurTexture" fragment shader parameter
													static const String sBlurTexture = "BlurTexture";
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sBlurTexture, pTextureBuffer);
													if (nStage >= 0) {
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
														cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
														cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
													}
												}

												{ // Set the "Texture" fragment shader parameter
													static const String sTexture = "Texture";
													const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pFrontSurfaceTextureBuffer->GetTextureBuffer());
													if (nStage >= 0) {
														cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
														cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
														cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
														cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
													}
												}

												// Draw the fullscreen quad
												pFullscreenQuad->Draw(((TextureBufferRectangle*)pFrontSurfaceTextureBuffer->GetTextureBuffer())->GetSize());
											}
										}
									}
								}
							}
						}
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
