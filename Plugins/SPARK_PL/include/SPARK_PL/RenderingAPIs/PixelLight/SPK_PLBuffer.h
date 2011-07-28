/*********************************************************\
 *  File: SPK_PLBuffer.h                                 *
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


#ifndef __SPARK_PL_BUFFER_H__
#define __SPARK_PL_BUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Core/SPK_Buffer.h>
	#include <Extensions/Renderers/SPK_QuadRendererInterface.h>
PL_WARNING_POP
#include "SPARK_PL/SPARK_PL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
	class IndexBuffer;
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A buffer to store particle mesh data to be rendered with PixelLight
*/
class SPK_PLBuffer : public SPK::Buffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLBufferCreator;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor of SPK_PLBuffer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] nNumOfVerticesPerParticle
		*    Number of vertices per particle (e.g. 4)
		*  @param[in] nNumOfIndicesPerParticle
		*    Number of indices per particle (e.g. 6)
		*  @param[in] nTexturingMode
		*    The texturing mode of this SPK_PLBuffer
		*  @param[in] nNumOfParticles
		*    Number of particles
		*/
		SPARK_PL_API SPK_PLBuffer(PLRenderer::Renderer &cRenderer, PLCore::uint32 nNumOfVerticesPerParticle, PLCore::uint32 nNumOfIndicesPerParticle, SPK::TexturingMode nTexturingMode, PLCore::uint32 nNumOfParticles);

		/**
		*  @brief
		*    Destructor of SPK_PLBuffer
		*/
		SPARK_PL_API virtual ~SPK_PLBuffer();

		/**
		*  @brief
		*    Returns the index buffer
		*
		*  @return
		*    The index buffer, can be a null pointer
		*/
		SPARK_PL_API PLRenderer::IndexBuffer *GetIndexBuffer() const;

		/**
		*  @brief
		*    Returns the vertex buffer
		*
		*  @return
		*    The vertex buffer, can be a null pointer
		*/
		SPARK_PL_API PLRenderer::VertexBuffer *GetVertexBuffer() const;


	//[-------------------------------------------------------]
	//[ Private virtual SPK::Buffer functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void swap(size_t index0, size_t index1) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer	 *m_pRenderer;		/**< PixelLight renderer to use, always valid */
		PLRenderer::IndexBuffer  *m_pIndexBuffer;	/**< PixelLight index buffer, can be a null pointer */
		PLRenderer::VertexBuffer *m_pVertexBuffer;	/**< PixelLight vertex buffer, can be a null pointer */


};

/**
*  @brief
*    A buffer creator to create PLBuffers
*/
class PLBufferCreator : public SPK::BufferCreator {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor of PLBufferCreator
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] nNumOfVerticesPerParticle
		*    Number of vertices per particle (e.g. 4)
		*  @param[in] nNumOfIndicesPerParticle
		*    Number of indices per particle (e.g. 6)
		*  @param[in] nTexturingMode
		*    The texturing mode of this SPK_PLBuffer
		*/
		SPARK_PL_API PLBufferCreator(PLRenderer::Renderer &cRenderer, PLCore::uint32 nNumOfVerticesPerParticle, PLCore::uint32 nNumOfIndicesPerParticle, SPK::TexturingMode nTexturingMode);


	//[-------------------------------------------------------]
	//[ Private virtual SPK::BufferCreator functions          ]
	//[-------------------------------------------------------]
	private:
		virtual SPK::Buffer *createBuffer(size_t nbParticles, const SPK::Group &group) const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;					/**< PixelLight renderer to use, always valid */
		PLCore::uint32		  m_nNumOfVerticesPerParticle;	/**< Number of vertices per particle (e.g. 4) */
		PLCore::uint32	  	  m_nNumOfIndicesPerParticle;	/**< Number of indices per particle (e.g. 6) */
		SPK::TexturingMode	  m_nTexturingMode;				/**< The texturing mode of this SPK_PLBuffer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_BUFFER_H__
