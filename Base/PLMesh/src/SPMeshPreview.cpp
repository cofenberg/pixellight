/*********************************************************\
 *  File: SPMeshPreview.cpp                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLMesh/MeshHandler.h"
#include "PLMesh/SPMeshPreview.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLMesh {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPMeshPreview)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPMeshPreview::SPMeshPreview(Renderer &cRenderer) : SPPreview(cRenderer),
	m_pMeshHandler(new MeshHandler())
{
}

/**
*  @brief
*    Destructor
*/
SPMeshPreview::~SPMeshPreview()
{
	delete m_pMeshHandler;
}

/**
*  @brief
*    Returns the used mesh
*/
Mesh *SPMeshPreview::GetMesh() const
{
	return m_pMeshHandler->GetMesh();
}

/**
*  @brief
*    Sets the used mesh
*/
void SPMeshPreview::SetMesh(Mesh *pMesh)
{
	m_pMeshHandler->SetMesh(pMesh);
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPMeshPreview::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Set all render states to known default settings
	cRenderer.Reset();

	// Clear the frame buffer
	cRenderer.Clear();

	// Get the used mesh
	const Mesh *pMesh = m_pMeshHandler->GetMesh();
	if (pMesh) {
		// [TODO] Draw the mesh
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
