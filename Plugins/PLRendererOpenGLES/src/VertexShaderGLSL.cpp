/*********************************************************\
 *  File: VertexShaderGLSL.cpp                           *
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
#include "PLRendererOpenGLES/ShaderLanguageGLSL.h"
#include "PLRendererOpenGLES/ShaderToolsGLSL.h"
#include "PLRendererOpenGLES/Renderer.h"
#include "PLRendererOpenGLES/VertexShaderGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
VertexShaderGLSL::~VertexShaderGLSL()
{
	// Destroy the OpenGL ES vertex shader
	glDeleteShader(m_nOpenGLESVertexShader);
}

/**
*  @brief
*    Returns the OpenGL ES vertex shader
*/
GLuint VertexShaderGLSL::GetOpenGLESVertexShader() const
{
	return m_nOpenGLESVertexShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VertexShaderGLSL::VertexShaderGLSL(PLRenderer::Renderer &cRenderer) : PLRenderer::VertexShader(cRenderer),
	m_nOpenGLESVertexShader(glCreateShader(GL_VERTEX_SHADER))
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String VertexShaderGLSL::GetShaderLanguage() const
{
	return ShaderLanguageGLSL::GLSL;
}

String VertexShaderGLSL::GetSourceCode() const
{
	// Get the length of the shader source, including the null termination character
	GLint nShaderSourceLength = 0;
	glGetShaderiv(m_nOpenGLESVertexShader, GL_SHADER_SOURCE_LENGTH, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		// The string class takes over the control of the string memory and also deletes it
		char *pszSourceCode = new char[nShaderSourceLength];
		glGetShaderSource(m_nOpenGLESVertexShader, nShaderSourceLength, nullptr, pszSourceCode);
		return String(pszSourceCode, false, nShaderSourceLength-1);	// -1 = excluding the null termination character
	}

	// Error!
	return "";
}

String VertexShaderGLSL::GetProfile() const
{
	// GLSL doesn't have profiles
	return "";
}

String VertexShaderGLSL::GetEntry() const
{
	// GLSL doesn't have an user defined entry point
	return "";
}

bool VertexShaderGLSL::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sEntry)
{
	// GLSL doesn't have profiles, so sProfile is just ignored
	// GLSL doesn't have an user defined entry point, so sEntry is just ignored
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLESVertexShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES
