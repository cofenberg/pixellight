/*********************************************************\
 *  File: AssimpSceneLoader.h                            *
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


#ifndef __PLASSIMP_ASSIMPSCENELOADER_H__
#define __PLASSIMP_ASSIMPSCENELOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneLoader/SceneLoader.h>
#include "PLAssimp/AssimpLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct aiNode;
struct aiScene;
namespace PLCore {
	class File;
}
namespace PLScene {
	class SceneNode;
	class SceneContainer;
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
*    Scene loader using Assimp
*/
class AssimpSceneLoader : public AssimpLoader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		AssimpSceneLoader();

		/**
		*  @brief
		*    Destructor
		*/
		~AssimpSceneLoader();

		/**
		*  @brief
		*    Loads the scene
		*
		*  @param[in,out] cContainer
		*    Scene container to fill
		*  @param[in]     cFile
		*    File to load from, must be opened and readable
		*  @param[in]     sHint
		*    Filename extension hint for Assimp, if empty string (e.g. load from memory), the filename
		*    extension (if there's one) of the used file will be given to Assimp
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Load(PLScene::SceneContainer &cContainer, PLCore::File &cFile, const PLCore::String &sHint = "");


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
		*    Loads the scene recursively
		*
		*  @param[in] cParentContainer
		*    Current PixelLight parent scene container
		*  @param[in] cAssimpNode
		*    Current Assimp node
		*/
		void LoadRec(PLScene::SceneContainer &cParentContainer, const aiNode &cAssimpNode);

		/**
		*  @brief
		*    Loads the given Assimp node (not recursively)
		*
		*  @param[in] cParentContainer
		*    Current PixelLight parent scene container
		*  @param[in] cAssimpNode
		*    Assimp node to load
		*  @param[in] bSetTransformation
		*    Set PixelLight scene node transformation?
		*/
		void LoadNode(PLScene::SceneContainer &cParentContainer, const aiNode &cAssimpNode, bool bSetTransformation);

		/**
		*  @brief
		*    Set's the transformation (relative to the parent) of a PixelLight scene node by using a given Assimp node
		*
		*  @param[in] cSceneNode
		*    PixelLight scene node
		*  @param[in] cAssimpNode
		*    Assimp node
		*/
		void SetNodeTransformation(PLScene::SceneNode &cSceneNode, const aiNode &cAssimpNode) const;

		/**
		*  @brief
		*    Loads the mesh of the given Assimp node
		*
		*  @param[in] cAssimpNode
		*    Assimp node to load the mesh from
		*/
		void LoadMesh(const aiNode &cAssimpNode);

		/**
		*  @brief
		*    Gets the total number of vertices and indices required for everything within a given Assimp node as one PixelLight mesh
		*
		*  @param[in]  cAssimpNode
		*    Assimp node to gather the data from
		*  @param[out] nNumOfVertices
		*    Receives the number of vertices
		*  @param[out] nNumOfIndices
		*    Receives the number of indices
		*  @param[out] bHasNormals
		*    Receives 'true' if there are normals, else 'false'
		*  @param[out] bHasTangentsAndBitangents
		*    Receives 'true' if there are tangents and bitangents, else 'false'
		*  @param[out] bHasTexCoords
		*    Receives 'true' if there are texture coordinates, else 'false'
		*  @param[out] nNumUVComponents
		*    Receives the number of components for a given UV channel (see aiMesh for details), must have at least "MaxNumOfTextureCoords"-elements
		*/
		void GetNumOfVerticesAndIndices(const aiNode &cAssimpNode, PLCore::uint32 &nNumOfVertices, PLCore::uint32 &nNumOfIndices, bool &bHasNormals,
										bool &bHasTangentsAndBitangents, bool &bHasTexCoords, unsigned int nNumUVComponents[]);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLScene::SceneContainer *m_pContainer;		/**< Scene container to fill, can be a null pointer */
		const aiScene			*m_pAssimpScene;	/**< Used Assimp scene, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_ASSIMPSCENELOADER_H__
