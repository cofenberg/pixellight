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
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Performs a calculation by using a script
*/
float Application::DoCalculation(const PLGeneral::String &sScriptFilename, float fFirst, float fSecond)
{
	float fResult = 0.0f;

	// Create the script instance
	Script *pScript = ScriptManager::GetInstance()->CreateFromFile(sScriptFilename);
	if (pScript) {
		float fFactor = 0.0f;

		{ // Call the script function "getFactor"
			// Get the typed dynamic parameters
			Params<float> cParams;

			// Call the script function
			FuncScriptPtr<float>(pScript, "getFactor").Call(cParams);

			// Get the result
			fFactor = cParams.Return;
		}

		// Call the script function "setFactor"
		FuncScriptPtr<void, float>(pScript, "setFactor").Call(Params<void, float>(fFactor + 1.0f));

		{ // Call the script function "calculate"
			// Get the typed dynamic parameters
			Params<float, float, float> cParams(fFirst, fSecond);

			// Call the script function
			FuncScriptPtr<float, float, float>(pScript, "calculate").Call(cParams);

			// Get the result
			fResult = cParams.Return;
		}

		// Print message
		System::GetInstance()->GetConsole().Print(pScript->GetScriptLanguage() + " script language: '" + sScriptFilename + "' input was " + fFirst + " and " + fSecond + ", result is " + fResult + '\n');

		// Cleanup
		delete pScript;
	}

	// Done
	return fResult;
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
	DoCalculation("Data/Scripts/Calculate.lua", 42.0f, 5.0f);
	DoCalculation("Data/Scripts/Calculate.js", 42.0f, 5.0f);
	DoCalculation("Data/Scripts/Calculate.as", 42.0f, 5.0f);
}
