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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() : ConsoleApplication()
{
	// Set application name and title
	SetName("43ScriptBindings");
	SetTitle(PLT("PLSample 43 - Script bindings"));
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
*    Calls the bindings script
*/
void Application::Bindings(const String &sScriptFilename)
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
	Bindings("Data/Scripts/43ScriptBindings.lua");
	Bindings("Data/Scripts/43ScriptBindings.js");
	Bindings("Data/Scripts/43ScriptBindings.as");
	Bindings("Data/Scripts/43ScriptBindings.py");
}
