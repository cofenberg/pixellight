/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight Sample 43 - Script bindings
 *      Simple 'Script Bindings'-Application using the PixelLight application framework
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
#include <PLCore/Main.h>
#include <PLCore/Runtime.h>
#include <PLCore/ModuleMain.h>
#include <PLCore/Log/Log.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/Script/Script.h>
#include <PLCore/Script/FuncScriptPtr.h>
#include <PLCore/Script/ScriptManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("43ScriptBindings")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight Sample 43 - Script bindings")
pl_module_end


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Runs a script
*/
void RunScript(const String &sScriptFilename)
{
	// Create the script instance
	// -> The RTTI script binding "ScriptBindingSample" class instance methods will be automatically available to the script as simple global functions
	Script *pScript = ScriptManager::GetInstance()->CreateFromFile(sScriptFilename);
	if (pScript) {
		// Print the name of the used script language
		System::GetInstance()->GetConsole().Print("-- " + pScript->GetScriptLanguage() + " script language --\n");

		// Call the script function "Bindings"
		FuncScriptPtr<void>(pScript, "Bindings").Call(Params<void>());

		// Cleanup
		delete pScript;

		// Print new line
		System::GetInstance()->GetConsole().Print("--\n");
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\"\n");
	}

	// Print new line
	System::GetInstance()->GetConsole().Print('\n');
}


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Scan PL-runtime directory for compatible plugins and load them in
	Runtime::ScanDirectoryPlugins();

	// Bring the log into the verbose mode so that the log also writes log entries
	// directly into the console. This way, we can e.g. see script errors at once.
	Log::GetInstance()->SetVerbose(true);

	// Do only show us error messages within the log
	Log::GetInstance()->SetLogLevel(Log::Error);

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
			RunScript("Data/Scripts/43ScriptBindings." + sScriptLanguageExtension);
		} else {
			// This script language has no filename extension?!
			System::GetInstance()->GetConsole().Print(sScriptLanguage + " has no filename extension\n");
		}

		// Write a new line into the console
		System::GetInstance()->GetConsole().Print('\n');
	}

	// Done
	return 0;
}
