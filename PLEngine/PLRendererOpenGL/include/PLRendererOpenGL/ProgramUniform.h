/*********************************************************\
 *  File: ProgramUniform.h                               *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDEREROPENGL_PROGRAMUNIFORM_H__
#define __PLRENDEREROPENGL_PROGRAMUNIFORM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramUniform.h>
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
*    Abstract OpenGL renderer program uniform
*/
class ProgramUniform : public PLRenderer::ProgramUniform {


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    If this uniform is a texture, this method sets the OpenGL texture assigned to the uniform
		*
		*  @param[in] nOpenGLTextureTarget
		*    OpenGL texture target
		*  @param[in] nOpenGLTexture
		*    OpenGL texture to set
		*
		*  @return
		*    The texture unit assigned to this uniform (same as GetTextureUnit()), negative on error
		*/
		virtual int Set(GLenum nOpenGLTextureTarget, GLuint nOpenGLTexture) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		ProgramUniform();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramUniform();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_PROGRAMUNIFORM_H__
