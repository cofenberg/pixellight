/*********************************************************\
 *  File: PLScriptNull.h                                 *
 *      Main header file of this project
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


/**
*  @mainpage PLScriptNull
*
*  @section intro_sec Introduction
*
*  This is the PLScriptNull reference.
*/


#ifndef __PLSCRIPTNULL_PLSCRIPTNULL_H__
#define __PLSCRIPTNULL_PLSCRIPTNULL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLSCRIPTNULL_EXPORTS
	// To export classes, methods and variables
	#define PLSCRIPTNULL_API			PL_GENERIC_API_EXPORT

	// To export RTTI elements
	#define PLSCRIPTNULL_RTTI_EXPORT	PL_GENERIC_RTTI_EXPORT
#else
	// To import classes, methods and variables
	#define PLSCRIPTNULL_API			PL_GENERIC_API_IMPORT

	// To import RTTI elements
	#define PLSCRIPTNULL_RTTI_EXPORT	PL_GENERIC_RTTI_IMPORT
#endif


#endif // __PLSCRIPTNULL_PLSCRIPTNULL_H__
