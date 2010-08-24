/*********************************************************\
 *  File: SRPEndHDR.cpp                                  *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include <PLScene/Compositing/General/SRPBegin.h>
#include "PLCompositing/HDR/HDRAverageLuminance.h"
#include "PLCompositing/HDR/HDRLightAdaptation.h"
#include "PLCompositing/HDR/HDRBloom.h"
#include "PLCompositing/HDR/SRPEndHDR.h"


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
pl_implement_class(SRPEndHDR)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPEndHDR::SRPEndHDR() :
	LuminanceConvert(this),
	Key(this),
	WhiteLevel(this),
	AverageLuminance(this),
	Tau(this),
	BloomBrightThreshold(this),
	BloomFactor(this),
	BloomBlurPasses(this),
	BloomDownscale(this),
	Gamma(this),
	Flags(this),
	m_pFullscreenQuad(NULL),
	m_pHDRAverageLuminance(NULL),
	m_pHDRLightAdaptation(NULL),
	m_pHDRBloom(NULL)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPEndHDR::~SRPEndHDR()
{
	// Destroy all used shaders
	DestroyShaders();

	// Destroy the HDR logarithmic average luminance calculation component
	if (m_pHDRAverageLuminance)
		delete m_pHDRAverageLuminance;

	// Destroy the HDR light adaptation calculation component
	if (m_pHDRLightAdaptation)
		delete m_pHDRLightAdaptation;

	// Destroy the HDR bloom calculation component
	if (m_pHDRBloom)
		delete m_pHDRBloom;

	// Destroy the fullscreen quad
	if (m_pFullscreenQuad)
		delete m_pFullscreenQuad;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader
*/
Shader *SRPEndHDR::GetFragmentShader(Renderer &cRenderer, bool bToneMapping, bool bAutomaticAverageLuminance, bool bBloom, bool bGammaCorrection)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bToneMapping][bAutomaticAverageLuminance][bBloom][bGammaCorrection];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bToneMapping][bAutomaticAverageLuminance][bBloom][bGammaCorrection]) {
		const static String ShaderFilename = "Fragment/SRPEndHDR.cg";

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
		if (bBloom) {
			sDefines += "#define BLOOM\n";
			sName    += "[Bloom]";
		}
		if (bGammaCorrection) {
			sDefines += "#define GAMMA_CORRECTION\n";
			sName    += "[GammaCorrection]";
		}

		{ // Load the shader
			#include "SRPEndHDR_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszEndHDR_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszEndHDR_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bToneMapping][bAutomaticAverageLuminance][bBloom][bGammaCorrection] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPEndHDR::DestroyShaders()
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
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneRendererPass functions ]
//[-------------------------------------------------------]
void SRPEndHDR::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the "PLScene::SRPBegin" instance
	SRPBegin *pSRPBegin = (SRPBegin*)GetFirstInstanceOfSceneRendererPassClass("PLScene::SRPBegin");
	if (pSRPBegin) {
		// Get the back render target of SRPBegin, this holds the current content
		SurfaceTextureBuffer *pSurfaceTextureBuffer = pSRPBegin->GetBackRenderTarget();
		if (pSurfaceTextureBuffer) {
			// Get the texture we will use as 'source texture' when rendering the fullscreen quad
			TextureBufferRectangle *pHDRTextureBuffer = (TextureBufferRectangle*)pSurfaceTextureBuffer->GetTextureBuffer();

			// Reset all render states to default
			cRenderer.GetRendererContext().GetEffectManager().Use();
			cRenderer.SetColorMask();

			// Get the requested features
			bool bToneMapping				= !(GetFlags() & NoToneMapping);
			bool bAutomaticAverageLuminance = !(GetFlags() & NoAutomaticAverageLuminance);
			bool bLightAdaptation			= !(GetFlags() & NoLightAdaptation);
			bool bBloom						= !(GetFlags() & NoBloom);
			bool bGammaCorrection			= !(GetFlags() & NoGammaCorrection);

			// Calculate average luminance, required for tone mapping with automatically calculated average luminance
			TextureBuffer *pHDRAverageLuminanceTextureBuffer = NULL;
			if (bAutomaticAverageLuminance) {
				if (!m_pHDRAverageLuminance)
					m_pHDRAverageLuminance = new HDRAverageLuminance(cRenderer);
				m_pHDRAverageLuminance->CalculateAverageLuminance((TextureBufferRectangle&)*pSurfaceTextureBuffer->GetTextureBuffer(), LuminanceConvert.Get());

				// Light adaptation
				if (bLightAdaptation && m_pHDRAverageLuminance->GetTextureBuffer()) {
					// [TODO] Would be nice if the "previous" data would not be stored in the scene renderer pass instance...
					if (!m_pHDRLightAdaptation)
						m_pHDRLightAdaptation = new HDRLightAdaptation(cRenderer);
					m_pHDRLightAdaptation->CalculateLightAdaptation(*m_pHDRAverageLuminance->GetTextureBuffer(), Timing::GetInstance()->GetTimeDifference()*Tau);
					pHDRAverageLuminanceTextureBuffer = m_pHDRLightAdaptation->GetTextureBuffer();
				} else {
					pHDRAverageLuminanceTextureBuffer = m_pHDRAverageLuminance->GetTextureBuffer();
				}
			}
			if (!pHDRAverageLuminanceTextureBuffer)
				bAutomaticAverageLuminance = false;

			// Calculate bloom
			if (bBloom) {
				if (BloomDownscale < 1.0f)
					BloomDownscale = 1.0f;
				if (!m_pHDRBloom)
					m_pHDRBloom = new HDRBloom(cRenderer);
				m_pHDRBloom->CalculateBloom((TextureBufferRectangle&)*pSurfaceTextureBuffer->GetTextureBuffer(), BloomBrightThreshold, bToneMapping, bAutomaticAverageLuminance,
											 LuminanceConvert.Get(), Key, WhiteLevel, AverageLuminance, pHDRAverageLuminanceTextureBuffer, BloomBlurPasses, BloomDownscale);

				// Show bloom texture (for debugging)
				if ((GetFlags() & ShowBloomTexture)) {
					bToneMapping			   = false;
					bAutomaticAverageLuminance = false;
					bLightAdaptation		   = false;
					bBloom					   = false;
					bGammaCorrection		   = false;
					pHDRTextureBuffer = (TextureBufferRectangle*)m_pHDRBloom->GetTextureBuffer();
				}
			}

			// Set the current render target back to the orignal one?
			if (GetFlags() & WriteToOriginalSurface)
				cRenderer.SetRenderTarget(pSRPBegin->GetOriginalRenderTarget());
			else
				pSRPBegin->SwapRenderTargets();

			// Get and set the fragment shader
			Shader *pFragmentShader = GetFragmentShader(cRenderer, bToneMapping, bAutomaticAverageLuminance, bBloom, bGammaCorrection);
			if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
				// Get and set the fragment shader program
				ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
				cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

				// Set tone mapping fragment shader parameters
				if (bToneMapping) { 
					{ // Set the "LuminanceConvert" fragment shader parameter
						static const String sLuminanceConvert = "LuminanceConvert";
						pFragmentShaderProgram->SetParameter3fv(sLuminanceConvert, LuminanceConvert.Get());
					}

					{ // Set the "Key" fragment shader parameter
						static const String sKey = "Key";
						pFragmentShaderProgram->SetParameter1f(sKey, (Key > 0.0f) ? Key : 0.0f);
					}

					{ // Set the "WhiteLevel" fragment shader parameter
						static const String sWhiteLevel = "WhiteLevel";
						pFragmentShaderProgram->SetParameter1f(sWhiteLevel, (WhiteLevel > 0.0f) ? WhiteLevel : 0.0f);
					}

					// Set the "AverageLuminance" fragment shader parameter
					if (bAutomaticAverageLuminance) {
						static const String sAverageLuminanceTexture = "AverageLuminanceTexture";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sAverageLuminanceTexture, pHDRAverageLuminanceTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU,  TextureAddressing::Wrap);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV,  TextureAddressing::Wrap);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					} else {
						static const String sAverageLuminance = "AverageLuminance";
						pFragmentShaderProgram->SetParameter1f(sAverageLuminance, AverageLuminance);
					}
				}

				// Set bloom fragment shader parameters
				if (bBloom) {
					{ // Set the "BloomFactor" fragment shader parameter
						static const String sBloomFactor = "BloomFactor";
						pFragmentShaderProgram->SetParameter1f(sBloomFactor, BloomFactor);
					}

					{ // Set the "BloomDownscale" fragment shader parameter
						static const String sBloomDownscale = "BloomDownscale";
						pFragmentShaderProgram->SetParameter1f(sBloomDownscale, BloomDownscale);
					}

					{ // Set the "BloomTexture" fragment shader parameter
						static const String sBloomTexture = "BloomTexture";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sBloomTexture, m_pHDRBloom->GetTextureBuffer());
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}
				}

				// Set gamma correction fragment shader parameters
				if (bGammaCorrection) { 
					// Set the "InvGamma" fragment shader parameter
					static const String sInvGamma = "InvGamma";
					float fInvGamma = Gamma;
					if (fInvGamma > 0.0f)
						fInvGamma = 1.0f/fInvGamma;
					pFragmentShaderProgram->SetParameter1f(sInvGamma, (fInvGamma > FLT_MIN) ? fInvGamma : FLT_MIN);
				}

				{ // Set the "HDRTexture" fragment shader parameter
					static const String sHDRTexture = "HDRTexture";
					const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sHDRTexture, pHDRTextureBuffer);
					if (nStage >= 0) {
						cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}
				}

				// Create the fullscreen quad instance if required
				if (!m_pFullscreenQuad)
					m_pFullscreenQuad = new FullscreenQuad(cRenderer);

				// Draw the fullscreen quad
				m_pFullscreenQuad->Draw(pHDRTextureBuffer->GetSize());
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
