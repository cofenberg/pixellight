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
#include <PLCore/Log/Log.h>
#include <PLCore/Base/Class.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLEngine/Compositing/Console/ConsoleCommand.h"
#include "PLEngine/Compositing/Console/SNConsoleBase.h"
#include "PLEngine/Application/SceneApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneApplication::SceneApplication(const String &sSceneFilename) : RenderApplication("PLScene::SPScene"),
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
*    Returns the root scene
*/
SceneContainer *SceneApplication::GetRootScene() const
{
	// Return pointer to root scene container
	return m_pRootScene;
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

		// Get the root scene
		SceneContainer *pRootScene = GetRootScene();
		if (pRootScene) {
			// Enable/disable standard edit features from the PixelLight scene graph (if the user hasn't changed anything :)
			SceneNode *pSceneNode = pRootScene->GetByName("PLEngine::SNEngineInformation0");
			if (pSceneNode)
				pSceneNode->SetActive(bEnabled);
			pSceneNode = pRootScene->GetByName("PLEngine::SNConsole0");
			if (pSceneNode)
				pSceneNode->SetActive(bEnabled);
		}

		// Setup log level
		Log::GetInstance()->SetLogLevel(static_cast<uint8>(m_bEditModeEnabled ? Log::Debug : Log::Info));
	}
}

/**
*  @brief
*    Quit the engine
*/
void SceneApplication::ConsoleCommandQuit(ConsoleCommand &cCommand)
{
	Exit(0);
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
	// Destroy the scene context
	if (m_pSceneContext)
		delete m_pSceneContext;

	// Call base implementation
	RenderApplication::DeInit();
}


//[-------------------------------------------------------]
//[ Protected virtual RenderApplication functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called once per update loop
*/
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
			SceneNode *pSceneNode = pRootContainer->Create("PLEngine::SNEngineInformation");
			if (pSceneNode)
				pSceneNode->SetActive(m_bEditModeEnabled);

			// Create console scene node - using the console command 'timescale <value>' we
			// can change the scene time (slowdown or accelerate)
			pSceneNode = pRootContainer->Create("PLEngine::SNConsole");
			if (pSceneNode && pSceneNode->GetClass()->IsDerivedFrom("PLEngine::SNConsoleBase")) {
				SNConsoleBase *pConsole = static_cast<SNConsoleBase*>(pSceneNode);

				// Register default commands
				pConsole->RegisterCommand(0,	"quit",		"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"exit",		"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"bye",		"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"logout",	"",	"",	Functor<void, ConsoleCommand &>(&SceneApplication::ConsoleCommandQuit, this));

				// Set active state
				pConsole->SetActive(m_bEditModeEnabled);
			}
		}

		// Set the root scene
		SetRootScene(pRootContainer);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
