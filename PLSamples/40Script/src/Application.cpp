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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LoadableManager.h>
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

	// Get the script source code
	const String sSourceCode = LoadableManager::GetInstance()->LoadStringFromFile(sScriptFilename);
	if (sSourceCode.GetLength()) {
		// Create the script instance by using the extension of the given filename to detect the script language
		Script *pScript = ScriptManager::GetInstance()->Create(ScriptManager::GetInstance()->GetScriptLanguageByExtension(Url(sScriptFilename).GetExtension()));
		if (pScript) {
			// Print the name of the used script language
			System::GetInstance()->GetConsole().Print("-- " + pScript->GetScriptLanguage() + " script language --\n");

			// Functor pointing to the static method "Application::StaticMethod"
			Functor<int, int> cStaticMethod(StaticMethod);

			// Functor pointing to the member method "Application::Method"
			Functor<int, int> cMethod(&Application::Method, this);

			// Functor pointing to the script function "scriptFunction"
			Functor<int, int> cScriptFunction(new FuncScriptPtr<int, int>(pScript, "scriptFunction"));

			// Tell our script about those functors so that we can use them within the script...
			pScript->AddDynamicFunction("cppFunction", cStaticMethod);
			pScript->AddDynamicFunction("cppMethod",   cMethod);

			// The following is possible as well: Script is calling C++, C++ is calling script... *g*
			pScript->AddDynamicFunction("cppScriptFunction", cScriptFunction);
			// ... although it depends on the used internal script API whether or not it actually works without issues. With
			// the Lua API there are no issues, but AngelScript can't run another AngelScript while one is already running.
			// But using this way, one can e.g. call an AngelScript function from inside a Lua script function...
			// But in general, to be on the safe side, don't do such crazy things... although, hm... *g*

			// Set the script source code
			if (pScript->SetSourceCode(sSourceCode)) {
				float fFactor = 0.0f;

				{ // Some functor fun
					// Call functors - as you can see, there's no difference whether it's a static method, a member method or a script function
					const int  nValue				 = 42;
					const int  nFunctionResult		 = cStaticMethod(nValue);
					const int  nMethodResult		 = cMethod(nValue);
					const int  nScriptFunctionResult = cScriptFunction(nValue);
					const bool bFunctorResultsEqual  = (nFunctionResult == nValue && nMethodResult == nValue && nScriptFunctionResult == nValue);
					System::GetInstance()->GetConsole().Print(String("Same functor behaviour: ") + (bFunctorResultsEqual ? "Yes" : "No") + '\n');

					{ // Call the script function "callCpp"
						// Get the typed dynamic parameters
						Params<int, int> cParams(nValue);

						// Call the script function
						FuncScriptPtr<int, int>(pScript, "callCpp").Call(cParams);

						// Get and check result
						const bool bEqual = (cParams.Return == (nFunctionResult + nMethodResult + nScriptFunctionResult));
						System::GetInstance()->GetConsole().Print(String("Dynamic function behaviour as expected: ") + (bEqual ? "Yes" : "No") + '\n');
					}
				}

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
				System::GetInstance()->GetConsole().Print('\'' + sScriptFilename + "' input was " + fFirst + " and " + fSecond + ", result is " + fResult + '\n');
			}

			// Cleanup
			delete pScript;

			// Print new line
			System::GetInstance()->GetConsole().Print("--\n\n");
		}
	}

	// Done
	return fResult;
}

/**
*  @brief
*    A method
*/
int Application::Method(int nFirst)
{
	return nFirst;
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    A static method
*/
int Application::StaticMethod(int nFirst)
{
	return nFirst;
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
	DoCalculation("Data/Scripts/Calculate.py", 42.0f, 5.0f);
}
