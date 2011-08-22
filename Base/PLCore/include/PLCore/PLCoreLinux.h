/*********************************************************\
 *  File: PLCoreLinux.h                                  *
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


#ifndef __PLCORE_LINUX_H__
#define __PLCORE_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Macros                                                ]
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
*    Invalid handle value (for data type PLCore::handle)
*/
#define NULL_HANDLE     0
#define INVALID_HANDLE -1


//[-------------------------------------------------------]
//[ C++0x definitions                                     ]
//[-------------------------------------------------------]
// GCC: Have a look at http://gcc.gnu.org/projects/cxx0x.html see which C++0x features are supported

// "nullptr"-definition
#if (__GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ < 3)
	// There's a bug in GCC 4.5.x ... 4.5.2 causing compiler errors when using the nullptr-class solution from below:
	//   "Bug 45383 - [4.5 Regression] Implicit conversion to pointer does no longer automatically generate operator== and operator!=."
	//   (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=45383)
	// ... looked a few minutes for a solution, without success... (just defining it as 0 is no solution and will introduce other compiler errors!)
	#error "Due to a bug in GCC 4.5.x ... 4.5.2 this GCC version is not supported. Please use a newer or older GCC version instead."
#elif ((__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)) && !defined(__clang__))
	/**
	*  @brief
	*    nullptr definition for compilers don't supporting this C++0x feature
	*
	*  @note
	*    - The implementation comes from the "A name for the null pointer: nullptr"-document (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2431.pdf)
	*/
	const class {
		public:
			template<class T> operator T*() const  { return 0; }
			template<class C, class T> operator T C::*() const  { return 0; }
		private:
			void operator&() const;
	} nullptr = {};
#endif

// "override"-definition, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#override (C++0x keyword is introduced in GCC 4.7 or clang 2.9)
#if ((__GNUC__ < 4 || __GNUC_MINOR__ < 7) && !defined(__clang__))
	#define override
#endif


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLCORE_EXPORTS
	#if defined(PLCORE_STATIC)
		// To export classes, methods and variables
		#define PLCORE_API

		// To export explicit template instantiations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#elif defined(HAVE_VISIBILITY_ATTR)
		// To export classes, methods and variables
		#define PLCORE_API __attribute__ ((visibility("default")))

		// To export explicit template instantiations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#else
		// To export classes, methods and variables
		#define PLCORE_API

		// To export explicit template instantiations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#endif
#else
	// To import classes, methods and variables
	#define PLCORE_API

	// To import explicit template instantiations (C++0x, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLCORE_TEMPLATE extern

	// To import RTTI elements
	#define PLCORE_RTTI_EXPORT 0
#endif

#if defined(HAVE_VISIBILITY_ATTR) && !defined(PLCORE_STATIC)
		// To import/export class templates
		#define PLCORE_TMPL __attribute__ ((visibility("default")))

		// To export plugin functions
		#define PLCORE_PLUGIN_API __attribute__ ((visibility("default")))
#else
		// To import/export class templates
		#define PLCORE_TMPL

		// To export plugin functions
		#define PLCORE_PLUGIN_API
#endif


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
// Standard types
namespace PLCore {


	typedef char				int8;
	typedef unsigned char		uint8;

	typedef short				int16;
	typedef unsigned short		uint16;

	typedef int					int32;
	typedef unsigned int		uint32;

	typedef int64_t 			int64;
	typedef uint64_t			uint64;

	typedef size_t				uint_ptr;

	typedef unsigned long		handle;


}


#endif // __PLCORE_LINUX_H__
