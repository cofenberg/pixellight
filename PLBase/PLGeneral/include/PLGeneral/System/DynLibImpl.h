/*********************************************************\
 *  File: DynLibImpl.h                                   *
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


#ifndef __PLGENERAL_DYNLIB_IMPL_H__
#define __PLGENERAL_DYNLIB_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Url;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'DynLib' implementations
*/
class DynLibImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DynLib;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		DynLibImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DynLibImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual DynLibImpl functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Returns if the dynamic library has been loaded
		*
		*  @return
		*    'true' if loaded, else 'false'
		*/
		virtual bool IsLoaded() const = 0;

		/**
		*  @brief
		*    Loads a dynamic library
		*
		*  @param[in] cUrl
		*    Path to the dynamic library
		*
		*  @return
		*    'true' if the library could be loaded, else false
		*/
		virtual bool Load(const Url &cUrl) = 0;

		/**
		*  @brief
		*    Get the absolute path to the dynamic library
		*
		*  @return
		*    The absolute path to the dynamic library
		*/
		virtual String GetAbsPath() const = 0;

		/**
		*  @brief
		*    Unloads the dynamic library
		*
		*  @return
		*    'true' if the library could be unloaded, else false
		*/
		virtual bool Unload() = 0;

		/**
		*  @brief
		*    Returns a pointer to a symbol in the library
		*
		*  @param[in] sSymbol
		*    Name of the symbol to retrieve
		*
		*  @return
		*    Pointer to the symbol, or a null pointer on error
		*/
		virtual void *GetSymbol(const String &sSymbol) const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_DYNLIB_IMPL_H__
