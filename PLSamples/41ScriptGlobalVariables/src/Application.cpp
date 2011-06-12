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
#include <PLCore/Script/Script.h>
#include <PLCore/Script/ScriptManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;


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
*    Runs a script
*/
void Application::RunScript(const String &sScriptFilename)
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
			ETypeID nTypeID = pScript->GetGlobalVariableTypeID("g_Factor");

			// Get the current value of the global variable
			String sOriginalValue = pScript->GetGlobalVariable("g_Factor");
			System::GetInstance()->GetConsole().Print("The value of the global variable \"g_Factor\" is \"" + sOriginalValue + "\"\n");

			// Set the current value of the global variable
			pScript->SetGlobalVariable("g_Factor", Var<int>(42));

			// Get the current value of the global variable
			String sValue = pScript->GetGlobalVariable("g_Factor");
			if (sValue == "42")
				System::GetInstance()->GetConsole().Print("The value of the global variable \"g_Factor\" was changed successfully\n");

			// Reset the original value
			pScript->SetGlobalVariable("g_Factor", Var<String>(sOriginalValue));

			// The global variable "this" shouldn't exist, yet
			if (pScript->IsGlobalVariable("this")) {
				// Error, "this" should not happen...
				System::GetInstance()->GetConsole().Print("Failed to add the global variable \"this\" because it's already there!?\n");
			} else {
				// Add global variable "this"
				pScript->SetGlobalVariable("this", Var<String>("Jap, that's me!"));
				System::GetInstance()->GetConsole().Print(pScript->IsGlobalVariable("this") ? "Global variable \"this\" was added successfully\n" : "Failed to add the global variable \"this\"\n");
			}
		} else {
			System::GetInstance()->GetConsole().Print("There's no global variable with the name \"g_Factor\"\n");
		}

		// Cleanup
		delete pScript;

		// Print new line
		System::GetInstance()->GetConsole().Print("--\n");
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\" (see log for details)\n");
	}

	// Print new line
	System::GetInstance()->GetConsole().Print('\n');
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Get a list of supported script languages
	const Array<String> &lstScriptLanguages = ScriptManager::GetInstance()->GetScriptLanguages();
	for (uint32 i=0; i<lstScriptLanguages.GetNumOfElements(); i++) {
		// Get the name of the found script language
		const String sScriptLanguage = lstScriptLanguages[i];

		// Write the name of the found script language into the console
		System::GetInstance()->GetConsole().Print("- " + sScriptLanguage + '\n');

		// Get the filename extension of the found script language
		const String sScriptLanguageExtension = ScriptManager::GetInstance()->GetScriptLanguageExtension(sScriptLanguage);
		if (sScriptLanguageExtension.GetLength()) {
			// Run a script
			RunScript("Data/Scripts/41ScriptGlobalVariables." + sScriptLanguageExtension);
		} else {
			// This script language has no filename extension?!
			System::GetInstance()->GetConsole().Print("- " + sScriptLanguage + " has no filename extension\n");
		}

		// Write a new line into the console
		System::GetInstance()->GetConsole().Print('\n');
	}
}
