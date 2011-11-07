/*********************************************************\
 *  File: InstallerFunctionsWindows.cpp                              *
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
#include <windows.h>
#undef Yield //problems with PLCore/System/System.h -> Yield() function (Windows has an old Yield function which is not used in win nt)
#undef GetSystemDirectory // problems with PLCore/Runtime.h -> GetSystemDirectory is a defined by the windows header
#include <PLCore/Runtime.h>
#include <PLCore/System/System.h>
#include <PLCore/String/String.h>
#include <PLCore/Registry/Registry.h>
// TODO this should be removed after correcting Runtime::GetSystemDirectory()
#include <PLCore/System/DynLib.h>
//-----------------

#include "InstallerFunctionsWindows.h"


//[-------------------------------------------------------]
//[ using namespace                                       ]
//[-------------------------------------------------------]
using namespace PLCore;

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
InstallerFunctionsWindows::InstallerFunctionsWindows() :
	lastErrorMessage("")
{
}

/**
*  @brief
*    Destructor
*/
InstallerFunctionsWindows::~InstallerFunctionsWindows()
{
}

Event<int>* InstallerFunctionsWindows::getProgressUpdateEvent()
{
	return &EventProgressUpdate;
}

//[-------------------------------------------------------]
//[ Protected virtual InstallerFunctionsImpl functions    ]
//[-------------------------------------------------------]

