/*********************************************************\
 *  File: SRPDeferredDepthFog.cpp                        *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SNCamera.h>
#include "PLCompositing/FullscreenQuad.h"
#include "PLCompositing/Shaders/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Shaders/Deferred/SRPDeferredDepthFog.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
	ShaderLanguage(this),
	FogColor(this),
	FogMode(this),
	FogStart(this),
	FogEnd(this),
	FogDensity(this),
	Flags(this),
	m_pProgramGenerator(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferredDepthFog::~SRPDeferredDepthFog()
{
	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
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
			// Get the vertex buffer of the fullscreen quad
			VertexBuffer *pVertexBuffer = pFullscreenQuad->GetVertexBuffer();
			if (pVertexBuffer) {
				// Get the normal/depth texture buffer to use
				TextureBufferRectangle *pNormalDepthTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
				if (pNormalDepthTextureBuffer) {
					// Get the shader language to use
					String sShaderLanguage = ShaderLanguage;
					if (!sShaderLanguage.GetLength())
						sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

					// Create the program generator if there's currently no instance of it
					if (!m_pProgramGenerator || m_pProgramGenerator->GetShaderLanguage() != sShaderLanguage) {
						// If there's an previous instance of the program generator, destroy it first
						if (m_pProgramGenerator) {
							delete m_pProgramGenerator;
							m_pProgramGenerator = nullptr;
						}

						// Choose the shader source codes depending on the requested shader language
						if (sShaderLanguage == "GLSL") {
							#include "SRPDeferredDepthFog_GLSL.h"
							m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredDepthFog_GLSL_VS, "110", sDeferredDepthFog_GLSL_FS, "110");	// OpenGL 2.0 ("#version 110")
						} else if (sShaderLanguage == "Cg") {
							#include "SRPDeferredDepthFog_Cg.h"
							m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredDepthFog_Cg_VS, "arbvp1", sDeferredDepthFog_Cg_FS, "arbfp1");
						}
					}

					// If there's no program generator, we don't need to continue
					if (m_pProgramGenerator) {
						// Reset all render states to default
						cRenderer.GetRendererContext().GetEffectManager().Use();

						// Reset the program flags
						m_cProgramFlags.Reset();

						// Set program flags
						switch (FogMode) {
							case LinearMode:
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_LINEAR_MODE)
								break;

							case ExponentialMode:
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_EXPONENTIAL_MODE)
								break;

							case Exponential2Mode:
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_EXPONENTIAL2_MODE)
								break;
						}

						// Get a program instance from the program generator using the given program flags
						ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);

						// Make our program to the current one
						if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
							// Set pointers to uniforms & attributes of a generated program if they are not set yet
							GeneratedProgramUserData *pGeneratedProgramUserData = static_cast<GeneratedProgramUserData*>(pGeneratedProgram->pUserData);
							if (!pGeneratedProgramUserData) {
								pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
								Program *pProgram = pGeneratedProgram->pProgram;
								// Vertex shader attributes
								static const String sVertexPosition = "VertexPosition";
								pGeneratedProgramUserData->pVertexPosition	= pProgram->GetAttribute(sVertexPosition);
								// Vertex shader uniforms
								static const String sTextureSize = "TextureSize";
								pGeneratedProgramUserData->pTextureSize		= pProgram->GetUniform(sTextureSize);
								// Fragment shader uniforms
								static const String sFarPlane = "FarPlane";
								pGeneratedProgramUserData->pFarPlane		= pProgram->GetUniform(sFarPlane);
								static const String sFogColor = "FogColor";
								pGeneratedProgramUserData->pFogColor		= pProgram->GetUniform(sFogColor);
								static const String sFogEnd = "FogEnd";
								pGeneratedProgramUserData->pFogEnd			= pProgram->GetUniform(sFogEnd);
								static const String sFogRange = "FogRange";
								pGeneratedProgramUserData->pFogRange		= pProgram->GetUniform(sFogRange);
								static const String sFogDensity = "FogDensity";
								pGeneratedProgramUserData->pFogDensity		= pProgram->GetUniform(sFogDensity);
								static const String sNormalDepthMap = "NormalDepthMap";
								pGeneratedProgramUserData->pNormalDepthMap	= pProgram->GetUniform(sNormalDepthMap);
							}

							// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
							if (pGeneratedProgramUserData->pVertexPosition)
								pGeneratedProgramUserData->pVertexPosition->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);

							// Set texture size
							if (pGeneratedProgramUserData->pTextureSize)
								pGeneratedProgramUserData->pTextureSize->Set(pNormalDepthTextureBuffer->GetSize());

							// Set the far plane parameter and ensure that the parameter is never ever 0
							if (pGeneratedProgramUserData->pFarPlane) {
								float fFarPlane = SNCamera::GetCamera() ? SNCamera::GetCamera()->ZFar : FLT_MIN;
								if (fFarPlane < FLT_MIN)
									fFarPlane = FLT_MIN;
								pGeneratedProgramUserData->pFarPlane->Set(fFarPlane);
							}

							// Fog color
							if (pGeneratedProgramUserData->pFogColor)
								pGeneratedProgramUserData->pFogColor->Set(FogColor.Get());

							// Fog end
							if (pGeneratedProgramUserData->pFogEnd)
								pGeneratedProgramUserData->pFogEnd->Set(FogEnd);

							// Fog range
							if (pGeneratedProgramUserData->pFogRange) {
								const float fFogRange = FogEnd - FogStart;
								pGeneratedProgramUserData->pFogRange->Set((fFogRange > FLT_MIN) ? fFogRange : FLT_MIN);
							}

							// Fog density
							if (pGeneratedProgramUserData->pFogDensity)
								pGeneratedProgramUserData->pFogDensity->Set(FogDensity);

							// Normal depth map
							if (pGeneratedProgramUserData->pNormalDepthMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pNormalDepthMap->Set(pNormalDepthTextureBuffer);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
								}
							}

							// Draw the fullscreen quad
							cRenderer.SetRenderState(RenderState::ScissorTestEnable, false);
							if (!(GetFlags() & DisableBlending)) {
								// Set blend mode
								cRenderer.SetRenderState(RenderState::BlendEnable,	true);
								cRenderer.SetRenderState(RenderState::SrcBlendFunc,	BlendFunc::One);
								cRenderer.SetRenderState(RenderState::DstBlendFunc,	BlendFunc::InvSrcAlpha);
							}
							pFullscreenQuad->Draw(true);
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
