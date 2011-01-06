/*********************************************************\
 *  File: SPTexturing.cpp                                 *
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
#include <PLGraphics/Image/Image.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "SPTexturing.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGraphics;
using namespace PLRenderer;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPTexturing)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTexturing::SPTexturing(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_pVertexBuffer(GetRenderer().CreateVertexBuffer()),
	m_pTextureBuffer(nullptr),
	m_fRotation(0.0f)
{
	// Setup the renderer vertex buffer for our quad
	if (m_pVertexBuffer) {
		// Tell the vertex buffer that it has to provide vertex position data. Each
		// vertex position has three floating point components. (x/y/z)
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);

		// There should also be a two component texture coordinate per vertex
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);

		// Now that we have added all desired vertex attributes, allocate the buffer. We want to have
		// four vertices (for each corner of the quad) and the usage of the buffer is considered
		// to be static - this means that the content of the vertex buffer isn't changed during runtime.
		// In fact this data CAN be changed at any time, but this isn't that performant and you should
		// avoid this whenever possible!
		m_pVertexBuffer->Allocate(4, Usage::Static);

		// Setup the vertex buffer data. We have to lock our buffer before we are able to manipulate it.
		if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Here we request a pointer to the given attribute of a certain vertex to fill it
			// with our data. If possible, you should always use the provided GetData(<VertexID>, <SEMANTIC>, <CHANNEL>)
			// and SetColor() functions to ensure that you put the data at the correct position into the buffer. For
			// instance the color value can have a different size on different renderer implementations! For
			// security we check the pointer given by GetData() for a null pointer, but normally that's not required.

			// Setup vertex 0
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
			if (pfVertex) {
				pfVertex[0] = -1.0f;
				pfVertex[1] =  1.0f;
				pfVertex[2] =  0.0f;
			}
			pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::TexCoord);
			if (pfVertex) {
				pfVertex[0] = 0.0f;
				pfVertex[1] = 0.0f;
			}

			// Setup vertex 1
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position);
			if (pfVertex) {
				pfVertex[0] = -1.0f;
				pfVertex[1] = -1.0f;
				pfVertex[2] =  0.0f;
			}
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord);
			if (pfVertex) {
				pfVertex[0] = 0.0f;
				pfVertex[1] = 1.0f;
			}

			// Setup vertex 2
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position);
			if (pfVertex) {
				pfVertex[0] = 1.0f;
				pfVertex[1] = 1.0f;
				pfVertex[2] = 0.0f;
			}
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord);
			if (pfVertex) {
				pfVertex[0] = 1.0f;
				pfVertex[1] = 0.0f;
			}

			// Setup vertex 3
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position);
			if (pfVertex) {
				pfVertex[0] =  1.0f;
				pfVertex[1] = -1.0f;
				pfVertex[2] =  0.0f;
			}
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord);
			if (pfVertex) {
				pfVertex[0] = 1.0f;
				pfVertex[1] = 1.0f;
			}

			// Now that we have filled the buffer with our data, unlock it. Locked buffers
			// CANNOT be used for rendering!
			m_pVertexBuffer->Unlock();
		}
	} else {
		// THIS should never, never happen! :)
	}

	{ // Setup the renderer texture buffer for our quad
		// Load in the image we want to use as texture
		Image cImage;
		if (cImage.Load("Data/Textures/PLLogo.dds")) {	// Within "Runtime/Data/Standard.zip"
			// Create the texture buffer instance by using our image data
			m_pTextureBuffer = (TextureBuffer*)GetRenderer().CreateTextureBuffer2D(cImage);
		}
	}
}

/**
*  @brief
*    Destructor
*/
SPTexturing::~SPTexturing()
{
	// Destroy our renderer vertex buffer (we will miss it ;-)
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;

	// Destroy the texture buffer
	if (m_pTextureBuffer)
		delete m_pTextureBuffer;
}
