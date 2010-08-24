/*********************************************************\
 *  File: SRPDeferredDepthFog.cpp                        *
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
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredDepthFog.h"


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
pl_implement_class(SRPDeferredDepthFog)


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredDepthFog::SRPDeferredDepthFog() :
	FogColor(this),
	FogMode(this),
	FogStart(this),
	FogEnd(this),
	FogDensity(this),
	Flags(this)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredDepthFog::~SRPDeferredDepthFog()
{
	// Destroy all used shaders
	DestroyShaders();
}

/**
*  @brief
*    Returns the fragment shader
*/
Shader *SRPDeferredDepthFog::GetFragmentShader(Renderer &cRenderer)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[FogMode];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[FogMode]) {
		const static String ShaderFilename = "Fragment/SRPDeferredDepthFog.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		switch (FogMode) {
			case LinearMode:
				sDefines += "#define LINEAR_MODE\n";
				sName    += "[LinearMode]";
				break;

			case ExponentialMode:
				sDefines += "#define EXPONENTIAL_MODE\n";
				sName    += "[ExponentialMode]";
				break;

			case Exponential2Mode:
				sDefines += "#define EXPONENTIAL2_MODE\n";
				sName    += "[Exponential2Mode]";
				break;

			default:
				return NULL; // Error!
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredDepthFog_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredDepthFog_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredDepthFog_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[FogMode] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredDepthFog::DestroyShaders()
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
void SRPDeferredDepthFog::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
	SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
	if (pSRPDeferredGBuffer) {
		// Get the fullscreen quad instance
		FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
		if (pFullscreenQuad) {
			// Get the normal/depth texture buffer to use
			TextureBufferRectangle *pNormalDepthTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
			if (pNormalDepthTextureBuffer) {
				// Reset all render states to default
				cRenderer.GetRendererContext().GetEffectManager().Use();

				// Get and set the fragment shader
				Shader *pFragmentShader = GetFragmentShader(cRenderer);
				if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
					// Get and set the fragment shader program
					ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
					cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

					{ // Set the "FarPlane" fragment shader parameter and ensure that the parameter is never ever 0
						static const String sFarPlane = "FarPlane";
						float fFarPlane = SNCamera::GetCamera() ? SNCamera::GetCamera()->ZFar : FLT_MIN;
						if (fFarPlane < FLT_MIN)
							fFarPlane = FLT_MIN;
						pFragmentShaderProgram->SetParameter1f(sFarPlane, fFarPlane);
					}

					{ // Set the "FogColor" fragment shader parameter
						static const String sFogColor = "FogColor";
						pFragmentShaderProgram->SetParameter4fv(sFogColor, FogColor.Get());
					}

					// Fog mode dependent parameters
					if (FogMode == LinearMode) {
						// Set the "FogStart" and "FogEnd" fragment shader parameter
						static const String sFogEnd = "FogEnd";
						pFragmentShaderProgram->SetParameter1f(sFogEnd, FogEnd);
						static const String sFogRange = "FogRange";
						const float fFogRange = FogEnd - FogStart;
						pFragmentShaderProgram->SetParameter1f(sFogRange, (fFogRange > FLT_MIN) ? fFogRange : FLT_MIN);
					} else {
						// Set the "FogDensity" fragment shader parameter
						static const String sFogDensity = "FogDensity";
						pFragmentShaderProgram->SetParameter1f(sFogDensity, FogDensity);
					}

					{ // Set the "NormalDepthTexture" fragment shader parameter
						static const String sNormalDepthTexture = "NormalDepthTexture";
						const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sNormalDepthTexture, pNormalDepthTextureBuffer);
						if (nStage >= 0) {
							cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
							cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
							cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
						}
					}

					// Set blend mode
					if (!(GetFlags() & DisableBlending)) {
						cRenderer.SetRenderState(RenderState::BlendEnable,	true);
						cRenderer.SetRenderState(RenderState::SrcBlendFunc,	BlendFunc::One);
						cRenderer.SetRenderState(RenderState::DstBlendFunc,	BlendFunc::InvSrcAlpha);
					}

					// Draw the fullscreen quad
					pFullscreenQuad->Draw(pNormalDepthTextureBuffer->GetSize());
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
