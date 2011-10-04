/*********************************************************\
 *  File: PLCoreWindows.h                                *
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


#ifndef __PLCORE_WINDOWS_H__
#define __PLCORE_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Macros                                                ]
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
	#include <stddef.h>	// For "size_t"
#else
	// Within Microsoft Visual Studio, 'wchar_t' can be defined as native type, in this case we don't need a special include
	#if !defined(_MSC_VER) || !defined(_WCHAR_T_DEFINED)
		#include <wctype.h>
	#endif
#endif

/**
*  @brief
*    Invalid handle value (for data type PLCore::handle)
*/
#ifdef WIN64
	#define NULL_HANDLE    0x0000000000000000
	#define INVALID_HANDLE 0xffffffffffffffff
#else
	#define NULL_HANDLE    0x00000000
	#define INVALID_HANDLE 0xffffffff
#endif


//[-------------------------------------------------------]
//[ C++11 definitions                                     ]
//[-------------------------------------------------------]
// Microsoft Visual Studio 2010: Have a look at http://blogs.msdn.com/b/vcblog/archive/2010/04/06/c-0x-core-language-features-in-vc10-the-table.aspx see which C++11 features are supported

// "nullptr"-definition
#if defined(__INTEL_COMPILER) || !defined(_MSC_VER) || _MSC_VER < 1600	// The Intel C++ compiler has no support for nullptr, 1600 = Microsoft Visual Studio 2010
	/**
	*  @brief
	*    nullptr definition for compilers don't supporting this C++11 feature
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


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_DISABLE(4100) // "'identifier' : unreferenced formal parameter"
PL_WARNING_DISABLE(4201) // "nonstandard extension used : nameless struct/union"
PL_WARNING_DISABLE(4231) // "nonstandard extension used : 'identifier' before template explicit instantiation" -> It's part of C++11 (see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
PL_WARNING_DISABLE(4481) // "nonstandard extension used: override specifier 'override'" -> It's part of C++11 (see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#override)


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLCORE_STATIC
	// Static library
	#define PLCORE_API
	#define PLCORE_TEMPLATE
	#define PLCORE_RTTI_EXPORT 1
#elif defined(PLCORE_EXPORTS)
	// To export classes, methods and variables
	#define PLCORE_API __declspec(dllexport)

	// To export explicit template instantiations
	#define PLCORE_TEMPLATE

	// To export RTTI elements
	#define PLCORE_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLCORE_API __declspec(dllimport)

	// To import explicit template instantiations (C++11, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLCORE_TEMPLATE extern

	// To import RTTI elements
	#define PLCORE_RTTI_EXPORT 0
#endif

// To export/import class templates
#define PLCORE_TMPL

// To create template instance
#define PLCORE_TEMPLATE_INSTANCE PLCORE_TEMPLATE template class PLCORE_API

// To export plugin functions
#ifdef PLCORE_STATIC
	#define PLCORE_PLUGIN_API
#else
	#define PLCORE_PLUGIN_API __declspec(dllexport)
#endif


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
namespace PLCore {


	// Standard types
	typedef __int8				int8;
	typedef unsigned __int8		uint8;

	typedef __int16				int16;
	typedef unsigned __int16	uint16;

	typedef __int32				int32;
	typedef unsigned __int32	uint32;

	typedef __int64				int64;
	typedef unsigned __int64	uint64;

	typedef size_t				uint_ptr;

	typedef unsigned int		handle;


}


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_DISABLE(4355) // 'this' : used in base member initializer list"


#endif // __PLCORE_WINDOWS_H__
