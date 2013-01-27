/*********************************************************\
 *  File: FontManager.cpp                                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <ft2build.h>
#include FT_FREETYPE_H
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/FontTexture.h"
#include "PLRendererOpenGLES2/FontManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
FontManager::FontManager(PLRenderer::Renderer &cRenderer) : PLRenderer::FontManagerBackend(cRenderer),
	m_pFTLibrary(new FT_Library),
	m_pProgramGenerator(nullptr),
	m_pVertexBuffer(nullptr)
{
	// Initialize the FreeType library object
	const FT_Error nError = FT_Init_FreeType(m_pFTLibrary);
	if (nError) {
		delete m_pFTLibrary;
		m_pFTLibrary = nullptr;
	}
}

/**
*  @brief
*    Destructor
*/
FontManager::~FontManager()
{
	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;

	// Destroy the vertex buffer
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;

	// Destroy the FreeType library object
	if (m_pFTLibrary) {
		FT_Done_FreeType(*m_pFTLibrary);
		delete m_pFTLibrary;
	}
}

/**
*  @brief
*    Returns the FreeType library object
*/
FT_Library *FontManager::GetFTLibrary() const
{
	return m_pFTLibrary;
}

/**
*  @brief
*    Returns the program for font rendering
*/
PLRenderer::Program *FontManager::GetProgram(GeneratedProgramUserData **ppGeneratedProgramUserData)
{
	// Create the program generator if there's currently no instance of it
	if (!m_pProgramGenerator) {
		// Get the shader language to use
		const String sShaderLanguage = m_pRenderer->GetDefaultShaderLanguage();

		// Create the program generator
		#include "FontManager_GLSL.h"
		m_pProgramGenerator = new PLRenderer::ProgramGenerator(*m_pRenderer, sShaderLanguage, sVertexShaderSourceCodeGLSL, "100", sFragmentShaderSourceCodeGLSL, "100");	// OpenGL ES 2.0 GLSL shader language 100
	}

	// If there's no program generator, we don't need to continue
	if (m_pProgramGenerator) {
		// Reset the program flags
		m_cProgramFlags.Reset();

		// Get a program instance from the program generator using the given program flags
		PLRenderer::ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);
		if (pGeneratedProgram) {
			PLRenderer::Program *pProgram = pGeneratedProgram->pProgram;

			// Set pointers to uniforms & attributes of a generated program if they are not set yet
			GeneratedProgramUserData *pGeneratedProgramUserData = static_cast<GeneratedProgramUserData*>(pGeneratedProgram->pUserData);
			if (!pGeneratedProgramUserData) {
				pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
				// Vertex shader attributes
				static const String sVertexPosition = "VertexPosition";
				pGeneratedProgramUserData->pVertexPosition					= pProgram->GetAttribute(sVertexPosition);
				// Vertex shader uniforms
				static const String sGlyphSizePenPosition = "GlyphSizePenPosition";
				pGeneratedProgramUserData->pGlyphSizePenPosition			= pProgram->GetUniform(sGlyphSizePenPosition);
				static const String sTextureCoordinateMinMax = "TextureCoordinateMinMax";
				pGeneratedProgramUserData->pTextureCoordinateMinMax			= pProgram->GetUniform(sTextureCoordinateMinMax);
				static const String sObjectSpaceToClipSpaceMatrix = "ObjectSpaceToClipSpaceMatrix";
				pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix	= pProgram->GetUniform(sObjectSpaceToClipSpaceMatrix);
				// Fragment shader uniforms
				static const String sGlyphMap = "GlyphMap";
				pGeneratedProgramUserData->pGlyphMap						= pProgram->GetUniform(sGlyphMap);
				static const String sColor = "Color";
				pGeneratedProgramUserData->pColor							= pProgram->GetUniform(sColor);
			}
			if (ppGeneratedProgramUserData)
				*ppGeneratedProgramUserData = pGeneratedProgramUserData;

			// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
			if (pGeneratedProgramUserData->pVertexPosition)
				pGeneratedProgramUserData->pVertexPosition->Set(GetVertexBuffer(), PLRenderer::VertexBuffer::Position);

			// Done
			return pProgram;
		}
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::FontManager functions      ]
//[-------------------------------------------------------]
PLRenderer::Font *FontManager::CreateFontTexture(File &cFile, uint32 nSize, uint32 nResolution)
{
	// Create the font instance
	PLRenderer::Font *pFont = new FontTexture(*this, cFile);

	// Is the font valid? If yes, should we set the font size and resolution right now?
	if (pFont->IsValid() && nSize && nResolution) {
		// Set the font size
		pFont->SetSize(nSize, nResolution);
	}

	// Return the created font
	return pFont;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the vertex buffer used for font rendering
*/
PLRenderer::VertexBuffer *FontManager::GetVertexBuffer()
{
	// Initialize vertex buffer
	if (!m_pVertexBuffer) {
		// Create the vertex buffer
		m_pVertexBuffer = m_pRenderer->CreateVertexBuffer();

		// Add vertex position attribute to the vertex buffer, zw stores the texture coordinate
		// -> First try efficient "half" (16 bit floating point) as data type, if this fails fall back to traditional more expensive "float" (32 bit floating point)
		if (!m_pVertexBuffer->AddVertexAttribute(PLRenderer::VertexBuffer::Position, 0, PLRenderer::VertexBuffer::Half3))
			m_pVertexBuffer->AddVertexAttribute(PLRenderer::VertexBuffer::Position, 0, PLRenderer::VertexBuffer::Float3);

		// Allocate four vertices
		m_pVertexBuffer->Allocate(4);

		// Fill vertex positions
		if (m_pVertexBuffer->Lock(PLRenderer::Lock::WriteOnly)) {
			// This is not performance critical, so, use the comfort method "VertexBuffer::SetFloat()" instead of "VertexBuffer::GetFloat()"

			// Vertex 0 - lower/left corner										x	  y		Index
			m_pVertexBuffer->SetFloat(0, PLRenderer::VertexBuffer::Position, 0, 0.0f, 0.0f, 0.0f);

			// Vertex 1 - lower/right corner									x	  y		Index
			m_pVertexBuffer->SetFloat(1, PLRenderer::VertexBuffer::Position, 0, 1.0f, 0.0f, 1.0f);

			// Vertex 2 - upper/left corner										x	  y		Index
			m_pVertexBuffer->SetFloat(2, PLRenderer::VertexBuffer::Position, 0, 0.0f, 1.0f, 2.0f);

			// Vertex 3 - upper/right corner									x	  y		Index
			m_pVertexBuffer->SetFloat(3, PLRenderer::VertexBuffer::Position, 0, 1.0f, 1.0f, 3.0f);

			// Unlock the vertex buffer
			m_pVertexBuffer->Unlock();
		}
	}

	// Return the vertex buffer
	return m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
