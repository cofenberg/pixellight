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
#include "PLRendererOpenGL/ShaderLanguageGLSL.h"
#include "PLRendererOpenGL/ShaderToolsGLSL.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/Extensions.h"
#include "PLRendererOpenGL/FragmentShaderGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
FragmentShaderGLSL::~FragmentShaderGLSL()
{
	// Destroy the OpenGL fragment shader
	glDeleteObjectARB(m_nOpenGLFragmentShader);
}

/**
*  @brief
*    Returns the OpenGL fragment shader
*/
GLuint FragmentShaderGLSL::GetOpenGLFragmentShader() const
{
	return m_nOpenGLFragmentShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FragmentShaderGLSL::FragmentShaderGLSL(PLRenderer::Renderer &cRenderer) : PLRenderer::FragmentShader(cRenderer),
	m_nOpenGLFragmentShader(glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB))
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
	glGetObjectParameterivARB(m_nOpenGLFragmentShader, GL_OBJECT_SHADER_SOURCE_LENGTH_ARB, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		// The string class takes over the control of the string memory and also deletes it
		char *pszSourceCode = new char[nShaderSourceLength];
		glGetShaderSourceARB(m_nOpenGLFragmentShader, nShaderSourceLength, nullptr, pszSourceCode);
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
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLFragmentShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void FragmentShaderGLSL::BackupDeviceData(uint8 **ppBackup)
{
	// Get the length of the shader source, including the null termination character
	GLint nShaderSourceLength = 0;
	glGetObjectParameterivARB(m_nOpenGLFragmentShader, GL_OBJECT_SHADER_SOURCE_LENGTH_ARB, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		*ppBackup = new uint8[nShaderSourceLength];
		glGetShaderSourceARB(m_nOpenGLFragmentShader, nShaderSourceLength, nullptr, reinterpret_cast<GLcharARB*>(*ppBackup));
		glDeleteObjectARB(m_nOpenGLFragmentShader);
		m_nOpenGLFragmentShader = 0;
	} else {
		*ppBackup = nullptr;
	}
}

void FragmentShaderGLSL::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup && !m_nOpenGLFragmentShader) {
		m_nOpenGLFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String(reinterpret_cast<char*>(*ppBackup), false));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
