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
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Gui/Resources/Font.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/Gui/SNGui.h>
#include "IngameGui.h"
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
//[ Public static data                                    ]
//[-------------------------------------------------------]
PLGui::Font *Application::GuiFont = nullptr;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	SlotOnKeyDown(this),
	m_pIngameGui(nullptr)
{
	// Set application name and title
	SetName("PLDemoIngameGUI");
	SetTitle(PLT("PL ingame GUI demo"));
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
	// Check whether the escape key was pressed
	if (nKey == PLGUIKEY_ESCAPE)
		// Shut down the application
		Exit(0);
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::ConsoleApplication functions ]
//[-------------------------------------------------------]
void Application::OnDeInit()
{
	// Destroy the GUI font
	if (GuiFont) {
		delete GuiFont;
		GuiFont = nullptr;
	}

	// Call base implementation
	BasicSceneApplication::OnDeInit();
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
		pWidget->SignalKeyDown.Connect(&SlotOnKeyDown);
		// [TODO] Linux: Currently we need to listen to the content widget key signals as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget)
			pWidget->GetContentWidget()->SignalKeyDown.Connect(&SlotOnKeyDown);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Set scene container flags
	cContainer.SetFlags(SceneNode::NoCulling | SceneNode::NoPause);

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
		// Create a 'ingame'-GUI scene node
		const SNGui *pGuiSceneNode = static_cast<SNGui*>(pContainer->Create("PLScene::SNGui", "GUI"));
		if (pGuiSceneNode) {
			// Setup the GUI
			Gui *pGui = pGuiSceneNode->GetGui();
			if (pGui) {
				// Create the GUI font
				if (!GuiFont) {
					GuiFont = new PLGui::Font(*pGui);
					GuiFont->LoadFromFile("Data/Fonts/LinLibertine_Re-2.7.9.9.otf", 18);
				}

				// Set GUI options
				pGui->SetMouseVisible(false);

				// Create ingame GUI container
				m_pIngameGui = new IngameGui(*this, pGui->GetRootWidget());
				m_pIngameGui->SetSize(Vector2i(1024, 768));
				m_pIngameGui->SetBackgroundColor(PLGraphics::Color4::Transparent);
				m_pIngameGui->SetFocus();
				m_pIngameGui->SetVisible(true);
			}
		}
	}

	// Set scene container
	SetScene(&cContainer);
}
