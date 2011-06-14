/*********************************************************\
 *  File: ScriptApplication.cpp                          *
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
#include <PLCore/Script/Script.h>
#include <PLCore/Script/FuncScriptPtr.h>
#include <PLCore/Script/ScriptManager.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLEngine/Application/ScriptApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ScriptApplication::ScriptApplication() : BasicSceneApplication(),
	m_pScript(nullptr)
{
	// Set application title
	SetTitle("PixelLight script application");
}

/**
*  @brief
*    Constructor
*/
ScriptApplication::ScriptApplication(String sScriptFilename) : BasicSceneApplication(),
	m_sScriptFilename(sScriptFilename),
	m_pScript(nullptr)
{
	// Set application title
	SetTitle("PixelLight script application");
}

/**
*  @brief
*    Destructor
*/
ScriptApplication::~ScriptApplication()
{
	// The used script instance is destroyed within "DeInit()"
}

/**
*  @brief
*    Returns the base directory of the application
*/
String ScriptApplication::GetBaseDirectory() const
{
	return m_sCurrentSceneBaseDirectory;
}

/**
*  @brief
*    Sets the base directory of the application
*/
void ScriptApplication::SetBaseDirectory(String sBaseDirectory)
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
		LoadableManager::GetInstance()->RemoveBaseDir(m_sCurrentSceneBaseDirectory);

	// Set the new application base directory
	m_sCurrentSceneBaseDirectory = sBaseDirectory;

	// Add the given base directory to the loadable manager
	if (m_sCurrentSceneBaseDirectory.GetLength())
		LoadableManager::GetInstance()->AddBaseDir(m_sCurrentSceneBaseDirectory);
}


//[-------------------------------------------------------]
//[ Proteced virtual PLCore::ConsoleApplication functions ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when application should initialize itself
*/
void ScriptApplication::OnInit()
{
	// Call base implementation
	BasicSceneApplication::OnInit();

	// Is there a script filename?
	if (m_sScriptFilename.GetLength())
		LoadScript(m_sScriptFilename);
}

/**
*  @brief
*    Called when application should de-initialize itself
*/
void ScriptApplication::OnDeInit()
{
	// Destroy the currently used script
	DestroyScript();

	// Call base implementation
	BasicSceneApplication::OnDeInit();
}


//[-------------------------------------------------------]
//[ Proteced virtual RenderApplication functions          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called once per update loop
*/
bool ScriptApplication::OnUpdate()
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
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads a script
*/
bool ScriptApplication::LoadScript(const String &sFilename)
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
void ScriptApplication::DestroyScript()
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
