/*********************************************************\
 *  File: FontManager.cpp                                *
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
#include <ft2build.h>
#include FT_FREETYPE_H
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include "PLRendererOpenGLES/Renderer.h"
#include "PLRendererOpenGLES/FontTexture.h"
#include "PLRendererOpenGLES/FontManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
FontManager::FontManager(PLRenderer::Renderer &cRenderer) : PLRenderer::FontManager(cRenderer),
	m_pFTLibrary(new FT_Library),
	m_pProgramGenerator(NULL),
	m_pVertexBuffer(NULL)
{
	// Initialize the FreeType library object
	const FT_Error nError = FT_Init_FreeType(m_pFTLibrary);
	if (nError) {
		delete m_pFTLibrary;
		m_pFTLibrary = NULL;
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
	if (m_pFTLibrary)
		delete m_pFTLibrary;
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
		m_pProgramGenerator = new PLRenderer::ProgramGenerator(*m_pRenderer, sShaderLanguage, sVertexShaderSourceCodeGLSL, "", sFragmentShaderSourceCodeGLSL, "");
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
			GeneratedProgramUserData *pGeneratedProgramUserData = (GeneratedProgramUserData*)pGeneratedProgram->pUserData;
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
	return NULL;
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
		m_pVertexBuffer->AddVertexAttribute(PLRenderer::VertexBuffer::Position, 0, PLRenderer::VertexBuffer::Float3);

		// Allocate
		m_pVertexBuffer->Allocate(4);

		// Fill
		if (m_pVertexBuffer->Lock(PLRenderer::Lock::WriteOnly)) {
		// Vertex 0 - lower/left corner
			// Position
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, PLRenderer::VertexBuffer::Position);
			pfVertex[Vector4::X] = 0.0f;	// x
			pfVertex[Vector4::Y] = 0.0f;	// y
			pfVertex[Vector4::Z] = 0.0f;	// Index

		// Vertex 1 - lower/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(1, PLRenderer::VertexBuffer::Position);
			pfVertex[Vector4::X] = 1.0f;	// x
			pfVertex[Vector4::Y] = 0.0f;	// y
			pfVertex[Vector4::Z] = 1.0f;	// Index

		// Vertex 2 - upper/left corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(2, PLRenderer::VertexBuffer::Position);
			pfVertex[Vector4::X] = 0.0f;	// x
			pfVertex[Vector4::Y] = 1.0f;	// y
			pfVertex[Vector4::Z] = 2.0f;	// Index

		// Vertex 3 - upper/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(3, PLRenderer::VertexBuffer::Position);
			pfVertex[Vector4::X] = 1.0f;	// x
			pfVertex[Vector4::Y] = 1.0f;	// y
			pfVertex[Vector4::Z] = 3.0f;	// Index

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
} // PLRendererOpenGLES
