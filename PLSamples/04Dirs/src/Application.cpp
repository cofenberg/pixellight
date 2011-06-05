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
#include <PLCore/Core.h>
#include <PLCore/Tools/Localization.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


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
Application::Application() : PLCore::ConsoleApplication()
{
	// Set application name and title
	SetName("04Dirs");
	SetTitle(PLT("PLSample 04 - Directories"));
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
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::Main()
{
	System::GetInstance()->GetConsole().Print("System directories:\n");
	System::GetInstance()->GetConsole().Print("- Executable: " + System::GetInstance()->GetExecutableFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Home:       " + System::GetInstance()->GetUserHomeDir() + '\n');
	System::GetInstance()->GetConsole().Print("- Data:       " + System::GetInstance()->GetUserDataDir() + '\n');
	System::GetInstance()->GetConsole().Print("- Current:    " + System::GetInstance()->GetCurrentDir() + '\n');
	System::GetInstance()->GetConsole().Print('\n');

	System::GetInstance()->GetConsole().Print("PixelLight directories:\n");
	System::GetInstance()->GetConsole().Print("- Runtime:    " + PLCore::Core::GetRuntimeDirectory() + '\n');
	System::GetInstance()->GetConsole().Print('\n');

	System::GetInstance()->GetConsole().Print("Application context:\n");
	System::GetInstance()->GetConsole().Print("- Executable: " + GetApplicationContext().GetExecutableFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Startup:    " + GetApplicationContext().GetStartupDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- AppDir:     " + GetApplicationContext().GetAppDirectory() + '\n');
	System::GetInstance()->GetConsole().Print("- Log:        " + GetApplicationContext().GetLogFilename() + '\n');
	System::GetInstance()->GetConsole().Print("- Config:     " + GetApplicationContext().GetConfigFilename() + '\n');
	System::GetInstance()->GetConsole().Print('\n');
}
