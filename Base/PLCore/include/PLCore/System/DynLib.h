/*********************************************************\
 *  File: DynLib.h                                       *
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


#ifndef __PLCORE_DYNLIB_H__
#define __PLCORE_DYNLIB_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/Url.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DynLibImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Dynamic library (aka "shared library") class
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class DynLib {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynLib();

		/**
		*  @brief
		*    Destructor
		*
		*  @note
		*    - The dynamic library is unloaded automatically
		*/
		PLCORE_API ~DynLib();

		/**
		*  @brief
		*    Loads a dynamic library
		*
		*  @param[in] sPath
		*    Path to the dynamic library
		*
		*  @return
		*    'true' if the library could be loaded, else 'false'
		*
		*  @note
		*    - Dependent dynamic libraries are first searched within the same path as the given one
		*    - If the library has already been loaded, this function will fail
		*/
		PLCORE_API bool Load(const String &sPath);

		/**
		*  @brief
		*    Returns if the dynamic library has been loaded
		*
		*  @return
		*    'true' if loaded, else 'false'
		*/
		PLCORE_API bool IsLoaded() const;

		/**
		*  @brief
		*    Get the path (set within 'Load()') to the dynamic library
		*
		*  @return
		*    The path to the dynamic library
		*/
		PLCORE_API String GetPath() const;

		/**
		*  @brief
		*    Get the absolute path to the dynamic library
		*
		*  @return
		*    The absolute path to the dynamic library
		*/
		PLCORE_API String GetAbsPath() const;

		/**
		*  @brief
		*    Returns a pointer to a symbol in the library
		*
		*  @param[in] sSymbol
		*    Name of the symbol to retrieve
		*
		*  @return
		*    Pointer to the symbol, or a null pointer on error
		*
		*  @note
		*    - The pointer to the symbol only stays valid as long as this dynamic library instance is not unloaded
		*/
		PLCORE_API void *GetSymbol(const String &sSymbol) const;

		/**
		*  @brief
		*    Unloads the dynamic library
		*
		*  @return
		*    'true' if the library could be unloaded, else false
		*/
		PLCORE_API bool Unload();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		DynLib(const DynLib &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		DynLib &operator =(const DynLib &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DynLibImpl *m_pDynLibImpl;	/**< Pointer to the system specific implementation (assumed to be never a null pointer!) */
		Url			m_cUrl;			/**< Url to the dynamic library */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNLIB_H__
