/*********************************************************\
 *  File: ProgramAttributeGLSL.h                         *
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


#ifndef __PLRENDEREROPENGLES2_PROGRAMATTRIBUTEGLSL_H__
#define __PLRENDEREROPENGLES2_PROGRAMATTRIBUTEGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramAttribute.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES GLSL renderer program attribute
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
		*  @param[in] nOpenGLESAttributeLocation
		*    OpenGL ES attribute location, must be valid!
		*/
		ProgramAttributeGLSL(int nOpenGLESAttributeLocation);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramAttributeGLSL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		int m_nOpenGLESAttributeLocation;	/**< OpenGL ES attribute location, always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramAttribute functions ]
	//[-------------------------------------------------------]
	public:
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLCore::uint32 nIndex) override;
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, PLCore::uint32 nChannel = 0) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_PROGRAMATTRIBUTEGLSL_H__
