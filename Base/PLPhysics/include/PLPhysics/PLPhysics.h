/*********************************************************\
 *  File: PLPhysics.h                                    *
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
*  @mainpage PLPhysics
*
*  @section intro_sec Introduction
*
*  This is the PLPhysics API reference.
*/


#ifndef __PLPHYSICS_PLPHYSICS_H__
#define __PLPHYSICS_PLPHYSICS_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLPhysics/PLPhysicsWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPhysics/PLPhysicsLinux.h"
#endif


#endif // __PLPHYSICS_PLPHYSICS_H__