bool InstallerFunctionsWindows::installRuntime() 
{
	String regDir = Runtime::GetRegistryDirectory();
	EventProgressUpdate(1);
	String regDataDir = Runtime::GetRegistryDataDirectory();
	EventProgressUpdate(1);
	String sysDir = Runtime::GetSystemDirectory();
	String sysDirt = Runtime::GetDirectory();
	EventProgressUpdate(1);
	String sysDataDir = Runtime::GetSystemDataDirectory();
	EventProgressUpdate(1);
	String localDir = Runtime::GetLocalDirectory();
	EventProgressUpdate(1);
	String localDataDir = Runtime::GetLocalDataDirectory();
	EventProgressUpdate(1);
	Version plVersion = Runtime::GetVersion();
	EventProgressUpdate(1);
	String plSuffix = Runtime::GetSuffix();
	EventProgressUpdate(1);
	

	// Check Windows version
	if (CheckWindowsVersion()) {
		// Get current directory
		PLCore::String currentDir = PLCore::System::GetInstance()->GetCurrentDir();

		//check the system PATH 
		PLCore::String plSystemDir = Runtime::GetDirectory();

		// This step is optional
		// Add directory to PATH variable
		/**
		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Environment", 0, KEY_READ | KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			// Query size of PATH variable
			DWORD nPathSize = 0;
			RegQueryValueEx(hKey, L"PATH", 0, nullptr, nullptr, &nPathSize);
			nPathSize += _MAX_PATH + 8;
			wchar_t *pszPath = new wchar_t[nPathSize];

			// Query value of PATH variable
			DWORD nType;
			DWORD nSize = nPathSize;
			LSTATUS nResult = RegQueryValueEx(hKey, L"PATH", 0, &nType, (BYTE*)pszPath, &nSize);
			if (nResult == ERROR_FILE_NOT_FOUND) {
				// Write to registry
				RegSetValueEx(hKey, L"PATH", 0, REG_SZ, (BYTE*)szDir, (DWORD)sizeof(wchar_t)*wcslen(szDir));
				RegFlushKey(hKey);
			} else if (nResult == ERROR_SUCCESS) {
				// Get upper case version
				wchar_t *pszPathUpcase = new wchar_t[nSize];
				wcscpy(pszPathUpcase, pszPath);
				_wcsupr(pszPathUpcase);

				// Check if path is already set to this directory
				if (!wcsstr(pszPathUpcase, szDirUpcase)) {
					// Add directory to path
					if (wcslen(pszPath) && pszPath[wcslen(pszPath) - 1] != L';')
						wcscat(pszPath, L";");
					wcscat(pszPath, szDir);
					wcscat(pszPath, L";");

					// Write back to registry
					pszPath[wcslen(pszPath) + 1] = L'\0';
					RegSetValueEx(hKey, L"PATH", 0, nType, (BYTE*)pszPath, (DWORD)sizeof(wchar_t)*wcslen(pszPath));
					RegFlushKey(hKey);
				}

				// Release data
				if (pszPathUpcase)
					delete [] pszPathUpcase;
			}

			// Clean up
			if (pszPath)
				delete [] pszPath;
			RegCloseKey(hKey);
		} else {
			//[TODO] create error output
			//Message(L"Failed to open \"HKEY_CURRENT_USER\\Environment\"");
		}

		// Get PixelLight suffix and compose registry key from it
		wchar_t szSuffix[256];
		mbstowcs(szSuffix, plSuffix, strlen(plSuffix)+1);
		wchar_t szSubkey[256];
		wcscpy(szSubkey, L"SOFTWARE\\PixelLight\\PixelLight-SDK");
		if (wcslen(szSuffix) > 0) {
			wcscat(szSubkey, L"-");
			wcscat(szSubkey, szSuffix);
		}
		**/

		
		//check if registry key for pl runtime is already set to this directory
		String regDataDir = Runtime::GetRegistryDataDirectory();
		if(regDataDir != currentDir)
		{
			//set the registry key
			
		} else {
			//the registry key is allready set to the current dir

		}

		/**
		// Add directory to registry key "SOFTWARE\\PixelLight\\PixelLight-SDK"
		const LONG nErrorCode = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubkey, 0, nullptr, 0, KEY_READ | KEY_WRITE, nullptr, &hKey, nullptr);
		if (nErrorCode == ERROR_SUCCESS) {
			// Set value
			RegSetValueEx(hKey, L"Runtime", 0, REG_SZ, (BYTE*)szDir, (DWORD)sizeof(wchar_t)*wcslen(szDir));
			RegFlushKey(hKey);

			// Clean up
			RegCloseKey(hKey);
		} else {
			// Converts a given Windows error code received by 'GetLastError()' into a human readable string
			LPTSTR pszError;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, nErrorCode, 0, reinterpret_cast<LPTSTR>(&pszError), 0, nullptr)) {
				wchar_t szMessage[256];
				//[TODO] create error output
				//swprintf(szMessage, 256, L"Failed to open or create \"HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK\" (%s)", pszError);
				//Message(szMessage);
				LocalFree(pszError);
			} else {
				//[TODO] create error output
				//Message(L"Failed to open or create \"HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK\"");
			}
		}
		**/
		broadcastNewPathEnvironment();

		// Output message
		//[TODO] create output
		//Message(L"PixelLight DLLs installed. You may need to restart your system.");
	} else {
		//[TODO] create error output
		lastErrorMessage = L"The installer requires Windows 2000/NT/XP";
	}
	// Done


	return false;
}

bool InstallerFunctionsWindows::checkRuntimeInstallation()
{
	//check the installation by getting the system directory.
	//this should return the runtime system installation path and should point to the current directory
	String currentDir = System::GetInstance()->GetCurrentDir();
	EventProgressUpdate(1);
	// TODO: use the runtime function when it works with static linked plcore ... it should find the dynamic ones
	//String plSystemDir = PLCore::Runtime::GetSystemDirectory();
	String plSystemDir = GetSystemDirectory();

	EventProgressUpdate(1);
	if(plSystemDir == currentDir)
	{
		//the PATH environment or the registry key is pointing to the current directory => PL is installed correctly
		EventProgressUpdate(1);
		return true;
	}

	EventProgressUpdate(1);
	// the pl runtime could not be found => the runtime isn't installed correctly 
	lastErrorMessage = L"The PLRuntime directory could not be found.";
	return false;
}

