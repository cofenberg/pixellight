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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>	// For PL_WARNING_DISABLE


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

	// To export explicit template instanciations
	#define PLCORE_TEMPLATE

	// To export RTTI elements
	#define PLCORE_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLCORE_API __declspec(dllimport)

	// To import explicit template instanciations
	#define PLCORE_TEMPLATE extern

	// To import RTTI elements
	#define PLCORE_RTTI_EXPORT 0
#endif

// To export/import class templates
#define PLCORE_TMPL

// To export plugin functions
#ifdef PLCORE_STATIC
	#define PLCORE_PLUGIN_API
#else
	#define PLCORE_PLUGIN_API __declspec(dllexport)
#endif


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_DISABLE(4355) // 'this' : used in base member initializer list"


#endif // __PLCORE_WINDOWS_H__
