/*********************************************************\
 *  File: SRPDeferred.cpp                                *
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
#include <PLMath/Vector2.h>
#include <PLMath/Vector4.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferred)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the first found instance of a SRPDeferredGBuffer scene renderer pass instance within the scene renderer pipeline
*/
SRPDeferredGBuffer *SRPDeferred::GetGBuffer() const
{
	static const String sClassName = "PLCompositing::SRPDeferredGBuffer";
	return (SRPDeferredGBuffer*)GetFirstInstanceOfSceneRendererPassClass(sClassName);
}

/**
*  @brief
*    Returns the vertex buffer of this deferred scene renderer pass
*/
VertexBuffer *SRPDeferred::GetVertexBuffer()
{
	// Initialize vertex buffer
	if (!m_pVertexBuffer) {
		// Get the renderer instance
		Renderer *pRenderer = GetRenderer();
		if (pRenderer) {
			// Create the vertex buffer
			m_pVertexBuffer = pRenderer->CreateVertexBuffer();

			// Add vertex position attribute to the vertex buffer
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float4);

			// Add texture coordinate attribute to the vertex buffer
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);

			// Allocate
			m_pVertexBuffer->Allocate(4);

			// Fill
			if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex 0 - lower/left corner
				// Position
				float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
				pfVertex[Vector4::X] = -1.0f;
				pfVertex[Vector4::Y] = -1.0f;
				pfVertex[Vector4::Z] =  0.0f;
				pfVertex[Vector4::W] =  1.0f;
				// Texture coordinate 0
				pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::TexCoord, 0);
				pfVertex[Vector2::X] = 0.0f;
				pfVertex[Vector2::Y] = 0.0f;

			// Vertex 1 - lower/right corner
				// Position
				pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position);
				pfVertex[Vector4::X] =  1.0f;
				pfVertex[Vector4::Y] = -1.0f;
				pfVertex[Vector4::Z] =  0.0f;
				pfVertex[Vector4::W] =  1.0f;
				// Texture coordinate 0
				pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord, 0);
				pfVertex[Vector2::X] = 1.0f;
				pfVertex[Vector2::Y] = 0.0f;

			// Vertex 2 - upper/left corner
				// Position
				pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position);
				pfVertex[Vector4::X] = -1.0f;
				pfVertex[Vector4::Y] =  1.0f;
				pfVertex[Vector4::Z] =  0.0f;
				pfVertex[Vector4::W] =  1.0f;
				// Texture coordinate 0
				pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord, 0);
				pfVertex[Vector2::X] = 0.0f;
				pfVertex[Vector2::Y] = 1.0f;

			// Vertex 3 - upper/right corner
				// Position
				pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position);
				pfVertex[Vector4::X] = 1.0f;
				pfVertex[Vector4::Y] = 1.0f;
				pfVertex[Vector4::Z] = 0.0f;
				pfVertex[Vector4::W] = 1.0f;
				// Texture coordinate 0
				pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord, 0);
				pfVertex[Vector2::X] = 1.0f;
				pfVertex[Vector2::Y] = 1.0f;

				// Unlock the vertex buffer
				m_pVertexBuffer->Unlock();
			}
		}
	}

	// Return the vertex buffer
	return m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SRPDeferred::SRPDeferred() :
	m_pVertexBuffer(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferred::~SRPDeferred()
{
	// Destroy the vertex buffer
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
