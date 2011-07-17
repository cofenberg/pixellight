/*********************************************************\
 *  File: MeshCreator.cpp                                *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLMesh/Mesh.h"
#include "PLMesh/Creator/MeshCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMesh {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshCreator)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshCreator::MeshCreator() :
	DrawStyle(this),
	Order(this),
	TexCoords(this),
	Normals(this),
	Material(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshCreator::~MeshCreator()
{
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a mesh
*/
Mesh *MeshCreator::Create(Mesh &cMesh, uint32 nLODLevel, bool bStatic) const
{
	// Set material
	PLRenderer::Material *pMaterial = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().LoadResource(Material);
	if (pMaterial)
		cMesh.SetMaterial(0, pMaterial);

	// Return the mesh
	return &cMesh;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
