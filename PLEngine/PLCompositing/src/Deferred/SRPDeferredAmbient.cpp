/*********************************************************\
 *  File: SRPDeferredAmbient.cpp                         *
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
#include "PLCompositing/Deferred/SRPDeferredAmbient.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredAmbient)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredAmbient::SRPDeferredAmbient() :
	AmbientColor(this),
	Flags(this)
{
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredAmbient::~SRPDeferredAmbient()
{
	// Destroy all used shaders
	DestroyShaders();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader for the requested visualisation mode
*/
Shader *SRPDeferredAmbient::GetFragmentShader(Renderer &cRenderer, bool bAlbedo, bool bAmbientOcclusion, bool bSelfIllumination)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bAlbedo][bAmbientOcclusion][bSelfIllumination];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bAlbedo][bAmbientOcclusion][bSelfIllumination]) {
		const static String ShaderFilename = "Fragment/SRPDeferredAmbient.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bAlbedo) {
			sDefines += "#define ALBEDO\n";
			sName    += "[Albedo]";
		}
		if (bAmbientOcclusion) {
			sDefines += "#define AMBIENTOCCLUSION\n";
			sName    += "[AmbientOcclusion]";
		}
		if (bSelfIllumination) {
			sDefines += "#define SELFILLUMINATION\n";
			sName    += "[SelfIllumination]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredAmbient_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredAmbient_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredAmbient_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bAlbedo][bAmbientOcclusion][bSelfIllumination] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredAmbient::DestroyShaders()
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
void SRPDeferredAmbient::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
	SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
	if (pSRPDeferredGBuffer) {
		// Get the fullscreen quad instance
		FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
		if (pFullscreenQuad) {
			// Get the texture buffer to use
			TextureBufferRectangle *pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0);
			if (pTextureBuffer) {
				// Reset all render states to default
				cRenderer.GetRendererContext().GetEffectManager().Use();

				// Use stencil buffer?
				if (!(GetFlags() & NoStencil)) {
					// Enable stencil test - ignore pixels tagged with 1 within the stencil buffer
					cRenderer.SetRenderState(RenderState::StencilEnable, true);
					cRenderer.SetRenderState(RenderState::StencilRef,    1);
					cRenderer.SetRenderState(RenderState::StencilFunc,   Compare::NotEqual);
				}

				// Self illumination used?
				const bool bSelfIllumination = pSRPDeferredGBuffer->IsColorTarget3Used() && !(GetFlags() & NoSelfIllumination);

				// Get and set the fragment shader
				Shader *pFragmentShader = GetFragmentShader(cRenderer, !(GetFlags() & NoAlbedo), !(GetFlags() & NoAmbientOcclusion), bSelfIllumination);
				if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
					// Get and set the fragment shader program
					ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
					cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

					{ // Set the "AmbientColor" fragment shader parameter
						static const String sAmbientColor = "AmbientColor";
						pFragmentShaderProgram->SetParameter3fv(sAmbientColor, AmbientColor.Get());
					}

					 // Set the "AlbedoTexture" fragment shader parameter
					if (!(GetFlags() & NoAlbedo) || !(GetFlags() & NoAmbientOcclusion)) {
						static const String sAlbedoTexture = "AlbedoTexture";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sAlbedoTexture, pTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}

					// Set the "SelfIlluminationTexture" fragment shader parameter
					if (bSelfIllumination) {
						static const String sSelfIlluminationTexture = "SelfIlluminationTexture";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sSelfIlluminationTexture, pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3));
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}

					// Draw the fullscreen quad
					pFullscreenQuad->Draw(pTextureBuffer->GetSize());
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
