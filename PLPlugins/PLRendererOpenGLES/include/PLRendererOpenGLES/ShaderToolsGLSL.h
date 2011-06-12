/*********************************************************\
 *  File: ShaderToolsGLSL.h                              *
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


#ifndef __PLRENDEREROPENGLES_SHADERTOOLSGLSL_H__
#define __PLRENDEREROPENGLES_SHADERTOOLSGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <GLES2/gl2.h>
#include <PLGeneral/String/String.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful OpenGL ES GLSL shader tool methods
*/
class ShaderToolsGLSL {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets and compiles the source code of an OpenGL ES shader
		*
		*  @param[in] nOpenGLESShader
		*    OpenGL ES shader to use
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If compiling the shader failed, compiler information is written into the log
		*/
		static bool SetSourceCode(GLuint nOpenGLESShader, const PLGeneral::String &sSourceCode);

		/**
		*  @brief
		*    Writes program information into the log
		*
		*  @param[in] nOpenGLProgram
		*    OpenGL program to use
		*/
		static void WriteProgramInformationIntoLog(GLuint nOpenGLESProgram);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_SHADERTOOLSGLSL_H__
