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
#include <PLCore/Log/Log.h>
#include <PLCore/File/Url.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Script/Script.h>
#include <PLCore/Script/FuncScriptPtr.h>
#include <PLCore/Script/ScriptManager.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
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
Application::Application() : CoreApplication()
{
	// Bring the log into the verbose mode so that the log also writes log entries
	// directly into the console. This way, we can e.g. see script errors at once.
	Log::GetInstance()->SetVerbose(true);

	// Do only show us error messages within the log
	Log::GetInstance()->SetLogLevel(Log::Error);
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
float Application::RunScript(const String &sScriptFilename, float fFirst, float fSecond)
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

			// Functor pointing to the static method "Application::StaticStringMethod"
			Functor<String, String> cStaticStringMethod(StaticStringMethod);

			// Functor pointing to the member method "Application::Method"
			Functor<int, int> cMethod(&Application::Method, this);

			// Functor pointing to the script function "ScriptFunction"
			Functor<int, int> cScriptFunction(new FuncScriptPtr<int, int>(pScript, "ScriptFunction"));

			// Tell our script about those functors so that we can use them within the script...
			pScript->AddGlobalFunction("CppFunction", cStaticMethod, "FirstNamespace.SecondNamespace");
			pScript->AddGlobalFunction("CppStringFunction", cStaticStringMethod);
			pScript->AddGlobalFunction("CppMethod", cMethod);

			// The following is possible as well: Script is calling C++, C++ is calling script... *g*
			pScript->AddGlobalFunction("CppScriptFunction", cScriptFunction);
			// ... although it depends on the used internal script API whether or not it actually works without issues. With
			// the Lua, Python and V8 (JavaScript) API there are no issues, but AngelScript can't run another AngelScript while one is already running.
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

					{ // Call the script function "CallCpp"
						// Get the typed dynamic parameters
						Params<int, int> cParams(nValue);

						// Call the script function
						FuncScriptPtr<int, int>(pScript, "CallCpp").Call(cParams);

						// Get and check result
						const bool bEqual = (cParams.Return == (nFunctionResult + nMethodResult + nScriptFunctionResult));
						System::GetInstance()->GetConsole().Print(String("Global function behaviour as expected: ") + (bEqual ? "Yes" : "No") + '\n');
					}
				}

				{ // Call the script function "GetFactor"
					// Get the typed dynamic parameters
					Params<float> cParams;

					// Call the script function
					FuncScriptPtr<float>(pScript, "GetFactor").Call(cParams);

					// Get the result
					fFactor = cParams.Return;
				}

				// Call the script function "SetFactor"
				FuncScriptPtr<void, float>(pScript, "SetFactor").Call(Params<void, float>(fFactor + 1.0f));

				{ // Call the script function "Calculate"
					// Get the typed dynamic parameters
					Params<float, float, float> cParams(fFirst, fSecond);

					// Call the script function
					FuncScriptPtr<float, float, float>(pScript, "Calculate").Call(cParams);

					// Get the result
					fResult = cParams.Return;
				}

				{ // Call the script function "ReturnMyString"
					// Get the typed dynamic parameters
					Params<String, String> cParams("MyString");

					// Call the script function
					FuncScriptPtr<String, String>(pScript, "ReturnMyString").Call(cParams);

					// Check the result
					System::GetInstance()->GetConsole().Print(String("Got my string: ") + (cParams.Return == "MyString" ? "Yes" : "No") + '\n');
				}

				// Print message
				System::GetInstance()->GetConsole().Print('\'' + sScriptFilename + "' input was " + fFirst + " and " + fSecond + ", result is " + fResult + '\n');

				{ // Call the script function "SayHello" which is inside the "PublicFunctions"-namespace
					// Get the typed dynamic parameters
					Params<String> cParams;

					// Call the script function
					FuncScriptPtr<String>(pScript, "SayHello", "PublicFunctions").Call(cParams);

					// Get the result
					System::GetInstance()->GetConsole().Print("The script function \"SayHello\" which is inside the \"PublicFunctions\"-namespace says \"" + cParams.Return + "\"\n");
				}
			} else {
				// Error!
				System::GetInstance()->GetConsole().Print("Failed to use the script source code \"" + sScriptFilename + "\"\n");
			}

			// Cleanup
			delete pScript;

			// Print new line
			System::GetInstance()->GetConsole().Print("--\n");
		}
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\"\n");
	}

	// Print new line
	System::GetInstance()->GetConsole().Print('\n');

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

/**
*  @brief
*    A static string method
*/
String Application::StaticStringMethod(String sFirst)
{
	return sFirst;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
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
			RunScript("Data/Scripts/42ScriptFunctors." + sScriptLanguageExtension, 42.0f, 5.0f);
		} else {
			// This script language has no filename extension?!
			System::GetInstance()->GetConsole().Print(sScriptLanguage + " has no filename extension\n");
		}

		// Write a new line into the console
		System::GetInstance()->GetConsole().Print('\n');
	}
}
