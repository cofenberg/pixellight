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
#include <PLGeneral/System/System.h>
#include <PLCore/Base/Class.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
Application::Application() : BasicSceneApplication(),
	EventHandlerKeyDown(&Application::OnKeyDown, this),
	m_nCurrentSelectedModifier(0)
{
	// Set application name and title
	SetName("PLDemoPostProcess");
	SetTitle(PLT("PL post process demo"));
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
void Application::OnKeyDown(uint32 nKey, uint32 nModifiers)
{
	switch (nKey) {
		// Check whether the escape key was pressed
		case PLGUIKEY_ESCAPE:
			// Shut down the application
			Exit(0);
			break;

		// Show/hide the help text
		case PLGUIKEY_F1:
		{
			// Get the info text scene node
			SceneNode *pSceneNode = GetRootScene() ? GetRootScene()->GetByName("InfoText") : nullptr;
			if (pSceneNode) {
				// Toggle the active state of the scene node
				pSceneNode->SetActive(!pSceneNode->IsActive());
			}
			break;
		}

		// Toggle post processing
		case PLGUIKEY_SPACE:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Loop through all available post process scene node modifiers
				uint32			   nIndex    = 0;
				SceneNodeModifier *pModifier = pCamera->GetModifier("PLCompositing::SNMPostProcess", nIndex);
				while (pModifier) {
					// Toggle the active state of the post process scene node modifier
					pModifier->SetActive(!pModifier->IsActive());

					// Next modifier, please
					pModifier = pCamera->GetModifier("PLCompositing::SNMPostProcess", ++nIndex);
				}
			}
			break;
		}

		// Next post process effect
		case PLGUIKEY_PRIOR:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Increase the current selected modifier index
				m_nCurrentSelectedModifier++;
				if (m_nCurrentSelectedModifier >= m_lstModifierClasses.GetNumOfElements())
					m_nCurrentSelectedModifier = 0;

				// Remove all old modifiers add the new one
				pCamera->ClearModifiers();
				pCamera->AddModifier(m_lstModifierClasses[m_nCurrentSelectedModifier]->GetClassName());
			}
			break;
		}

		// Previous post process effect
		case PLGUIKEY_NEXT:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Decrease the current selected modifier index
				if (m_nCurrentSelectedModifier)
					m_nCurrentSelectedModifier--;
				else
					m_nCurrentSelectedModifier = m_lstModifierClasses.GetNumOfElements()-1;

				// Remove all old modifiers add the new one
				pCamera->ClearModifiers();
				pCamera->AddModifier(m_lstModifierClasses[m_nCurrentSelectedModifier]->GetClassName());
			}
			break;
		}

		// Custom post process effect: "Rainbow"
		case PLGUIKEY_1:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new one
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessCrazyBars", "ColorScaleY=\"0.002\"");
			}
			break;
		}

		// Custom post process effect: "Cartoon"
		case PLGUIKEY_2:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new ones
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "LuminanceConvert=\"-0.2125 -0.7154 -0.0721\"");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessCombineMultiplicate");
			}
			break;
		}

		// Custom post process effect: "Animated cartoon"
		case PLGUIKEY_3:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new ones
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "LuminanceConvert=\"-0.2125 -0.7154 -0.0721\"");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessOldFilm");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessCombineMultiplicate");
			}
			break;
		}

		// Custom post process effect: "Animated old cartoon"
		case PLGUIKEY_4:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new ones
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "LuminanceConvert=\"-0.2125 -0.7154 -0.0721\"");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessCombineMultiplicate");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessOldFilm");
			}
			break;
		}

		// Custom post process effect: "Scatch"
		case PLGUIKEY_5:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new one
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "LuminanceConvert=\"-0.2125 -0.7154 -0.0721\"");
			}
			break;
		}

		// Custom post process effect: "Animated old scatch"
		case PLGUIKEY_6:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new ones
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "LuminanceConvert=\"-0.2125 -0.7154 -0.0721\"");
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessOldFilm");
			}
			break;
		}

		// Custom post process effect: "Edeg glow"
		case PLGUIKEY_7:
		{
			SceneNode *pCamera = reinterpret_cast<SceneNode*>(GetCamera());
			if (pCamera) {
				// Remove all old modifiers add the new one
				pCamera->ClearModifiers();
				pCamera->AddModifier("PLPostProcessEffects::SNMPostProcessEdgeDetect", "Filename=\"Data/PostProcesses/EdgeGlow.pp\"");
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
		pWidget->SignalKeyDown.Connect(&EventHandlerKeyDown);
		// [TODO] Linux: Currently we need to listen to the content widget key signals as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget)
			pWidget->GetContentWidget()->SignalKeyDown.Connect(&EventHandlerKeyDown);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Create a scene node with the soldier mesh
	cContainer.Create("PLScene::SNMesh", "Soldier", "Position=\"0.0 -0.7 -4.0\" Scale=\"0.008 0.008 0.008\" Mesh=\"Data/Meshes/Soldier.mesh\"");

	// Create a nice particle effect behind the soldier
	cContainer.Create("PLParticleGroups::PGMagic2", "Magic2", "Position=\"0.0 0.0 -25.0\"");

	// Create a moving light source to illuminate the scene
	cContainer.Create("PLScene::SNPointLight", "Light", "Position=\"1.0 2.0 -2.0\" Flags=\"Flares|Corona|Blend\" Range=\"15.0\"");

	// Create a camera - this time we increase the camera FOV to get a better space feeling :)
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FixedCamera", "Position=\"0.0 0.0 -2.5\" Rotation=\"0.0 180.0 0.0\" FOV=\"60\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		// Make this to our main scene camera
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));

		// Get class list of all available post process scene node modifiers
		m_lstModifierClasses.Clear();
		PLCore::ClassManager::GetInstance()->GetClasses(m_lstModifierClasses, "PLCompositing::SNMPostProcess", PLCore::Recursive, PLCore::NoBase, PLCore::NoAbstract);

		// 'Activate' the first effect
		if (m_lstModifierClasses.GetNumOfElements())
			pCamera->AddModifier(m_lstModifierClasses[m_nCurrentSelectedModifier]->GetClassName());
	}

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = static_cast<SPScene*>(pPainter);
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);
	}

	// Within the parent container...
	SceneContainer *pContainer = cContainer.GetContainer();
	if (pContainer) {
		// Add our information text scene nodes
		SceneNode *pInfoText = pContainer->Create("PLScene::SceneContainer", "InfoText", "Flags=\"NoCulling\"");
		if (pInfoText && pInfoText->IsInstanceOf("PLScene::SceneContainer")) {
			SceneContainer *pInfoTextContainer = static_cast<SceneContainer*>(pInfoText);
			pInfoTextContainer->Create("PLScene::SNText2D", '0', "Position=\"0.01 0.01\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("'F1'        = Show/hide this help text")       + '\"');
			pInfoTextContainer->Create("PLScene::SNText2D", '1', "Position=\"0.01 0.03\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("'Space'     = Enable/disable post processing") + '\"');
			pInfoTextContainer->Create("PLScene::SNText2D", '2', "Position=\"0.01 0.05\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("'1-7'       = Custom post process effects")    + '\"');
			pInfoTextContainer->Create("PLScene::SNText2D", '3', "Position=\"0.01 0.07\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("'Page up'   = Next post process effect")       + '\"');
			pInfoTextContainer->Create("PLScene::SNText2D", '4', "Position=\"0.01 0.09\" Flags=\"No3DPosition|NoCenter\" Text=\"" + PLT("'Page down' = Previous post process effect")   + '\"');
		}
	}

	// Set scene container
	SetScene(&cContainer);
}
