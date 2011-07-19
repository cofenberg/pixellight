/*********************************************************\
 *  File: ProgramUniformBlockGLSL.h                      *
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


#ifndef __PLRENDEREROPENGL_PROGRAMUNIFORMBLOCKGLSL_H__
#define __PLRENDEREROPENGL_PROGRAMUNIFORMBLOCKGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLRenderer/Renderer/ProgramUniformBlock.h>
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
*    OpenGL GLSL renderer program uniform block
*/
class ProgramUniformBlockGLSL : public PLRenderer::ProgramUniformBlock {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ProgramGLSL;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nOpenGLProgram
		*    OpenGL program, must be valid!
		*  @param[in] nUniformBlockIndex
		*    Uniform block index, must be valid!
		*  @param[in] nUniformBlockSize
		*    Uniform block size, must be valid!
		*  @param[in] sShaderLanguage
		*    The name of the shader language the uniform block is using (for example "GLSL" or "Cg")
		*/
		ProgramUniformBlockGLSL(GLuint nOpenGLProgram, GLuint nUniformBlockIndex, GLint nUniformBlockSize, const PLCore::String &sShaderLanguage);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramUniformBlockGLSL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sShaderLanguage;			/**< The name of the shader language the uniform block is using (for example "GLSL" or "Cg") */
		GLuint		   m_nOpenGLProgram;			/**< OpenGL program, always valid! */
		GLint		   m_nUniformBlockIndex;		/**< OpenGL uniform block index */
		GLint		   m_nOpenGLUniformBlockSize;	/**< OpenGL uniform block size */
		int			   m_nBindingPoint;				/**< Used binding point, <0 means not yet assigned */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramUniformBlock functions ]
	//[-------------------------------------------------------]
	public:
		virtual bool SetUniformBuffer(PLRenderer::UniformBuffer *pUniformBuffer, PLCore::uint32 nBindingPoint);
		virtual PLCore::uint32 GetIndex() const;
		virtual PLCore::uint32 GetSize() const;
		virtual PLCore::uint32 GetUniformOffset(const PLCore::String &sUniformName) const;
		virtual PLCore::uint32 GetUniformSize(const PLCore::String &sUniformName) const;
		virtual PLCore::uint32 GetUniformNumOfArrayElements(const PLCore::String &sUniformName) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_PROGRAMUNIFORMBLOCKGLSL_H__
