/*********************************************************\
 *  File: SceneApplication.cpp                          *
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
#include <PLCore/Base/Class.h>
#include <PLInput/Input/Virtual/VirtualController.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/Console/ConsoleCommand.h>
#include <PLScene/Scene/SceneNodes/Console/SNConsoleBase.h>
#include "PLEngine/Application/SceneApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneApplication)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the root scene
*/
SceneContainer *SceneApplication::GetRootScene()
{
	// Return pointer to root scene container
	return m_pRootScene;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneApplication::SceneApplication(const String &sSceneFilename) : RenderApplication("PLScene::SPScene"),
	EventHandlerInputControllerFound(&SceneApplication::OnInputControllerFound, this),
	m_pSceneContext(nullptr),
	m_pRootScene(nullptr),
	m_bEditModeEnabled(false)
{
	// By default, edit mode is enabled
	SetEditModeEnabled(true);

	// Set application title
	SetTitle("PixelLight scene application");
}

/**
*  @brief
*    Destructor
*/
SceneApplication::~SceneApplication()
{
}

/**
*  @brief
*    Returns the scene context
*/
SceneContext *SceneApplication::GetSceneContext() const
{
	return m_pSceneContext;
}

/**
*  @brief
*    Returns whether or not edit mode is enabled
*/
bool SceneApplication::IsEditModeEnabled() const
{
	return m_bEditModeEnabled;
}

/**
*  @brief
*    Sets whether or not edit mode is enabled
*/
void SceneApplication::SetEditModeEnabled(bool bEnabled)
{
	// State change?
	if (m_bEditModeEnabled != bEnabled) {
		// Backup the new state
		m_bEditModeEnabled = bEnabled;

		// Close the edit dialog if edit mode is disabled
		if (!bEnabled)
			CloseEditDialog();

		// Get the root scene
		SceneContainer *pRootScene = GetRootScene();
		if (pRootScene) {
			// Enable/disable standard edit features from the PixelLight scene graph (if the user hasn't changed anything :)
			SceneNode *pSceneNode = pRootScene->Get("PLScene::SNEngineInformation0");
			if (pSceneNode)
				pSceneNode->SetActive(bEnabled);
			pSceneNode = pRootScene->Get("PLScene::SNConsole0");
			if (pSceneNode)
				pSceneNode->SetActive(bEnabled);
		}

		// Setup log level
		Log::GetInstance()->SetLogLevel(static_cast<uint8>(m_bEditModeEnabled ? Log::Debug : Log::Info));
	}
}

/**
*  @brief
*    Returns whether the edit dialog is currently opened or not
*/
bool SceneApplication::IsEditDialogOpend()
{
	// [TODO] PLGui: New edit GUI
//	return m_cEditDialog.IsLoaded();
	return false;
}

/**
*  @brief
*    Opens the edit dialog
*/
void SceneApplication::OpenEditDialog(PLGui::Widget *pParent)
{
	// [TODO] PLGui: New edit GUI
/*	// Is edit mode enabled and isn't the edit dialog already opened?
	if (m_pSceneContext && m_bEditModeEnabled && !m_cEditDialog.IsLoaded()) {
		// Create dialog
		GuiEdit *pEdit = new GuiEdit(*m_pSceneContext, pParent);
		pEdit->SetVisible(true);
		m_cEditDialog.Load(pEdit);
	}
*/
}

/**
*  @brief
*    Closes the edit dialog
*/
bool SceneApplication::CloseEditDialog()
{
	// [TODO] PLGui: New edit GUI
	/*
	if (m_cEditDialog.IsLoaded()) {
		m_cEditDialog.GetWindow()->Destroy();

		// Native GUI
		Gui *pGui = GuiManager::GetInstance()->GetSystemGui();
		if (pGui) {
			// Process GUI messages
			if (pGui->PendingMessages())
				pGui->ProcessMessages();
		}

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
	*/
	return false;
}

/**
*  @brief
*    Quit the engine
*/
void SceneApplication::ConsoleCommandQuit(ConsoleCommand &cCommand)
{
	Exit(0);
}

/**
*  @brief
*    Opens the engine edit dialog and deactivates the owner console automatically
*/
void SceneApplication::ConsoleCommandEditDialog(ConsoleCommand &cCommand)
{
	// Deactivate the owner console
	SNConsoleBase *pConsole = cCommand.GetConsole();
	if (pConsole)
		pConsole->Deactivate();

	// Open the edit dialog
	OpenEditDialog();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set root scene
*/
void SceneApplication::SetRootScene(SceneContainer *pRootScene)
{
	// Set pointer to painter
	m_pRootScene = pRootScene;
}


//[-------------------------------------------------------]
//[ Protected virtual ConsoleApplication functions        ]
//[-------------------------------------------------------]
bool SceneApplication::Init()
{
	// Call base implementation
	if (RenderApplication::Init()) {
		// Get renderer context
		RendererContext *pRendererContext = GetRendererContext();
		if (pRendererContext) {
			// Create scene context
			m_pSceneContext = new SceneContext(*pRendererContext);

			// Set default input controller
			m_pSceneContext->SetDefaultInputController(GetInputController());

			// Connect the input controller found event handler to the corresponding scene context event
			m_pSceneContext->EventInputControllerFound.Connect(&EventHandlerInputControllerFound);

			// Create root scene
			OnCreateRootScene();
			if (!m_bRunning)
				return false;

			// Done
			return true;
		}
	}

	// Error
	return false;
}

void SceneApplication::DeInit()
{
	// Close the edit dialog
	CloseEditDialog();

	// Destroy the scene context
	if (m_pSceneContext)
		delete m_pSceneContext;

	// Call base implementation
	RenderApplication::DeInit();
}


//[-------------------------------------------------------]
//[ Protected virtual RenderApplication functions         ]
//[-------------------------------------------------------]
bool SceneApplication::OnUpdate()
{
	// Update the root scene container - we need to do this before drawing the first frame
	if (m_pSceneContext) {
		m_pSceneContext->Cleanup();

		// Update the scene context
		m_pSceneContext->Update();
	}

	// Call base implementation
	return RenderApplication::OnUpdate();
}


//[-------------------------------------------------------]
//[ Protected virtual SceneApplication functions          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to create the application's root scene
*/
void SceneApplication::OnCreateRootScene()
{
	// [TODO] Load 'm_sSceneFilename' if provided

	// Is there a scene context?
	if (m_pSceneContext) {
		// First, create the scene root container which holds the scene container with our 'concrete' scene within it
		SceneContainer *pRootContainer = m_pSceneContext->GetRoot() ? static_cast<SceneContainer*>(m_pSceneContext->GetRoot()->Create("PLScene::SceneContainer", "RootScene")) : nullptr;
		if (pRootContainer) {
			// Protect this important container!
			pRootContainer->SetProtected(true);

			// Create a scene container with our 'concrete scene'
			SceneNode *pSceneContainerNode = pRootContainer->Create("PLScene::SceneContainer", "Scene");
			if (pSceneContainerNode && pSceneContainerNode->IsContainer()) {
				// Protect this important container!
				pSceneContainerNode->SetProtected(true);
			}

			// Create scene node for engine information
			SceneNode *pSceneNode = pRootContainer->Create("PLScene::SNEngineInformation");
			if (pSceneNode)
				pSceneNode->SetActive(m_bEditModeEnabled);

			// Create console scene node - using the console command 'timescale <value>' we
			// can change the scene time (slowdown or accelerate)
			pSceneNode = pRootContainer->Create("PLScene::SNConsole");
			if (pSceneNode && pSceneNode->GetClass()->IsDerivedFrom("PLScene::SNConsoleBase")) {
				SNConsoleBase *pConsole = static_cast<SNConsoleBase*>(pSceneNode);

				// Register default commands
				pConsole->RegisterCommand(0,	"quit",			"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"exit",			"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"bye",			"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"logout",		"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));

				// Edit commands
				pConsole->RegisterCommand(1,	"editdialog",	"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandEditDialog, this));

				// Set active state
				pConsole->SetActive(m_bEditModeEnabled);
			}
		}

		// Set the root scene
		SetRootScene(pRootContainer);
	}
}

/**
*  @brief
*    Function that is called when an input controller has been found
*/
void SceneApplication::OnInputControllerFound(Controller *pInputController, String sInputSemantic)
{
	// Is there an application input controller?
	if (m_pInputController) {
		// Try to connect all controls automatically with the virtual standard controller
		pInputController->ConnectAll(m_pInputController, "", sInputSemantic);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
