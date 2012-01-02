/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/File/File.h>
#include <PLCore/System/System.h>
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Script/ScriptManager.h>
#include <PLCore/Frontend/FrontendContext.h>
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
	{ // Set no multi-user if standalone application
		// -> In case the file "PLViewer.cfg" is in the same directory as the executable, or within one directory "above" (e.g. because there are "x86" and "x64" versions)
		//    run this application in "standalone-mode"
		// -> When shipping something by using PLViewer, experience tells that there's always such a file provided to set the desired settings, so, this is no drawback
		//    and this enables us to provide just one version of this executable
		const String sDirectory = cFrontend.GetContext().GetAppDirectory() + '/';
		if (File(sDirectory + GetConfigName()).IsFile() ||															// Windows example: "C:\MyApplication\PLViewer.cfg"
			File(sDirectory + System::GetInstance()->GetPlatformArchitecture() + '/' + GetConfigName()).IsFile()) {	// Windows example: "C:\MyApplication\x86\PLViewer.cfg"
			// The configuration file exists, so run this application in standalone mode (e.g. log and configuration will not be written into the user directory)
			SetMultiUser(false);
		}
	}

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
*    Loads a resource which type has to be evaluated internally
*/
bool Application::LoadResource(const String &sFilename)
{
	bool bResult = false;	// Error by default

	// Clear the scene, after calling this method the scene is empty
	ClearScene();

	// Get file extension
	const String sExtension = Url(sFilename).GetExtension();
	if (sExtension.GetLength()) {
		{ // Make the directory of the scene to load in to the current directory

			// Ok, the next thing is tricky, and every solution will end up in being a hack due to lack of information.
			// Within materials, meshes etc. there are usually relative paths provided, no absolute (not just true for PixelLight file formats).
			// Further, those paths are usually relative to a project root resulting e.g. within a default directory layout like
			// - Root
			//   - Data
			//     - Meshes
			//     - Materials
			// For "normal" projects this is no issue because everything is usually relative to the root project directory...
			// ... but this viewer must be able to pick out e.g. a mesh out of nowhere and must still be able to locate the required
			// other resources like materials. So, in here, we can only work with heuristics... this can and will of course go from
			// time to time horribly wrong...

			// First try: Find the first "Data" occurrence with the given filename and hope that it's the project root directory

			// Get filename as clean URL
			Url cUrl = Url(sFilename);
			cUrl.Collapse();

			// Get the first part of the path, and then look for "Data"
			uint32 nPathPos = 0;
			String sPart = cUrl.GetFirstPath(nPathPos);
			while (sPart != "Data" && sPart.GetLength())
				sPart = cUrl.GetNextPath(nPathPos);
			if (sPart == "Data") {
				// Set the current directory of the application
				System::GetInstance()->SetCurrentDir(cUrl.GetRoot() + cUrl.GetPath().GetSubstring(0, nPathPos - 5));	// -5 = Remove "Data/"
			} else {
				// Second try: Cut of "/Data/Scenes/" and hope that it's the project root directory.
				// If it's not there, take the directory the given resource is in.

				// Validate path
				const String sDirectory = cUrl.CutFilename();

				// Search for "/Data/Scenes/" and get the prefix of that, in case it's not there just use directly the scene directory
				const int nIndex = sDirectory.IndexOf("/Data/Scenes/");

				// Set the current directory of the application
				System::GetInstance()->SetCurrentDir("file://" + ((nIndex >= 0) ? sDirectory.GetSubstring(0, nIndex) : sDirectory) + '/');
			}
		}

		// The viewer supports loading in multiple resource types, but scenes and scripts are
		// the most important because most powerful ones, so give them the highest priority.
		// -> It would be possible to implement support for scripting so that e.g. a Lua script
		//    can be used to decide how to process a resource. But this viewer should be able to
		//    work without external data and should be kept as simple as possible, so we stick to C++.

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

		// Ask the loadable system for the resource type
		} else {
			// Get loadable type
			LoadableType *pLoadableType = LoadableManager::GetInstance()->GetTypeByExtension(sExtension);
			if (pLoadableType) {
				// Mesh
				if (pLoadableType->GetName() == "Mesh") {
					// Load the mesh
					if (LoadMesh(sFilename)) {
						// Done, get us out of here right now!
						bResult = true;
					} else {
						// Write an error message into the log
						PL_LOG(Error, "Failed to load the mesh \"" + sFilename + '\"')
					}

				// Material
				} else if (pLoadableType->GetName() == "Material") {
					// Load the material
					if (LoadMaterialImage(sFilename)) {
						// Done, get us out of here right now!
						bResult = true;
					} else {
						// Write an error message into the log
						PL_LOG(Error, "Failed to load the material \"" + sFilename + '\"')
					}

				// Image
				} else if (pLoadableType->GetName() == "Image") {
					// Load the image
					if (LoadMaterialImage(sFilename)) {
						// Done, get us out of here right now!
						bResult = true;
					} else {
						// Write an error message into the log
						PL_LOG(Error, "Failed to load the image \"" + sFilename + '\"')
					}
				}
			}

			// Unknown file-type?
			if (!bResult) {
				// Write an error message into the log
				PL_LOG(Error, "Failed to load the resource \"" + sFilename + "\" because the file-type is unknown")
			}
		}
	} else {
		// Write an error message into the log
		PL_LOG(Error, "Failed to load the resource \"" + sFilename + "\" because the file has no extension")
	}

	// Set the state text, show the user a native filename within the GUI
	SetStateText(bResult ? Url(sFilename).GetNativePath() : ("Failed to load \"" + Url(sFilename).GetNativePath() + "\" (see log for details)"));

	// Activated color gradient background within the scene renderer, or at least try it
	// -> The standard scene renderer compositions of PixelLight within "Standard.zip" always have an inactive "PLCompositing::SRPBackgroundColorGradient"-instance
	// -> By using a color gradient background, also completely black/gray/white etc. meshes can be seen which is a good thing as a default setting within this viewer
	GetSceneRendererTool().SetPassAttribute("BackgroundColorGradient", "Flags", "");

	// Done
	return bResult;
}

/**
*  @brief
*    Loads a mesh
*/
bool Application::LoadMesh(const String &sFilename)
{
	// Get the scene container (the 'concrete scene')
	SceneContainer *pSceneContainer = GetScene();
	if (pSceneContainer) {
		// Create a mesh scene node
		SceneNode *pPrimarySceneNode = pSceneContainer->Create("PLScene::SNMesh", "Mesh", "Mesh=\"" + sFilename + "\"");

		// Configure a generic scene
		ConfigureGenericScene(*pSceneContainer, pPrimarySceneNode);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Loads a material/image
*/
bool Application::LoadMaterialImage(const String &sFilename)
{
	// Get the scene container (the 'concrete scene')
	SceneContainer *pSceneContainer = GetScene();
	if (pSceneContainer) {
		// Create a scene node representing a simple box with the given material/image as skin
		SceneNode *pPrimarySceneNode = pSceneContainer->Create("PLScene::SNMesh", "Mesh", "Mesh=\"Default\" Skin=\"" + sFilename + "\"");

		// Configure a generic scene
		ConfigureGenericScene(*pSceneContainer, pPrimarySceneNode);

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
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


//[-------------------------------------------------------]
//[ Protected virtual Application functions               ]
//[-------------------------------------------------------]
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
//[ Protected virtual PLCore::CoreApplication functions   ]
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

		// Activated color gradient background within the scene renderer, or at least try it
		GetSceneRendererTool().SetPassAttribute("BackgroundColorGradient", "Flags", "");
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
