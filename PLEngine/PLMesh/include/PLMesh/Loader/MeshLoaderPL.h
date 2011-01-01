/*********************************************************\
 *  File: MeshLoaderPL.h                                 *
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


#ifndef __PLMESH_MESHLOADER_PL_H__
#define __PLMESH_MESHLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLMesh/Loader/MeshFile.h"
#include "PLMesh/Loader/MeshLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	template <class AType> class Stack;
}
namespace PLRenderer {
	class IndexBuffer;
}
namespace PLMesh {
	class Weight;
	class Skeleton;
	class Geometry;
	class MeshLODLevel;
	class VertexWeights;
	class MeshMorphTarget;
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
*    Mesh loader implementation for the PixelLight mesh binary (Little-Endian) file format
*/
class MeshLoaderPL : public MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshLoaderPL, "PLMesh", PLMesh::MeshLoader, "Mesh loader implementation for the PixelLight mesh binary (Little-Endian) file format")
		pl_properties
			pl_property("Formats",	"mesh,MESH")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, Mesh&, PLGeneral::File&, "Load method. The loaded mesh is static.", "")
		pl_method_3(LoadParams, bool, Mesh&, PLGeneral::File&, bool, "Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.", "")
		pl_method_2(Save, bool, Mesh&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API bool Load(Mesh &cMesh, PLGeneral::File &cFile);
		PLMESH_API bool LoadParams(Mesh &cMesh, PLGeneral::File &cFile, bool bStatic);
		PLMESH_API bool Save(Mesh &cMesh, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshLoaderPL();


	//[-------------------------------------------------------]
	//[ File loading                                          ]
	//[-------------------------------------------------------]
	private:
		// File loading
		bool ReadMeshFile(Mesh &cMesh, PLGeneral::File &cFile, MeshFile::Chunk &cChunk, bool bStatic) const;
		bool ReadMaterials(Mesh &cMesh, PLGeneral::File &cFile) const;
		bool ReadMesh(Mesh &cMesh, PLGeneral::File &cFile, bool bStatic) const;
		bool ReadLODLevel(PLGeneral::File &cFile, MeshLODLevel &cLODLevel, bool bStatic) const;
		bool ReadIndexBuffer(PLGeneral::File &cFile, PLRenderer::IndexBuffer &cIndexBuffer, bool bStatic) const;
		bool ReadGeometry(PLGeneral::File &cFile, Geometry &cGeometry) const;
		bool ReadWeight(PLGeneral::File &cFile, Weight &cWeight) const;
		bool ReadVertexWeights(PLGeneral::File &cFile, VertexWeights &cVertexWeights) const;
		bool ReadMorphTarget(PLGeneral::File &cFile, MeshMorphTarget &cMorphTarget, bool bStatic) const;
		bool ReadVertexBuffer(PLGeneral::File &cFile, PLRenderer::VertexBuffer &cVertexBuffer, PLGeneral::uint32 nIndex, bool bStatic) const;
		bool ReadVertexAttribute(PLGeneral::File &cFile, PLRenderer::VertexBuffer &cVertexBuffer) const;
		bool ReadSkeleton(Mesh &cMesh, PLGeneral::File &cFile) const;
		bool ReadAnchorPoints(Mesh &cMesh, PLGeneral::File &cFile) const;
		bool ReadAnimations(PLGeneral::File &cFile) const;
		bool ReadMorphTargetAnimation(Mesh &cMesh, PLGeneral::File &cFile) const;
		bool ReadMeshBoundingBox(Mesh &cMesh, PLGeneral::File &cFile) const;

		// Tools
		MeshFile::Chunk ReadChunk(PLGeneral::File &cFile) const;


	//[-------------------------------------------------------]
	//[ File saving                                           ]
	//[-------------------------------------------------------]
	private:
		// File saving
		bool WriteMeshFile(Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
		bool WriteMaterials(const Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
		bool WriteMesh(Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
		bool WriteLODLevel(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, MeshLODLevel &cLODLevel) const;
		bool WriteIndexBuffer(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, PLRenderer::IndexBuffer &cIndexBuffer) const;
		bool WriteGeometry(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, const Geometry &cGeometry) const;
		bool WriteWeight(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, const Weight &cWeight) const;
		bool WriteVertexWeights(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, VertexWeights &cVertexWeights) const;
		bool WriteMorphTarget(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, MeshMorphTarget &cMorphTarget) const;
		bool WriteVertexBuffer(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, PLRenderer::VertexBuffer &cVertexBuffer) const;
		bool WriteVertexAttribute(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, const PLRenderer::VertexBuffer::Attribute &cVertexAttribute) const;
		bool WriteSkeleton(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, Skeleton &cSkeleton) const;
		bool WriteAnchorPoints(Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
// [TODO] Update this
//		bool WriteAnimations(const Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
		bool WriteMorphTargetAnimation(Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, PLGeneral::uint32 nAnimation) const;
		bool WriteMeshBoundingBox(const Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;

		// Tools
		bool BeginChunk(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack, PLGeneral::uint32 nType) const;
		bool EndChunk(PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHLOADER_PL_H__
