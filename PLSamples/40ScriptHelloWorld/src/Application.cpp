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
#include <PLScript/FuncScriptPtr.h>
#include <PLScript/ScriptManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLScript;


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
	SetName("40ScriptHelloWorld");
	SetTitle(PLT("PLSample 40 - Hello world script"));
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
		// Call the script function "SayHello"
		FuncScriptPtr<void>(pScript, "SayHello").Call(Params<void>());

		// Cleanup
		delete pScript;
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\" (see log for details)\n");
	}
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
			RunScript("Data/Scripts/40ScriptHelloWorld." + sScriptLanguageExtension);
		} else {
			// This script language has no filename extension?!
			System::GetInstance()->GetConsole().Print("- " + sScriptLanguage + " has no filename extension\n");
		}

		// Write a new line into the console
		System::GetInstance()->GetConsole().Print('\n');
	}
}
