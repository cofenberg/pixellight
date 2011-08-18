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
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Button.h>
#include <PLInput/Input/Virtual/VirtualController.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Compositing/SceneRendererManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLInput;
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
Application::Application(Frontend &cFrontend) : EngineApplication(cFrontend),
	SlotOnControl(this)
{
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
			SetCamera(reinterpret_cast<SNCamera*>(pCamera));
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
*    Called when a control event has occurred
*/
void Application::OnControl(Control &cControl)
{
	// Is it a button and was it just hit?
	if (cControl.GetType() == ControlButton && reinterpret_cast<Button&>(cControl).IsHit()) {
		// Check whether the escape key was pressed
		if (cControl.GetName() == "Escape") {
			// Shut down the application
			Exit(0);

		// Restart the game
		} else if (cControl.GetName() == "R") {
			Restart();

		// Toggle post processing
		} else if (cControl.GetName() == "P") {
			// Get the camera
			const SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Loop through all available post process scene node modifiers
				bool			   bRenderToTexture = false;
				uint32			   nIndex			= 0;
				SceneNodeModifier *pModifier		= pCamera->GetModifier("PLCompositing::SNMPostProcess", nIndex);
				while (pModifier) {
					// Toggle the active state of the post process scene node modifier
					pModifier->SetActive(!pModifier->IsActive());
					if (pModifier->IsActive())
						bRenderToTexture = true;

					// Next modifier, please
					pModifier = pCamera->GetModifier("PLCompositing::SNMPostProcess", ++nIndex);
				}

				// Enable/disable render to texture for the post processing feature
				GetSceneRendererTool().SetPassAttribute("Begin", "Flags", bRenderToTexture ? "" : "Inactive");
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Create a scene container with our 'concrete sound scene' using the default sound API
	SceneNode *pSceneContainerNode = cContainer.Create("PLSound::SCSound", "SoundScene", "Pitch=\"0.6\"");
	if (pSceneContainerNode && pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer")) {
		SceneContainer *pSceneContainer = static_cast<SceneContainer*>(pSceneContainerNode);

		// Protect this important container!
		pSceneContainer->SetProtected(true);

		// Populate the scene container
		// Setup scene surface painter
		SurfacePainter *pPainter = GetPainter();
		if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
			SPScene *pSPScene = static_cast<SPScene*>(pPainter);
			pSPScene->SetRootContainer(cContainer.GetContainer());
			pSPScene->SetSceneContainer(pSceneContainer);

			// Get the scene context
			SceneContext *pSceneContext = GetSceneContext();
			if (pSceneContext) {
				// Create us a scene renderer
				SceneRenderer *pSceneRenderer = pSceneContext->GetSceneRendererManager().Create("2DGame");
				if (pSceneRenderer) {
					// Add begin scene renderer pass
					pSceneRenderer->Create("PLCompositing::SRPBegin", "Begin", "TextureFormat=\"R8G8B8A8\" Flags=\"Inactive\"");

					// Add our own scene renderer pass
					pSceneRenderer->Create("SRP2DGame", "2DGame");

					// Add post processing scene renderer pass
					pSceneRenderer->Create("PLCompositing::SRPPostProcessing", "PostProcessing");

					// Add end scene renderer pass
					pSceneRenderer->Create("PLCompositing::SRPEnd", "End");

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

void Application::OnInputControllerFound(Controller *pInputController, String sInputSemantic)
{
	// Call base implementation
	EngineApplication::OnInputControllerFound(pInputController, sInputSemantic);

	// Is there an application input controller? If so, connect gun (SNGun)...
	if (m_pInputController && sInputSemantic == "Gun") {
		pInputController->Connect("X",		m_pInputController->GetControl("RotY"), -0.05f);
		// "Left" is connected automatically within "EngineApplication::OnInputControllerFound()" with the virtual standard controller
		// "Right" is connected automatically within "EngineApplication::OnInputControllerFound()" with the virtual standard controller
		pInputController->Connect("Left",	m_pInputController->GetControl("Forward"));
		pInputController->Connect("Right",	m_pInputController->GetControl("Backward"));
		pInputController->Connect("Left",	m_pInputController->GetControl("StrafeLeft"));
		pInputController->Connect("Right",	m_pInputController->GetControl("StrafeRight"));
		pInputController->Connect("Fire",	m_pInputController->GetControl("Button1"));
		pInputController->Connect("Fire",	m_pInputController->GetControl("Button2"));
		pInputController->Connect("Fire",	m_pInputController->GetControl("Button3"));
		pInputController->Connect("Fire",	m_pInputController->GetControl("Button4"));
		pInputController->Connect("Fire",	m_pInputController->GetControl("Button5"));
	}
}

void Application::OnCreateInputController()
{
	// Call base implementation
	EngineApplication::OnCreateInputController();

	// Get virtual input controller
	Controller *pController = reinterpret_cast<Controller*>(GetInputController());
	if (pController)
		pController->SignalOnControl.Connect(SlotOnControl);
}
