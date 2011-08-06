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
#include <PLCore/Log/Log.h>
#include <PLCore/Base/Class.h>
#include <PLCore/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Button.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLPhysics/Body.h>
#include <PLPhysics/World.h>
#include <PLPhysics/SceneNodes/SNRagdoll.h>
#include <PLPhysics/SceneNodes/RagdollBody.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLScene;
using namespace PLPhysics;


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
Application::Application() : EngineApplication(),
	SlotOnControl(this),
	m_pLine(nullptr),
	m_pRagdoll(nullptr),
	m_bApplyForce(false),
	m_bTorqueForce(false)
{
	// Set application name and title
	SetName("63PhysicsRagdoll");
	SetTitle(PLT("PL ragdoll physics sample"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));

	// Add command line argument for choosing the physics API
	m_cCommandLine.AddArgument("PhysicsAPI", "Physics API", "PLPhysicsNewton::World", false);
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
*    Returns the name of the used physics API
*/
String Application::GetPhysicsAPI() const
{
	return m_sPhysicsAPI;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function where the user has to choose the desired physics API
*/
bool Application::ChoosePhysicsAPI()
{
	// Because I'am pessimistic I expect by default that the user has canceled the choice *sigh*
	bool bResult = false; // Error by default

	// Are there multiple physics API's available?
	List<const PLCore::Class*> lstClasses;
	PLCore::ClassManager::GetInstance()->GetClasses(lstClasses, "PLPhysics::World", PLCore::Recursive, PLCore::NoBase, PLCore::NoAbstract);
	if (lstClasses.GetNumOfElements()) {
		if (lstClasses.GetNumOfElements() == 1) {
			// Get the class name of the physics API
			m_sPhysicsAPI = lstClasses[0]->GetClassName();

			// An API was 'chosen'...
			bResult = true; // Done
		} else {
			// Select the default physics API
			m_sPhysicsAPI = "PLPhysicsNewton::World";
			bResult = true; // Done
		}

		// Was an API chosen?
		if (bResult) {
			// Destroy the old root scene
			SceneContainer *pRootScene = GetRootScene();
			if (pRootScene) {
				// Setup scene surface painter
				SurfacePainter *pPainter = GetPainter();
				if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
					SPScene *pSPScene = static_cast<SPScene*>(pPainter);
					pSPScene->SetRootContainer(nullptr);
					pSPScene->SetSceneContainer(nullptr);
					pSPScene->SetCamera(nullptr);
				}

				// Destroy old root scene
				SetRootScene(nullptr);
				delete pRootScene;
			}

			// Reset variables
			m_pLine        = nullptr;
			m_pRagdoll     = nullptr;
			m_bApplyForce  = false;
			m_bTorqueForce = false;

			// Create new root scene
			OnCreateRootScene();
		}
	} else {
		PL_LOG(Error, "No physics API available")
	}

	// Done
	return bResult;
}

/**
*  @brief
*    Returns a PL physics body of the given ragdoll
*/
Body *Application::GetPhysicsBody() const
{
	// First at all, IS there a ragdoll?
	if (m_pRagdoll) {
		// Get a ragdoll body
		RagdollBody *pRagdollBody = m_pRagdoll->GetBody("Soldat Head");

		// Return the PL physics body of the selected ragdoll body
		if (pRagdollBody)
			return pRagdollBody->GetBody();
	}

	// Error!
	return nullptr;
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
		if (cControl.GetName() == "Escape") {
			// Shut down the application?
			Exit(0);

		// Reset the small falling physics box?
		} else if (cControl.GetName() == "R") {
			// Check your pointer to the ragdoll
			if (reinterpret_cast<Button&>(cControl).IsHit() && m_pRagdoll) {
				// Reset the position and rotation
				m_pRagdoll->GetTransform().SetPosition(Vector3(0.3f, 2.0f, 7.1f));
				m_pRagdoll->GetTransform().SetRotation(Quaternion::Identity);
				
				// Recreate the physics bodies
				m_pRagdoll->CreatePhysics();
			}

		// Apply a force to the ragdoll?
		} else if (cControl.GetName() == "F") {
			// Toggle state
			m_bApplyForce = !m_bApplyForce;

			// Update the line scene node
			if (m_pLine) {
				m_pLine->SetActive(m_bApplyForce);
				m_pLine->SetAttribute("StartPosition", "0.3 4.0 7.1");
			}

		// Apply a torque to the ragdoll?
		} else if (cControl.GetName() == "T") {
			// Toggle state
			m_bTorqueForce = !m_bTorqueForce;

		// Toggle gravity?
		} else if (cControl.GetName() == "G") {
			// Check your pointer to the ragdoll
			if (reinterpret_cast<Button&>(cControl).IsHit() && m_pRagdoll) {
				// Toggle state
				m_pRagdoll->SetAttribute("UseGravity", String::Format("%d", !m_pRagdoll->GetAttribute("UseGravity")->GetBool()));
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

	// Valid default physics API given?
	String sClassName = m_cCommandLine.GetValue("PhysicsAPI");
	if (sClassName.GetLength()) {
		const PLCore::Class *pClass = PLCore::ClassManager::GetInstance()->GetClass(sClassName);
		if (pClass && pClass->IsDerivedFrom("PLPhysics::World")) {
			m_sPhysicsAPI = sClassName;

			// Create new root scene
			OnCreateRootScene();
		}
	}

	// Choose physics API
	if (!m_sPhysicsAPI.GetLength() && !ChoosePhysicsAPI()) {
		// Error!
		Exit(1);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::AbstractFrontend functions    ]
//[-------------------------------------------------------]
void Application::OnUpdate()
{
	// One important word at the beginning: DON'T COPYCAT THIS!
	// The following is 'just' a simple demonstration how the scene graph 'can' be used. It's
	// definitely not good to update your scene nodes in the way you can see within this function.
	// Its quite to intricate, inflexible and not performant.

	// Call base implementation
	EngineApplication::OnUpdate();

	// Check your pointer to the ragdoll
	if (m_pRagdoll && (m_bApplyForce || m_bTorqueForce)) {
		Body *pBody = GetPhysicsBody();
		if (pBody && pBody->GetWorld().IsSimulationActive()) {
			// Apply force?
			if (m_bApplyForce) {
				Vector3 vPos;
				pBody->GetPosition(vPos);
				Vector3 vDir = (Vector3(0.3f, 4.0f, 7.1f) - vPos)*16;

				// Add a force to the start position of the box
				pBody->AddForce(vDir);

				// Update the line scene node
				if (m_pLine)
					m_pLine->SetAttribute("EndPosition", vPos.ToString());
			}

			// Apply torque?
			if (m_bTorqueForce) {
				// Add a torque
				pBody->AddTorque(Vector3(25.5f, 6.0f, 4.5f));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Set no scene container as default
	SetScene(nullptr);

	// Physics API given?
	if (m_sPhysicsAPI.GetLength()) {
		// Create a scene container with our 'concrete physics scene', the physics simulation is not active by default
		SceneNode *pSceneContainerNode = cContainer.Create("PLPhysics::SCPhysicsWorld", "Scene", "PhysicsAPI=\"" + m_sPhysicsAPI + "\" SimulationActive=\"0\"");
		if (pSceneContainerNode && pSceneContainerNode->IsInstanceOf("PLScene::SceneContainer")) {
			SceneContainer *pSceneContainer = static_cast<SceneContainer*>(pSceneContainerNode);

			// Protect this important container!
			pSceneContainer->SetProtected(true);

			// Populate the scene container
			// Create an static physics scene node with the 'floor' mesh
			SceneNode *pSceneNode = pSceneContainer->Create("PLScene::SNMesh", "Floor", "Position=\"0.0 -1.08 5.0\" Scale=\"10.0 0.1 10.0\" Mesh=\"Default\"");
			// Add Newton physics body modifier to the floor scene node
			if (pSceneNode)
				pSceneNode->AddModifier("PLPhysics::SNMPhysicsBodyBox");

			// Create a 'helper' scene node attached to the ragdoll and used as camera target
			pSceneContainer->Create("PLScene::SNHelper", "RagdollTargetHelper");

			// Throw in a cooool ragdoll into the scene :)
			m_pRagdoll = static_cast<SNRagdoll*>(pSceneContainer->Create("PLPhysics::SNRagdoll", "Ragdoll", "Position=\"0.3 2.0 7.1\" Scale=\"0.015 0.015 0.015\" Mesh=\"Data/Meshes/Soldier.mesh\" RagdollFilename=\"Data/Misc/Soldier.ragdoll\" InitFrozen=\"0\""));
			// Add an anchor scene node modifier attaching the camera target helper scene node to the ragdoll
			if (m_pRagdoll)
				m_pRagdoll->AddModifier("PLScene::SNMAnchor", "AttachedNode=\"RagdollTargetHelper\" PositionOffset=\"0.0 80.0 0.0\"");

			// Create a big static physics box scene node
			pSceneNode = pSceneContainer->Create("PLScene::SNMesh", "BigBox", "Position=\"1.5 0.0 5.5\" Scale=\"1.5 1.5 1.5\" Mesh=\"Default\"");
			// Add Newton physics body modifier to the floor scene node
			if (pSceneNode)
				pSceneNode->AddModifier("PLPhysics::SNMPhysicsBodyBox");

			// Create a static physics box scene node
			pSceneNode = pSceneContainer->Create("PLScene::SNMesh", "Box", "Position=\"0.3 0.0 7.5\" Scale=\"1.0 1.0 1.0\" Mesh=\"Default\"");
			// Add Newton physics body modifier to the floor scene node
			if (pSceneNode)
				pSceneNode->AddModifier("PLPhysics::SNMPhysicsBodyBox");

			// Create a 'line'
			m_pLine = pSceneContainer->Create("PLScene::SNLine", "Line");

			// Create a camera
			SceneNode *pCamera = pSceneContainer->Create("PLScene::SNCamera", "LookAtCamera", "Position=\"0.0 5.0 15.0\"");
			if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
				// Make this to our main scene camera
				SetCamera(reinterpret_cast<SNCamera*>(pCamera));

				// Add a 'look at' scene node modifier
				pCamera->AddModifier("PLScene::SNMRotationTarget", "Target=\"RagdollTargetHelper\"");
			}

			// Setup scene surface painter
			SurfacePainter *pPainter = GetPainter();
			if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
				SPScene *pSPScene = static_cast<SPScene*>(pPainter);
				pSPScene->SetRootContainer(cContainer.GetContainer());
				pSPScene->SetSceneContainer(pSceneContainer);
			}

			// Within the parent container...
			SceneContainer *pContainer = cContainer.GetContainer();
			if (pContainer) {
				// Add our information text scene nodes
				SceneNode *pInfoText = pContainer->Create("PLScene::SceneContainer", "InfoText", "Flags=\"NoCulling\"");
				if (pInfoText && pInfoText->IsInstanceOf("PLScene::SceneContainer")) {
					SceneContainer *pInfoTextContainer = static_cast<SceneContainer*>(pInfoText);
					
					// The name of the used physics API
					pInfoTextContainer->Create("PLScene::SNText2D", "PhysicsAPI", "Position=\"0.01 0.01\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("Physics API: ") + GetPhysicsAPI() + '\"');

					// Draw keys information
					pInfoTextContainer->Create("PLScene::SNText2D", "Keys",      "Position=\"0.01 0.04\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("Keys:")                        + '\"');
					pInfoTextContainer->Create("PLScene::SNText2D", "Reset",     "Position=\"0.06 0.08\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("r=Reset ragdoll")              + '\"');
					pInfoTextContainer->Create("PLScene::SNText2D", "AddForce",  "Position=\"0.06 0.10\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("f=Add force to the ragdoll")   + '\"');
					pInfoTextContainer->Create("PLScene::SNText2D", "AddTorque", "Position=\"0.06 0.12\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("t=Add torque to the ragdoll")  + '\"');
					pInfoTextContainer->Create("PLScene::SNText2D", "Gravity",   "Position=\"0.06 0.14\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("g=Toggle gravity")             + '\"');
				}
			}

			// Our scene is complete, now activate the physics simulation - let's rock'n'roll!
			pSceneContainer->SetAttribute("SimulationActive", "1");

			// Set scene container
			SetScene(pSceneContainer);
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
