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
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	EventHandlerKeyDown(&Application::NotifyKeyDown, this)
{
	// Set application name and title
	SetName("PLDemoSPARK_PL");
	SetTitle(PLT("PL SPARK demo"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
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
	// One important word at the beginning: DON'T COPYCAT THIS!
	// The following is 'just' a simple demonstration how the scene graph 'can' be used. It's
	// definitely not good to update your scene nodes in the way you can see within this function.
	// Its quite to intricate, inflexible and not performant. Use for example a scene node modifier
	// added to your scene node (in this case 'the white light') for this job!

	// Call base implementation
	if (BasicSceneApplication::OnUpdate()) {
		// Get the scene container with our 'concrete scene'
		SceneContainer *pSceneContainer = GetScene();
		if (pSceneContainer) {
			// Get the scene node with the name 'Light' (our 'white light')
			SceneNode *pLight = pSceneContainer->Get("Light");
			if (pLight) {
				// This variable is used for the light animation. Its just static you keep the implementation
				// for a good demo overview completely within this function.
				static float fLightTimer = 0.0f;

				// We set the current light position using the RTTI class interface. This is quite comfortable
				// and universal because you haven't to care about the concrete class type - just set the
				// variable values. For performance critical situations it's recommened to avoid using this RTTI
				// functions to set your variables and use the conrete provided class interfaces instead.
				pLight->SetAttribute("Position", String::Format("%g %g %g", Math::Sin(fLightTimer),
					Math::Sin(fLightTimer)/2+2, -(Math::Cos(fLightTimer)+5)));

				// Update the light timer by using the time difference between the last and the current frame
				fLightTimer += Timing::GetInstance()->GetTimeDifference();
			}
		}

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

		// Add a controller modifier so we can look around the camera by using a default control
		pCamera->AddModifier("PLScene::SNMLookController");

		// Fix roll to avoid a camera twist
		pCamera->AddModifier("PLScene::SNMRotationFixRoll");

		// Add a controller modifier so we can move around the camera by using a default control
		pCamera->AddModifier("PLScene::SNMMoveController");
	}

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Position=\"0 0 -5\" Scale=\"4 0.1 4\" Mesh=\"Default\"");

	// Create an instance of the fire particle effect scene node
	cContainer.Create("SNFireDemo", "Fire", "Position=\"0.5 0.3 -5\" Scale=\"0.1 0.1 0.1\"");

	// Create an instance of the basic particle effect scene node
	cContainer.Create("SNBasicDemo", "Basic", "Position=\"-0.5 0.1 -8\" Scale=\"0.5 0.5 0.5\"");

	// Create an instance of the gravitation particle effect scene node
	cContainer.Create("SNGravitationDemo", "Gravitation", "Position=\"-1 1 -5\" Scale=\"0.5 0.5 0.5\"");

	// Create an instance of the galaxy particle effect scene node
	cContainer.Create("SNGalaxyDemo", "Galaxy", "Position=\"-3 0.5 -8\" Scale=\"0.5 0.5 0.5\"");

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = static_cast<SPScene*>(pPainter);
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);
	}

	// Set scene container
	SetScene(&cContainer);
}
