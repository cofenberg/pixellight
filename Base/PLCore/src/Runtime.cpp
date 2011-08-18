/*********************************************************\
 *  File: Runtime.cpp                                    *
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
#include <PixelLight.h>
#include "PLCore/System/DynLib.h"
#include "PLCore/System/System.h"
#include "PLCore/File/Url.h"
#include "PLCore/File/Directory.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Registry/Registry.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Runtime.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get used PixelLight installation type
*/
Runtime::EType Runtime::GetType()
{
	#ifdef PLCORE_STATIC
		// No doubt, the executable is using the static linked version of PLCore
		return StaticInstallation;
	#else
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
				return LocalInstallation;
			} else {
				// The PixelLight runtime is registered within the system, making this to a system installation
				return SystemInstallation;
			}
		}

		// Error!
		return UnknownInstallation;
	#endif
}

/**
*  @brief
*    Get PixelLight version
*/
Version Runtime::GetVersion()
{
	return Version(
		PIXELLIGHT_NAME,
		"",
		PIXELLIGHT_VERSION_MAJOR,
		PIXELLIGHT_VERSION_MINOR,
		PIXELLIGHT_VERSION_PATCH,
		PIXELLIGHT_VERSION_RELEASE
	);
}

/**
*  @brief
*    Return whether or not this is a debug version of PixelLight
*/
bool Runtime::IsDebugVersion()
{
	#ifdef _DEBUG
		// The executable is using a debug version of PixelLight
		return true;
	#else
		// The executable is using a release version of PixelLight
		return false;
	#endif
}

/**
*  @brief
*    Get PixelLight suffix
*/
String Runtime::GetSuffix()
{
	return PIXELLIGHT_SUFFIX;
}

/**
*  @brief
*    Try to find the local PL-runtime directory
*/
String Runtime::GetLocalDirectory()
{
	#ifdef PLCORE_STATIC
		// No doubt, the executable is using the static linked version of PLCore... We don't know any so called "runtime"...
	#else
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
				return sAbsPLCorePath;	// Done
			} else {
				// The PixelLight runtime is registered within the system, making this to a system installation
			}
		}
	#endif

	// Error!
	return "";
}

/**
*  @brief
*    Try to find the local PL-runtime data directory
*/
String Runtime::GetLocalDataDirectory()
{
	// Get PixelLight local runtime directory
	const String sPLDirectory = GetLocalDirectory();
	if (sPLDirectory.GetLength()) {
		// Return the local runtime data directory
		return Url(sPLDirectory + "/../Data/").Collapse().GetUrl();
	} else {
		// Error!
		return "";
	}
}

/**
*  @brief
*    Try to find the system PL-runtime directory by reading the registry
*/
String Runtime::GetSystemDirectory()
{
	// Windows
	#ifdef WIN32
		// Get path to PixelLight runtime
		Registry cRegistry;
		if (cRegistry.GetRegistryType() == Registry::Windows) {
			// Get suffix
			String sSuffix = GetSuffix();
			if (sSuffix.GetLength() > 0)
				sSuffix = '-' + sSuffix;

			// On 64 bit *Windows* systems, "Wow6432Node" is added automatically for 32 bit applications by the OS

			// Read registry key "PixelLight-SDK" ("SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-SDK" on a 64 bit version and 32 bit application)
			String sSubkey = "SOFTWARE\\PixelLight\\PixelLight-SDK" + sSuffix;
			if (cRegistry.Open(Registry::KeyLocalMachine, sSubkey, Registry::RegRead)) {
				const String sRuntime = cRegistry.GetValueString("Runtime");
				if (sRuntime.GetLength())
					return sRuntime; // Done
			}

			// Read registry key "PixelLight-Runtime" ("SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-Runtime" on a 64 bit version and 32 bit application)
			sSubkey = "SOFTWARE\\PixelLight\\PixelLight-Runtime" + sSuffix;
			if (cRegistry.Open(Registry::KeyLocalMachine, sSubkey, Registry::RegRead)) {
				const String sRuntime = cRegistry.GetValueString("Runtime");
				if (sRuntime.GetLength())
					return sRuntime; // Done
			}
		}

		// No runtime directory was found in the registry
		return "";
	#endif

	// Linux
	#ifdef LINUX
		// [TODO] Maybe we could distinguish between different versions and therefore different directories
		//        (e.g. based on current version or library name)

		// Check if a local pixellight runtime is specified in the environment variable PL_RUNTIME
		const String sRuntime = System::GetInstance()->GetEnvironmentVariable("PL_RUNTIME");
		if (sRuntime.GetLength() > 0) {
			// Use local runtime
			return sRuntime;
		}

		// Let's first check if a local installation is present in '/usr/local/share/pixellight/Runtime'.
		// If it is, we will use that
		Directory cDirectory("/usr/local/share/pixellight/Runtime");
		if (cDirectory.Exists() && cDirectory.IsDirectory())
			return "/usr/local/share/pixellight/Runtime";

		// Otherwise, we will use a global installation in '/usr/share/pixellight/Runtime'
		// For now, just return a static path
		return "/usr/share/pixellight/Runtime";
	#endif
}

