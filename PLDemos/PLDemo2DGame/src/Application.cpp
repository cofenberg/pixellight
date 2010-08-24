/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Compositing/SceneRendererManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
Application::Application() : BasicSceneApplication(),
	EventHandlerKeyDown(&Application::NotifyKeyDown, this)
{
	// Set application name and title
	SetName("PLDemo2DGame");
	SetTitle(PLT("PL 2D game demo"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}

/**
*  @brief
*    Restarts the game
*/
void Application::Restart()
{
	// Get the scene container
	SceneContainer *pSceneContainer = GetScene();
	if (pSceneContainer) {
		// Clean up your scene container
		pSceneContainer->Clear();

		// Create the camera (we need the camera to control the post processing)
		SceneNode *pCamera = pSceneContainer->Create("PLScene::SNCamera", "FixedCamera");
		if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
			// Add a post process scene node modifier from the 'PLPostProcessEffects'-plugin
			pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessOldFilm", "Flags='Inactive'");

			// Make this to our main scene camera
			SetCamera((SNCamera*)pCamera);
		}

		// Create an UFO from mars attacking the earth :D
		pSceneContainer->Create("SNUFO", "Ufo");

		// Create the gun (the player)
		pSceneContainer->Create("SNGun", "Gun", "Position=\"157 155\"");
	}
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
	switch (nKey) {
		// Check whether the escape key was pressed
		case PLGUIKEY_ESCAPE:
			Exit(0); // Shut down the application
			break;

		// Restart the game
		case PLGUIKEY_R:
			Restart();
			break;

		// Toggle post processing
		case PLGUIKEY_P:
		{
			// Get the camera
			const SceneNode *pCamera = (SceneNode*)GetCamera();
			if (pCamera) {
				// Loop through all available post process scene node modifiers
				uint32			   nIndex    = 0;
				SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcess", nIndex);
				while (pModifier) {
					// Toggle the active state of the post process scene node modifier
					pModifier->SetActive(!pModifier->IsActive());

					// Next modifier, please
					pModifier = pCamera->GetModifier("PLScene::SNMPostProcess", ++nIndex);
				}
			}
			break;
		}
	}
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
//[ Private virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Create a scene container with our 'concrete sound scene' using the default sound API
	SceneNode *pSceneContainerNode = cContainer.Create("PLSound::SCSound", "SoundScene", "Pitch=\"0.6\"");
	if (pSceneContainerNode && pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer")) {
		SceneContainer *pSceneContainer = (SceneContainer*)pSceneContainerNode;

		// Protect this important container!
		pSceneContainer->SetProtected(true);

		// Populate the scene container
		// Setup scene surface painter
		SurfacePainter *pPainter = GetPainter();
		if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
			SPScene *pSPScene = (SPScene*)pPainter;
			pSPScene->SetRootContainer(cContainer.GetContainer());
			pSPScene->SetSceneContainer(pSceneContainer);

			// Get the scene context
			SceneContext *pSceneContext = GetSceneContext();
			if (pSceneContext) {
				// Create us a scene renderer
				SceneRenderer *pSceneRenderer = pSceneContext->GetSceneRendererManager().Create("2DGame");
				if (pSceneRenderer) {
					// Add our own scene renderer pass
					pSceneRenderer->Create("SRP2DGame", "2DGame");

					// Add post processing scene renderer pass
					pSceneRenderer->Create("PLScene::SRPPostProcessing", "PostProcessing");

					// Make this scene renderer to the default scene renderer of our scene surface painter
					pSPScene->SetDefaultSceneRenderer(pSceneRenderer->GetName());
				}
			}
		}

		// Set scene container
		SetScene(pSceneContainer);

		// Start the game
		Restart();
	}
}
