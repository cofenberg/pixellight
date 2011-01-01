/*********************************************************\
 *  File: PLPhysicsODE.h                                 *
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
*  @mainpage PLPhysicsODE
*
*  @section intro_sec Introduction
*
*  This is the PLPhysicsODE reference.
*/


#ifndef __PLPHYSICSODE_PLPHYSICSODE_H__
#define __PLPHYSICSODE_PLPHYSICSODE_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLPhysicsODE/PLPhysicsODEWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPhysicsODE/PLPhysicsODELinux.h"
#endif


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4100) // "'identifier' : unreferenced formal parameter"
	#include <ode/ode.h>
PL_WARNING_POP


#endif // __PLPHYSICSODE_PLPHYSICSODE_H__
