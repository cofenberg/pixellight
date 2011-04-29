/*********************************************************\
 *  File: LoadableManager.h                              *
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


#ifndef __PLCORE_LOADABLEMANAGER_H__
#define __PLCORE_LOADABLEMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Singleton.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
#include "PLCore/Tools/Loadable.h"
#include "PLCore/Base/Event/EventHandler.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Directory;
}
namespace PLCore {
	class Class;
	class Loader;
	class LoadableType;
	class LoadableManager;
}


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
PLCORE_TEMPLATE template class PLCORE_API PLGeneral::Singleton<PLCore::LoadableManager>;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loadable manager
*
*  @remarks
*    A loadable class is for instance an image that can be loaded & saved in multiple ways/formats.
*    Such a loadable is registered within this manager as a 'loadable type'. Each loadable type can
*    have multiple loaders which load/save the loadable within a concreate way/format.
*
*    Example:
*      - Image
*        - ImageLoaderEXR (*.exr)
*      - Mesh
*        - MeshLoaderPL (*.mesh)
*        - MeshLoader3ds (*.3ds)
*        - MeshLoaderObj (*.obj)
*    -> By asking the loadable manager which 'file formats/extensions' are supported for the 'Mesh' type,
*       it will return in this example 'mesh, 3ds. obj'. One loader can also support multiple formats.
*
*  @note
*    - An empty string is also a valid base directory and represents the current system directory
*      (see PLGeneral::System::GetCurrentDir())
*/
class LoadableManager : public PLGeneral::Singleton<LoadableManager> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class LoadableType;
	friend class PLGeneral::Singleton<LoadableManager>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Types                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of loadable types
		*
		*  @return
		*    The number of loadable types
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfTypes();

		/**
		*  @brief
		*    Returns a loadable type
		*
		*  @param[in] nIndex
		*    Loadable type index
		*
		*  @return
		*    The requested loadable type, a null pointer on error
		*/
		PLCORE_API LoadableType *GetType(PLGeneral::uint32 nIndex);

		/**
		*  @brief
		*    Returns a loadable type by using it's name
		*
		*  @param[in] sName
		*    Loadable type name
		*
		*  @return
		*    The requested loadable type, a null pointer on error
		*/
		PLCORE_API LoadableType *GetType(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Returns a loadable type by using a loadable extension
		*
		*  @param[in] sExtension
		*    Extension of loadable
		*
		*  @return
		*    The requested loadable type, a null pointer on error
		*/
		PLCORE_API LoadableType *GetTypeByExtension(const PLGeneral::String &sExtension);

		//[-------------------------------------------------------]
		//[ Loaders                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of loaders
		*
		*  @return
		*    The number of loaders
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfLoaders();

		/**
		*  @brief
		*    Returns a loader by using an index
		*
		*  @param[in] nIndex
		*    Loader index
		*
		*  @return
		*    The requested loader, a null pointer on error
		*/
		PLCORE_API Loader *GetLoader(PLGeneral::uint32 nIndex);

		/**
		*  @brief
		*    Returns a loader by using a loadable extension
		*
		*  @param[in] sExtension
		*    Extension of loadable
		*
		*  @return
		*    The requested loader, a null pointer on error
		*/
		PLCORE_API Loader *GetLoader(const PLGeneral::String &sExtension);

		//[-------------------------------------------------------]
		//[ Formats                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of supported formats
		*
		*  @return
		*    The number of supported formats
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfFormats();

		/**
		*  @brief
		*    Returns a supported format
		*
		*  @param[in] nIndex
		*    Format index
		*
		*  @return
		*    The requested supported format, empty string on error
		*/
		PLCORE_API PLGeneral::String GetFormat(PLGeneral::uint32 nIndex);

		/**
		*  @brief
		*    Returns whether loading is supported for the given format
		*
		*  @param[in] sExtension
		*    Extension of the format
		*  @param[in] sType
		*    Required loadable type, if empty string ignore loadable type
		*
		*  @return
		*    'true' if loading is supported for the given format, else 'false'
		*/
		PLCORE_API bool IsFormatLoadSupported(const PLGeneral::String &sExtension, const PLGeneral::String &sType = "");

		/**
		*  @brief
		*    Returns whether saving is supported for the given format
		*
		*  @param[in] sExtension
		*    Extension of the format
		*  @param[in] sType
		*    Required loadable type, if empty string ignore loadable type
		*
		*  @return
		*    'true' if saving is supported for the given format, else 'false'
		*/
		PLCORE_API bool IsFormatSaveSupported(const PLGeneral::String &sExtension, const PLGeneral::String &sType = "");

		//[-------------------------------------------------------]
		//[ Base directories                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of base directories
		*
		*  @return
		*    Number of base directories
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfBaseDirs() const;

		/**
		*  @brief
		*    Returns one of the base directories
		*
		*  @param[in] nNum
		*    Number of the base directory to get
		*
		*  @return
		*    Path of the base directory or empty string
		*/
		PLCORE_API PLGeneral::String GetBaseDir(PLGeneral::uint32 nNum) const;

		/**
		*  @brief
		*    Checks whether the given path is a base directory
		*
		*  @param[in] sPath
		*    Path to the base directory
		*
		*  @return
		*    'true', if the given path is a base directory, else 'false'
		*/
		PLCORE_API bool IsBaseDir(const PLGeneral::String &sPath) const;

		/**
		*  @brief
		*    Adds a base directory
		*
		*  @param[in] sPath
		*    Path to the base directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool AddBaseDir(const PLGeneral::String &sPath);

		/**
		*  @brief
		*    Set the priority of base directories
		*
		*  @param[in] sFirstPath
		*    Path to the first base directory
		*  @param[in] sSecondPath
		*    Path to the second base directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*
		*  @remarks
		*    This function changes the order of the two base dirs
		*    so that sSecondPath comes right after sFirstPath.
		*/
		PLCORE_API bool SetBaseDirPriority(const PLGeneral::String &sFirstPath, const PLGeneral::String &sSecondPath);

		/**
		*  @brief
		*    Remove a base directory
		*
		*  @param[in] sPath
		*    Base directory to remove
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool RemoveBaseDir(const PLGeneral::String &sPath);

		/**
		*  @brief
		*    Remove a base directory
		*
		*  @param[in] nNum
		*    Number of the base directory to remove
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool RemoveBaseDir(PLGeneral::uint32 nNum);

		/**
		*  @brief
		*    Removes all base directories
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool ClearBaseDirs();

		/**
		*  @brief
		*    Gets the relative version of an absolute filename
		*
		*  @param[in] sFilename
		*    Absolute filename to get the realtive version from
		*
		*  @return
		*    Relative filename, empty string on error (maybe unknown loadable type?)
		*
		*  @note
		*    - This function only checks whether there's a loadable type for the given file type,
		*      if so, the request is given to this loadable type
		*
		*  @see
		*    - LoadableType::GetRelativeFilePath()
		*/
		PLCORE_API PLGeneral::String GetRelativeFilename(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Scan a directory for data packages and add them as base paths to the loadable manager
		*
		*  @param[in] sPath
		*    Directory to search in
		*  @param[in] sExtension
		*    Extension of the archives to add (e.g. 'zip' or 'pak')
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool ScanPackages(const PLGeneral::String &sPath, const PLGeneral::String &sExtension = "*.zip");

		/**
		*  @brief
		*    Opens a file by using base directories
		*
		*  @param[in] cFile
		*    File object
		*  @param[in] sFilename
		*    Filename of the file to open
		*  @param[in] bCreate
		*    Create the file if it doesn't exist?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool OpenFile(PLGeneral::File &cFile, const PLGeneral::String &sFilename, bool bCreate = false) const;

		/**
		*  @brief
		*    Loads in a string by using a file
		*
		*  @param[in] sFilename
		*    Name of the file to read the string from
		*  @param[in] nFormat
		*    String format, "PLGeneral::String::ASCII" or "PLGeneral::String::Unicode" (not recommended!)
		*
		*  @return
		*    The read string, empty string on error or if the file is just empty
		*
		*  @note
		*    - The file is opened by using base directories
		*    - It's not recommended to read in Unicode by using this method because internally
		*      wchar_t is used and this data type has not the same size on every platform
		*/
		PLCORE_API PLGeneral::String LoadStringFromFile(const PLGeneral::String &sFilename, PLGeneral::String::EFormat nFormat = PLGeneral::String::ASCII) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API LoadableManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~LoadableManager();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Register a class
		*
		*  @param[in] pClass
		*    Class to register, must be valid!
		*
		*  @note
		*    - If the class is not derived from 'Loader' it is ignored
		*    - The given class must be a new one, so this function did not check whether the
		*      class is already registered
		*/
		void OnClassLoaded(const Class *pClass);

		/**
		*  @brief
		*    Registers queued classes
		*/
		void RegisterClasses();


	//[-------------------------------------------------------]
	//[ Private slots                                         ]
	//[-------------------------------------------------------]
	private:
		EventHandler<const Class*> SlotClassLoaded;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General
		PLGeneral::Array<LoadableType*>						 m_lstTypes;		/**< List of loadable types */
		PLGeneral::HashMap<PLGeneral::String, LoadableType*> m_mapTypes;		/**< Map of loadable types */
		PLGeneral::Array<PLGeneral::String>					 m_lstBaseDirs;		/**< List of base directories */
		PLGeneral::Array<const Class*>						 m_lstNewClasses;	/**< New classes to register as soon as required */

		// Filled by LoadableType
		PLGeneral::Array<Loader*>							 m_lstLoaders;			/**< List of loaders */
		PLGeneral::HashMap<PLGeneral::String, Loader*>		 m_mapLoaders;			/**< Map of loaders (key = extension) */
		PLGeneral::Array<PLGeneral::String>					 m_lstFormats;			/**< List of loadable formats */
		PLGeneral::HashMap<PLGeneral::String, LoadableType*> m_mapTypesByExtension;	/**< Map of loadable types (key = extension) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOADABLEMANAGER_H__
