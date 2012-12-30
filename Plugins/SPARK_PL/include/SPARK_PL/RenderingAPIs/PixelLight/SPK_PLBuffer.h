/*********************************************************\
 *  File: SPK_PLBuffer.h                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
