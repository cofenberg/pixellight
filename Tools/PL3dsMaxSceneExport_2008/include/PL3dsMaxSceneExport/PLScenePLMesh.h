/*********************************************************\
 *  File: PLScenePLMesh.h                                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
namespace PLCore {
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
		PLScenePLMesh(PLScene &cScene, IGameNode &cIGameNode, const PLCore::String &sName);

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
		bool Save(const PLCore::String &sApplicationDrive, const PLCore::String &sApplicationDir);

		// File saving
		bool WriteMeshFile(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMaterials(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMesh(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteLODLevel(FILE &cFile, ChunkStack &cChunkStack, int nLODLevel);
		bool WriteIndexBuffer(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteGeometry(FILE &cFile, ChunkStack &cChunkStack, int nGeometry);
		bool WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack);
		bool WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack, morphChannel &cMorphChannel);
		bool WritePointCacheMorphTargets(FILE &cFile, ChunkStack &cChunkStack, PLCore::File &cPointCacheFile);
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
		bool BeginChunk(FILE &cFile, ChunkStack &cChunkStack, PLCore::uint32 nType);
		bool EndChunk(FILE &cFile, ChunkStack &cChunkStack);
		bool Write(FILE &cFile, void *pBuffer, ULONG nSize);
		void GetChunkString(PLCore::uint32 nType, char szString[]);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<Animation*> m_lstPointCacheAnimations;	/**< Internal point cache animation list */


};


#endif // __PL_SCENEPLMESH_H__