/**
*  @brief
*    Try to find the system PL-runtime data directory by reading the registry
*/
String Runtime::GetSystemDataDirectory()
{
	// Get PixelLight system runtime directory
	const String sPLDirectory = GetSystemDirectory();
	if (sPLDirectory.GetLength()) {
		// Return the system runtime data directory
		return Url(sPLDirectory + "/../Data/").Collapse().GetUrl();
	} else {
		// Error!
		return "";
	}
}

/**
*  @brief
*    Try to find the PL-runtime directory used by the running process
*/
String Runtime::GetDirectory()
{
	// First: Try to find the local PL-runtime directory
	String sPLDirectory = GetLocalDirectory();
	if (!sPLDirectory.GetLength()) {
		// No local PL-runtime directory found

		// Second: Try to find the system PL-runtime directory by reading the registry
		sPLDirectory = GetSystemDirectory();
	}

	// Done
	return sPLDirectory;
}

/**
*  @brief
*    Try to find the PL-runtime data directory used by the running process
*/
String Runtime::GetDataDirectory()
{
	// Get PixelLight runtime directory used by the running process
	const String sPLDirectory = GetDirectory();
	if (sPLDirectory.GetLength()) {
		// Return the runtime data directory used by the running process
		return Url(sPLDirectory + "/../Data/").Collapse().GetUrl();
	} else {
		// Error!
		return "";
	}
}

/**
*  @brief
*    Scan PL-runtime directory for compatible plugins and load them in
*/
void Runtime::ScanDirectoryPlugins(const String &sDirectory, bool bDelayedPluginLoading)
{
	// Get PixelLight runtime directory
	const String sPLDirectory = (sDirectory.GetLength()) ? sDirectory : GetDirectory();
	if (sPLDirectory.GetLength()) {
		// Scan for plugins in the PixelLight runtime directory, but not recursively, please. This is quite useful
		// for projects which can be used completely dynamically, but can also be used in other C++ projects
		// to access certain features.
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory, NonRecursive, bDelayedPluginLoading);

		// Scan for plugins in PixelLight runtime directory
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory + "/Plugins/", Recursive, bDelayedPluginLoading);
	}
}

/**
*  @brief
*    Scan PL-runtime directory for compatible data and register it
*/
void Runtime::ScanDirectoryData(const String &sDirectory)
{
	// Get PixelLight runtime data directory
	const String sPLDataDirectory = (sDirectory.GetLength()) ? sDirectory : GetDataDirectory();
	if (sPLDataDirectory.GetLength()) {
		// Add runtime directory
		LoadableManager::GetInstance()->AddBaseDir(sPLDataDirectory);

		// Add packages from PixelLight runtime directory
		LoadableManager::GetInstance()->ScanPackages(sPLDataDirectory);
	}
}

/**
*  @brief
*    Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
*/
void Runtime::ScanDirectoryPluginsAndData()
{
	// Wow, just have a look at this ueber-complex implementation
	ScanDirectoryPlugins();
	ScanDirectoryData();
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the PLCore shared library
*/
String Runtime::GetPLCoreSharedLibraryName()
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
