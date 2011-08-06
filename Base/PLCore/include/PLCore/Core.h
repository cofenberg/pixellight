/*********************************************************\
 *  File: Core.h                                         *
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


#ifndef __PLCORE_CORE_H__
#define __PLCORE_CORE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Version.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight framework core class
*/
class Core {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Try to find the PL-runtime directory by reading the registry
		*
		*  @return
		*    Path to the PL-runtime directory (e.g. "C:\PixelLight\Runtime"), or ""
		*
		*  @see
		*    - 'Registry' class documentation
		*/
		PLCORE_API static String GetRuntimeDirectory();

		/**
		*  @brief
		*    Get PixelLight version
		*
		*  @return
		*    Version of this PixelLight installation
		*/
		PLCORE_API static Version GetVersion();

		/**
		*  @brief
		*    Get PixelLight suffix
		*
		*  @return
		*    Suffix of this PixelLight installation
		*/
		PLCORE_API static String GetSuffix();

		/**
		*  @brief
		*    Scan PL-runtime directory for compatible plugins and load them in
		*
		*  @param[in] bDelayedPluginLoading
		*    'true' if it's allowed to perform delayed shared library loading to speed up the program start, else 'false'
		*
		*  @remarks
		*    The implementation does the following tasks:
		*    - Scan for plugins in PixelLight runtime directory non-recursively
		*    - Scan for plugins in PixelLight runtime directory "Plugins/" recursively
		*
		*  @see
		*    - Core::GetRuntimeDirectory()
		*    - ClassManager::ScanPlugins()
		*/
		PLCORE_API static void ScanRuntimeDirectoryPlugins(bool bDelayedPluginLoading = true);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CORE_H__
