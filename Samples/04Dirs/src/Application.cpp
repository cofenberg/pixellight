/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Runtime.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
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
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void Application::Main()
{
	// System directories
	System::GetInstance()->GetConsole().Print("System directories:\n");
	System::GetInstance()->GetConsole().Print("- Executable:    " + System::GetInstance()->GetExecutableFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Home:          " + System::GetInstance()->GetUserHomeDir() + '\n');
	System::GetInstance()->GetConsole().Print("- Data:          " + System::GetInstance()->GetUserDataDir() + '\n');
	System::GetInstance()->GetConsole().Print("- Current:       " + System::GetInstance()->GetCurrentDir() + '\n');
	System::GetInstance()->GetConsole().Print('\n');

	// PixelLight runtime directories (usually you only need "Runtime::GetDirectory()" and "Runtime::GetDirectoryData()")
	System::GetInstance()->GetConsole().Print("PixelLight runtime directories:\n");
	System::GetInstance()->GetConsole().Print("- Local:         " + Runtime::GetLocalDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Local data:    " + Runtime::GetLocalDataDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- System:        " + Runtime::GetSystemDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- System data:   " + Runtime::GetSystemDataDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Registry:      " + Runtime::GetRegistryDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Registry data: " + Runtime::GetRegistryDataDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Runtime:       " + Runtime::GetDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Runtime data:  " + Runtime::GetDataDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- PLCore:        " + Runtime::GetPLCoreSharedLibraryDirectory() + '\n');
	System::GetInstance()->GetConsole().Print('\n');

	// Application context
	System::GetInstance()->GetConsole().Print("Application context:\n");
	System::GetInstance()->GetConsole().Print("- Executable:    " + GetApplicationContext().GetExecutableFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Startup:       " + GetApplicationContext().GetStartupDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- AppDir:        " + GetApplicationContext().GetAppDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Log:           " + GetApplicationContext().GetLogFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Config:        " + GetApplicationContext().GetConfigFilename() + '\n');
	System::GetInstance()->GetConsole().Print('\n');
}
