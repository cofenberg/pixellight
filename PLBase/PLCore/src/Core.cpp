/*********************************************************\
 *  File: Core.cpp                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/System/System.h>

#include <PLGeneral/System/Console.h>

#include <PLGeneral/Registry/Registry.h>
#include <PLGeneral/File/Directory.h>
#include "PLCore/Core.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Try to find the PL-Runtime directory by reading the registry
*/
String Core::GetRuntimeDirectory()
{
	// Windows
	#ifdef WIN32
		// Get path to PixelLight runtime
		Registry cRegistry;
		if (cRegistry.GetRegistryType() == Registry::Windows) {
			// Get suffix
			String sSuffix = Core::GetSuffix();
			if (sSuffix.GetLength() > 0)
				sSuffix = '-' + sSuffix;

			// On 64 bit *Windows* systems, "Wow6432Node" is added automatically for 32 bit applications by the OS

			// Read registry key "PixelLight-SDK" ("SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-SDK" on a 64 bit version and 32 bit application)
			String sSubkey = "SOFTWARE\\PixelLight\\PixelLight-SDK" + sSuffix;
			if (cRegistry.Open(Registry::KeyLocalMachine, sSubkey, Registry::RegRead)) {
				String sRuntime = cRegistry.GetValueString("Runtime");
				if (sRuntime.GetLength())
					return sRuntime; // Done
			}

			// Read registry key "PixelLight-Runtime" ("SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-Runtime" on a 64 bit version and 32 bit application)
			sSubkey = "SOFTWARE\\PixelLight\\PixelLight-Runtime" + sSuffix;
			if (cRegistry.Open(Registry::KeyLocalMachine, sSubkey, Registry::RegRead)) {
				String sRuntime = cRegistry.GetValueString("Runtime");
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
		String sRuntime = System::GetInstance()->GetEnvironmentVariable("PL_RUNTIME");
		if (sRuntime.GetLength() > 0) {
			// Use local runtime
			return sRuntime;
		}

		// Let's first check if a local installation is present in '/usr/local/share/pixellight/Runtime'.
		// If it is, we will use that
		Directory cDirectory("/usr/local/share/pixellight/Runtime");
		if (cDirectory.Exists() && cDirectory.IsDirectory()) {
			return "/usr/local/share/pixellight/Runtime";
		}

		// Otherwise, we will use a global installation in '/usr/share/pixellight/Runtime'
		// For now, just return a static path
		return "/usr/share/pixellight/Runtime";
	#endif
}

/**
*  @brief
*    Get PixelLight version
*/
Version Core::GetVersion()
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
*    Get PixelLight suffix
*/
String Core::GetSuffix()
{
	return PIXELLIGHT_SUFFIX;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
