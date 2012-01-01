/*********************************************************\
 *  File: GeometryShaderGLSL.cpp                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRendererOpenGL/Extensions.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/GeometryShaderGLSL.h"


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
GeometryShaderGLSL::~GeometryShaderGLSL()
{
	// Destroy the OpenGL geometry shader
	glDeleteObjectARB(m_nOpenGLGeometryShader);
}

/**
*  @brief
*    Returns the OpenGL geometry shader
*/
GLuint GeometryShaderGLSL::GetOpenGLGeometryShader() const
{
	return m_nOpenGLGeometryShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GeometryShaderGLSL::GeometryShaderGLSL(PLRenderer::Renderer &cRenderer) : PLRenderer::GeometryShader(cRenderer),
	m_nInputPrimitiveType(InputTriangles),
	m_nOutputPrimitiveType(OutputTriangles),
	m_nNumOfOutputVertices(0),
	m_nOpenGLGeometryShader(glCreateShaderObjectARB(GL_GEOMETRY_SHADER_EXT))
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::GeometryShader functions   ]
//[-------------------------------------------------------]
GeometryShaderGLSL::EInputPrimitiveType GeometryShaderGLSL::GetInputPrimitiveType() const
{
	return m_nInputPrimitiveType;
}

GeometryShaderGLSL::EOutputPrimitiveType GeometryShaderGLSL::GetOutputPrimitiveType() const
{
	return m_nOutputPrimitiveType;
}

uint32 GeometryShaderGLSL::GetNumOfOutputVertices() const
{
	return m_nNumOfOutputVertices;
}

bool GeometryShaderGLSL::SetSourceCode(const String &sSourceCode, EInputPrimitiveType nInputPrimitiveType, EOutputPrimitiveType nOutputPrimitiveType, uint32 nNumOfOutputVertices, const String &sProfile, const String &sEntry)
{
	// Backup the input/output primitive type and the number of output vertices
	m_nInputPrimitiveType  = nInputPrimitiveType;
	m_nOutputPrimitiveType = nOutputPrimitiveType;
	m_nNumOfOutputVertices = nNumOfOutputVertices;

	// GLSL doesn't have profiles, so sProfile is just ignored
	// GLSL doesn't have an user defined entry point, so sEntry is just ignored
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLGeometryShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String GeometryShaderGLSL::GetShaderLanguage() const
{
	return ShaderLanguageGLSL::GLSL;
}

String GeometryShaderGLSL::GetSourceCode() const
{
	// Get the length of the shader source, including the null termination character
	GLint nShaderSourceLength = 0;
	glGetObjectParameterivARB(m_nOpenGLGeometryShader, GL_OBJECT_SHADER_SOURCE_LENGTH_ARB, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		// The string class takes over the control of the string memory and also deletes it
		char *pszSourceCode = new char[nShaderSourceLength];
		glGetShaderSourceARB(m_nOpenGLGeometryShader, nShaderSourceLength, nullptr, pszSourceCode);
		return String(pszSourceCode, false, nShaderSourceLength-1);	// -1 = excluding the null termination character
	}

	// Error!
	return "";
}

String GeometryShaderGLSL::GetProfile() const
{
	// GLSL doesn't have profiles
	return "";
}

String GeometryShaderGLSL::GetEntry() const
{
	// GLSL doesn't have an user defined entry point
	return "";
}

bool GeometryShaderGLSL::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sEntry)
{
	// GLSL doesn't have profiles, so sProfile is just ignored
	// GLSL doesn't have an user defined entry point, so sEntry is just ignored
	return ShaderToolsGLSL::SetSourceCode(m_nOpenGLGeometryShader, sSourceCode);
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void GeometryShaderGLSL::BackupDeviceData(uint8 **ppBackup)
{
	// Get the length of the shader source, including the null termination character
	GLint nShaderSourceLength = 0;
	glGetObjectParameterivARB(m_nOpenGLGeometryShader, GL_OBJECT_SHADER_SOURCE_LENGTH_ARB, &nShaderSourceLength);
	if (nShaderSourceLength > 1) {
		*ppBackup = new uint8[nShaderSourceLength];
		glGetShaderSourceARB(m_nOpenGLGeometryShader, nShaderSourceLength, nullptr, reinterpret_cast<GLcharARB*>(*ppBackup));
		glDeleteObjectARB(m_nOpenGLGeometryShader);
		m_nOpenGLGeometryShader = 0;
	} else {
		*ppBackup = nullptr;
	}
}

void GeometryShaderGLSL::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup && !m_nOpenGLGeometryShader) {
		m_nOpenGLGeometryShader = glCreateShaderObjectARB(GL_GEOMETRY_SHADER_EXT);

		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String(reinterpret_cast<char*>(*ppBackup), false));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
