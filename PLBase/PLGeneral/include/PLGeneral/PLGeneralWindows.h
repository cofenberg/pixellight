/*********************************************************\
 *  PLGeneral Library                                    *
 *  ----------------------------------------------------
 *  File: PLGeneralWindows.h
 *      Windows definitions for PLGeneral
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


#ifndef __PLGENERAL_WINDOWS_H__
#define __PLGENERAL_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Makros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Backups the current warning state for all warnings
*/
#ifdef __MINGW32__
	#define PL_WARNING_PUSH
#else
	#define PL_WARNING_PUSH __pragma(warning(push))
#endif

/**
*  @brief
*    Restores the last warning state pushed onto the stack
*/
#ifdef __MINGW32__
	#define PL_WARNING_POP
#else
	#define PL_WARNING_POP __pragma(warning(pop))
#endif

/**
*  @brief
*    Disables a warning
*
*  @param[in] WarningID
*    ID of the warning to disable
*/
#ifdef __MINGW32__
	#define PL_WARNING_DISABLE(WarningID)
#else
	#define PL_WARNING_DISABLE(WarningID) __pragma(warning(disable: WarningID))
#endif


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#ifdef __MINGW32__
	#include <_mingw.h>	// For "__int8", "__int16" and so so definitions
	// Within "_mingw.h", "__int32" is defined as "long" while PixelLight assumes "int", so, we change the definition
	#define __int32 int
	#include <stddef.h>	// For "size_t" and "NULL"
#else
	/**
	*  @brief
	*    The 'NULL'-definition is for instance used to null a pointer
	*
	*  @note
	*    - Do NOT use this for 'virtual Test() = NULL', use 'virtual Test() = 0' instead!
	*/
	#ifndef NULL
		#define NULL 0
	#endif

	// Within VisualStudio, 'wchar_t' can be defined as native type, in this case we don't need a special include
	#if !defined(_MSC_VER) || !defined(_WCHAR_T_DEFINED)
		#include <wctype.h>
	#endif
#endif

/**
*  @brief
*    Invalid handle value (for data type PLGeneral::handle)
*/
#ifdef WIN64
	#define INVALID_HANDLE 0xffffffffffffffff
#else
	#define INVALID_HANDLE 0xffffffff
#endif


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_DISABLE(4100) // "'identifier' : unreferenced formal parameter"
PL_WARNING_DISABLE(4201) // "nonstandard extension used : nameless struct/union"
PL_WARNING_DISABLE(4231) // "nonstandard extension used : 'identifier' before template explicit instantiation"


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLGENERAL_STATIC
	// Static library
	#define PLGENERAL_API
	#define PLGENERAL_TEMPLATE
#elif defined(PLGENERAL_EXPORTS)
	// To export classes, methods and variables
	#define PLGENERAL_API __declspec(dllexport)

	// To export explicit template instanciations
	#define PLGENERAL_TEMPLATE
#else
	// To import classes, methods and variables
	#define PLGENERAL_API __declspec(dllimport)

	// To import explicit template instanciations
	#define PLGENERAL_TEMPLATE extern
#endif

// To export/import class templates
#define PLGENERAL_TMPL

// To export plugin functions
#ifdef PLGENERAL_STATIC
	#define PLGENERAL_PLUGIN_API
#else
	#define PLGENERAL_PLUGIN_API __declspec(dllexport)
#endif


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
namespace PLGeneral {


	// Standard types
	typedef __int8				int8;
	typedef unsigned __int8		uint8;
	typedef unsigned __int8		utf8;

	typedef __int16				int16;
	typedef unsigned __int16	uint16;

	typedef __int32				int32;
	typedef unsigned __int32	uint32;

	typedef __int64				int64;
	typedef unsigned __int64	uint64;

	typedef size_t				uint_ptr;

	typedef unsigned int		handle;


}


#endif // __PLGENERAL_WINDOWS_H__
