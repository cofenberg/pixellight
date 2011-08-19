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
#include "MyRTTIClass.h"
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
Application::Application() : CoreApplication(),
	SlotOnMySignal(this),
	m_pMyRTTIClass(new MyRTTIClass())
{
	// Connect event handler
	m_pMyRTTIClass->MySignal.Connect(SlotOnMySignal);

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
	// Destroy the RTTI object instance
	delete m_pMyRTTIClass;
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
	// Get the script source code
	const String sSourceCode = LoadableManager::GetInstance()->LoadStringFromFile(sScriptFilename);
	if (sSourceCode.GetLength()) {
		// Create the script instance by using the extension of the given filename to detect the script language
		Script *pScript = ScriptManager::GetInstance()->Create(ScriptManager::GetInstance()->GetScriptLanguageByExtension(Url(sScriptFilename).GetExtension()));
		if (pScript) {
			// Tell the script about "Application::GetMyRTTIClassInstance"
			pScript->AddGlobalFunction("GetMyRTTIClassInstance", Functor<MyRTTIClass*, MyRTTIClass*>(&Application::GetMyRTTIClassInstance, this));

			// Set the script source code
			if (pScript->SetSourceCode(sSourceCode)) {
				// Print the name of the used script language
				System::GetInstance()->GetConsole().Print("-- " + pScript->GetScriptLanguage() + " script language --\n");

				// Call the script function "OOP"
				FuncScriptPtr<void>(pScript, "OOP").Call(Params<void>());

				{ // Call the script function "UseCppRTTIObject"
					Params<MyRTTIClass*, MyRTTIClass*> cParams(m_pMyRTTIClass);
					FuncScriptPtr<MyRTTIClass*, MyRTTIClass*>(pScript, "UseCppRTTIObject").Call(cParams);
					if (cParams.Return != m_pMyRTTIClass)
						System::GetInstance()->GetConsole().Print("Error, script returned invalid RTTI object instance!\n");
				}

				// Cleanup
				delete pScript;

				// Print new line
				System::GetInstance()->GetConsole().Print("--\n");
			} else {
				// Error!
				System::GetInstance()->GetConsole().Print("Failed to use the script source code \"" + sScriptFilename + "\"\n");
			}
		}
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Failed to load the script \"" + sScriptFilename + "\"\n");
	}

	// Print new line
	System::GetInstance()->GetConsole().Print('\n');
}

/**
*  @brief
*    Called on MySignal signal
*/
void Application::OnMySignal(String sParameter)
{
	System::GetInstance()->GetConsole().Print(sParameter + " emitted MySignal signal\n");
}

/**
*  @brief
*    Returns the MyRTTIClass instance
*/
MyRTTIClass *Application::GetMyRTTIClassInstance(MyRTTIClass *pObject)
{
	return (pObject == m_pMyRTTIClass) ? m_pMyRTTIClass : nullptr;
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
			RunScript("Data/Scripts/44ScriptOOP." + sScriptLanguageExtension);
		} else {
			// This script language has no filename extension?!
			System::GetInstance()->GetConsole().Print(sScriptLanguage + " has no filename extension\n");
		}

		// Write a new line into the console
		System::GetInstance()->GetConsole().Print('\n');
	}
}
