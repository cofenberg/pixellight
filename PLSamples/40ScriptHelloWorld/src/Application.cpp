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
Application::Application() : PLCore::ConsoleApplication()
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
*    Calls the hello world script
*/
void Application::SayHello(const PLGeneral::String &sScriptFilename)
{
	// Create the script instance
	Script *pScript = ScriptManager::GetInstance()->CreateFromFile(sScriptFilename);
	if (pScript) {
		// Call the script function "sayHello"
		FuncScriptPtr<void>(pScript, "sayHello").Call(Params<void>());

		// Cleanup
		delete pScript;
	}
}


//[-------------------------------------------------------]
//[ Private virtual ConsoleApplication functions          ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Get the instance of the script manager singleton
	ScriptManager *pScriptManager = ScriptManager::GetInstance();

	{ // Get a list of supported script languages
		const Array<String> &lstScriptLanguages = pScriptManager->GetScriptLanguages();
		System::GetInstance()->GetConsole().Print("Supported script languages:\n");
		for (uint32 i=0; i<lstScriptLanguages.GetNumOfElements(); i++)
			System::GetInstance()->GetConsole().Print("- " + lstScriptLanguages[i] + '\n');
		System::GetInstance()->GetConsole().Print('\n');
	}

	// Run some scripts
	SayHello("Data/Scripts/HelloWorld.lua");
	SayHello("Data/Scripts/HelloWorld.js");
	SayHello("Data/Scripts/HelloWorld.as");
	SayHello("Data/Scripts/HelloWorld.py");
}
