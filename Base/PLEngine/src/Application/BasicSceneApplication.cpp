/*********************************************************\
 *  File: BasicSceneApplication.cpp                      *
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
#include <PLCore/System/System.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneQuery.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLScene/Scene/SceneNodes/SNKeyValue.h>
#include <PLScene/Scene/SceneNodes/Console/ConsoleCommand.h>
#include <PLScene/Scene/SceneNodes/Console/SNConsoleBase.h>
#include "PLEngine/Application/BasicSceneApplication.h"


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
pl_implement_class(BasicSceneApplication)


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String BasicSceneApplication::DefaultSceneRenderer = "Forward.sr";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BasicSceneApplication::BasicSceneApplication(const String &sSceneFilename) : SceneApplication(sSceneFilename),
	EventHandlerSceneNode   (&BasicSceneApplication::OnSceneNode,    this),
	EventHandlerLoadProgress(&BasicSceneApplication::OnLoadProgress, this),
	m_sDefaultSceneRenderer(DefaultSceneRenderer),
	m_pFirstFoundCamera(nullptr),
	m_bHasLoadScreen(false)
{
	// Set application title
	SetTitle("PixelLight basic scene application");
}

/**
*  @brief
*    Destructor
*/
BasicSceneApplication::~BasicSceneApplication()
{
}

/**
*  @brief
*    Returns the scene container
*/
SceneContainer *BasicSceneApplication::GetScene() const
{
	// This cast is safe because we 'know' it can ONLY be a scene container!
	return static_cast<SceneContainer*>(m_cSceneContainerHandler.GetElement());
}

/**
*  @brief
*    Sets the scene container
*/
void BasicSceneApplication::SetScene(SceneContainer *pContainer)
{
	m_cSceneContainerHandler.SetElement(pContainer);
}

/**
*  @brief
*    Clears the scene, after calling this method the scene is empty
*/
void BasicSceneApplication::ClearScene()
{
	// Get the scene container holding our scene
	SceneContainer *pContainer = GetScene();
	if (pContainer) {
		// Clear the old scene
		pContainer->Clear();

		// Cleanup the scene context right now to ensure that all 'delete this'-marked scene nodes are really gone!
		// If this is not done, we may get problems with for example the names of dynamic textures because there may
		// occure name conflicts if multiple render-to-texture scene containers want to render into a same named texture...
		// Topics like 'the new scene is using resources that are already loaded in' must be handled on another level, e.g.
		// by delaying the unloading of currently unreferenced resources.
		if (m_pSceneContext)
			m_pSceneContext->Cleanup();
	}
}

/**
*  @brief
*    Get scene camera
*/
SNCamera *BasicSceneApplication::GetCamera() const
{
	// This cast is safe because we 'know' it can ONLY be a camera!
	return reinterpret_cast<SNCamera*>(m_cCameraHandler.GetElement());
}

/**
*  @brief
*    Get scene renderer tool
*/
SceneRendererTool &BasicSceneApplication::GetSceneRendererTool()
{
	// Return scene renderer tool
	return m_cSceneRendererTool;
}

/**
*  @brief
*    Get scene renderer tool
*/
const SceneRendererTool &BasicSceneApplication::GetSceneRendererTool() const
{
	// Return scene renderer tool
	return m_cSceneRendererTool;
}

/**
*  @brief
*    Get screenshot tool
*/
Screenshot &BasicSceneApplication::GetScreenshotTool()
{
	// Return screenshot tool
	return m_cScreenshot;
}


//[-------------------------------------------------------]
//[ Public virtual BasicSceneApplication functions        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets the scene camera
*/
void BasicSceneApplication::SetCamera(SNCamera *pCamera)
{
	// Deactivate the current camera
	if (m_cCameraHandler.GetElement())
		m_cCameraHandler.GetElement()->SetActive(false);

	// Set new camera
	m_cCameraHandler.SetElement(reinterpret_cast<SceneNode*>(pCamera));

	// Get scene surface painter... and inform it about the new set camera
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene"))
		static_cast<SPScene*>(pPainter)->SetCamera(pCamera);

	// Activate the new camera
	if (pCamera)
		reinterpret_cast<SceneNode*>(pCamera)->SetActive(true);

	// Emit signal
	SignalCameraSet();
}

