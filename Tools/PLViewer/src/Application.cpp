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
#include <PLCore/File/Url.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Script/ScriptManager.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Button.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SPScene.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLInput;
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
Application::Application(Frontend &cFrontend) : ScriptApplication(cFrontend),
	SlotOnControl(this)
{
	// Set no multiuser if standalone application
	#ifdef STANDALONE
		SetMultiUser(false);
		SetName("PLViewerStandalone");
	#else
		SetName("PLViewer");
	#endif

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
}

/**
*  @brief
*    Loads a resource
*/
bool Application::LoadResource(const String &sFilename)
{
	bool bResult = false;	// Error by default

	// Get file extension
	const String sExtension = Url(sFilename).GetExtension();
	if (sExtension.GetLength()) {
		// Is the given filename a supported scene?
		if (LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "Scene")) {
			// Is the given resource a scene?
			if (LoadScene(sFilename)) {
				// Done, get us out of here right now!
				bResult = true;
			} else {
				// Write an error message into the log
				PL_LOG(Error, "Failed to load the scene \"" + sFilename + '\"')
			}

		// Is the given file a supported script?
		} else if (ScriptManager::GetInstance()->GetScriptLanguageByExtension(sExtension).GetLength()) {
			// Load the script
			if (LoadScript(sFilename)) {
				// Done, get us out of here right now!
				bResult = true;
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

	// Set the state text
	SetStateText(bResult ? sFilename : ("Failed to load \"" + sFilename + "\" (see log for details)"));

	// Done
	return bResult;
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
		if (cControl.GetName() == "KeyboardEscape") {
			// Shut down the application
			Exit(0);

		// Make a screenshot from the current render target
		} else if (cControl.GetName() == "KeyboardF12") {
			GetScreenshotTool().SaveScreenshot();

		// Toggle mouse cursor visibility
		} else if (cControl.GetName() == "KeyboardM") {
			// Toggle mouse cursor visibility
			GetFrontend().SetMouseVisible(!GetFrontend().IsMouseVisible());
		}
	}
}

/**
*  @brief
*    Sets the state text
*/
void Application::SetStateText(const String &sText)
{
	// Just misuse the frontend title to communicate with the user
	GetFrontend().SetTitle("PixelLight viewer - Use drag'n'drop to load in a scene/script - " + sText);
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void Application::OnInitLog()
{
	// Check 'Standalone' commando line flag
	if (m_cCommandLine.IsValueSet("Standalone"))
		SetMultiUser(false);

	// Call base implementation
	ScriptApplication::OnInitLog();
}

void Application::OnInit()
{
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
				// No filename provided
			}
		}
	}

	// Anything to load in?
	if (sFilename.GetLength()) {
		// Reset the current script file, else "ScriptApplication::OnInit()" will load and start the script given to it's constructor
		m_sScriptFilename = "";
	}

	// Call base implementation
	ScriptApplication::OnInit();

	// Load resource (if it's one :)
	if (sFilename.GetLength()) {
		// Load the resource
		LoadResource(sFilename);
	} else {
		// Set the state text
		SetStateText("Nothing loaded");
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::AbstractFrontend functions  ]
//[-------------------------------------------------------]
void Application::OnDrop(const Container<String> &lstFiles)
{
	// Load resource (if it's one :)
	LoadResource(lstFiles[0]);
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateInputController()
{
	// Call base implementation
	ScriptApplication::OnCreateInputController();

	// Get virtual input controller
	Controller *pController = reinterpret_cast<Controller*>(GetInputController());
	if (pController)
		pController->SignalOnControl.Connect(SlotOnControl);
}


//[-------------------------------------------------------]
//[ Public virtual PLEngine::EngineApplication functions  ]
//[-------------------------------------------------------]
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

	// Call base implementation
	return ScriptApplication::LoadScene(sFilename);
}
