/*********************************************************\
 *  File: SPK_PLBuffer.cpp                               *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLBuffer::SPK_PLBuffer(Renderer &cRenderer, uint32 nNumOfVerticesPerParticle, uint32 nNumOfIndicesPerParticle, SPK::TexturingMode nTexturingMode, uint32 nNumOfParticles) : SPK::Buffer(),
	m_pRenderer(&cRenderer),
	m_pIndexBuffer(nNumOfIndicesPerParticle   ? m_pRenderer->CreateIndexBuffer()  : nullptr),
	m_pVertexBuffer(nNumOfVerticesPerParticle ? m_pRenderer->CreateVertexBuffer() : nullptr)
{
	// Setup the index buffer - if there's one
	if (m_pIndexBuffer) {
		// Tell the index buffer about the maximum number of vertices so it can decide automatically which index buffer data type should be used
		m_pIndexBuffer->SetElementTypeByMaximumIndex(nNumOfParticles*nNumOfVerticesPerParticle);

		// Allocate the index buffer, the index data is not changed dynamically, so mark it as static
		m_pIndexBuffer->Allocate(nNumOfParticles*nNumOfIndicesPerParticle, Usage::Static);
	}

	// Setup the vertex buffer - if there's one
	if (m_pVertexBuffer) {
		// Add vertex attributes
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (nTexturingMode == SPK::TEXTURE_2D)
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
		else if (nTexturingMode == SPK::TEXTURE_3D)
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float3);
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Color, 0, VertexBuffer::RGBA);

		// Allocate the vertex buffer
		m_pVertexBuffer->Allocate(nNumOfParticles*nNumOfVerticesPerParticle, Usage::Dynamic);
	}
}

SPK_PLBuffer::~SPK_PLBuffer()
{
	// Cleanup
	if (m_pIndexBuffer)
		delete m_pIndexBuffer;
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}

/**
*  @brief
*    Returns the index buffer
*/
IndexBuffer *SPK_PLBuffer::GetIndexBuffer() const
{
	return m_pIndexBuffer;
}

/**
*  @brief
*    Returns the vertex buffer
*/
VertexBuffer *SPK_PLBuffer::GetVertexBuffer() const
{
	return m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Private virtual SPK::Buffer functions                 ]
//[-------------------------------------------------------]
void SPK_PLBuffer::swap(size_t index0, size_t index1)
{
	// [TODO] Implement me, although it looks like that this method is not really used...
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of PLBufferCreator
*/
PLBufferCreator::PLBufferCreator(Renderer &cRenderer, uint32 nNumOfVerticesPerParticle, uint32 nNumOfIndicesPerParticle, SPK::TexturingMode nTexturingMode) :
	m_pRenderer(&cRenderer),
	m_nNumOfVerticesPerParticle(nNumOfVerticesPerParticle),
	m_nNumOfIndicesPerParticle(nNumOfIndicesPerParticle),
	m_nTexturingMode(nTexturingMode)
{
}


//[-------------------------------------------------------]
//[ Private virtual SPK::BufferCreator functions          ]
//[-------------------------------------------------------]
SPK::Buffer *PLBufferCreator::createBuffer(size_t nbParticles, const SPK::Group &group) const
{
	return new SPK_PLBuffer(*m_pRenderer, m_nNumOfVerticesPerParticle, m_nNumOfIndicesPerParticle, m_nTexturingMode, static_cast<uint32>(nbParticles));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
