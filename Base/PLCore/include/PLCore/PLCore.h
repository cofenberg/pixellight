/*********************************************************\
 *  File: PLCore.h                                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


/**
*  @mainpage PLCore
*
*  @section intro_sec Introduction
*
*  This is the PLCore API reference.
*/


#ifndef __PLCORE_H__
#define __PLCORE_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLCore/PLCoreWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLCore/PLCoreLinux.h"
#endif


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLCORE_STATIC
	// Static library
	#define PLCORE_API			// -
	#define PLCORE_RTTI_EXPORT	1
#elif defined(PLCORE_EXPORTS)
	// To export classes, methods and variables
	#define PLCORE_API			PL_GENERIC_API_EXPORT

	// To export RTTI elements
	#define PLCORE_RTTI_EXPORT	PL_GENERIC_RTTI_EXPORT
#else
	// To import classes, methods and variables
	#define PLCORE_API			PL_GENERIC_API_IMPORT

	// To import RTTI elements
	#define PLCORE_RTTI_EXPORT	PL_GENERIC_RTTI_IMPORT
#endif


#endif // __PLCORE_H__
