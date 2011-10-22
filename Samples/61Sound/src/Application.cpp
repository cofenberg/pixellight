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
#include <PLCore/Base/Class.h>
#include <PLCore/Tools/Timing.h>
#include <PLCore/Tools/Localization.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Control.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
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
	// Add command line argument for choosing the sound API
	#ifdef ANDROID
		m_cCommandLine.AddArgument("SoundAPI", "Sound API", "PLSoundOpenSLES::SoundManager", false);
	#else
		m_cCommandLine.AddArgument("SoundAPI", "Sound API", "PLSoundOpenAL::SoundManager", false);
	#endif
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
*    Returns the name of the used sound API
*/
String Application::GetSoundAPI() const
{
	return m_sSoundAPI;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the text of the time scale text node
*/
void Application::UpdateTimeScaleTextNode()
{
	// Get the scene
	SceneContainer *pSceneContainer = GetScene();
	if (pSceneContainer) {
		// Get the scene info text container
		SceneContainer *pInfoTextContainer = static_cast<SceneContainer*>(pSceneContainer->GetByName("Parent.InfoText"));
		if (pInfoTextContainer) {
			// Get the time scale text scene node
			SceneNode *pInfoTextNode = pInfoTextContainer->GetByName("TimeScale");
			if (pInfoTextNode) {
				pInfoTextNode->SetAttribute("Text", PLT("1/2/0=Decrease/increase/reset timescale (current: ") +
					String::Format("%g)", Timing::GetInstance()->GetTimeScaleFactor()));
			}
		}
	}
}

/**
*  @brief
*    Called when a control event has occurred
*/
void Application::OnControl(Control &cControl)
{
	// Is it a button?
	if (cControl.GetType() == ControlButton) {
		// Check whether the escape key was pressed
		if (cControl.GetName() == "KeyboardEscape") {
			// Shut down the application
			Exit(0);
		} else {
			// Get current time difference
			Timing *pTimer = Timing::GetInstance();
			float fTimeDiff        = pTimer->GetTimeDifference();
			float fTimeScaleFactor = pTimer->GetTimeScaleFactor();

			// Check button
			if (cControl.GetName() == "Keyboard1") {
				// Decrease timescale
				pTimer->SetTimeScaleFactor(fTimeScaleFactor-fTimeDiff);
				if (pTimer->GetTimeScaleFactor() < 0.1f)
					pTimer->SetTimeScaleFactor(0.1f);
			} else if (cControl.GetName() == "Keyboard2") {
				// Increase timescale
				pTimer->SetTimeScaleFactor(fTimeScaleFactor+fTimeDiff);
				if (pTimer->GetTimeScaleFactor() > 4.0f)
					pTimer->SetTimeScaleFactor(4.0f);
			} else if (cControl.GetName() == "Keyboard3") {
				// Reset timescale
				pTimer->SetTimeScaleFactor();
			}

			// Time scale factor changed?
			if (fTimeScaleFactor != pTimer->GetTimeScaleFactor()) {
				// Update the time scale text node
				UpdateTimeScaleTextNode();

				// Update the pitch variable of the sound container using the time scale factor
				SceneContainer *pSceneContainer = GetScene();
				if (pSceneContainer)
					pSceneContainer->SetAttribute("Pitch", String::Format("%g", pTimer->GetTimeScaleFactor()));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void Application::OnInit()
{
	// Call base implementation
	EngineApplication::OnInit();

	// Valid default sound API given?
	String sClassName = m_cCommandLine.GetValue("SoundAPI");
	if (sClassName.GetLength()) {
		const Class *pClass = ClassManager::GetInstance()->GetClass(sClassName);
		if (pClass && pClass->IsDerivedFrom("PLSound::SoundManager")) {
			m_sSoundAPI = sClassName;

			// Create new root scene
			OnCreateRootScene();
		}
	}
	if (!m_sSoundAPI.GetLength()) {
		// Error!
		Exit(1);
	}

	// Clear the content of the current used render target by using gray (this way, in case on an graphics error we might still see at least something)
	GetSceneRendererTool().SetPassAttribute("Begin", "ColorClear", "0.5 0.5 0.5 0");
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Set no scene container as default
	SetScene(nullptr);

	// Sound API given?
	if (m_sSoundAPI.GetLength()) {
		// Create a scene container with our 'concrete sound scene' using the chosen sound API
		SceneNode *pSceneContainerNode = cContainer.Create("PLSound::SCSound", "SoundScene", "SoundAPI=\"" + m_sSoundAPI + "\" Pitch=\"" + String::Format("%g", Timing::GetInstance()->GetTimeScaleFactor()) + '\"');
		if (pSceneContainerNode && pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer")) {
			SceneContainer *pSceneContainer = static_cast<SceneContainer*>(pSceneContainerNode);

			// Protect this important container!
			pSceneContainer->SetProtected(true);

			// Set scene container
			SetScene(pSceneContainer);

			// Populate the scene container
			// Create a camera
			SceneNode *pCamera = pSceneContainer->Create("PLScene::SNCamera", "FreeCamera", "Position=\"0.0 -1.5 1.4\" Rotation=\"-14.0 180.0 0.0\"");
			if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
				// Make this to our main scene camera
				SetCamera(reinterpret_cast<SNCamera*>(pCamera));

				// Add a controller modifier so we can look around the camera by using a default control
				pCamera->AddModifier("PLEngine::SNMLookController");

				// Fix roll to avoid a camera twist
				pCamera->AddModifier("PLScene::SNMRotationFixRoll");

				// Add a controller modifier so we can move around the camera by using a default control
				pCamera->AddModifier("PLEngine::SNMMoveController", "Speed=\"2\"");

				// Make this camera to the 'sound listener'
				pSceneContainer->SetAttribute("Listener", pCamera->GetName());
			}

			// Create the floor
			pSceneContainer->Create("PLScene::SNMesh", "Floor", "Position=\"0.0 -2.1 -5.0\" Rotation=\"0.0 180.0 0.0\" Scale=\"4.0 0.1 4.0\" Mesh=\"Default\"");

			// Create a box on the floor
			pSceneContainer->Create("PLScene::SNMesh", "Box", "Position=\"0.0 -1.5 -5.0\" Scale=\"0.5 0.5 0.5\" Mesh=\"Default\"");

			// Create rain particles and rain sound
			pSceneContainer->Create("PLParticleGroups::PGRain", "Rain", "Position=\"0.0 15.0 -5.0\" Flags=\"ForceUpdate\" MediumSize=\"3\"");
			pSceneContainer->Create("PLSound::SNSound", "RainSound", "Sound=\"Data/Sounds/Rain.ogg\" Volume=\"0.2\"");

			// Footsteps sound
			pSceneContainer->Create("PLSound::SNSound", "Sound", "Sound=\"Data/Sounds/Walking.ogg\"");

			// Create the soldier walking in the rain :)
			SceneNode *pSoldier = pSceneContainer->Create("PLScene::SNMesh", "Soldier", "Position=\"0.0 -1.5 -5.0\" Scale=\"0.007 0.007 0.007\" Mesh=\"Data/Meshes/Soldier.mesh\"");
			if (pSoldier) {
				// Add animation modifier
				pSoldier->AddModifier("PLScene::SNMMeshAnimation", "Name=\"walk_0\" Speed=\"2\"");

				// Let the soldier walk on a path...
				pSoldier->AddModifier("PLScene::SNMPositionPath", "Filename=\"Data/Misc/61Sound_Soldier.path\" Speed=\"0.5\" Flags=\"NodeIndexProgress\" Interpolation=\"CatmullRomCurve\"");

				// ... and we should look into the direction he's moving
				pSoldier->AddModifier("PLScene::SNMRotationMoveDirection");

				// Link the footsteps sound with the soldier
				pSoldier->AddModifier("PLScene::SNMAnchor", "AttachedNode=\"Sound\"");
			}

			// Setup scene surface painter
			SurfacePainter *pPainter = GetPainter();
			if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
				SPScene *pSPScene = static_cast<SPScene*>(pPainter);
				pSPScene->SetRootContainer(cContainer.GetContainer());
				pSPScene->SetSceneContainer(pSceneContainer);
			}

			// Within the parent container...
			SceneContainer *pContainer = pSceneContainer->GetContainer();
			if (pContainer) {
				// Get/add our information text scene nodes
				SceneNode *pInfoText = pContainer->Create("PLScene::SceneContainer", "InfoText", "Flags=\"NoCulling\"");
				if (pInfoText && pInfoText->IsInstanceOf("PLScene::SceneContainer")) {
					SceneContainer *pInfoTextContainer = static_cast<SceneContainer*>(pInfoText);

					// The name of the used sound API
					pInfoTextContainer->Create("PLScene::SNText2D", "SoundAPI", "Position=\"0.01 0.01\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("Sound API: ") + GetSoundAPI() + '\"');

					// Draw keys information
					pInfoTextContainer->Create("PLScene::SNText2D", "Keys",      "Position=\"0.01 0.04\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("Keys:")                      + '\"');
					pInfoTextContainer->Create("PLScene::SNText2D", "TimeScale", "Position=\"0.06 0.08\" Flags=\"No3DPosition|NoCenter\"");
					UpdateTimeScaleTextNode();
				}
			}
		}
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