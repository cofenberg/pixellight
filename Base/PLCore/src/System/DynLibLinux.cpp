/*********************************************************\
 *  File: DynLibLinux.cpp                                *
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
#if !defined(ANDROID) && !defined(APPLE)
	#include <link.h>	// For "dlinfo", not available on Android and Mac OS X
#endif
#include <dlfcn.h>
#include <stdio.h>
#include "PLCore/File/Url.h"
#include "PLCore/System/DynLibLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DynLibLinux::DynLibLinux() :
	m_pLib(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
DynLibLinux::~DynLibLinux()
{
	// Unload the library
	Unload();
}


//[-------------------------------------------------------]
//[ Private virtual DynLibImpl functions                  ]
//[-------------------------------------------------------]
bool DynLibLinux::IsLoaded() const
{
	// Return whether the library has been loaded
	return (m_pLib != nullptr);
}

bool DynLibLinux::Load(const Url &cUrl)
{
	// Is already a library loaded?
	if (m_pLib)
		return false; // Error!

	// Load library. Under Linux, there's nothing like 'LOAD_WITH_ALTERED_SEARCH_PATH' from MS Windows so the other files
	// will be searched within the same directory as this one. This has to be configured by using the RPATH when linking
	// the resulting binary (see http://www.cmake.org/Wiki/CMake_RPATH_handling). Type e.g. "objdump -x libPLCore.so" and
	// have a look at "Dynamic Section"->"RPATH", should be "$ORIGIN" when this option is enabled.
	const String sPath = cUrl.GetUnixPath();
	m_pLib = dlopen((sPath.GetFormat() == String::ASCII) ? sPath.GetASCII() : sPath.GetUTF8(), RTLD_LAZY);

	// Return whether loading of the library was successful
	if (m_pLib) {
		// Done
		return true;
	} else {
		// Error: Failed to load dll!
		return false;
	}
}

String DynLibLinux::GetAbsPath() const
{
	#if !defined(ANDROID) && !defined(APPLE)
		// "dlinfo" is not available on Android and Mac OS X
		link_map *pLinkMap = nullptr;
		if (m_pLib && !dlinfo(m_pLib, RTLD_DI_LINKMAP, &pLinkMap)) {
			// Success
			return String::FromUTF8(pLinkMap->l_name);
		}
	#endif

	// Error!
	return "";
}

bool DynLibLinux::Unload()
{
	if (m_pLib) {
		// Unload library
		if (!dlclose(m_pLib)) {
			m_pLib = nullptr;

			// Done
			return true;
		}
	}

	// Error, could not unload the library
	return false;
}

void *DynLibLinux::GetSymbol(const String &sSymbol) const
{
	// Is the library loaded?
	return m_pLib ? dlsym(m_pLib, (sSymbol.GetFormat() == String::ASCII) ? sSymbol.GetASCII() : sSymbol.GetUTF8()) : nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
