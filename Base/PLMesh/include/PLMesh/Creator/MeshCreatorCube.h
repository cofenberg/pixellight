/*********************************************************\
 *  File: MeshCreatorCube.h                              *
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


#ifndef __PLMESH_MESHCREATOR_CUBE_H__
#define __PLMESH_MESHCREATOR_CUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLMesh/Creator/MeshCreator.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cube mesh creator class
*
*  @note
*    - If texture coordinates are generated each side has its own vertices
*    - Order of the materials of MultiMaterials is true:
*      x-positive (0), x-negative (1), y-positive (2),
*      y-negative (3), z-positive (4), z-negative (5)
*/
class MeshCreatorCube : public MeshCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshCreatorCube, "PLMesh", PLMesh::MeshCreator, "Cube mesh creator class")
		// Attributes
		pl_attribute(Dimension,			PLMath::Vector3,	PLMath::Vector3(0.5f, 0.5f, 0.5f),	ReadWrite,	DirectValue,	"Cube dimension",							"")
		pl_attribute(MultiMaterials,	bool,				false,								ReadWrite,	DirectValue,	"Should each side has it's own material?",	"")
		pl_attribute(Offset,			PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Offset to center",							"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshCreatorCube();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshCreatorCube();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Sets the four normal vectors of a cube side
		*
		*  @param[in] cVertexBuffer
		*    Vertex buffer to use
		*  @param[in] nSide
		*    Cube side
		*  @param[in] fX
		*    X component of the normal vector
		*  @param[in] fY
		*    Y component of the normal vector
		*  @param[in] fZ
		*    Z component of the normal vector
		*/
		void SetNormals(PLRenderer::VertexBuffer &cVertexBuffer, PLCore::uint32 nSide, float fX, float fY, float fZ) const;


	//[-------------------------------------------------------]
	//[ Private virtual MeshCreator functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual Mesh *Create(Mesh &cMesh, PLCore::uint32 nLODLevel = 0, bool bStatic = true) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHCREATOR_CUBE_H__
