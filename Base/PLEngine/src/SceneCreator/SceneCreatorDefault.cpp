/*********************************************************\
 *  File: SceneCreatorDefault.cpp                        *
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
#include <PLScene/Scene/SceneContainer.h>
#include "PLEngine/SceneCreator/SceneCreatorDefault.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneCreatorDefault)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SceneCreatorDefault::SceneCreatorDefault()
{
}

/**
*  @brief
*    Destructor
*/
SceneCreatorDefault::~SceneCreatorDefault()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneCreator functions                 ]
//[-------------------------------------------------------]
SNCamera *SceneCreatorDefault::Create(SceneContainer &cSceneContainer) const
{
	// Create a scene node representing a simple box
	SceneNode *pPrimarySceneNode = cSceneContainer.Create("PLScene::SNMesh", "Box", "Mesh=\"Default\"");

	// Configure a generic scene and return the preferred camera scene node
	return SceneCreator::ConfigureGenericScene(cSceneContainer, pPrimarySceneNode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
