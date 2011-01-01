/*********************************************************\
 *  File: Loadable.h                                     *
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


#ifndef __PLCORE_LOADABLE_H__
#define __PLCORE_LOADABLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
	class Parameters;
}
namespace PLCore {
	class Loader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract loadable (serialization) base class, derive your loadable classes from this class
*
*  @note
*    - If your loadable has special parameters for loading/saving don't forgett to document it within your class!
*/
class Loadable {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the filename this loadable was given to loaded from
		*
		*  @return
		*    The filename this loadable was given to loaded from
		*/
		PLCORE_API PLGeneral::String GetFilename() const;

		/**
		*  @brief
		*    Returns the absolute filename this loadable was loaded from
		*
		*  @return
		*    The absolute filename this loadable was loaded from
		*/
		PLCORE_API PLGeneral::String GetUrl() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Loads the loadable from a file given by filename
		*
		*  @param[in] sFilename
		*    Loadable filename
		*  @param[in] sParams
		*    Optional load method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the load method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If no method name was provided, 'Load' if sParams is empty, or 'LoadParams' if sParams is not empty is used automatically
		*/
		PLCORE_API virtual bool Load(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Loads the loadable from a file given by a pointer
		*
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*  @param[in] sParams
		*    Optional load method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the load method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If no method name was provided, 'Load' if sParams is empty, or 'LoadParams' if sParams is not empty is used automatically
		*/
		PLCORE_API virtual bool Load(PLGeneral::File &cFile, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Saves the loadable to a file given by filename
		*
		*  @param[in] sFilename
		*    Loadable filename
		*  @param[in] sParams
		*    Optional save method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the save method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If no method name was provided, 'Save' if sParams is empty, or 'SaveParams' if sParams is not empty is used automatically
		*/
		PLCORE_API virtual bool Save(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Saves the loadable to a file given by pointer
		*
		*  @param[in] cFile
		*    File to save into, must be opened and writable
		*  @param[in] sParams
		*    Optional save method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the save method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If no method name was provided, 'Save' if sParams is empty, or 'SaveParams' if sParams is not empty is used automatically
		*/
		PLCORE_API virtual bool Save(PLGeneral::File &cFile, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Reloads the loadable
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's nothing loaded?)
		*
		*  @note
		*    - Same as pLoadable->Load(pLoadable->GetAbsFilename())
		*/
		PLCORE_API virtual bool Reload();

		/**
		*  @brief
		*    Unloads the loadable
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API virtual bool Unload();

		/**
		*  @brief
		*    Returns the loadable type name
		*
		*  @return
		*    The loadable type name
		*/
		PLCORE_API virtual PLGeneral::String GetLoadableTypeName() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Loadable();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Loadable();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Calls the loadable in order to load or save
		*
		*  @param[in] cFile
		*    File to load from, MUST be opened
		*  @param[in] cLoader
		*    Loader to use
		*  @param[in] sMethod
		*    Name of the method to use
		*  @param[in] sParams
		*    Method parameters
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The default implementation is empty and will return always 'false'
		*/
		PLCORE_API virtual bool CallLoadable(PLGeneral::File &cFile, Loader &cLoader, const PLGeneral::String &sMethod, const PLGeneral::String &sParams);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sFilename;	/**< The filename this loadable was given to loaded from */
		PLGeneral::String m_sUrl;		/**< The absolute filename this loadable was loaded from */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOADABLE_H__
