/*********************************************************\
 *  File: MeshLoaderX.h                                  *
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


#ifndef __PLDEFAULTFILEFORMATS_DIRECTX_MESHLOADER_X_H__
#define __PLDEFAULTFILEFORMATS_DIRECTX_MESHLOADER_X_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/MeshLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Matrix4x4;
}
namespace PLDefaultFileFormats {
	class XNode;
	class XMesh;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader implementation for the x-format (DirectX)
*
*  @note
*    - All single meshes are combined to ONE mesh
*/
class MeshLoaderX : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderX, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for the x-format (DirectX)")
		pl_properties
			pl_property("Formats",	"x")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLMesh::Mesh&, PLGeneral::File&, "Load method. The loaded mesh is static.", "")
		pl_method_3(LoadParams, bool, PLMesh::Mesh&, PLGeneral::File&, bool, "Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.", "")
		pl_method_2(Save, bool, PLMesh::Mesh&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);
		bool LoadParams(PLMesh::Mesh &cMesh, PLGeneral::File &cFile, bool bStatic);
		bool Save(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshLoaderX();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderX();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Processes a block of DirectX nodes
		*
		*  @param[out] cMesh
		*    Mesh to load into
		*  @param[in]  pXNode
		*    Current X node, can be NULL
		*  @param[in]  mTransform
		*    Current transform matrix
		*  @param[in]  nVertexOffset
		*    Vertex offset
		*  @param[in]  nIndexOffset
		*    Index offset
		*  @param[out] lstXMeshes
		*    List of XMeshes
		*/
		void ProcessNodes(PLMesh::Mesh &cMesh, XNode *pXNode, const PLMath::Matrix4x4 &mTransform, PLGeneral::uint32 &nVertexOffset, PLGeneral::uint32 &nIndexOffset,
						  PLGeneral::Array<XMesh*> &lstXMeshes) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DIRECTX_MESHLOADER_X_H__
