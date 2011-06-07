/*********************************************************\
 *  File: MeshLoaderPLXml.h                              *
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


#ifndef __PLMESH_MESHLOADER_PLXML_H__
#define __PLMESH_MESHLOADER_PLXML_H__
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
*    Mesh loader implementation for the PixelLight mesh XML file format
*/
class MeshLoaderPLXml : public MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshLoaderPLXml, "PLMesh", PLMesh::MeshLoader, "Mesh loader implementation for the PixelLight mesh XML file format")
		// Properties
		pl_properties
			pl_property("Formats",	"xmesh,XMESH")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		bool,	Mesh&,	PLGeneral::File&,			"Load method. The loaded mesh is static.",															"")
		pl_method_3(LoadParams,	bool,	Mesh&,	PLGeneral::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.",	"")
		pl_method_2(Save,		bool,	Mesh&,	PLGeneral::File&,			"Save method",																						"")
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
		PLMESH_API MeshLoaderPLXml();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshLoaderPLXml();


	//[-------------------------------------------------------]
	//[ File loading                                          ]
	//[-------------------------------------------------------]
	private:
		// File loading
		bool LoadV1(Mesh &cMesh, const PLGeneral::XmlElement &cMeshElement, bool bStatic) const;
		bool ReadMaterials(Mesh &cMesh, const PLGeneral::XmlElement &cMaterialsElement) const;
		bool ReadLODLevels(Mesh &cMesh, const PLGeneral::XmlElement &cLODLevelsElement, bool bStatic) const;
		bool ReadLODLevel(MeshLODLevel &cLODLevel, const PLGeneral::XmlElement &cLODLevelElement, bool bStatic) const;
		bool ReadIndexBuffer(PLRenderer::IndexBuffer &cIndexBuffer, const PLGeneral::XmlElement &cIndexBufferElement, bool bStatic) const;
		bool ReadGeometry(Geometry &cGeometry, const PLGeneral::XmlElement &cGeometryElement) const;
		bool ReadMorphTargets(Mesh &cMesh, const PLGeneral::XmlElement &cMorphTargetsElement, bool bStatic) const;
		bool ReadMorphTarget(MeshMorphTarget &cMorphTarget, const PLGeneral::XmlElement &cMorphTargetElement, bool bStatic) const;
		bool ReadVertexBuffer(PLRenderer::VertexBuffer &cVertexBuffer, PLGeneral::uint32 nIndex, const PLGeneral::XmlElement &cVertexBufferElement, bool bStatic) const;
		bool ReadVertexAttribute(PLRenderer::VertexBuffer &cVertexBuffer, const PLGeneral::XmlElement &cVertexAttributeElement) const;
		bool ReadWeights(Mesh &cMesh, const PLGeneral::XmlElement &cWeightsElement) const;
		bool ReadVertexWeightsContainer(Mesh &cMesh, const PLGeneral::XmlElement &cVertexWeightsContainerElement) const;
		bool ReadSkeletons(Mesh &cMesh, const PLGeneral::XmlElement &cSkeletonsElement) const;
		bool ReadSkeleton(Mesh &cMesh, const PLGeneral::XmlElement &cSkeletonElement) const;
		bool ReadAnchorPoints(Mesh &cMesh, const PLGeneral::XmlElement &cAnchorPointsElement) const;
		bool ReadAnimations(PLGeneral::File &cFile) const;
		bool ReadMorphTargetAnimations(Mesh &cMesh, const PLGeneral::XmlElement &cMorphTargetAnimationsElement) const;
		bool ReadMorphTargetAnimation(Mesh &cMesh, const PLGeneral::XmlElement &cMorphTargetElement) const;
		bool ReadMeshBoundingBox(Mesh &cMesh, const PLGeneral::XmlElement &cBoundingBoxElement) const;


	//[-------------------------------------------------------]
	//[ File saving                                           ]
	//[-------------------------------------------------------]
	private:
		// File saving
		bool WriteMeshFile(Mesh &cMesh, PLGeneral::XmlElement &cMeshElement) const;
		bool WriteMaterials(const Mesh &cMesh, PLGeneral::XmlElement &cMeshElement) const;
		bool WriteMesh(Mesh &cMesh, PLGeneral::XmlElement &cMeshElement) const;
		bool WriteLODLevel(MeshLODLevel &cLODLevel, PLGeneral::uint32 nID, PLGeneral::XmlElement &cLODLevelsElement) const;
		bool WriteIndexBuffer(PLRenderer::IndexBuffer &cIndexBuffer, PLGeneral::XmlElement &cLODLevelElement) const;
		bool WriteGeometry(const Geometry &cGeometry, PLGeneral::uint32 nID, PLGeneral::XmlElement &cGeometriesElement) const;
		bool WriteWeight(const Weight &cWeight, PLGeneral::uint32 nID, PLGeneral::XmlElement &cWeightsElement) const;
		bool WriteVertexWeights(VertexWeights &cVertexWeights, PLGeneral::uint32 nID, PLGeneral::XmlElement &cVertexWeightsElement) const;
		bool WriteMorphTarget(MeshMorphTarget &cMorphTarget, PLGeneral::uint32 nID, PLGeneral::XmlElement &cMorphTargetsElement) const;
		bool WriteVertexBuffer(PLRenderer::VertexBuffer &cVertexBuffer, PLGeneral::uint32 nID, PLGeneral::XmlElement &pVertexBuffersElement) const;
		bool WriteVertexAttribute(const PLRenderer::VertexBuffer::Attribute &cVertexAttribute, PLGeneral::uint32 nID, PLGeneral::XmlElement &cVertexAttributesElement) const;
		bool WriteSkeleton(Skeleton &cSkeleton, PLGeneral::uint32 nID, PLGeneral::XmlElement &cSkeletonsElement) const;
		bool WriteAnchorPoints(Mesh &cMesh, PLGeneral::XmlElement &cMeshElement) const;
// [TODO] Update this
//		bool WriteAnimations(const Mesh &cMesh, PLGeneral::File &cFile, PLGeneral::Stack<MeshFile::Chunk> &cChunkStack) const;
		bool WriteMorphTargetAnimation(Mesh &cMesh, PLGeneral::uint32 nAnimation, PLGeneral::XmlElement &cMorphTargetAnimationsElement) const;
		bool WriteMeshBoundingBox(const Mesh &cMesh, PLGeneral::XmlElement &cMeshElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHLOADER_PLXML_H__
