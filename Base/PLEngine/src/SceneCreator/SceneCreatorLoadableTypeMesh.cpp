/*********************************************************\
 *  File: SceneCreatorLoadableTypeMesh.cpp               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Log/Log.h>
#include <PLMesh/MeshHandler.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/SNMesh.h>
#include "PLEngine/SceneCreator/SceneCreatorLoadableTypeMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneCreatorLoadableTypeMesh)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SceneCreatorLoadableTypeMesh::SceneCreatorLoadableTypeMesh()
{
}

/**
*  @brief
*    Destructor
*/
SceneCreatorLoadableTypeMesh::~SceneCreatorLoadableTypeMesh()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneCreator functions                 ]
//[-------------------------------------------------------]
SNCamera *SceneCreatorLoadableTypeMesh::Create(SceneContainer &cSceneContainer) const
{
	// Get the mesh filename
	const String sFilename = Filename.Get();

	// Create a mesh scene node
	SceneNode *pPrimarySceneNode = cSceneContainer.Create("PLScene::SNMesh", "Mesh", "Mesh=\"" + sFilename + '\"');

	// Security check for better usability: Has the scene node a mesh with at least one material?
	// -> If not the scene node mesh may not be visible and the user may wonder what's going on, so, in this case enable scene node debug mode
	if (pPrimarySceneNode && pPrimarySceneNode->GetMeshHandler() && !pPrimarySceneNode->GetMeshHandler()->GetNumOfMaterials()) {
		PL_LOG(Warning, "Mesh viewer: The mesh \"" + sFilename + "\" has no materials")

		// Switch the mesh scene node into wireframe debug mode so that the user can see what's going on
		pPrimarySceneNode->SetDebugFlags(SceneNode::DebugEnabled | SceneNode::DebugNoLocalCoordinateAxis | SceneNode::DebugNoName | SceneNode::DebugNoAABBox | SNMesh:: DebugShowWireframe);
	}

	// Configure a generic scene and return the preferred camera scene node
	return SceneCreator::ConfigureGenericScene(cSceneContainer, pPrimarySceneNode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