bool BasicSceneApplication::LoadScene(const String &sFilename)
{
	// Get the scene container holding our scene
	SceneContainer *pContainer = GetScene();
	if (!pContainer)
		return false; // Error! (should NEVER happen...)

	// Ensure that the edit dialog is closed...
	CloseEditDialog();

	// Disable the ingame GUI
	SceneNode *pGui = pContainer->GetContainer()->GetByName("GUI");
	if (pGui)
		pGui->SetActive(false);

	// Clear the scene, after calling this method the scene is empty
	ClearScene();

	// Load the scene
	bool bResult = pContainer->Load(sFilename);
	if (bResult) {
		// Set a null pointer camera and default scene renderer
		m_pFirstFoundCamera = nullptr;
		m_sStartCamera		= "";
		m_bHasLoadScreen	= false;

		// Get scene surface painter
		SurfacePainter *pPainter = GetPainter();
		if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
			// Reset to default scene renderer
			m_sDefaultSceneRenderer = DefaultSceneRenderer;

			// Sets all scene renderer pass attribute values to their default value
			GetSceneRendererTool().SetDefaultValues();

			// Assign the first found camera scene node to your surface listener and look for
			// known key/value data scene nodes
			SceneQuery *pSceneQuery = pContainer->CreateQuery("PLScene::SQEnumerate");
			if (pSceneQuery) {
				// Connect event handler
				pSceneQuery->SignalSceneNode.Connect(EventHandlerSceneNode);

				// Perform the query
				pSceneQuery->PerformQuery();

				// Destroy the query
				pContainer->DestroyQuery(*pSceneQuery);
			}

			// Set the used scene renderer
			GetSceneRendererTool().SetSceneRenderer(pContainer, m_sDefaultSceneRenderer, DefaultSceneRenderer);

			// Is there a given start camera?
			SceneNode *pCamera = nullptr;
			if (m_sStartCamera.GetLength()) {
				SceneNode *pStartCamera = pContainer->GetByName(m_sStartCamera);
				if (pStartCamera && pStartCamera->IsCamera())
					pCamera = pStartCamera;
			}

			// Use the first found camera?
			if (!pCamera)
				pCamera = m_pFirstFoundCamera;

			// Activate the current used camera by default
			if (pCamera)
				pCamera->SetActive(true);

			// Assign this camera to the scene renderer and to the application
			SetCamera(reinterpret_cast<SNCamera*>(pCamera));

			// Post process keys
			for (uint32 i=0; i<m_lstPostKeys.GetNumOfElements(); i++) {
				const SNKeyValue *pKeyValue = m_lstPostKeys[i];

				// SceneRendererVariables
				if (pKeyValue && pKeyValue->Key.GetString() == "SceneRendererVariables") {
					// Sets scene renderer pass attribute values using a string
					GetSceneRendererTool().SetValues(pKeyValue->Value.GetString());
				}
			}
		}
		m_lstPostKeys.Clear();

		// Emit the scene loading has been finished successfully event
		SignalSceneLoadingFinished();
	}

	// Enable the ingame GUI
	if (pGui)
		pGui->SetActive(true);

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Protected virtual ConsoleApplication functions        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to OnInit()
*/
bool BasicSceneApplication::Init()
{
	// Call base implementation
	if (SceneApplication::Init()) {
		// Initialize scene renderer tool
		m_cSceneRendererTool.SetPainter(GetPainter());

		// Initialize screenshot tool
		m_cScreenshot.SetRendererContext(GetRendererContext());
		m_cScreenshot.SetPainter(GetPainter());

		// Set screenshot directory
		if (m_bMultiUser)
			m_cScreenshot.SetScreenshotDirectory(System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir);
		else
			m_cScreenshot.SetScreenshotDirectory(System::GetInstance()->GetCurrentDir());

		// Done
		return true;
	}

	// Error
	return false;
}


