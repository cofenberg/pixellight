/*********************************************************\
 *  File: SRPDeferredGBufferDebug.cpp                    *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLCompositing/Shaders/Deferred/SRPDeferredGBufferDebug.h"


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
	ShaderLanguage(this),
	Mode(this),
	m_pProgramGenerator(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferredGBufferDebug::~SRPDeferredGBufferDebug()
{
	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
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
			// Get the vertex buffer of the fullscreen quad
			VertexBuffer *pVertexBuffer = pFullscreenQuad->GetVertexBuffer();
			if (pVertexBuffer) {
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
					String sDeferredGBufferDebug_VS;
					String sDeferredGBufferDebug_FS;
					if (sShaderLanguage == "GLSL") {
						#include "SRPDeferredGBufferDebug_GLSL.h"
						sDeferredGBufferDebug_VS = sDeferredGBufferDebug_GLSL_VS;
						sDeferredGBufferDebug_FS = sDeferredGBufferDebug_GLSL_FS;
					} else if (sShaderLanguage == "Cg") {
						#include "SRPDeferredGBufferDebug_Cg.h"
						sDeferredGBufferDebug_VS = sDeferredGBufferDebug_Cg_VS;
						sDeferredGBufferDebug_FS = sDeferredGBufferDebug_Cg_FS;
					}

					// Create the program generator
					if (sDeferredGBufferDebug_VS.GetLength() && sDeferredGBufferDebug_FS.GetLength())
						m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredGBufferDebug_VS, "arbvp1", sDeferredGBufferDebug_FS, "arbfp1", true);
				}

				// If there's no program generator, we don't need to continue
				if (m_pProgramGenerator) {
					// Reset the program flags
					m_cProgramFlags.Reset();

					// Get the texture buffer to use and the program flags
					TextureBufferRectangle *pTextureBuffer = nullptr;
					switch (Mode) {
						case ShowAlbedo:
							// RGB components of RT0
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_ALBEDO)
							break;

						case ShowAmbientOcclusion:
							// A component of RT0
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(0);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_AMBIENTOCCLUSION)
							break;

						case ShowNormals:
							// RG components of RT1
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_NORMALS)
							break;

						case ShowDepth:
							// B component of RT1
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_DEPTH)
							break;

						case ShowSpecularColor:
							// RGB components of RT2
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(2);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_SPECULAR_COLOR)
							break;

						case ShowSpecularExponent:
							// A component of RT2
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(2);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_SPECULAR_EXPONENT)
							break;

						case ShowSelfIllumination:
							// RGB components of RT3
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_SELFILLUMINATION)
							break;

						case ShowGlow:
							// A component of RT3
							pTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(3);
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_GLOW)
							break;

						default:
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHOW_BLACK)
							break;
					}

					// Reset all render states to default
					cRenderer.GetRendererContext().GetEffectManager().Use();

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
							static const String sNearPlane = "NearPlane";
							pGeneratedProgramUserData->pNearPlane		= pProgram->GetUniform(sNearPlane);
							static const String sRange = "Range";
							pGeneratedProgramUserData->pRange			= pProgram->GetUniform(sRange);
							static const String sMap = "Map";
							pGeneratedProgramUserData->pMap				= pProgram->GetUniform(sMap);
						}

						// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
						if (pGeneratedProgramUserData->pVertexPosition)
							pGeneratedProgramUserData->pVertexPosition->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);

						// Set texture size
						if (pGeneratedProgramUserData->pTextureSize)
							pGeneratedProgramUserData->pTextureSize->Set(pTextureBuffer ? pTextureBuffer->GetSize() : PLMath::Vector2i::Zero);

						// Near plane
						if (pGeneratedProgramUserData->pNearPlane)
							pGeneratedProgramUserData->pNearPlane->Set(SNCamera::GetCamera() ? SNCamera::GetCamera()->ZNear : 0.1f);

						// Set the range parameter and ensure that the parameter is never ever 0
						if (pGeneratedProgramUserData->pRange) {
							float fRange = SNCamera::GetCamera() ? (SNCamera::GetCamera()->ZFar - SNCamera::GetCamera()->ZNear) : FLT_MIN;
							if (fRange < FLT_MIN)
								fRange = FLT_MIN;
							pGeneratedProgramUserData->pRange->Set(fRange);
						}

						// Map
						if (pGeneratedProgramUserData->pMap) {
							const int nTextureUnit = pGeneratedProgramUserData->pMap->Set(pTextureBuffer);
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
						pFullscreenQuad->Draw();
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
