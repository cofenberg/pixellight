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
#include "PLRendererOpenGL/Misc/ExtensionDefinitions.h"
#include "PLRendererOpenGL/ShaderToolsGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets and compiles the source code of an OpenGL shader
*/
bool ShaderToolsGLSL::SetSourceCode(GLuint nOpenGLShader, const String &sSourceCode)
{
	// Load the shader source
	const char *pszSourceCode = sSourceCode.GetASCII();
	glShaderSourceARB(nOpenGLShader, 1, &pszSourceCode, NULL);

	// Compile the shader
	glCompileShaderARB(nOpenGLShader);

	// Check the compile status
	GLint nCompiled = GL_FALSE;
	glGetObjectParameterivARB(nOpenGLShader, GL_OBJECT_COMPILE_STATUS_ARB, &nCompiled);
	if (nCompiled == GL_TRUE) {
		// All went fine, return the shader
		return true;
	} else {
		// Error, failed to compile the shader!
		WriteInformationIntoLog(nOpenGLShader);

		// Error!
		return false;
	}
}

/**
*  @brief
*    Writes program information into the log
*/
void ShaderToolsGLSL::WriteInformationIntoLog(GLuint nOpenGLObject)
{
	// Get the length of the information (including a null termination)
	GLint nInformationLength = 0;
	glGetObjectParameterivARB(nOpenGLObject, GL_OBJECT_INFO_LOG_LENGTH_ARB, &nInformationLength);
	if (nInformationLength > 1) {
		// Allocate memory for the information
		char *pszInformationLog = new char[nInformationLength];

		// Get the information
		glGetInfoLogARB(nOpenGLObject, nInformationLength, NULL, pszInformationLog);

		// Write the error into the log - the PixelLight string class takes over the control of the allocated string buffer
		String sInformationLog(pszInformationLog, false, nInformationLength-1);	// -1 = excluding the terminating zero
		PL_LOG(Error, sInformationLog)
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // OpenGL
