/*********************************************************\
 *  File: ProgramUniformBlockGLSL.cpp                    *
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
#include "PLRendererOpenGL/ProgramUniformBlockGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramUniformBlockGLSL::ProgramUniformBlockGLSL(GLuint nOpenGLProgram, GLuint nUniformBlockIndex, GLint nUniformBlockSize) :
	m_nOpenGLProgram(nOpenGLProgram),
	m_nUniformBlockIndex(nUniformBlockIndex),
	m_nOpenGLUniformBlockSize(nUniformBlockSize)
{
}

/**
*  @brief
*    Destructor
*/
ProgramUniformBlockGLSL::~ProgramUniformBlockGLSL()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramUniformBlock functions ]
//[-------------------------------------------------------]
uint32 ProgramUniformBlockGLSL::GetIndex() const
{
	return m_nUniformBlockIndex;
}

uint32 ProgramUniformBlockGLSL::GetSize() const
{
	return m_nOpenGLUniformBlockSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
