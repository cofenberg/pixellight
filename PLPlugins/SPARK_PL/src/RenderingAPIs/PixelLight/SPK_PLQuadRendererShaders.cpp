/*********************************************************\
 *  File: SPK_PLQuadRendererShaders.cpp                  *
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
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLQuadRendererShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLQuadRendererShaders *SPK_PLQuadRendererShaders::Create(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage, float fScaleX, float fScaleY)
{
	SPK_PLQuadRendererShaders *pSPK_PLQuadRendererShaders = new SPK_PLQuadRendererShaders(cRenderer, sShaderLanguage, fScaleX, fScaleY);
	registerObject(pSPK_PLQuadRendererShaders);
	return pSPK_PLQuadRendererShaders;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of SPK_PLQuadRendererShaders
*/
SPK_PLQuadRendererShaders::SPK_PLQuadRendererShaders(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage, float fScaleX, float fScaleY) : SPK_PLQuadRenderer(cRenderer, fScaleX, fScaleY),
	m_pEventHandlerDirty(new PLCore::EventHandler<PLRenderer::Program*>(&SPK_PLQuadRendererShaders::OnDirty, this)),
	m_sShaderLanguage(sShaderLanguage),
	m_pVertexShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr),
	m_pPositionProgramAttribute(nullptr),
	m_pTexCoordProgramAttribute(nullptr),
	m_pColorProgramAttribute(nullptr),
	m_pObjectSpaceToClipSpaceMatrixProgramUniform(nullptr),
	m_pTextureMapProgramUniform(nullptr)
{
	// Get the shader language to use
	if (!m_sShaderLanguage.GetLength())
		m_sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

	// Create the GPU program right now?
	if (!m_pProgram || m_pProgram->GetShaderLanguage() != m_sShaderLanguage) {
		// If there's an previous instance of the program, destroy it first
		if (m_pProgram) {
			delete m_pProgram;
			m_pProgram = nullptr;
		}
		if (m_pFragmentShader) {
			delete m_pFragmentShader;
			m_pFragmentShader = nullptr;
		}
		if (m_pVertexShader) {
			delete m_pVertexShader;
			m_pVertexShader = nullptr;
		}
		m_pPositionProgramAttribute						= nullptr;
		m_pTexCoordProgramAttribute						= nullptr;
		m_pColorProgramAttribute						= nullptr;
		m_pObjectSpaceToClipSpaceMatrixProgramUniform	= nullptr;
		m_pTextureMapProgramUniform						= nullptr;

		// Get the shader language instance
		PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(m_sShaderLanguage);
		if (pShaderLanguage) {
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (m_sShaderLanguage == "GLSL") {
				#include "SPK_PLQuadRendererShaders_GLSL.h"
				if (cRenderer.GetAPI() == "OpenGL ES 2.0") {
					// Get shader source codes
					sVertexShaderSourceCode   = "#version 100\n" + sSPK_PLQuadRendererShaders_GLSL_VS;
					sFragmentShaderSourceCode = "#version 100\n" + sSPK_PLQuadRendererShaders_GLSL_FS;
				} else {
					// Remove precision qualifiers so that we're able to use 110 (OpenGL 2.0 shaders) instead of 130 (OpenGL 3.0 shaders,
					// with this version we can keep the precision qualifiers) so that this shader requirements are as low as possible
					sVertexShaderSourceCode   = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sSPK_PLQuadRendererShaders_GLSL_VS);
					sFragmentShaderSourceCode = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sSPK_PLQuadRendererShaders_GLSL_FS);
				}
			} else if (m_sShaderLanguage == "Cg") {
				#include "SPK_PLQuadRendererShaders_Cg.h"
				sVertexShaderSourceCode   = sSPK_PLQuadRendererShaders_Cg_VS;
				sFragmentShaderSourceCode = sSPK_PLQuadRendererShaders_Cg_FS;
			}

			// Create a vertex shader instance
			m_pVertexShader = pShaderLanguage->CreateVertexShader();
			if (m_pVertexShader) {
				// Set the vertex shader source code
				m_pVertexShader->SetSourceCode(sVertexShaderSourceCode, "arbvp1");
			}

			// Create a fragment shader instance
			m_pFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pFragmentShader) {
				// Set the fragment shader source code
				m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode, "arbfp1");
			}

			// Create a program instance
			m_pProgram = pShaderLanguage->CreateProgram();
			if (m_pProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pProgram->SetVertexShader(m_pVertexShader);
				m_pProgram->SetFragmentShader(m_pFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pProgram->EventDirty.Connect(m_pEventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pProgram);
			}
		}
	}
}

