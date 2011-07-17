/*********************************************************\
 *  File: PLPhysicsWindows.h                             *
 *      Windows definitions for PLPhysics
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


#ifndef __PLPHYSICS_WINDOWS_H__
#define __PLPHYSICS_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLPHYSICS_EXPORTS
	// To export classes, methods and variables
	#define PLPHYSICS_API __declspec(dllexport)

	// To export RTTI elements
	#define PLPHYSICS_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLPHYSICS_API __declspec(dllimport)

	// To import RTTI elements
	#define PLPHYSICS_RTTI_EXPORT 0
#endif


#endif // __PLPHYSICS_WINDOWS_H__
