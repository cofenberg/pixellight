/*********************************************************\
 *  File: DynLibWindows.cpp                              *
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
#include "PLGeneral/File/Url.h"
#include "PLGeneral/System/SystemWindows.h"
#include "PLGeneral/System/DynLibWindows.h"


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
DynLibWindows::DynLibWindows() :
	m_hModule(NULL)
{
}

/**
*  @brief
*    Destructor
*/
DynLibWindows::~DynLibWindows()
{
}


//[-------------------------------------------------------]
//[ Private virtual DynLibImpl functions                  ]
//[-------------------------------------------------------]
bool DynLibWindows::IsLoaded() const
{
	// Return whether the library has been loaded
	return (m_hModule != NULL);
}

bool DynLibWindows::Load(const Url &cUrl)
{
	// Is already a library loaded?
	if (m_hModule) return false; // Error!

	// Load library
	String sWindowsPath = cUrl.GetWindowsPath();
	if (sWindowsPath.GetFormat() == String::ASCII)
		m_hModule = ::LoadLibraryExA(sWindowsPath.GetASCII(),   NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	else
		m_hModule = ::LoadLibraryExW(sWindowsPath.GetUnicode(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	// Return whether loading of the library was successful
	if (m_hModule) {
		// Done
		return true;
	} else {
		// Error: Failed to load dll!
		return false;
	}
}

String DynLibWindows::GetAbsPath() const
{
	// Allocate a buffer that is large enough to hold the information
	wchar_t *pszBuffer = new wchar_t[MAX_PATH];

	// Get module filename as Unicode
	if (GetModuleFileNameW(m_hModule, pszBuffer, MAX_PATH)) {
		return String(pszBuffer, false); // Do not copy, please
	} else {
		// We no longer need the data, so free it
		delete [] pszBuffer;

		// Error
		return "";
	}
}

bool DynLibWindows::Unload()
{
	if (m_hModule != NULL) {
		// Unload library
		if (::FreeLibrary(m_hModule)) {
			m_hModule = NULL;

			// Done
			return true;
		}
	}

	// Error, could not unload the library
	return false;
}

void *DynLibWindows::GetSymbol(const String &sSymbol) const
{
	// Is the library loaded?
	return m_hModule ? ::GetProcAddress(m_hModule, sSymbol.GetASCII()) : NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
