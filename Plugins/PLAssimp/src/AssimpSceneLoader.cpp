/*********************************************************\
 *  File: AssimpSceneLoader.cpp                          *
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
#include <Assimp/aiScene.h>
#include <Assimp/assimp.hpp>
#include <Assimp/aiPostProcess.h>
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLMath/Matrix4x4.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLAssimp/IOSystem.h"
#include "PLAssimp/AssimpSceneLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
AssimpSceneLoader::AssimpSceneLoader() :
	m_pContainer(nullptr),
	m_pAssimpScene(nullptr)
{
}

/**
*  @brief
*    Constructor
*/
AssimpSceneLoader::AssimpSceneLoader(const String &sDefaultTextureFileExtension) : AssimpLoader(sDefaultTextureFileExtension),
	m_pContainer(nullptr),
	m_pAssimpScene(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
AssimpSceneLoader::~AssimpSceneLoader()
{
}

/**
*  @brief
*    Loads the scene
*/
bool AssimpSceneLoader::Load(SceneContainer &cContainer, File &cFile, const String &sHint)
{
	// Reset states
	m_pContainer	= &cContainer;
	m_pAssimpScene	= nullptr;

	// Create an instance of the Assimp importer class
	Assimp::Importer cAssimpImporter;

	// Get the magic filename (concept based on "Assimp::MemoryIOSystem")
	const String sMagicFilename = (IOSystem::MagicDefaultFilename + String('.') + (sHint.GetLength() ? sHint : cFile.GetUrl().GetExtension()));

	// Set IO handler (the importer takes ownership of the object and will destroy it afterwards)
	cAssimpImporter.SetIOHandler(new IOSystem(cFile, sMagicFilename.GetASCII(), sMagicFilename.GetLength()));

	// Let Assimp load in the scene (scene remains in possession of the importer instance)
	// [TODO] Make it possible to select the post processing quality from the outside
	m_pAssimpScene = cAssimpImporter.ReadFile(sMagicFilename.GetUTF8(), aiProcessPreset_TargetRealtime_Quality|aiProcess_TransformUVCoords|aiProcess_FlipUVs);
	if (m_pAssimpScene) {
		// Load the scene recursively
		LoadRec(cContainer, *m_pAssimpScene->mRootNode);

		// [TODO] Load lights
		// [TODO] Load cameras

		// Error!
		return false;
	} else {
		// Write an error message into the log
		PL_LOG(Error, cAssimpImporter.GetErrorString())

		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the scene recursively
*/
void AssimpSceneLoader::LoadRec(SceneContainer &cParentContainer, const aiNode &cAssimpNode)
{
	// Are there any child nodes?
	if (cAssimpNode.mNumChildren) {
		// There are child nodes, this means we need a scene container for this Assimp node

		// Create the scene container for this Assimp node
		SceneContainer *pContainer = static_cast<SceneContainer*>(cParentContainer.Create("PLScene::SceneContainer", AssimpStringToPL(cAssimpNode.mName)));
		if (pContainer) {
			// Set the transformation (relative to the parent) of a PixelLight scene node by using a given Assimp node
			SetNodeTransformation(*pContainer, cAssimpNode);

			// Load the current Assimp node, don't set a transform (already set within the created scene container above)
			LoadNode(*pContainer, cAssimpNode, false);

			// Loop through all child nodes recursively
			for (unsigned int nAssimpChild=0; nAssimpChild<cAssimpNode.mNumChildren; nAssimpChild++)
				LoadRec(*pContainer, *cAssimpNode.mChildren[nAssimpChild]);
		}
	} else {
		// There are no child nodes, this is a leaf (= "PLScene::SceneNode" instead of "PLScene::SceneContainer")

		// Load the current Assimp node
		LoadNode(cParentContainer, cAssimpNode, true);
	}
}

/**
*  @brief
*    Loads the given Assimp node (not recursively)
*/
void AssimpSceneLoader::LoadNode(SceneContainer &cParentContainer, const aiNode &cAssimpNode, bool bSetTransformation)
{
	// PixelLight scene node created to represent the given Assimp node
	SceneNode *pSceneNode = nullptr;

	// Are there any meshes within this Assimp node?
	if (cAssimpNode.mNumMeshes) {
		// Create an "PLScene::SNMesh"-instance
		pSceneNode = cParentContainer.Create("PLScene::SNMesh", AssimpStringToPL(cAssimpNode.mName));

		// [TODO] Load/set mesh
	} else {
		// Create an "PLScene::SNUnknown"-instance
		pSceneNode = cParentContainer.Create("PLScene::SNUnknown", AssimpStringToPL(cAssimpNode.mName));
	}

	// Set the transformation (relative to the parent) of a PixelLight scene node by using a given Assimp node?
	if (bSetTransformation && pSceneNode)
		SetNodeTransformation(*pSceneNode, cAssimpNode);
}

/**
*  @brief
*    Set's the transformation (relative to the parent) of a PixelLight scene node by using a given Assimp node
*/
void AssimpSceneLoader::SetNodeTransformation(SceneNode &cSceneNode, const aiNode &cAssimpNode) const
{
	// Lookout!
	// -> PixelLight matrices are stored in column major order like OpenGL does (right-handed matrix)
	// -> Assimp matrices are stored in row major order
	Matrix3x4 mPL;
	const aiMatrix4x4 &mAssimp = cAssimpNode.mTransformation;
	mPL.xx = mAssimp.a1; mPL.xy = mAssimp.a2; mPL.xz = mAssimp.a3; mPL.xw = mAssimp.a4;
	mPL.yx = mAssimp.b1; mPL.yy = mAssimp.b2; mPL.yz = mAssimp.b3; mPL.yw = mAssimp.b4;
	mPL.zx = mAssimp.c1; mPL.zy = mAssimp.c2; mPL.zz = mAssimp.c3; mPL.zw = mAssimp.c4;
//	mPL.wx = mAssimp.d1; mPL.wy = mAssimp.d2; mPL.wz = mAssimp.d3; mPL.ww = mAssimp.d4; // Not required

	// Set scene node transformation
	cSceneNode.GetTransform().SetMatrix(mPL);
}

/**
*  @brief
*    Loads the mesh of the given Assimp node
*/
void AssimpSceneLoader::LoadMesh(const aiNode &cAssimpNode)
{
	// Gather general mesh information
	uint32		 nNumOfVertices = 0;						/**< Number of mesh vertices */
	uint32		 nNumOfIndices  = 0;						/**< Number of mesh indices */
	bool		 bHasNormals = false;						/**< Are there normals? */
	bool		 bHasTangentsAndBitangents = false;			/**< Are there tangents and bitangents? */
	bool		 bHasTexCoords = false;						/**< Are there texture coordinates? */
	unsigned int nNumUVComponents[MaxNumOfTextureCoords];	/**< Specifies the number of components for a given UV channel (see aiMesh for details) */
	for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++)
		nNumUVComponents[nChannel] = 0;
	GetNumOfVerticesAndIndices(cAssimpNode, nNumOfVertices, nNumOfIndices, bHasNormals, bHasTangentsAndBitangents, bHasTexCoords, nNumUVComponents);

	// [TODO] Under construction

	// Loop through all meshes this node is using
	for (unsigned int nAssimpMesh=0; nAssimpMesh<cAssimpNode.mNumMeshes; nAssimpMesh++) {
		// Get the used mesh
		const aiMesh &cAssimpMesh = *m_pAssimpScene->mMeshes[cAssimpNode.mMeshes[nAssimpMesh]];
	}
}

/**
*  @brief
*    Gets the total number of vertices and indices required for everything within a given Assimp node as one PixelLight mesh
*/
void AssimpSceneLoader::GetNumOfVerticesAndIndices(const aiNode &cAssimpNode, uint32 &nNumOfVertices, uint32 &nNumOfIndices, bool &bHasNormals,
						bool &bHasTangentsAndBitangents, bool &bHasTexCoords, unsigned int nNumUVComponents[])
{
	// Loop through all meshes this node is using
	for (unsigned int nAssimpMesh=0; nAssimpMesh<cAssimpNode.mNumMeshes; nAssimpMesh++) {
		// Get the used mesh
		const aiMesh &cAssimpMesh = *m_pAssimpScene->mMeshes[cAssimpNode.mMeshes[nAssimpMesh]];

		// Update the number of vertices
		nNumOfVertices += cAssimpMesh.mNumVertices;

		// Loop through all mesh faces and update the number of indices
		for (unsigned int nAssimpFace=0; nAssimpFace<cAssimpMesh.mNumFaces; nAssimpFace++)
			nNumOfIndices += cAssimpMesh.mFaces[nAssimpFace].mNumIndices;

		// Are there normals?
		if (cAssimpMesh.HasNormals())
			bHasNormals = true;

		// Are there tangents and bitangents?
		if (cAssimpMesh.HasTangentsAndBitangents())
			bHasTangentsAndBitangents = true;

		// Are there texture coordinates?
		if (cAssimpMesh.GetNumUVChannels()) {
			bHasTexCoords = true;

			// Loop through the supported number of texture coord sets (UV(W) channels)
			for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++) {
				if (nNumUVComponents[nChannel] < cAssimpMesh.mNumUVComponents[nChannel])
					nNumUVComponents[nChannel] = cAssimpMesh.mNumUVComponents[nChannel];
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
