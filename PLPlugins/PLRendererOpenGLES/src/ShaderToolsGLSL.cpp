/*********************************************************\
 *  File: ShaderToolsGLSL.cpp                            *
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
#include <PLGeneral/Log/Log.h>
#include "PLRendererOpenGLES/ShaderToolsGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets and compiles the source code of an OpenGL ES shader
*/
bool ShaderToolsGLSL::SetSourceCode(GLuint nOpenGLESShader, const String &sSourceCode)
{
	// Load the shader source
	const char *pszSourceCode = sSourceCode.GetASCII();
	glShaderSource(nOpenGLESShader, 1, &pszSourceCode, nullptr);

	// Compile the shader
	glCompileShader(nOpenGLESShader);

	// Check the compile status
	GLint nCompiled = GL_FALSE;
	glGetShaderiv(nOpenGLESShader, GL_COMPILE_STATUS, &nCompiled);
	if (nCompiled == GL_TRUE) {
		// All went fine, return the shader
		return true;
	} else {
		// Error, failed to compile the shader!

		// Get the length of the information
		GLint nInformationLength = 0;
		glGetShaderiv(nOpenGLESShader, GL_INFO_LOG_LENGTH, &nInformationLength);
		if (nInformationLength > 1) {
			// Allocate memory for the information
			char *pszInformationLog = new char[nInformationLength];

			// Get the information
			glGetShaderInfoLog(nOpenGLESShader, nInformationLength, nullptr, pszInformationLog);

			// Write the error into the log - the PixelLight string class takes over the control of the allocated string buffer
			String sInformationLog(pszInformationLog, false, nInformationLength-1);	// -1 = excluding the terminating zero
			PL_LOG(Error, sInformationLog)
		}

		// Error!
		return false;
	}
}

/**
*  @brief
*    Writes program information into the log
*/
void ShaderToolsGLSL::WriteProgramInformationIntoLog(GLuint nOpenGLESProgram)
{
	// Get the length of the information
	GLint nInformationLength = 0;
	glGetProgramiv(nOpenGLESProgram, GL_INFO_LOG_LENGTH, &nInformationLength);
	if (nInformationLength > 1) {
		// Allocate memory for the information
		char *pszInformationLog = new char[nInformationLength];

		// Get the information
		glGetProgramInfoLog(nOpenGLESProgram, nInformationLength, nullptr, pszInformationLog);

		// Write the error into the log - the PixelLight string class takes over the control of the allocated string buffer
		String sInformationLog(pszInformationLog, false, nInformationLength-1);	// -1 = excluding the terminating zero
		PL_LOG(Error, sInformationLog)
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES
