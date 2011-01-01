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


#ifndef __PLRENDEREROPENGL_SHADERTOOLSGLSL_H__
#define __PLRENDEREROPENGL_SHADERTOOLSGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful OpenGL GLSL shader tool methods
*/
class ShaderToolsGLSL {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets and compiles the source code of an OpenGL shader
		*
		*  @param[in] nOpenGLShader
		*    OpenGL shader to use
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If compiling the shader failed, compiler information is written into the log
		*/
		static bool SetSourceCode(GLuint nOpenGLShader, const PLGeneral::String &sSourceCode);

		/**
		*  @brief
		*    Writes information into the log
		*
		*  @param[in] nOpenGLObject
		*    OpenGL object to use
		*/
		static void WriteInformationIntoLog(GLuint nOpenGLObject);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_SHADERTOOLSGLSL_H__
