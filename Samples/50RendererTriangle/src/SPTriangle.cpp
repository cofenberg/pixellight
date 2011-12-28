/*********************************************************\
 *  File: SPTriangle.cpp                                 *
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
#include <PLMath/Half.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "SPTriangle.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPTriangle)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTriangle::SPTriangle(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_pVertexBuffer(GetRenderer().CreateVertexBuffer()),
	m_fRotation(0.0f)
{
	// Setup the renderer vertex buffer for our triangle
	if (m_pVertexBuffer) {
		// Tell the vertex buffer that it has to provide vertex position data. Each
		// vertex position has three floating point components. (x/y/z)
		// -> First try efficient "half" (16 bit floating point) as data type, if this fails fall back to traditional more expensive "float" (32 bit floating point)
		// -> This is just an example. Because the half data type is no primitive C++ data type there's a CPU conversion overhead you may
		//    want to avoid in case it's not worth the effort... like when only drawing a simple triangle... as mentioned, this is just an example.
		bool bPositionHalf = true;
		if (!m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Half3)) {
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
			bPositionHalf = false;
		}

		// There should also be a color value per vertex. Note that the internal representation
		// depends on the used renderer implementation.
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Color, 0, VertexBuffer::RGBA);

		// Now that we have added all desired vertex attributes, allocate the buffer. We want to have
		// three vertices (for each corner of the triangle) and the usage of the buffer is considered
		// to be static - this means that the content of the vertex buffer isn't changed during runtime.
		// In fact this data CAN be changed at any time, but this isn't that performant and you should
		// avoid this whenever possible!
		m_pVertexBuffer->Allocate(3, Usage::Static);

		// Setup the vertex buffer data. We have to lock our buffer before we are able to manipulate it.
		if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Here we request a pointer to the given attribute of a certain vertex to fill it
			// with our data. If possible, you should always use the provided GetData(<VertexID>, <SEMANTIC>, <CHANNEL>)
			// and SetColor() functions to ensure that you put the data at the correct position into the buffer. For
			// instance the color value can have a different size on different renderer implementations! For
			// security we check the pointer given by GetData() for a null pointer, but normally that's not required.

			// Setup vertex color
			m_pVertexBuffer->SetColor(0, Color4::Red);
			m_pVertexBuffer->SetColor(1, Color4::Green);
			m_pVertexBuffer->SetColor(2, Color4::Blue);

			// Check the used data type for the vertex position
			if (bPositionHalf) {
				// Setup vertex 0
				uint16 *pnVertex = static_cast<uint16*>(m_pVertexBuffer->GetData(0, VertexBuffer::Position));
				if (pnVertex) {
					pnVertex[0] = Half::Zero;
					pnVertex[1] = Half::One;
					pnVertex[2] = Half::Zero;
				}

				// Setup vertex 1
				pnVertex = static_cast<uint16*>(m_pVertexBuffer->GetData(1, VertexBuffer::Position));
				if (pnVertex) {
					pnVertex[0] = Half::FromFloat(-1.0f);
					pnVertex[1] = Half::FromFloat(-1.0f);
					pnVertex[2] = Half::Zero;
				}

				// Setup vertex 2
				pnVertex = static_cast<uint16*>(m_pVertexBuffer->GetData(2, VertexBuffer::Position));
				if (pnVertex) {
					pnVertex[0] = Half::One;
					pnVertex[1] = Half::FromFloat(-1.0f);
					pnVertex[2] = Half::Zero;
				}
			} else {
				// Setup vertex 0
				float *pfVertex = static_cast<float*>(m_pVertexBuffer->GetData(0, VertexBuffer::Position));
				if (pfVertex) {
					pfVertex[0] = 0.0f;
					pfVertex[1] = 1.0f;
					pfVertex[2] = 0.0f;
				}

				// Setup vertex 1
				pfVertex = static_cast<float*>(m_pVertexBuffer->GetData(1, VertexBuffer::Position));
				if (pfVertex) {
					pfVertex[0] = -1.0f;
					pfVertex[1] = -1.0f;
					pfVertex[2] =  0.0f;
				}

				// Setup vertex 2
				pfVertex = static_cast<float*>(m_pVertexBuffer->GetData(2, VertexBuffer::Position));
				if (pfVertex) {
					pfVertex[0] =  1.0f;
					pfVertex[1] = -1.0f;
					pfVertex[2] =  0.0f;
				}
			}

			// Now that we have filled the buffer with our data, unlock it. Locked buffers
			// CANNOT be used for rendering!
			m_pVertexBuffer->Unlock();
		}
	} else {
		// THIS should never, never happen! :)
	}
}

/**
*  @brief
*    Destructor
*/
SPTriangle::~SPTriangle()
{
	// Destroy our renderer vertex buffer (we will miss it ;-)
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}
