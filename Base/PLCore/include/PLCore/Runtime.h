/*********************************************************\
 *  File: Runtime.h                                      *
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


#ifndef __PLCORE_RUNTIME_H__
#define __PLCORE_RUNTIME_H__
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
*    PixelLight framework runtime class
*
*  @note
*    - There can be a local and system runtime at the same time, although this is not recommended
*/
class Runtime {


	//[-------------------------------------------------------]
	//[ Definitions                                           ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Runtime installation type
		*/
		enum EType {
			StaticInstallation,	/**< The running process is using the static linked version of PLCore */
			LocalInstallation,	/**< The PixelLight runtime is in the same directory as the running process, making this to a local installation */
			SystemInstallation,	/**< The PixelLight runtime is registered within the system, making this to a system installation */
			UnknownInstallation	/**< Unkown PixelLight runtime installation type */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Passive information                                   ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get used PixelLight installation type
		*
		*  @return
		*    Used PixelLight installation type the running process is using
		*/
		PLCORE_API static EType GetType();

		/**
		*  @brief
		*    Get PixelLight version
		*
		*  @return
		*    Version of this PixelLight installation the running process is using
		*/
		PLCORE_API static Version GetVersion();

		/**
		*  @brief
		*    Return whether or not this is a debug version of PixelLight
		*
		*  @return
		*    'true' if the running process is using a debug version of PixelLight, else 'false'
		*/
		PLCORE_API static bool IsDebugVersion();

		/**
		*  @brief
		*    Get PixelLight suffix
		*
		*  @return
		*    Suffix of this PixelLight installation the running process is using
		*/
		PLCORE_API static String GetSuffix();

		/**
		*  @brief
		*    Try to find the local PL-runtime directory
		*
		*  @return
		*    Path to the local PL-runtime directory (e.g. "C:\MyApplication\x86"), or ""
		*/
		PLCORE_API static String GetLocalDirectory();

		/**
		*  @brief
		*    Try to find the local PL-runtime data directory
		*
		*  @return
		*    Path to the local PL-runtime data directory (e.g. "C:\MyApplication\Data"), or ""
		*/
		PLCORE_API static String GetLocalDataDirectory();

		/**
		*  @brief
		*    Try to find the system PL-runtime directory by reading the registry
		*
		*  @return
		*    Path to the system PL-runtime directory (e.g. "C:\PixelLight\Runtime\x86"), or ""
		*
		*  @see
		*    - 'Registry' class documentation
		*/
		PLCORE_API static String GetSystemDirectory();

		/**
		*  @brief
		*    Try to find the system PL-runtime data directory by reading the registry
		*
		*  @return
		*    Path to the system PL-runtime data directory (e.g. "C:\PixelLight\Runtime\Data"), or ""
		*
		*  @see
		*    - 'Registry' class documentation
		*/
		PLCORE_API static String GetSystemDataDirectory();

		/**
		*  @brief
		*    Try to find the PL-runtime directory used by the running process
		*
		*  @return
		*    Path to the PL-runtime directory used by the running process (e.g. "C:\MyApplication\x86" or "C:\PixelLight\Runtime\x86" etc.), or ""
		*
		*  @remarks
		*    As soon as an application executable is started and therfore has become a running process, it's bound to a
		*    certain PixelLight runtime. Usually, an OS will first search for required shared libraries within the same
		*    directory the application executable is in. If the PLCore shared library was found within the application
		*    executable directory, this means that a local PixelLight runtime is used. Of course, there can be a local
		*    and system PixelLight runtime at the same time (although this is not recommended), but this still means, that
		*    in the described situation, the local PLCore shared library is used and therefore the local PixelLight runtime.
		*    The "GetDirectory()"-method returns the PixelLight runtime used by the running process. This means that internally
		*    "GetLocalDirectory()" is called at first and if this method returns an empty string, a "GetSystemDirectory()"
		*    call follows in exactly this order.
		*/
		PLCORE_API static String GetDirectory();

		/**
		*  @brief
		*    Try to find the PL-runtime data directory used by the running process
		*
		*  @return
		*    Path to the PL-runtime data directory used by the running process (e.g. "C:\MyApplication\Data" or "C:\PixelLight\Runtime\Data" etc.), or ""
		*
		*  @see
		*    - GetDirectory()
		*/
		PLCORE_API static String GetDataDirectory();


		//[-------------------------------------------------------]
		//[ Active actions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Scan system PL-runtime directory for compatible plugins and load them in
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
		*    - Runtime::GetDirectory()
		*    - ClassManager::ScanPlugins()
		*/
		PLCORE_API static void ScanDirectoryPlugins(bool bDelayedPluginLoading = true);

		/**
		*  @brief
		*    Scan system PL-runtime directory for compatible data and register it
		*
		*  @remarks
		*    The implementation does the following tasks:
		*    - Add PixelLight runtime directory "Data/" as a base directory to the loadable manager
		*    - Scan for data in PixelLight runtime directory "Data/"
		*
		*  @see
		*    - LoadableManager::AddBaseDir()
		*    - LoadableManager::ScanPackages()
		*/
		PLCORE_API static void ScanDirectoryData();


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the name of the PLCore shared library
		*
		*  @return
		*    The name of the PLCore shared library (e.g. "libPLCore.so" or "PLCoreD.dll")
		*/
		static String GetPLCoreSharedLibraryName();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_RUNTIME_H__
