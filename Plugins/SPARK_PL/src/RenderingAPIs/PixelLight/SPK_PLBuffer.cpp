/*********************************************************\
 *  File: SPK_PLBuffer.cpp                               *
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
	return new SPK_PLBuffer(*m_pRenderer, m_nNumOfVerticesPerParticle, m_nNumOfIndicesPerParticle, m_nTexturingMode, nbParticles);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
