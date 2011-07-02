/*********************************************************\
 *  File: MySceneContext.cpp                             *
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
#include <PLScene/Scene/SceneContainer.h>
#include "MySceneContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLScene;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MySceneContext::MySceneContext()
{
	// Needed, otherwise the program exits with a pure virtual method call error
	// if this where called in the base class constructor
	InitScene();
}

/**
*  @brief
*    Destructor
*/
MySceneContext::~MySceneContext()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLQt::QPLSceneContext functions     ]
//[-------------------------------------------------------]
void MySceneContext::OnCreateScene(SceneContainer &cContainer)
{
	// Create a camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera", "Position=\"1 2 -3\" Rotation=\"25 0 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera"))
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Position=\"0.0 0.0 5.0\" Rotation=\"0.0 180.0 0.0\" Scale=\"4.0 0.1 4.0\" Mesh=\"Default\"");

	// Set scene container
	SetScene(&cContainer);
}
