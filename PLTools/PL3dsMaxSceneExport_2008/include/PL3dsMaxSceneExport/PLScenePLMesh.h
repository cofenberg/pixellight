/*********************************************************\
 *  File: PLScenePLMesh.h                                *
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


#ifndef __PL_SCENEPLMESH_H__
#define __PL_SCENEPLMESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stack>
#include "PL3dsMaxSceneExport/PLSceneMesh.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight mesh
*/
class PLScenePLMesh : public PLSceneMesh {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		typedef std::stack<PLMesh::MeshFile::Chunk> ChunkStack;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScene
		*    Scene this mesh is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this mesh
		*/
		PLScenePLMesh(PLScene &cScene, IGameNode &cIGameNode, const std::string &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLScenePLMesh();

		/**
		*  @brief
		*    Saves the mesh
		*
		*  @param[in] sApplicationDrive
		*    Application drive
		*  @param[in] sApplicationDir
		*    Application directory
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Save(const std::string &sApplicationDrive, const std::string &sApplicationDir);

		// File saving
		bool WriteMeshFile(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMaterials(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMesh(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteLODLevel(FILE &cFile, ChunkStack &cChunkStack, int nLODLevel);
		bool WriteIndexBuffer(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteGeometry(FILE &cFile, ChunkStack &cChunkStack, int nGeometry);
		bool WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack, morphChannel &cMorphChannel);
		bool WritePointCacheMorphTargets(FILE &cFile, ChunkStack &cChunkStack, PLGeneral::File &cPointCacheFile);
		bool WriteWeight(FILE &cFile, ChunkStack &cChunkStack, const Weight &cWeight);
		bool WriteVertexWeights(FILE &cFile, ChunkStack &cChunkStack, const Vertex &cVertex, int nWeights);
		bool WriteVertexBuffer(FILE &cFile, ChunkStack &cChunkStack, int nVertexBuffer);
		bool WriteVertexBufferMorph(FILE &cFile, ChunkStack &cChunkStack, std::vector<Point3*> &lstPoints);
		bool WriteVertexAttribute(FILE &pFile, ChunkStack &cChunkStack, int nVertexAttribute);
		bool WriteSkeleton(FILE &pFile, ChunkStack &cChunkStack);
		bool WriteMeshBoundingBox(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMorphTargetAnimation(FILE &cFile, ChunkStack &cChunkStack);
		bool WritePointCacheAnimation(FILE &cFile, ChunkStack &cChunkStack, Animation &cAnimation);
		bool WriteAnimations(FILE &cFile, ChunkStack &cChunkStack);
		bool BeginChunk(FILE &cFile, ChunkStack &cChunkStack, PLGeneral::uint32 nType);
		bool EndChunk(FILE &cFile, ChunkStack &cChunkStack);
		bool Write(FILE &cFile, void *pBuffer, ULONG nSize);
		void GetChunkString(PLGeneral::uint32 nType, char szString[]);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::Array<Animation*> m_lstPointCacheAnimations;	/**< Internal point cache animation list */


};


#endif // __PL_SCENEPLMESH_H__
