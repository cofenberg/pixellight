/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
#include "MyPicking.h"
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGui;
using namespace PLRenderer;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	EventHandlerKeyDown(&Application::NotifyKeyDown, this),
	m_pMyPicking(nullptr)
{
	// Set application name and title
	SetName("PLDemoPicking");
	SetTitle(PLT("PL picking demo"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
	// Destroy the picking component
	if (m_pMyPicking)
		delete m_pMyPicking;
}


//[-------------------------------------------------------]
//[ Public virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::SetCamera(SNCamera *pCamera)
{
	// Call base implementation
	BasicSceneApplication::SetCamera(pCamera);

	// Do also set the camera to use within the picking component
	if (m_pMyPicking)
		m_pMyPicking->SetCamera(pCamera);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a key is pressed down
*/
void Application::NotifyKeyDown(uint32 nKey, uint32 nModifiers)
{
	// Check whether the escape key was pressed
	if (nKey == PLGUIKEY_ESCAPE)
		// Shut down the application
		Exit(0);
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::GuiApplication functions       ]
//[-------------------------------------------------------]
void Application::OnCreateMainWindow()
{
	// Call base implementation
	BasicSceneApplication::OnCreateMainWindow();

	// Connect event handler
	Widget *pWidget = GetMainWindow();
	if (pWidget) {
		pWidget->EventKeyDown.Connect(&EventHandlerKeyDown);
		// [TODO] Linux: Currently we need to listen to the content widget key events as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget)
			pWidget->GetContentWidget()->EventKeyDown.Connect(&EventHandlerKeyDown);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::RenderApplication functions ]
//[-------------------------------------------------------]
bool Application::OnUpdate()
{
	// Call base implementation
	if (BasicSceneApplication::OnUpdate()) {
		// Perform the picking
		if (m_pMyPicking)
			m_pMyPicking->PerformPicking();

		// Done
		return true;
	} else {
		// Not updated
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Create a camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera", "Position=\"1 2 -3\" Rotation=\"25 210 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		// Make this to our main scene camera
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));
	}

	// Create a scene node with the soldier mesh - in debug mode, show some fancy technical visualisations
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
