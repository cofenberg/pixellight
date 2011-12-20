/*********************************************************\
 *  File: InstallerFunctions.cpp                         *
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
#include <PLCore/Runtime.h>
#include <PLCore/File/Url.h>
#include <PLCore/System/System.h>
#include "InstallerFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
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

void InstallerFunctions::ConnectProgressEventHandler(EventHandler<int> *pProgressEventHandler)
{
	m_cEventProgressUpdate.Connect(*pProgressEventHandler);
}

bool InstallerFunctions::InstallRuntime()
{
	// Install the PixelLight runtime

	// I know it's a bit redundand but we should check the current installation
	if (!CheckRuntimeInstallation()) {
		m_cEventProgressUpdate(1);

		// Get the directory this executable is in
		// -> There's no need to add platform architecture information because this executable is directly within the proper runtime directory
		m_cEventProgressUpdate(1);
		const String sExecutableDirectory = System::GetInstance()->GetCurrentDir();
		m_cEventProgressUpdate(1);

		// Write the PixelLight-runtime directory into the registry and or path or whatever is needed on the specific plattform
		String sMessage;
		if (Runtime::SetDirectory(sExecutableDirectory, &sMessage)) {
			m_sLastSuccessMessage = "PixelLight runtime installed at \"" +  Url(sExecutableDirectory).GetNativePath() + "\"\n\nYou may need to restart your system";	// Show the user a native path he's familiar with
			m_cEventProgressUpdate(1);

			// Success
			return true;
		} else {
			// Error!
			m_sLastErrorMessage = "Failed to write the PixelLight-runtime directory into the registry: \"" + sMessage + '\"';
			m_cEventProgressUpdate(1);

			// Error ocurred!
			return false;
		}
	}

	// The PixelLight runtime is already installed
	m_cEventProgressUpdate(4);

	// Success
	return true;
}

int InstallerFunctions::GetInstallRuntimeProgressSteps() const
{
	return INSTALL_RUNTIME_PROGRESS_STEPS;
}

bool InstallerFunctions::CheckRuntimeInstallation()
{
	// Get the current PixelLight runtime directory (e.g. "file://C:/PixelLight/Runtime/x86" on Windows)
	// -> Do also ensure that the registry entry is pointing to the same directory the PLCore shared library is in
	const String sDirectory = Runtime::GetDirectory();
	m_cEventProgressUpdate(1);
	const String sPLCoreSharedLibraryDirectory = Runtime::GetPLCoreSharedLibraryDirectory();

	m_cEventProgressUpdate(1);
	const String sRegistryDirectory = Runtime::GetRegistryDirectory();
	// [TODO] Windows: One thing... "Runtime::GetPLCoreSharedLibraryDirectory()" is going to load "PLCore.dll" and the OS will also have a look
	// into the directory PLInstall is in, meaning this dll will be found even if the directory is not within the PATH environment variable.
	// -> So, this test is pointless because it will always tell us "Yes, I was able to find PLCore.dll" :/
	// -> We probably should access the PATH environment variable by using the registry
	m_cEventProgressUpdate(1);

	if (sDirectory.GetLength() && sPLCoreSharedLibraryDirectory == sRegistryDirectory) {
		// The PATH environment or the registry key is pointing to the current directory => PixelLight is already installed correctly
		m_cEventProgressUpdate(1);
		m_sLastSuccessMessage = "PixelLight runtime is already installed at \"" +  Url(sDirectory).GetNativePath() + '\"';	// Show the user a native path he's familiar with

		// Success
		return true;
	}

	// The PixelLight runtime could not be found => the runtime isn't installed correctly
	m_cEventProgressUpdate(1);
	m_sLastErrorMessage = "The PixelLight runtime directory could not be found";

	// Error!
	return false;
}

int InstallerFunctions::GetCheckRuntimeProgressSteps() const
{
	return CHECK_RUNTIME_PROGRESS_STEPS;
}

String InstallerFunctions::GetLastErrorDescription() const
{
	return m_sLastErrorMessage;
}

String InstallerFunctions::GetLastSuccessMessage() const
{
	return m_sLastSuccessMessage;
}