int InstallerFunctionsWindows::getInstallRuntimeProgressSteps()
{

	return INSTALL_RUNTIME_PROGRESS_STEPS;
}


int InstallerFunctionsWindows::getCheckRuntimeProgressSteps()
{

	return CHECK_RUNTIME_PROGRESS_STEPS;
}

PLCore::String InstallerFunctionsWindows::getErrorDescription()
{
	return lastErrorMessage;
}
//[-------------------------------------------------------]
//[ Private InstallerFunctionsWindows functions           ]
//[-------------------------------------------------------]

bool InstallerFunctionsWindows::CheckWindowsVersion()
{
	OSVERSIONINFOEX ver;

	// Initialize structure
	ZeroMemory(&ver, sizeof(OSVERSIONINFOEX));
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	// Get version info
	if (!GetVersionEx((OSVERSIONINFO*)&ver)) {
		// Error with OSVERSIONINFOEX, try OSVERSIONINFO
		ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO*)&ver))
			return false;
	}

	// Check Windows version
	return ver.dwPlatformId == VER_PLATFORM_WIN32_NT;
}

void InstallerFunctionsWindows::broadcastNewPathEnvironment() 
{
		// We need to send a broadcast so other processes will be informed about the change. If this is not done,
		// 'dlls' still will not be found although the "PATH" environment variable was updated!
		ULONG_PTR nResult;
		SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_NORMAL, 4000, &nResult);

}

/**
* ----------------------------------------------------------------------------------------------------------------
* TODO: THIS METHODS SHOULD WORK WITH THE STATIC LINKED PLCORE TOO!!! 
* this is just a copy from Runtime.h ... should be corrected there and the functions from Runtime should be used!!
* ----------------------------------------------------------------------------------------------------------------
**/
PLCore::String InstallerFunctionsWindows::GetDirectoryDynamic(Runtime::EType nType)
{
	// Get the name of the PLCore shared library
	const String sPLCoreSharedLibrary = GetPLCoreSharedLibraryName();

	// Load the shared library (should never ever fail because this executable is already using this shared library...)
	DynLib cPLCoreDynLib;
	if (cPLCoreDynLib.Load(sPLCoreSharedLibrary)) {
		// Get the absolute path the PLCore shared library is in
		const String sAbsPLCorePath = Url(cPLCoreDynLib.GetAbsPath()).CutFilename();

		// Get the absolute filename of the running process
		const String sAbsProcessPath = Url(System::GetInstance()->GetExecutableFilename()).CutFilename();

		// Is the PLCore shared library within the same directory as the running process?
		if (sAbsPLCorePath == sAbsProcessPath) {
			// The PixelLight runtime is in the same directory as the running process, making this to a local installation
			return (nType == Runtime::LocalInstallation) ? sAbsPLCorePath : "";	// Done
		} else {
			// The PixelLight runtime is registered within the system, making this to a system installation
			return (nType == Runtime::SystemInstallation) ? sAbsPLCorePath : "";	// Done
		}
	}

	//error
	return "";
}

String InstallerFunctionsWindows::GetPLCoreSharedLibraryName()
{
	#ifdef _DEBUG
		// The executable is using a debug version of PixelLight
		#ifdef LINUX
			return "libPLCoreD.so";
		#elif defined(WIN32)
			return "PLCoreD.dll";
		#endif
	#else
		// The executable is using a release version of PixelLight
		#ifdef LINUX
			return "libPLCore.so";
		#elif defined(WIN32)
			return "PLCore.dll";
		#endif
	#endif
}


String InstallerFunctionsWindows::GetSystemDirectory()
{
	// First: Try to find the PL-runtime directory by using the PLCore shared library
	String sPLDirectory = GetDirectoryDynamic(Runtime::SystemInstallation);
	if (!sPLDirectory.GetLength()) {
		// Second: Try to find the system PL-runtime directory by reading the registry
		sPLDirectory = Runtime::GetRegistryDirectory();
	}

	// Done
	return sPLDirectory;
}