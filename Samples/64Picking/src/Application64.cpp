/*********************************************************\
 *  File: Application64.cpp                              *
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
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Control.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
#include "MyPicking.h"
#include "Application64.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application64)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application64::Application64(Frontend &cFrontend) : EngineApplication(cFrontend),
	SlotOnControl(this),
	m_pMyPicking(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
Application64::~Application64()
{
	// Destroy the picking component
	if (m_pMyPicking)
		delete m_pMyPicking;
}


//[-------------------------------------------------------]
//[ Public virtual PLEngine::EngineApplication functions  ]
//[-------------------------------------------------------]
void Application64::SetCamera(SNCamera *pCamera)
{
	// Call base implementation
	EngineApplication::SetCamera(pCamera);

	// Do also set the camera to use within the picking component
	if (m_pMyPicking)
		m_pMyPicking->SetCamera(pCamera);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a control event has occurred
*/
void Application64::OnControl(Control &cControl)
{
	// Check whether the escape key was pressed
	if (cControl.GetType() == ControlButton && cControl.GetName() == "KeyboardEscape")
		Exit(0); // Shut down the application
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void Application64::OnInit()
{
	// Call base implementation
	EngineApplication::OnInit();

	// Clear the content of the current used render target by using gray (this way, in case on an graphics error we might still see at least something)
	GetSceneRendererTool().SetPassAttribute("Begin", "ColorClear", "0.5 0.5 0.5 0");
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::AbstractFrontend functions    ]
//[-------------------------------------------------------]
void Application64::OnUpdate()
{
	// Call base implementation
	EngineApplication::OnUpdate();

	// Perform the picking
	if (m_pMyPicking)
		m_pMyPicking->PerformPicking();
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void Application64::OnCreateScene(SceneContainer &cContainer)
{
	// Create a camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera", "Position=\"1 2 -3\" Rotation=\"25 210 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		// Make this to our main scene camera
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));
	}

	// Create a scene node with the soldier mesh - in debug mode, show some fancy technical visualizations
	SceneNode *pSceneNode = cContainer.Create("PLScene::SNMesh", "Soldier", "Position=\"0.0 0.1 -5.0\" Scale=\"0.008 0.008 0.008\" Mesh=\"Data/Meshes/Soldier.mesh\" DebugFlags=\"DebugShowWireframe|DebugShowJoints|DebugShowJointNames|DebugShowSkeleton\"");
	if (pSceneNode) {
		// Rotate the soldier
		pSceneNode->AddModifier("PLScene::SNMRotationLinearAnimation", "Velocity=\"0 10 0\"");

		// Playback the animation named "walk_0" letting the soldier walk
		pSceneNode->AddModifier("PLScene::SNMMeshAnimation", "Name=\"walk_0\"");

		// Animate the morph target named "blink" letting the soldier blink from time to time
		pSceneNode->AddModifier("PLScene::SNMMeshMorphBlink", "Name=\"blink\"");
	}

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Position=\"0.0 0.0 -5.0\" Rotation=\"0.0 180.0 0.0\" Scale=\"4.0 0.1 4.0\" Mesh=\"Default\"");

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = static_cast<SPScene*>(pPainter);
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);
	}

	// Set scene container
	SetScene(&cContainer);

	// Create the picking component
	m_pMyPicking = new MyPicking(*this);
}

void Application64::OnCreateInputController()
{
	// Call base implementation
	EngineApplication::OnCreateInputController();

	// Get virtual input controller
	Controller *pController = reinterpret_cast<Controller*>(GetInputController());
	if (pController)
		pController->SignalOnControl.Connect(SlotOnControl);
}
