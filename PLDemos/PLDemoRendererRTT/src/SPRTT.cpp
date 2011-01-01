/*********************************************************\
 *  File: SPRTT.cpp                                      *
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
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLMesh/MeshManager.h>
#include "SPRTT.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPRTT)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPRTT::SPRTT(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_pMeshManager(new MeshManager(GetRenderer())),
	m_pMeshHandler(new MeshHandler()),
	m_pPositionVertexBuffer(NULL),
	m_pColorVertexBuffer(NULL),
	m_fRotation(0.0f)
{
	// Get/create the 'teapot' mesh
	m_pMeshHandler->SetMesh(m_pMeshManager->CreateMesh("PLMesh::MeshCreatorTeapot", true, ""));

	// Create the renderer vertex buffer for our triangle positions and texture coordinates
	m_pPositionVertexBuffer = cRenderer.CreateVertexBuffer();
	if (m_pPositionVertexBuffer) {
		// Add required vertex attributes
		m_pPositionVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		m_pPositionVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);

		// Allocate the vertex buffer
		m_pPositionVertexBuffer->Allocate(4, Usage::Static);
		
		// Setup the vertex buffer data
		if (m_pPositionVertexBuffer->Lock(Lock::WriteOnly)) {
			// Setup vertex 0
			float *pfVertex = (float*)m_pPositionVertexBuffer->GetData(0, VertexBuffer::Position);
			pfVertex[0] = -1.0f;
			pfVertex[1] = -1.0f;
			pfVertex[2] =  0.0f;
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(0, VertexBuffer::TexCoord);
			pfVertex[0] =  0.0f;
			pfVertex[1] =  0.0f;

			// Setup vertex 1
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(1, VertexBuffer::Position);
			pfVertex[0] =  1.0f;
			pfVertex[1] = -1.0f;
			pfVertex[2] =  0.0f;
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(1, VertexBuffer::TexCoord);
			pfVertex[0] = 1.0f;
			pfVertex[1] = 0.0f;

			// Setup vertex 2
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(2, VertexBuffer::Position);
			pfVertex[0] = -1.0f;
			pfVertex[1] =  1.0f;
			pfVertex[2] =  0.0f;
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(2, VertexBuffer::TexCoord);
			pfVertex[0] = 0.0f;
			pfVertex[1] = 1.0f;

			// Setup vertex 3
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(3, VertexBuffer::Position);
			pfVertex[0] = 1.0f;
			pfVertex[1] = 1.0f;
			pfVertex[2] = 0.0f;
			pfVertex    = (float*)m_pPositionVertexBuffer->GetData(3, VertexBuffer::TexCoord);
			pfVertex[0] = 1.0f;
			pfVertex[1] = 1.0f;

			// Unlock the vertex buffer
			m_pPositionVertexBuffer->Unlock();
		}
	} else {
		// THIS should never, never happen! :)
	}
	m_pColorVertexBuffer = cRenderer.CreateVertexBuffer();
	if (m_pColorVertexBuffer) {
		// Add required vertex attributes
		m_pColorVertexBuffer->AddVertexAttribute(VertexBuffer::Color, 0, VertexBuffer::RGBA);

		// Allocate the vertex buffer
		m_pColorVertexBuffer->Allocate(4, Usage::Static);

		// Setup the vertex buffer data
		if (m_pColorVertexBuffer->Lock(Lock::WriteOnly)) {
			// Setup vertex 0
			m_pColorVertexBuffer->SetColor(0, Color4::Red);

			// Setup vertex 1
			m_pColorVertexBuffer->SetColor(1, Color4::Green);

			// Setup vertex 2
			m_pColorVertexBuffer->SetColor(2, Color4::White);

			// Setup vertex 3
			m_pColorVertexBuffer->SetColor(3, Color4::Blue);

			// Unlock the vertex buffer
			m_pColorVertexBuffer->Unlock();
		}
	} else {
		// THIS should never, never happen! :)
	}
}

/**
*  @brief
*    Destructor
*/
SPRTT::~SPRTT()
{
	// Destroy our mesh handler
	delete m_pMeshHandler;

	// Destroy our mesh manager
	delete m_pMeshManager;

	// Destroy our renderer vertex buffer (we will miss it ;-)
	if (m_pPositionVertexBuffer)
		delete m_pPositionVertexBuffer;
	if (m_pColorVertexBuffer)
		delete m_pColorVertexBuffer;
}
