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
	SetName("40Script");
	SetTitle(PLT("PLSample 40 - Script"));
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
//[ Private virtual ConsoleApplication functions          ]
//[-------------------------------------------------------]
void Application::Main()
{
	// [TODO] Script support is currently under construction

	// Get the instance of the script manager singleton
	ScriptManager *pScriptManager = ScriptManager::GetInstance();

	{ // Get a list of supported script languages
		const Array<String> &lstScriptLanguages = pScriptManager->GetScriptLanguages();
		System::GetInstance()->GetConsole().Print("Supported script languages:\n");
		for (uint32 i=0; i<lstScriptLanguages.GetNumOfElements(); i++)
			System::GetInstance()->GetConsole().Print("- " + lstScriptLanguages[i] + '\n');
		System::GetInstance()->GetConsole().Print('\n');
	}

	// Lua
	if (pScriptManager->IsSupported("Lua")) {
		System::GetInstance()->GetConsole().Print("Using Lua script language\n");
		Script *pScript = pScriptManager->Create("Lua");
		delete pScript;
	}

	// JavaScript
	if (pScriptManager->IsSupported("JavaScript")) {
		System::GetInstance()->GetConsole().Print("Using JavaScript script language\n");
		Script *pScript = pScriptManager->Create("JavaScript");
		delete pScript;
	}

	// Python
	if (pScriptManager->IsSupported("Python")) {
		System::GetInstance()->GetConsole().Print("Using Python script language\n");
		Script *pScript = pScriptManager->Create("Python");
		delete pScript;
	}
}
