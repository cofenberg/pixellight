/*********************************************************\
 *  File: SystemMacOSX.cpp                               *
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
#include <mach-o/dyld.h>	// For _NSGetExecutablePath
#include "PLCore/System/SystemMacOSX.h"


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
SystemMacOSX::SystemMacOSX()
{
}

/**
*  @brief
*    Destructor
*/
SystemMacOSX::~SystemMacOSX()
{
}


//[-------------------------------------------------------]
//[ Private virtual SystemImpl functions                  ]
//[-------------------------------------------------------]
String SystemMacOSX::GetPlatform() const
{
	static const String sString = "MacOSX";
	return sString;
}

String SystemMacOSX::GetModuleFilenameByMemoryAddress(const void *pMemoryAddress) const
{
	// [TODO] Test whether or not the Linux implementation works (compiles and runs correctly) for Mac OS X as well
	return "";
}

String SystemMacOSX::GetExecutableFilename() const
{
	// First of all, get the length of the executable filename (including the terminating zero)
	uint32_t nSize = 0;
	_NSGetExecutablePath(nullptr, &nSize);
	if (nSize) {
		// Executable filename
		char *pszTemp = new char[nSize];
		if (!_NSGetExecutablePath(pszTemp, &nSize)) {
			// Get the string
			const String sString = String::FromUTF8(pszTemp);

			// We no longer need the data, so free it
			delete [] pszTemp;

			// Done
			return sString;
		} else {
			// We no longer need the data, so free it
			delete [] pszTemp;
		}
	}

	// Error!
	return "";
}

String SystemMacOSX::GetSharedLibraryExtension() const
{
	static const String sString = "dylib";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
