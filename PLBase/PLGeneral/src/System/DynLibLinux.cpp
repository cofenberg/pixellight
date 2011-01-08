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
#include <dlfcn.h>
#include <stdio.h>
#include "PLGeneral/File/Url.h"
#include "PLGeneral/System/DynLibLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


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

	// Load library
	// [TODO] Check whether there's something like 'LOAD_WITH_ALTERED_SEARCH_PATH' so the other files
	// will be searched within the same directory as this one. If not, we must change the current directory
	// in here...
	const String sPath = cUrl.GetUnixPath();
	m_pLib = dlopen((sPath.GetFormat() == String::ASCII) ? sPath.GetASCII() : (char*)sPath.GetUTF8(), RTLD_NOW);
	if (!m_pLib)
		printf("[PLGeneral] error while loading %s \n %s\n", sPath.GetASCII(), dlerror());

	// Return whether loading of the library was successful
	return m_pLib;
}

String DynLibLinux::GetAbsPath() const
{
	// [TODO] Implement me
	return "";
}

bool DynLibLinux::Unload()
{
	if (m_pLib) {
		// Unload library
		if (dlclose(m_pLib)) {
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
	return m_pLib ? dlsym(m_pLib, (sSymbol.GetFormat() == String::ASCII) ? sSymbol.GetASCII() : (char*)sSymbol.GetUTF8()) : nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
