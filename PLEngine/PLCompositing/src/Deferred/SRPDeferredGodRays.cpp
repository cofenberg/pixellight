/*********************************************************\
 *  File: SRPDeferredGodRays.cpp                         *
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
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredGodRays.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredGodRays)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredGodRays::SRPDeferredGodRays() :
	NumerOfSamples(this),
	Density(this),
	Weight(this),
	Decay(this),
	LightPosition(this),
	Color(this),
	Flags(this)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGodRays::~SRPDeferredGodRays()
{
	// Destroy all used shaders
	DestroyShaders();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader
*/
Shader *SRPDeferredGodRays::GetFragmentShader(Renderer &cRenderer, bool bDiscard)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bDiscard];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bDiscard]) {
		const static String ShaderFilename = "Fragment/SRPDeferredGodRays.cg";

		// [TODO] Currently, "discard" produces pixel chaos using glslf, but we really need glslf because we're using real loops...
		bDiscard = false;

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bDiscard) {
			sDefines += "#define DISCARD\n";
			sName    += "[Discard]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredGodRays_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGodRays_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGodRays_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bDiscard] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredGodRays::DestroyShaders()
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
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredGodRays::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Skip black god rays, they have no visible incluence!
	if (Color.Get() != Color3::Black && NumerOfSamples != 0) {
		// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass and check whether or not color target 3 has real information in it
		SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
		if (pSRPDeferredGBuffer && pSRPDeferredGBuffer->IsColorTarget3Used()) {
			// Get the fullscreen quad instance
			FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
			if (pFullscreenQuad) {
				// Get the texture buffer to use
				TextureBufferRectangle *pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
				if (pTextureBuffer) {
					// Reset all render states to default
					cRenderer.GetRendererContext().GetEffectManager().Use();

					// Get and set the fragment shader
					Shader *pFragmentShader = GetFragmentShader(cRenderer, !(GetFlags() & NoDiscard));
					if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
						// Get and set the fragment shader program
						ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
						cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

						{ // Set the "NumerOfSamples" fragment shader parameter
							static const String sNumerOfSamples = "NumerOfSamples";
							pFragmentShaderProgram->SetParameter1i(sNumerOfSamples, (NumerOfSamples > 0) ? NumerOfSamples : 1);
						}

						{ // Set the "Density" fragment shader parameter
							static const String sDensity = "Density";
							pFragmentShaderProgram->SetParameter1f(sDensity, (Density > FLT_MIN) ? Density : FLT_MIN);
						}

						{ // Set the "Weight" fragment shader parameter
							static const String sWeight = "Weight";
							pFragmentShaderProgram->SetParameter1f(sWeight, Weight);
						}

						{ // Set the "Decay" fragment shader parameter
							static const String sDecay = "Decay";
							pFragmentShaderProgram->SetParameter1f(sDecay, Decay);
						}

						{ // Set the "LightPosition" fragment shader parameter
							static const String sLightPosition = "LightPosition";
							pFragmentShaderProgram->SetParameter2f(sLightPosition, LightPosition.Get().x*pTextureBuffer->GetSize().x, LightPosition.Get().y*pTextureBuffer->GetSize().y);
						}

						{ // Set the "Color" fragment shader parameter
							static const String sColor = "Color";
							pFragmentShaderProgram->SetParameter3fv(sColor, Color.Get());
						}

						{ // Set the "Texture" fragment shader parameter
							static const String sTexture = "Texture";
							const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pTextureBuffer);
							if (nStage >= 0) {
								cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
								cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
								cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
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
