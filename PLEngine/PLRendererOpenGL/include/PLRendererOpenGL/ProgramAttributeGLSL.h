/*********************************************************\
 *  File: ProgramAttributeGLSL.h                         *
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


#ifndef __PLRENDEREROPENGL_PROGRAMATTRIBUTEGLSL_H__
#define __PLRENDEREROPENGL_PROGRAMATTRIBUTEGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramAttribute.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL GLSL renderer program attriute
*/
class ProgramAttributeGLSL : public PLRenderer::ProgramAttribute {


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
		*  @param[in] nOpenGLAttributeLocation
		*    OpenGL attribute location, must be valid!
		*/
		ProgramAttributeGLSL(int nOpenGLAttributeLocation);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramAttributeGLSL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		int m_nOpenGLAttributeLocation;	/**< OpenGL attribute location, always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramAttribute functions ]
	//[-------------------------------------------------------]
	public:
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLGeneral::uint32 nIndex);
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, PLGeneral::uint32 nChannel = 0);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_PROGRAMATTRIBUTEGLSL_H__
