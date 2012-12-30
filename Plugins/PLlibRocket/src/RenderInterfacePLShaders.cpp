/*********************************************************\
 *  File: RenderInterfacePLShaders.cpp                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#include "PLlibRocket/RenderInterfacePLShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderInterfacePLShaders::RenderInterfacePLShaders(RendererContext &cRendererContext) : RenderInterfacePL(cRendererContext),
	m_pVertexShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr)
{
	// Get the used renderer
	Renderer &cRenderer = cRendererContext.GetRenderer();
	
	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
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

		// Create a vertex shader instance
		m_pVertexShader = pShaderLanguage->CreateVertexShader(sVertexShaderSourceCode, "arbvp1");

		// Create a fragment shader instance
		m_pFragmentShader = pShaderLanguage->CreateFragmentShader(sFragmentShaderSourceCode, "arbfp1");

		// Create a program instance and assign the created vertex and fragment shaders to it
		m_pProgram = pShaderLanguage->CreateProgram(m_pVertexShader, m_pFragmentShader);
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
} // PLlibRocket
