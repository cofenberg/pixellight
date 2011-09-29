/*********************************************************\
 *  File: AssimpMeshLoader.h                             *
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


#ifndef __PLASSIMP_ASSIMPMESHLOADER_H__
#define __PLASSIMP_ASSIMPMESHLOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Geometry.h>
#include "PLAssimp/AssimpLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct aiNode;
struct aiScene;
struct aiMatrix4x4;
namespace PLCore {
	class File;
}
namespace PLMesh {
	class Mesh;
}
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader using Assimp
*/
class AssimpMeshLoader : public AssimpLoader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		AssimpMeshLoader();

		/**
		*  @brief
		*    Destructor
		*/
		~AssimpMeshLoader();

		/**
		*  @brief
		*    Loads the mesh
		*
		*  @param[in,out] cMesh
		*    Mesh to fill
		*  @param[in]     cFile
		*    File to load from, must be opened and readable
		*  @param[in]     bStatic
		*    'true' if the mesh is static, else 'false'
		*  @param[in]     sHint
		*    Filename extension hint for Assimp, if empty string (e.g. load from memory), the filename
		*    extension (if there's one) of the used file will be given to Assimp
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Load(PLMesh::Mesh &cMesh, PLCore::File &cFile, bool bStatic, const PLCore::String &sHint = "");


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		static const PLCore::uint32 MaxNumOfTextureCoords = 0x4;	/**< Supported number of texture coord sets (UV(W) channels) - same as AI_MAX_NUMBER_OF_TEXTURECOORDS */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Adds the materials
		*/
		void AddMaterials();

		/**
		*  @brief
		*    Gets the total number of vertices and indices required for everything as one PixelLight mesh recursively
		*
		*  @param[in]  cAssimpNode
		*    Assimp node to gather the data from
		*  @param[out] nNumOfVertices
		*    Receives the number of vertices
		*  @param[out] nNumOfIndices
		*    Receives the number of indices
		*/
		void GetNumOfVerticesAndIndicesRec(const aiNode &cAssimpNode, PLCore::uint32 &nNumOfVertices, PLCore::uint32 &nNumOfIndices);

		/**
		*  @brief
		*    Fills the mesh data recursively
		*
		*  @param[in]  cAssimpNode
		*    Assimp node to gather the data from
		*  @param[in]  cVertexBuffer
		*    Vertex buffer to fill
		*  @param[in]  cIndexBuffer
		*    Index buffer to fill
		*  @param[in]  lstGeometries
		*    Geometries to fill
		*  @param[in]  mAssimpTransformation
		*    Current absolute Assimp transformation matrix (local to global space)
		*  @param[out] nNumOfVertices
		*    Receives the number of processed vertices
		*  @param[out] nNumOfIndices
		*    Receives the number of processed indices
		*/
		void FillMeshRec(const aiNode &cAssimpNode, PLRenderer::VertexBuffer &cVertexBuffer, PLRenderer::IndexBuffer &cIndexBuffer, PLCore::Array<PLMesh::Geometry> &lstGeometries,
						 const aiMatrix4x4 &mAssimpTransformation, PLCore::uint32 &nNumOfVertices, PLCore::uint32 &nNumOfIndices);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMesh::Mesh  *m_pMesh;										/**< Mesh to fill, can be a null pointer */
		const aiScene *m_pAssimpScene;								/**< Used Assimp scene, can be a null pointer */
		bool		   m_bHasNormals;								/**< Are there normals? */
		bool		   m_bHasTangentsAndBitangents;					/**< Are there tangents and bitangents? */
		bool		   m_bHasTexCoords;								/**< Are there texture coordinates? */
		unsigned int   m_nNumUVComponents[MaxNumOfTextureCoords];	/**< Specifies the number of components for a given UV channel (see aiMesh for details) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_ASSIMPMESHLOADER_H__