//[-------------------------------------------------------]
//[ Protected virtual SceneApplication functions          ]
//[-------------------------------------------------------]
void BasicSceneApplication::OnCreateRootScene()
{
	// Get the scene context
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		// First, create the scene root container which holds the scene container with our 'concrete' scene within it
		SceneContainer *pRootContainer = pSceneContext->GetRoot() ? static_cast<SceneContainer*>(pSceneContext->GetRoot()->Create("PLScene::SceneContainer", "RootScene")) : nullptr;
		if (pRootContainer) {
			// Protect this important container!
			pRootContainer->SetProtected(true);

			// Create a scene container with our 'concrete scene'
			SceneNode *pSceneContainerNode = pRootContainer->Create("PLScene::SceneContainer", "Scene");
			if (pSceneContainerNode && pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer")) {
				SceneContainer *pSceneContainer = static_cast<SceneContainer*>(pSceneContainerNode);

				// Protect this important container!
				pSceneContainer->SetProtected(true);

				// Connect event handler
				if (pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer"))
					static_cast<SceneContainer*>(pSceneContainerNode)->SignalLoadProgress.Connect(EventHandlerLoadProgress);

				// Create the 'concrete scene'
				OnCreateScene(*pSceneContainer);
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
				pConsole->RegisterCommand(0,	"quit",			"",	"",	Functor<void, ConsoleCommand &>(&BasicSceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"exit",			"",	"",	Functor<void, ConsoleCommand &>(&BasicSceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"bye",			"",	"",	Functor<void, ConsoleCommand &>(&BasicSceneApplication::ConsoleCommandQuit, this));
				pConsole->RegisterCommand(0,	"logout",		"",	"",	Functor<void, ConsoleCommand &>(&BasicSceneApplication::ConsoleCommandQuit, this));

				// Edit commands
				pConsole->RegisterCommand(1,	"editdialog",	"",	"",	Functor<void, ConsoleCommand &>(&BasicSceneApplication::ConsoleCommandEditDialog, this));

				// Set active state
				pConsole->SetActive(m_bEditModeEnabled);
			}
		}

		// Set the root scene
		SetRootScene(pRootContainer);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual BasicSceneApplication functions     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to create the application's scene container
*/
void BasicSceneApplication::OnCreateScene(SceneContainer &cContainer)
{
	// [TODO] Load 'm_sSceneFilename' if provided

	// Set scene container flags
	cContainer.SetFlags(SceneNode::NoCulling | SceneNode::NoPause);

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = static_cast<SPScene*>(pPainter);
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);
	}

	// Create a camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "Camera");
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

	// Create a scene node with the statue mesh which can produce a shadow
	cContainer.Create("PLScene::SNMesh", "Box", "Position=\"0.0 0.0 -5.0\" Mesh=\"Default\"");

	// Set scene container
	SetScene(&cContainer);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a scene node was found
*/
void BasicSceneApplication::OnSceneNode(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// Is this a camera?
	if (cSceneNode.IsCamera()) {
		if (!m_pFirstFoundCamera)
			m_pFirstFoundCamera = &cSceneNode;

		// Deactivate all camera's by default
		cSceneNode.SetActive(false);

	// Key/value data scene node?
	} else if (cSceneNode.IsInstanceOf("PLScene::SNKeyValue")) {
		const SNKeyValue &cKeyValue = static_cast<const SNKeyValue&>(cSceneNode);

		// SceneRenderer
		if (cKeyValue.Key.GetString() == "SceneRenderer") {
			m_sDefaultSceneRenderer = cKeyValue.Value.GetString();

		// SceneRendererVariables
		} else if (cKeyValue.Key.GetString() == "SceneRendererVariables") {
			m_lstPostKeys.Add(&cKeyValue);

		// ClearColor
		} else if (cKeyValue.Key.GetString() == "ClearColor") {
			// Get scene surface painter
			SurfacePainter *pPainter = GetPainter();
			if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
				SceneRenderer *pSceneRenderer = static_cast<SPScene*>(pPainter)->GetDefaultSceneRenderer();
				if (pSceneRenderer) {
					SceneRendererPass *pSceneRendererPass = pSceneRenderer->GetByName("Begin");
					if (pSceneRendererPass)
						pSceneRendererPass->SetAttribute("ColorClear", cKeyValue.Value.GetString());
				}
			}

		// StartCamera
		} else if (cKeyValue.Key.GetString() == "StartCamera") {
			m_sStartCamera = cKeyValue.Value.GetString();
		}

	// Load screen scene node?
	} else if (cSceneNode.IsInstanceOf("PLScene::SNLoadScreenBase")) {
		m_bHasLoadScreen = true;
	}
}

/**
*  @brief
*    Called on load progress
*/
void BasicSceneApplication::OnLoadProgress(float fLoadProgress)
{
	// Call the 'update'-function so we can see the progress within the load screen
	if (m_bHasLoadScreen)
		Update();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
