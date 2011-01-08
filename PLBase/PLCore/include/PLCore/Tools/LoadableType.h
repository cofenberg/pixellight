/*********************************************************\
 *  File: LoadableType.h                                 *
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


#ifndef __PLCORE_LOADABLETYPE_H__
#define __PLCORE_LOADABLETYPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Loader;
class Class;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class describing a loadable type
*
*  @remarks
*    This is used for managing search paths and loadable formats for a loadable type.
*/
class LoadableType {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class LoadableManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the loadable type
		*
		*  @return
		*    Name of the loadable type
		*/
		PLCORE_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Returns the class of the loadable type
		*
		*  @return
		*    Class of the loadable type
		*/
		PLCORE_API const Class &GetClass() const;

		/**
		*  @brief
		*    Gets the relative version of an absolute file path
		*
		*  @param[in] sPath
		*    Absolute file path to get the realtive version from
		*
		*  @return
		*    Relative file path, empty string on error
		*
		*  @note
		*    - The function will take the FS base directories into account, the first match
		*      will be used
		*    - MS Windows example: 'C:\test\test.bmp' -> 'test.bmp'
		*/
		PLCORE_API PLGeneral::String GetRelativeFilePath(const PLGeneral::String &sPath) const;

		//[-------------------------------------------------------]
		//[ Formats & loaders                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of supported formats
		*
		*  @return
		*    The number of supported formats
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfFormats() const;

		/**
		*  @brief
		*    Returns a supported formats
		*
		*  @param[in] nIndex
		*    Format index
		*
		*  @return
		*    The requested supported format, empty string on error
		*/
		PLCORE_API PLGeneral::String GetFormat(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the number of loaders
		*
		*  @return
		*    The number of loaders
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfLoaders() const;

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
		PLCORE_API Loader *GetLoader(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Returns a loader by using a loadable extension
		*
		*  @param[in] sExtension
		*    Extension of loader
		*
		*  @return
		*    The requested loader, a null pointer on error (format is not supported)
		*/
		PLCORE_API Loader *GetLoader(const PLGeneral::String &sExtension) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Name of the loadable type
		*  @param[in] cClass
		*    Class the loadable type
		*/
		LoadableType(const PLGeneral::String &sName, const Class &cClass);

		/**
		*  @brief
		*    Destructor
		*/
		~LoadableType();

		/**
		*  @brief
		*    Adds loader to this loadable type
		*
		*  @param[in] cLoader
		*    Loader to add
		*/
		void AddLoader(Loader &cLoader);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String							   m_sName;			/**< Name of the loadable type */
		const Class									  *m_pClass;		/**< Class the loadable type, always valid! */
		PLGeneral::Array<Loader*>					   m_lstLoaders;	/**< List of loaders */
		PLGeneral::HashMap<PLGeneral::String, Loader*> m_mapLoaders;	/**< Map of loaders (key = extension) */
		PLGeneral::Array<PLGeneral::String>			   m_lstFormats;	/**< List of loadable formats */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOADABLETYPE_H__
