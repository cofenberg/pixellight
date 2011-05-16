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
#include <PLGeneral/System/Console.h>
#include <PLCore/Tools/Localization.h>
#include <PLScript/Script.h>
#include <PLScript/ScriptManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLScript;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() : ConsoleApplication()
{
	// Set application name and title
	SetName("41ScriptGlobalVariables");
	SetTitle(PLT("PLSample 41 - Global script variables"));
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
*    Performs some script stuff
*/
void Application::DoScriptStuff(const String &sScriptFilename)
{
	// Create the script instance
	Script *pScript = ScriptManager::GetInstance()->CreateFromFile(sScriptFilename);
	if (pScript) {
		// Print the name of the used script language
		System::GetInstance()->GetConsole().Print("-- " + pScript->GetScriptLanguage() + " script language --\n");

		{ // Enumerate all global variables
			// Get a list of all global variables
			const Array<String> &lstGlobalVariables = pScript->GetGlobalVariables();
			System::GetInstance()->GetConsole().Print(String("Number of global variables: ") + lstGlobalVariables.GetNumOfElements() + '\n');
			for (uint32 i=0; i<lstGlobalVariables.GetNumOfElements(); i++)
				System::GetInstance()->GetConsole().Print(String("- Global variable ") + i + ": \"" + lstGlobalVariables[i] + "\"\n");
		}

		// Check whether or not "g_Factor" is a global variable
		if (pScript->IsGlobalVariable("g_Factor")) {
			// Get the type of the global variable
			ETypeID nType = pScript->GetGlobalVariableType("g_Factor");

			// Get the current value of the global variable
			String sOriginalValue = pScript->GetGlobalVariable("g_Factor");
			System::GetInstance()->GetConsole().Print("The value of the global variable \"g_Factor\" is \"" + sOriginalValue + "\"\n");

			// Set the current value of the global variable
			pScript->SetGlobalVariable("g_Factor", "42");

			// Get the current value of the global variable
			String sValue = pScript->GetGlobalVariable("g_Factor");
			if (sValue == "42")
				System::GetInstance()->GetConsole().Print("The value of the global variable \"g_Factor\" was changed successfully\n");

			// Reset the original value
			pScript->SetGlobalVariable("g_Factor", sOriginalValue);
		} else {
			System::GetInstance()->GetConsole().Print("There's no global variable with the name \"g_Factor\"\n");
		}

		// Cleanup
		delete pScript;

		// Print new line
		System::GetInstance()->GetConsole().Print("--\n\n");
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\"\n");
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Run some scripts
	DoScriptStuff("Data/Scripts/41ScriptGlobalVariables.lua");
	DoScriptStuff("Data/Scripts/41ScriptGlobalVariables.js");
	DoScriptStuff("Data/Scripts/41ScriptGlobalVariables.as");
	DoScriptStuff("Data/Scripts/41ScriptGlobalVariables.py");
}
