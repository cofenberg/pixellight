/*********************************************************\
 *  File: FragmentShaderGLSL.cpp                         *
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
#include "PLRendererOpenGLES2/ShaderLanguageGLSL.h"
#include "PLRendererOpenGLES2/ShaderToolsGLSL.h"
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/FragmentShaderGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
FragmentShaderGLSL::~FragmentShaderGLSL()
{
	// Destroy the OpenGL ES fragment shader
	glDeleteShader(m_nOpenGLESFragmentShader);
}

/**
*  @brief
*    Returns the OpenGL ES fragment shader
*/
GLuint FragmentShaderGLSL::GetOpenGLESFragmentShader() const
{
	return m_nOpenGLESFragmentShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FragmentShaderGLSL::FragmentShaderGLSL(PLRenderer::Renderer &cRenderer) : PLRenderer::FragmentShader(cRenderer),
	m_nOpenGLESFragmentShader(glCreateShader(GL_FRAGMENT_SHADER))
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String FragmentShaderGLSL::GetShaderLanguage() const
{
	return ShaderLanguageGLSL::GLSL;
}

String FragmentShaderGLSL::GetSourceCode() const
{
	// Get the length of the shader source, including the null termination character
	GLint nShaderSourceLength = 0;
	glGetShaderiv(m_nOpenGLESFragmentShader, GL_SHADER_SOURCE_LENGTH, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		// The string class takes over the control of the string memory and also deletes it
		char *pszSourceCode = new char[nShaderSourceLength];
		glGetShaderSource(m_nOpenGLESFragmentShader, nShaderSourceLength, nullptr, pszSourceCode);
		return String(pszSourceCode, false, nShaderSourceLength-1);	// -1 = excluding the null termination character
	}

	// Error!
	return "";
}

String FragmentShaderGLSL::GetProfile() const
{
	// GLSL doesn't have profiles
	return "";
}

String FragmentShaderGLSL::GetEntry() const
{
	// GLSL doesn't have an user defined entry point
	return "";
}

bool FragmentShaderGLSL::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sEntry)
{
	// GLSL doesn't have profiles, so sProfile is just ignored
	// GLSL doesn't have an user defined entry point, so sEntry is just ignored
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLESFragmentShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
