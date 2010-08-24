/*********************************************************\
 *  File: SRPDeferredGBufferDebug.cpp                    *
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
#include "PLCompositing/Deferred/SRPDeferredGBufferDebug.h"


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
pl_implement_class(SRPDeferredGBufferDebug)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredGBufferDebug::SRPDeferredGBufferDebug() :
	Mode(this)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGBufferDebug::~SRPDeferredGBufferDebug()
{
	// Destroy all used shaders
	DestroyShaders();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader for the requested debug mode
*/
Shader *SRPDeferredGBufferDebug::GetFragmentShader(Renderer &cRenderer, bool bBlack)
{
	// Get the mode
	const uint32 nMode = bBlack ? UnknownMode : Mode;

	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[nMode];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[nMode]) {
		const static String ShaderFilename = "Fragment/SRPDeferredGBufferDebug.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bBlack) {
			sDefines += "#define SHOW_BLACK\n";
			sName    += "[ShowBlack]";
		} else {
			switch (Mode) {
				case ShowAlbedo:
					sDefines += "#define SHOW_ALBEDO\n";
					sName    += "[ShowAlbedo]";
					break;

				case ShowAmbientOcclusion:
					sDefines += "#define SHOW_AMBIENTOCCLUSION\n";
					sName    += "[ShowAmbientOcclusion]";
					break;

				case ShowNormals:
					sDefines += "#define SHOW_NORMALS\n";
					sName    += "[ShowNormals]";
					break;

				case ShowDepth:
					sDefines += "#define SHOW_DEPTH\n";
					sName    += "[ShowDepth]";
					break;

				case ShowSpecularColor:
					sDefines += "#define SHOW_SPECULAR_COLOR\n";
					sName    += "[ShowSpecularColor]";
					break;

				case ShowSpecularExponent:
					sDefines += "#define SHOW_SPECULAR_EXPONENT\n";
					sName    += "[ShowSpecularExponent]";
					break;

				case ShowSelfIllumination:
					sDefines += "#define SHOW_SELFILLUMINATION\n";
					sName    += "[ShowSelfIllumination]";
					break;

				case ShowGlow:
					sDefines += "#define SHOW_GLOW\n";
					sName    += "[ShowGlow]";
					break;
			}
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredGBufferDebug_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredGBufferDebug_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredGBufferDebug_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines);
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[nMode] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredGBufferDebug::DestroyShaders()
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
void SRPDeferredGBufferDebug::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
	SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
	if (pSRPDeferredGBuffer) {
		// Get the fullscreen quad instance
		FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
		if (pFullscreenQuad) {
			// Get the texture buffer to use
			TextureBufferRectangle *pTextureBuffer = NULL;
			switch (Mode) {
				case ShowAlbedo:
					// RGB components of RT0
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0);
					break;

				case ShowAmbientOcclusion:
					// A component of RT0
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0);
					break;

				case ShowNormals:
					// RG components of RT1
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
					break;

				case ShowDepth:
					// B component of RT1
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
					break;

				case ShowSpecularColor:
					// RGB components of RT2
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(2);
					break;

				case ShowSpecularExponent:
					// A component of RT2
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(2);
					break;

				case ShowSelfIllumination:
					// RGB components of RT3
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
					break;

				case ShowGlow:
					// A component of RT3
					pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
					break;
			}

			// Reset all render states to default
			cRenderer.GetRendererContext().GetEffectManager().Use();

			// Get and set the fragment shader
			Shader *pFragmentShader = GetFragmentShader(cRenderer, (pTextureBuffer == NULL));
			if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
				// Get and set the fragment shader program
				ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
				cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

				{ // Set the "CameraNarPlane" fragment shader parameter
					static const String sCameraNarPlane = "CameraNarPlane";
					pFragmentShaderProgram->SetParameter1f(sCameraNarPlane, SNCamera::GetCamera() ? SNCamera::GetCamera()->ZNear : 0.1f);
				}

				{ // Set the "CameraRange" fragment shader parameter and ensure that the parameter is never ever 0
					static const String sCameraRange = "CameraRange";
					float fCameraRange = SNCamera::GetCamera() ? (SNCamera::GetCamera()->ZFar - SNCamera::GetCamera()->ZNear) : FLT_MIN;
					if (fCameraRange < FLT_MIN)
						fCameraRange = FLT_MIN;
					pFragmentShaderProgram->SetParameter1f(sCameraRange, fCameraRange);
				}

				// Set texture buffer
				if (pTextureBuffer) {
					static const String sTexture = "Texture";
					const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sTexture, pTextureBuffer);
					if (nStage >= 0) {
						cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
						cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
						cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
					}

					// Draw the fullscreen quad
					pFullscreenQuad->Draw(pTextureBuffer->GetSize());
				} else {
					// Draw the fullscreen quad
					pFullscreenQuad->Draw(PLMath::Vector2i::Zero);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
