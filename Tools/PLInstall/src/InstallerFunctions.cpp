/*********************************************************\
 *  File: InstallerFunctions.cpp                                     *
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
#include "InstallerFunctions.h"

#include <PLCore/Runtime.h>
#include <PLCore/File/Url.h>
#include <PLCore/System/System.h>

//[-------------------------------------------------------]
//[ using namespace                                       ]
//[-------------------------------------------------------]
using namespace PLCore;

//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
InstallerFunctions::InstallerFunctions()
{

}

/**
*  @brief
*    Destructor
*/
InstallerFunctions::~InstallerFunctions()
{

}

void InstallerFunctions::connectProgressEventHandler(PLCore::EventHandler<int> *pProgressEventHandler)
{
	m_pEventProgressUpdate.Connect(*pProgressEventHandler);
}

bool InstallerFunctions::installRuntime()
{/**

	// Install the PixelLight runtime

	// Get the directory this executable is in and add the  platform architecture
	const String sExecutableDirectory =  Url(sExecutableFilename).Collapse().CutFilename() +  System::GetInstance()->GetPlatformArchitecture() + '/';
	// In case  PLInstall is not within the runtime directory, but I assume this will  never be the case because the new installer is using the Qt shared libraries
	const String sExecutableDirectory =  Url(sExecutableFilename).Collapse().CutFilename();

	// Write the PL-runtime directory into the registry
	if (Runtime::SetDirectory(sExecutableDirectory, &sMessage))
		sMessage = "PixelLight runtime installed at \"" +  sExecutableDirectory + "\"\n\nYou may need to restart your system";   
	// Success
	else
		sMessage = "Failed to write the PL-runtime directory into  the registry: \"" + sMessage + '\"';                            // Error
	**/
	return false;
}

int InstallerFunctions::getInstallRuntimeProgressSteps()
{
	return INSTALL_RUNTIME_PROGRESS_STEPS;
}

bool InstallerFunctions::checkRuntimeInstallation()
{	 
    // Get the current PL-runtime directory (e.g.  "C:\PixelLight\Runtime\x86")
    // -> Do also ensure that the registry entry is pointing to the same directory the PLCore shared library is in
    const String sDirectory = Runtime::GetDirectory();
	m_pEventProgressUpdate(1);
	const String sPLCoreSharedLibraryDirectory = Runtime::GetPLCoreSharedLibraryDirectory();
	String tes = Url(sPLCoreSharedLibraryDirectory).GetNativePath();
	m_pEventProgressUpdate(1);
	const String sRegistryDirectory = Runtime::GetRegistryDirectory();
	m_pEventProgressUpdate(1);

	
    if (sDirectory.GetLength() &&  sPLCoreSharedLibraryDirectory ==  sRegistryDirectory)
    {
		// The PixelLight runtime is already installed
		//the PATH environment or the registry key is pointing to the current directory => PL is installed correctly
		m_pEventProgressUpdate(1);
		m_sLastSuccessMessage = "PixelLight runtime is already installed at \"" +  sDirectory + '\"';
		return true;
	}

	m_pEventProgressUpdate(1);
	// the pl runtime could not be found => the runtime isn't installed correctly 
	m_sLastErrorMessage = L"The PLRuntime directory could not be found.";
	return false;
}

int InstallerFunctions::getCheckRuntimeProgressSteps()
{
	return CHECK_RUNTIME_PROGRESS_STEPS;
}

String InstallerFunctions::getLastErrorDescription()
{
	return m_sLastErrorMessage;
}

String InstallerFunctions::getLastSuccessMessage()
{
	return m_sLastSuccessMessage;
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]