/**
*  @brief
*    Destructor of SPK_PLQuadRendererShaders
*/
SPK_PLQuadRendererShaders::~SPK_PLQuadRendererShaders()
{
	// Destroy shaders
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pVertexShader)
		delete m_pVertexShader;

	// Destroy the event handler
	delete m_pEventHandlerDirty;
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLQuadRendererShaders::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Update the vertex buffer
		UpdateVertexBuffer(group);

		// Setup render states
		InitBlending();
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));

		/*
			// [TODO] Alpha test
			if (isRenderingHintEnabled(SPK::ALPHA_TEST)) {
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestEnable,    true);
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestFunction,  Compare::GreaterEqual);
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestReference, Tools::FloatToUInt32(getAlphaTestThreshold()));
			} else {
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestEnable, false);
			}
			*/

		// Make our program to the current one
		if (GetPLRenderer().SetProgram(m_pProgram)) {
			// Set the "ObjectSpaceToClipSpaceMatrix" fragment shader parameter
			if (m_pObjectSpaceToClipSpaceMatrixProgramUniform)
				m_pObjectSpaceToClipSpaceMatrixProgramUniform->Set(m_mWorldViewProjection);

			// Set "TextureMap" program uniform
			if (m_pTextureMapProgramUniform) {
				Texture *pTexture = m_pTextureHandler->GetTexture();
				if (pTexture && pTexture->GetTextureBuffer()) {
					const int nTextureUnit = m_pTextureMapProgramUniform->Set(pTexture->GetTextureBuffer());
					if (nTextureUnit >= 0) {
						GetPLRenderer().SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Wrap);
						GetPLRenderer().SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Wrap);
						GetPLRenderer().SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
						GetPLRenderer().SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
						GetPLRenderer().SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::Linear);
					}
				}
			}

			// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
			VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
			if (m_pPositionProgramAttribute)
				m_pPositionProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
			if (m_pTexCoordProgramAttribute)
				m_pTexCoordProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::TexCoord);
			if (m_pColorProgramAttribute)
				m_pColorProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Color);

			// Make the index buffer to the current renderer index buffer
			IndexBuffer *pIndexBuffer = m_pSPK_PLBuffer->GetIndexBuffer();
			if (pIndexBuffer)
				GetPLRenderer().SetIndexBuffer(pIndexBuffer);

			// Draw
			GetPLRenderer().DrawIndexedPrimitives(Primitive::TriangleList, 0, group.getNbParticles()*NumOfVerticesPerParticle-1, 0, group.getNbParticles()*NumOfIndicesPerParticle);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a program became dirty
*/
void SPK_PLQuadRendererShaders::OnDirty(Program *pProgram)
{
	// Get attributes and uniforms
	if (pProgram == m_pProgram) {
		m_pPositionProgramAttribute						= m_pProgram->GetAttribute("VertexPosition");
		m_pTexCoordProgramAttribute						= m_pProgram->GetAttribute("VertexTexCoord");
		m_pColorProgramAttribute						= m_pProgram->GetAttribute("VertexColor");
		m_pObjectSpaceToClipSpaceMatrixProgramUniform	= m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
		m_pTextureMapProgramUniform						= m_pProgram->GetUniform("TextureMap");
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
