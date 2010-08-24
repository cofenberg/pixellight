/*********************************************************\
 *  File: SRPDeferredEdgeAA.cpp                          *
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
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include <PLScene/Compositing/General/SRPBegin.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredEdgeAA.h"


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
pl_implement_class(SRPDeferredEdgeAA)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredEdgeAA::SRPDeferredEdgeAA() :
	WeightScale(this),
	Flags(this)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredEdgeAA::~SRPDeferredEdgeAA()
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
Shader *SRPDeferredEdgeAA::GetFragmentShader(Renderer &cRenderer, bool bMoreSamples, bool bShowEdges, bool bShowEdgesOnly)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bMoreSamples][bShowEdges][bShowEdgesOnly];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bMoreSamples][bShowEdges][bShowEdgesOnly]) {
		const static String ShaderFilename = "Fragment/SRPDeferredEdgeAA.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bMoreSamples) {
			sDefines += "#define MORE_SAMPLES\n";
			sName    += "[MoreSamples]";
		}
		if (bShowEdges) {
			sDefines += "#define SHOW_EDGES\n";
			sName    += "[ShowEdges]";
		}
		if (bShowEdgesOnly) {
			sDefines += "#define SHOW_EDGESONLY\n";
			sName    += "[ShowEdgesOnly]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredEdgeAA_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredEdgeAA_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredEdgeAA_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bMoreSamples][bShowEdges][bShowEdgesOnly] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredEdgeAA::DestroyShaders()
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
void SRPDeferredEdgeAA::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
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

						// Get and set the fragment shader
						Shader *pFragmentShader = GetFragmentShader(cRenderer, (GetFlags() & MoreSamples) != 0, (GetFlags() & ShowEdges) || (GetFlags() & ShowEdgesOnly), (GetFlags() & ShowEdgesOnly) != 0);
						if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
							// Get and set the fragment shader program
							ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
							cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

							{ // Set the "MinGradient" fragment shader parameter
								static const String sMinGradient = "MinGradient";
								pFragmentShaderProgram->SetParameter1f(sMinGradient, (pNormalDepthTextureBuffer->GetFormat() == TextureBuffer::R32G32B32A32F) ? 0.00001f : 0.001f);
							}

							{ // Set the "WeightScale" fragment shader parameter
								static const String sWeightScale = "WeightScale";
								pFragmentShaderProgram->SetParameter1f(sWeightScale, WeightScale);
							}

							// Set the "EdgeColor" fragment shader parameter
							if ((GetFlags() & ShowEdges) || (GetFlags() & ShowEdgesOnly)) {
								static const String sEdgeColor = "EdgeColor";
								pFragmentShaderProgram->SetParameter3fv(sEdgeColor, (GetFlags() & ShowEdgesOnly) ? Color3::White : Color3::Red);
							}

							{ // Set the "FrontTexture" fragment shader parameter
								static const String sFrontTexture = "FrontTexture";
								const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sFrontTexture, pFrontSurfaceTextureBuffer->GetTextureBuffer());
								if (nStage >= 0) {
									cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
									cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
									cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
								}
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

							// Draw the fullscreen quad
							pFullscreenQuad->Draw(pNormalDepthTextureBuffer->GetSize());
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
