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
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/File/Url.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Script/Script.h>
#include <PLCore/Script/FuncScriptPtr.h>
#include <PLCore/Script/ScriptManager.h>
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
using namespace PLCore;
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
// A helper to be able to toggle between 'choose resource file at start' and 'load
// default resource at start' (quite comfortable if you make many experiments :)
const String Application::DefaultFilename = "";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	SlotOnKeyDown(this),
	SlotOnDrop(this),
	m_pFileDialog(nullptr),
	m_pScript(nullptr)
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
	m_cCommandLine.AddArgument("Filename", "Resource (e.g. scene or script) filename", "", false);
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
*    Returns the base directory of the application
*/
String Application::GetBaseDirectory() const
{
	return m_sCurrentSceneBaseDirectory;
}

/**
*  @brief
*    Sets the base directory of the application
*/
void Application::SetBaseDirectory(String sBaseDirectory)
{
	// Is the given base directory absolute?
	if (!Url(sBaseDirectory).IsAbsolute()) {
		// Nope - if there's currently a script running, use it's absolute filename as start point
		if (m_pScript) {
			// Get the directory the script is in
			const String sDirectory = Url(m_sScriptFilename).Collapse().CutFilename();

			// Construct the application base directory
			sBaseDirectory = sDirectory + sBaseDirectory;
		}
	}

	// Remove the current application base directory from the loadable manager
	if (m_sCurrentSceneBaseDirectory.GetLength())
		PLCore::LoadableManager::GetInstance()->RemoveBaseDir(m_sCurrentSceneBaseDirectory);

	// Set the new application base directory
	m_sCurrentSceneBaseDirectory = sBaseDirectory;

	// Add the given base directory to the loadable manager
	if (m_sCurrentSceneBaseDirectory.GetLength())
		PLCore::LoadableManager::GetInstance()->AddBaseDir(m_sCurrentSceneBaseDirectory);
}

/**
*  @brief
*    Openes a file dialog in which the user can choose a resource
*/
String Application::ChooseFilename()
{
	// [TODO] PLGui
	return "";
	/*
	// Create and show a file choose dialog in which the user can select a resource file which should be loaded
	if (m_pFileDialog && m_pFileDialog->IsVisible())
		return "";

	// Create the choose file dialog
	if (!m_pFileDialog) {
		m_pFileDialog = new DialogChooseFile();
		m_pFileDialog->SetTitle(PLT("Choose resource"));

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
*    Loads a resource
*/
bool Application::LoadResource(const String &sFilename)
{
	// Get file extension
	const String sExtension = Url(sFilename).GetExtension();
	if (sExtension.GetLength()) {
		// Is the given filename a supported scene?
		if (LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "Scene")) {
			// Is the given resource a scene?
			if (LoadScene(sFilename)) {
				// Done, get us out of here right now!
				return true;
			} else {
				// Write an error message into the log
				PL_LOG(Error, "Failed to load the scene \"" + sFilename + '\"')
			}

		// Is the given file a supported script?
		} else if (ScriptManager::GetInstance()->GetScriptLanguageByExtension(sExtension).GetLength()) {
			// Load the script
			if (LoadScript(sFilename)) {
				// Done, get us out of here right now!
				return true;
			} else {
				// Write an error message into the log
				PL_LOG(Error, "Failed to load the script \"" + sFilename + '\"')
			}

		// Unknown file-type
		} else {
			// Write an error message into the log
			PL_LOG(Error, "Failed to load the resource \"" + sFilename + "\" because the file-type is unknown")
		}
	} else {
		// Write an error message into the log
		PL_LOG(Error, "Failed to load the resource \"" + sFilename + "\" because the file has no extension")
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads a scene
*/
bool Application::LoadScene(const String &sFilename)
{
	{ // Make the directory of the scene to load in to the application base directory
		// Validate path
		const String sDirectory = Url(sFilename).Collapse().CutFilename();

		// Search for "/Data/Scenes/" and get the prefix of that
		String sBaseDirectory;
		int nIndex = sDirectory.IndexOf("/Data/Scenes/");
		if (nIndex >= 0)
			sBaseDirectory = sDirectory.GetSubstring(0, nIndex);
		sBaseDirectory = "file://" + sBaseDirectory + '/';

		// Set the base directory of the application
		SetBaseDirectory(sBaseDirectory);
	}

	// Load the scene
	return BasicSceneApplication::LoadScene(sFilename);
}

/**
*  @brief
*    Loads a script
*/
bool Application::LoadScript(const String &sFilename)
{
	// Destroy the currently used script
	DestroyScript();

	// Create the script instance
	m_pScript = ScriptManager::GetInstance()->CreateFromFile(sFilename);
	if (m_pScript) {
		// Backup the script filename
		m_sScriptFilename = sFilename;

		// Add the global variable "this" to the script so that it's able to access "this" RTTI class instance
		m_pScript->SetGlobalVariable("this", Var<Object*>(this));

		// Call the initialize script function
		FuncScriptPtr<void>(m_pScript, "OnInit").Call(Params<void>());

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Destroys the currently used script
*/
void Application::DestroyScript()
{
	// Is there a script?
	if (m_pScript) {
		// Call the de-initialize script function
		FuncScriptPtr<void>(m_pScript, "OnDeInit").Call(Params<void>());

		// Destroy the used script instance
		delete m_pScript;
		m_pScript = nullptr;
		m_sScriptFilename = "";
	}
}

/**
*  @brief
*    Called when a key is pressed down
*/
void Application::OnKeyDown(uint32 nKey, uint32 nModifiers)
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
void Application::OnDrop(const DataObject &cDataObject)
{
	// Load resource (if it's one :)
	LoadResource(cDataObject.GetFiles()[0]);
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
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
	// Call base implementation
	BasicSceneApplication::OnInit();

	// Filename given?
	String sFilename = m_cCommandLine.GetValue("Filename");
	if (!sFilename.GetLength()) {
		// Get the filename of the default by using the PLViewer configuration
		const String sConfigDefault = GetConfig().GetVar("PLViewerConfig", "DefaultFilename");
		if (sConfigDefault.GetLength()) {
			// Set the default filename
			sFilename = sConfigDefault;
		} else {
			// Load a default resource on start?
			if (DefaultFilename.GetLength()) {
				// Set the default filename
				sFilename = DefaultFilename;
			} else {
				// Choose the filename
				sFilename = ChooseFilename();
			}
		}
	}

	// Is there a name given?
	if (sFilename.GetLength()) {
		// Load resource (if it's one :)
		if (LoadResource(sFilename))
			return; // Done, get us out of here right now!
	} else {
		// Error, no scene given
	}

	// Set exit code to error
	Exit(1);
}

void Application::DeInit()
{
	// Destroy the currently used script
	DestroyScript();

	// Call base implementation
	BasicSceneApplication::DeInit();
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
		pWidget->SignalDrop.   Connect(&SlotOnDrop);
		// [TODO] Linux: Currently we need to listen to the content widget key signals as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget) {
			pWidget->GetContentWidget()->SignalKeyDown.Connect(&SlotOnKeyDown);
			pWidget->GetContentWidget()->SignalDrop.   Connect(&SlotOnDrop);
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::RenderApplication functions ]
//[-------------------------------------------------------]
bool Application::OnUpdate()
{
	// Is there a script?
	if (m_pScript) {
		// Call the update script function
		FuncScriptPtr<void>(m_pScript, "OnUpdate").Call(Params<void>());
	}

	// Call base implementation
	return BasicSceneApplication::OnUpdate();
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
