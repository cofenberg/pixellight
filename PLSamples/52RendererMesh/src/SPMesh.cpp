/*********************************************************\
 *  File: SPMesh.cpp                                     *
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
#include <PLMesh/MeshManager.h>
#include "SPMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLRenderer;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPMesh)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPMesh::SPMesh(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_fRotation(0.0f),
	m_pMeshManager(new MeshManager(GetRenderer())),
	m_pMeshHandler(new MeshHandler())
{
	// Get/create the 'teapot'-mesh
	m_pMeshHandler->SetMesh(m_pMeshManager->CreateMesh("PLMesh::MeshCreatorTeapot", true, ""));
}

/**
*  @brief
*    Destructor
*/
SPMesh::~SPMesh()
{
	// Destroy our mesh handler
	delete m_pMeshHandler;

	// Destroy our mesh manager
	delete m_pMeshManager;
}
