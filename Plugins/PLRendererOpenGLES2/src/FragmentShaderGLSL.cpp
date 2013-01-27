/*********************************************************\
 *  File: FragmentShaderGLSL.cpp                         *
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
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FragmentShaderGLSL::FragmentShaderGLSL(PLRenderer::Renderer &cRenderer, GLenum nShaderType) : PLRenderer::FragmentShader(cRenderer),
	m_nOpenGLESFragmentShader(glCreateShader(nShaderType))
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

String FragmentShaderGLSL::GetArguments() const
{
	// GLSL doesn't have shader compiler arguments
	return "";
}

String FragmentShaderGLSL::GetEntry() const
{
	// GLSL doesn't have an user defined entry point
	return "";
}

bool FragmentShaderGLSL::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sArguments, const String &sEntry)
{
	// GLSL doesn't have profiles, so sProfile is just ignored
	// GLSL doesn't have shader compiler arguments, so sArguments is just ignored
	// GLSL doesn't have an user defined entry point, so sEntry is just ignored
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLESFragmentShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
