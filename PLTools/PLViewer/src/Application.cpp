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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SPScene.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGui;
using namespace PLRenderer;
using namespace PLScene;
using namespace PLEngine;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application)


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
// A helper to be able to toggle between 'choose scene file at start' and 'load
// default scene at start' (quite comfortable if you make many experiments :)
const String Application::DefaultScene = "";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	SlotNotifyKeyDown(this),
	SlotNotifyDrop(this),
	m_pFileDialog(nullptr)
{
	// Set no multiuser if standalone application
	#ifdef STANDALONE
		SetMultiUser(false);
		SetName("PLViewerStandalone");
	#else
		SetName("PLViewer");
	#endif

	// Set application name and title
	SetTitle(PLT("PixelLight viewer"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));

	// This application accepts all the standard parameters that are defined in the application
	// base class (such as --help etc.). The last parameter however is the filename to load, so add that.
	m_cCommandLine.AddFlag("Standalone", "-s", "--standalone", "Standalone application, write log and configuration into the directory the executable is in", false);
	m_cCommandLine.AddArgument("Filename", "Scene filename", "", false);
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
	// PLGui will destroy the file dialog automatically...
}

/**
*  @brief
*    Openes a file dialog in which the user can choose a scene
*/
String Application::ChooseScene()
{
	// [TODO] PLGui
	return "";
	/*
	// Create and show a file choose dialog in which the user can select a scene file which should be loaded
	if (m_pFileDialog && m_pFileDialog->IsVisible())
		return "";

	// Create the choose file dialog
	if (!m_pFileDialog) {
		m_pFileDialog = new DialogChooseFile();
		m_pFileDialog->SetTitle(PLT("Choose scene"));

		// Add 'scene' file filter
		m_pFileDialog->AddFiltersFromLoadableType("Scene", true, false);

		// Add 'all files' file filter
		m_pFileDialog->AddFilter("*.*", PLT("All files"));

		// Setup the other stuff...
		m_pFileDialog->SetMode(false, true);

		// Set the start directory
		m_pFileDialog->SetStartDir(System::GetInstance()->GetCurrentDir() + "/Data/Scenes/");
	}

	// Show choose file dialog
	m_pFileDialog->GetGui()->ShowDialogModal(*m_pFileDialog, GetMainWindow());
	return m_pFileDialog->GetSelectedFile();
	*/
}

/**
*  @brief
*    Loads a scene
*/
bool Application::LoadScene(const String &sFilename)
{
	// Remove the base directory of the previously loaded scene from the loadable manager
	if (m_sCurrentSceneBaseDirectory.GetLength())
		PLCore::LoadableManager::GetInstance()->RemoveBaseDir(m_sCurrentSceneBaseDirectory);
	m_sCurrentSceneBaseDirectory = "";

	{ // Add the base directory of the scene to load is in
		// Validate path
		const String sDirectory = Url(sFilename).Collapse().CutFilename();

		// Search for "/Data/Scenes/" and get the prefix of that
		int nIndex = sDirectory.IndexOf("/Data/Scenes/");
		if (nIndex >= 0)
			m_sCurrentSceneBaseDirectory = sDirectory.GetSubstring(0, nIndex);
		m_sCurrentSceneBaseDirectory = "file://" + m_sCurrentSceneBaseDirectory + '/';

		// Add the base directory of the current scene to the loadable manager
		PLCore::LoadableManager::GetInstance()->AddBaseDir(m_sCurrentSceneBaseDirectory);
	}

	// Load the scene
	return BasicSceneApplication::LoadScene(sFilename);
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
	// Make a screenshot from the current render target
	if (nKey == PLGUIKEY_F12)
		GetScreenshotTool().SaveScreenshot();

	// Toggle mouse cursor visibility
	else if (nKey == PLGUIKEY_M) {
		// Get the system GUI
		Gui *pGui = Gui::GetSystemGui();
		if (pGui) {
			// Toggle mouse cursor visibility
			pGui->SetMouseVisible(!pGui->IsMouseVisible());
		}
	}

	// Exit viewer
	else if (nKey == PLGUIKEY_ESCAPE) {
		Exit(0);
	}
}

/**
*  @brief
*    Called when something was dropped down
*/
void Application::NotifyDrop(const DataObject &cDataObject)
{
	// Load scene (if it's one :)
	LoadScene(cDataObject.GetFiles()[0]);
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::ConsoleApplication functions ]
//[-------------------------------------------------------]
void Application::OnInitLog()
{
	// Check 'Standalone' commando line flag
	if (m_cCommandLine.IsValueSet("Standalone"))
		SetMultiUser(false);

	// Call base implementation
	BasicSceneApplication::OnInitLog();
}

void Application::OnInit()
{
	// Scene filename given?
	String sSceneFilename = m_cCommandLine.GetValue("Filename");
	if (!sSceneFilename.GetLength()) {
		// Get the filename of the default scene by using the PLViewer configuration
		const String sConfigDefaultScene = GetConfig().GetVar("PLViewerConfig", "DefaultScene");
		if (sConfigDefaultScene.GetLength()) {
			// Set the default scene
			sSceneFilename = sConfigDefaultScene;
		} else {
			// Load a default scene on start?
			if (DefaultScene.GetLength()) {
				// Set the default scene
				sSceneFilename = DefaultScene;
			} else {
				// Choose the scene filename
				sSceneFilename = ChooseScene();
			}
		}
	}

	// Is there a scene name given?
	if (sSceneFilename.GetLength()) {
		// Load scene
		if (!LoadScene(sSceneFilename)) {
			// Present the user an sweet 'ERROR!!!'-message
			// [TODO] PLGui
			// pWindow->GetGui()->MessageBox("Error", "Failed to load the given scene, the program will terminate now.\nHave a look into the log for detailed information.");

			// Set exit code to error
			Exit(1);
		}
	} else {
		// No scene given
		Exit(1);
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
		pWidget->SignalKeyDown.Connect(&SlotNotifyKeyDown);
		pWidget->SignalDrop.   Connect(&SlotNotifyDrop);
		// [TODO] Linux: Currently we need to listen to the content widget key signals as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget) {
			pWidget->GetContentWidget()->SignalKeyDown.Connect(&SlotNotifyKeyDown);
			pWidget->GetContentWidget()->SignalDrop.   Connect(&SlotNotifyDrop);
		}
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

	// [TODO] PLGui
	/*
	// Within the parent container...
	SceneContainer *pContainer = cContainer.GetContainer();
	if (pContainer) {
		// Create a 'ingame'-GUI scene node
		const SNGui *pGuiSceneNode = static_cast<SNGui*>(pContainer->Create("PLScene::SNGui", "GUI"));
		if (pGuiSceneNode) {
			// Setup the GUI
			Gui *pGui = static_cast<Gui*>(pGuiSceneNode->GetGui());
			if (pGui) {
				pGui->SetTooltipEnabled(false);
				pGui->SetMouseVisible(false);

				// Create ingame GUI container
				Window *pGuiContainer = new GuiContainer(*this, pGui);
				pGuiContainer->SetSize(1024, 768);
				pGuiContainer->SetBackgroundColor(PLGraphics::Color4::Transparent);
				pGuiContainer->SetFocus(true);
				pGuiContainer->SetVisible(true);
			}
		}
	}
	*/

	// Set scene container
	SetScene(&cContainer);
}
