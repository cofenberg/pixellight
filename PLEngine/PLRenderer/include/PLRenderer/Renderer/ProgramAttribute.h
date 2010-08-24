/*********************************************************\
 *  File: ProgramAttribute.h                             *
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


#ifndef __PLRENDERER_PROGRAMATTRIBUTE_H__
#define __PLRENDERER_PROGRAMATTRIBUTE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/VertexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer program attribute
*
*  @note
*    - For per-vertex data
*/
class ProgramAttribute {


	//[-------------------------------------------------------]
	//[ Public virtual ProgramAttribute functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets a attribute by using an index to reference the vertex buffer attribute to use
		*
		*  @param[in] pVertexBuffer
		*    Vertex buffer to use, can be NULL
		*  @param[in] nIndex
		*    Index of the vertex buffer attribute to connect with the vertex shader attribute
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLGeneral::uint32 nIndex) = 0;

		/**
		*  @brief
		*    Sets a attribute by using a semantic to reference the vertex buffer attribute to use
		*
		*  @param[in] pVertexBuffer
		*    Vertex buffer to use, can be NULL
		*  @param[in] nSemantic
		*    Semantic of the vertex buffer attribute to connect with the vertex shader attribute
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic, maximum see MaxPipelineChannels)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, PLGeneral::uint32 nChannel = 0) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API ProgramAttribute();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ProgramAttribute();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ProgramAttribute(const ProgramAttribute &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ProgramAttribute &operator =(const ProgramAttribute &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_PROGRAMATTRIBUTE_H__
