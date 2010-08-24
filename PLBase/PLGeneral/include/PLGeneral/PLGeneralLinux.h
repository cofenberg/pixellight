/*********************************************************\
 *  PLGeneral Library                                    *
 *  ----------------------------------------------------
 *  File: PLGeneralLinux.h
 *      Linux definitions for PLGeneral
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


#ifndef __PLGENERAL_LINUX_H__
#define __PLGENERAL_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Makros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Backups the current warning state for all warnings
*/
#define PL_WARNING_PUSH

/**
*  @brief
*    Restores the last warning state pushed onto the stack
*/
#define PL_WARNING_POP

/**
*  @brief
*    Disables a warning
*
*  @param[in] WarningID
*    ID of the warning to disable
*/
#define PL_WARNING_DISABLE(WarningID)


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stddef.h>
#include <stdint.h>


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    The 'NULL'-definition is for instance used to null a pointer
*
*  @note
*    - Do NOT use this for 'virtual void Test() = NULL', use 'virtual void Test() = 0' instead!
*/
#ifndef NULL
	#define NULL 0
#endif

/**
*  @brief
*    Invalid handle value (for data type PLGeneral::handle)
*/
#define INVALID_HANDLE -1


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLGENERAL_EXPORTS
	#if defined(PLGENERAL_STATIC)
		// To export classes, methods and variables
		#define PLGENERAL_API

		// To export explicit template instanciations
		#define PLGENERAL_TEMPLATE
	#elif defined(HAVE_VISIBILITY_ATTR)
		// To export classes, methods and variables
		#define PLGENERAL_API __attribute__ ((visibility("default")))

		// To export explicit template instanciations
		#define PLGENERAL_TEMPLATE
	#else
		// To export classes, methods and variables
		#define PLGENERAL_API

		// To export explicit template instanciations
		#define PLGENERAL_TEMPLATE
	#endif
#else
	// To import classes, methods and variables
	#define PLGENERAL_API

	// To import explicit template instanciations
	#define PLGENERAL_TEMPLATE extern
#endif

#if defined(HAVE_VISIBILITY_ATTR) && !defined(PLGENERAL_STATIC)
		// To import/export class templates
		#define PLGENERAL_TMPL __attribute__ ((visibility("default")))

		// To export plugin functions
		#define PLGENERAL_PLUGIN_API __attribute__ ((visibility("default")))
#else
		// To import/export class templates
		#define PLGENERAL_TMPL

		// To export plugin functions
		#define PLGENERAL_PLUGIN_API
#endif


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
// Standard types
namespace PLGeneral {


	typedef char				int8;
	typedef unsigned char		uint8;
	typedef unsigned char		utf8;

	typedef short				int16;
	typedef unsigned short		uint16;

	typedef int					int32;
	typedef unsigned int		uint32;

	typedef int64_t 			int64;
	typedef uint64_t			uint64;

	typedef int					handle;


}


#endif // __PLGENERAL_LINUX_H__
