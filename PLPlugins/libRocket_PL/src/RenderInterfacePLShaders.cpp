/*********************************************************\
 *  File: RenderInterfacePLShaders.cpp                   *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include "libRocket_PL/RenderInterfacePLShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderInterfacePLShaders::RenderInterfacePLShaders(RendererContext &cRendererContext, uint32 nWindowWidth, uint32 nWindowHeight) : RenderInterfacePL(cRendererContext, nWindowWidth, nWindowHeight),
	m_pVertexShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr)
{
	// Get the used renderer
	Renderer &cRenderer = cRendererContext.GetRenderer();
	
	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
		// Create the shader instances
		m_pVertexShader   = pShaderLanguage->CreateVertexShader();
		m_pFragmentShader = pShaderLanguage->CreateFragmentShader();

		// Shader source code
		String sVertexShaderSourceCode;
		String sFragmentShaderSourceCode;
		if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
			#include "RenderInterfacePLShaders_GLSL.h"

			// Figure out the GLSL version to use
			if (cRenderer.GetAPI() == "OpenGL ES 2.0") {
				// Get shader source codes
				sVertexShaderSourceCode   = "#version 100\n" + sVertexShaderSourceCodeGLSL;
				sFragmentShaderSourceCode = "#version 100\n" + sFragmentShaderSourceCodeGLSL;
			} else {
				// Remove precision qualifiers so that we're able to use 110 (OpenGL 2.0 shaders) instead of 130 (OpenGL 3.0 shaders,
				// with this version we can keep the precision qualifiers) so that this shader requirements are as low as possible
				sVertexShaderSourceCode   = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sVertexShaderSourceCodeGLSL);
				sFragmentShaderSourceCode = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sFragmentShaderSourceCodeGLSL);
			}
		} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
			#include "RenderInterfacePLShaders_Cg.h"
			sVertexShaderSourceCode   = sVertexShaderSourceCodeCg;
			sFragmentShaderSourceCode = sFragmentShaderSourceCodeCg;
		}

		// Set the vertex shader source code
		if (m_pVertexShader)
			m_pVertexShader->SetSourceCode(sVertexShaderSourceCode, "arbvp1");

		// Set the fragment shader source code
		if (m_pFragmentShader)
			m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode, "arbfp1");

		// Create a program instance
		m_pProgram = pShaderLanguage->CreateProgram();
		if (m_pProgram) {
			// Assign the created vertex and fragment shaders to the program
			m_pProgram->SetVertexShader(m_pVertexShader);
			m_pProgram->SetFragmentShader(m_pFragmentShader);
		}
	}
}

/**
*  @brief
*    Destructor
*/
RenderInterfacePLShaders::~RenderInterfacePLShaders()
{
	// Cleanup
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pVertexShader)
		delete m_pVertexShader;
}


//[-------------------------------------------------------]
//[ Public virtual RenderInterfacePL functions            ]
//[-------------------------------------------------------]
bool RenderInterfacePLShaders::ConfigureRenderSystem()
{
	// Call base implementation
	if (RenderInterfacePL::ConfigureRenderSystem()) {
		// Get the used renderer
		Renderer &cRenderer = GetRendererContext().GetRenderer();

		// Make our program to the current one
		if (cRenderer.SetProgram(m_pProgram)) {
			// Set "WindowSizeInv" program uniform
			ProgramUniform *pProgramUniform = m_pProgram->GetUniform("WindowSizeInv");
			if (pProgramUniform) {
				const Rectangle &cRectangle = cRenderer.GetViewport();
				pProgramUniform->Set(cRectangle.GetWidth() ? 1.0f/cRectangle.GetWidth() : 1.0f, cRectangle.GetHeight() ? 1.0f/cRectangle.GetHeight() : 1.0f);

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual Rocket::Core::RenderInterface functions ]
//[-------------------------------------------------------]
void RenderInterfacePLShaders::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	// Get the used renderer
	Renderer &cRenderer = GetRendererContext().GetRenderer();

	// Get the compiled geometry instance
	RocketPLCompiledGeometry *pRocketPLCompiledGeometry = reinterpret_cast<RocketPLCompiledGeometry*>(geometry);

	// Set "Translation" program uniform
	ProgramUniform *pProgramUniform = m_pProgram->GetUniform("Translation");
	if (pProgramUniform)
		pProgramUniform->Set(translation.x, translation.y);

	// Set "TextureMap" program uniform
	pProgramUniform = m_pProgram->GetUniform("TextureMap");
	if (pProgramUniform) {
		// Get the texture
		Texture *pTexture = pRocketPLCompiledGeometry->pTextureHandler ? pRocketPLCompiledGeometry->pTextureHandler->GetResource() : nullptr;

		// Get the texture buffer
		TextureBuffer *pTextureBuffer = pTexture ? pTexture->GetTextureBuffer() : nullptr;

		// Set the texture buffer
		const int nTextureUnit = pProgramUniform->Set(pTextureBuffer);
		if (nTextureUnit >= 0) {
			cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::Linear);
		}
	}

	// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
	VertexBuffer *pVertexBuffer = pRocketPLCompiledGeometry->pVertexBuffer;
	ProgramAttribute *pProgramAttribute = m_pProgram->GetAttribute("VertexPosition");
	if (pProgramAttribute)
		pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
	pProgramAttribute = m_pProgram->GetAttribute("VertexTexCoord");
	if (pProgramAttribute)
		pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::TexCoord);
	pProgramAttribute = m_pProgram->GetAttribute("VertexColor");
	if (pProgramAttribute)
		pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Color);

	// Set the index buffer
	IndexBuffer *pIndexBuffer = pRocketPLCompiledGeometry->pIndexBuffer;
	cRenderer.SetIndexBuffer(pIndexBuffer);

	// Draw the index primitives
	cRenderer.DrawIndexedPrimitives(Primitive::TriangleList, 0, pVertexBuffer->GetNumOfElements() - 1, 0, pIndexBuffer->GetNumOfElements());
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
RenderInterfacePLShaders::RenderInterfacePLShaders(const RenderInterfacePLShaders &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
RenderInterfacePLShaders &RenderInterfacePLShaders::operator =(const RenderInterfacePLShaders &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL
