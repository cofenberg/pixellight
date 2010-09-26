/*********************************************************\
 *  File: FullscreenQuad.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLScene/Compositing/FullscreenQuad.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FullscreenQuad::FullscreenQuad(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pVertexBuffer(NULL)
{
}

/**
*  @brief
*    Destructor
*/
FullscreenQuad::~FullscreenQuad()
{
	// Destroy the vertex buffer
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}

/**
*  @brief
*    Returns the vertex buffer of this fullscreen quad
*/
VertexBuffer *FullscreenQuad::GetVertexBuffer()
{
	// Initialize vertex buffer
	if (!m_pVertexBuffer) {
		// Create the vertex buffer
		m_pVertexBuffer = m_pRenderer->CreateVertexBuffer();

		// Add vertex position attribute to the vertex buffer, zw stores the texture coordinate
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float4);

		// Allocate
		m_pVertexBuffer->Allocate(4);

		// Fill
		if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Vertex 0 - lower/left corner
			// Position
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
			pfVertex[Vector4::X] = -1.0f;
			pfVertex[Vector4::Y] = -1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  0.0f;
			pfVertex[Vector4::W] =  0.0f;

		// Vertex 1 - lower/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position);
			pfVertex[Vector4::X] =  1.0f;
			pfVertex[Vector4::Y] = -1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  1.0f;
			pfVertex[Vector4::W] =  0.0f;

		// Vertex 2 - upper/left corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position);
			pfVertex[Vector4::X] = -1.0f;
			pfVertex[Vector4::Y] =  1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  0.0f;
			pfVertex[Vector4::W] =  1.0f;

		// Vertex 3 - upper/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position);
			pfVertex[Vector4::X] = 1.0f;
			pfVertex[Vector4::Y] = 1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;

			// Unlock the vertex buffer
			m_pVertexBuffer->Unlock();
		}
	}

	// Return the vertex buffer
	return m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
