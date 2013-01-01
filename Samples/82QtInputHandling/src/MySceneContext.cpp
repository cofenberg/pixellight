/*********************************************************\
 *  File: MySceneContext.cpp                             *
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
//[ Protected virtual PLFrontendQt::QPLSceneContext functions ]
//[-------------------------------------------------------]
void MySceneContext::OnCreateScene(SceneContainer &cContainer)
{
	// Create first camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera1", "Position=\"1 2 -3\" Rotation=\"25 0 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));

		// Add a controller modifier so we can look around the camera by using a default control
		pCamera->AddModifier("PLEngine::SNMEgoLookController");

		// Add a controller modifier so we can move around the camera by using a default control
		pCamera->AddModifier("PLEngine::SNMMoveController");
	}

	// Create second camera
	pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera2", "Position=\"1 2 -3\" Rotation=\"25 0 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		// Add a controller modifier so we can look around the camera by using a default control
		pCamera->AddModifier("PLEngine::SNMEgoLookController");

		// Add a controller modifier so we can move around the camera by using a default control
		pCamera->AddModifier("PLEngine::SNMMoveController");
	}

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Position=\"0.0 0.0 5.0\" Rotation=\"0.0 180.0 0.0\" Scale=\"4.0 0.1 4.0\" Mesh=\"Default\"");

	// Set scene container
	SetScene(&cContainer);
}
