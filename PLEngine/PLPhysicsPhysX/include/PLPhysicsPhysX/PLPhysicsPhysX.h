/*********************************************************\
 *  File: PLPhysicsPhysX.h                               *
 *      Main header file of this project
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


/**
*  @mainpage PLPhysicsPhysX
*
*  @section intro_sec Introduction
*
*  This is the PLPhysicsPhysX reference.
*/


#ifndef __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
#define __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLPhysicsPhysX/PLPhysicsPhysXWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPhysicsPhysX/PLPhysicsPhysXLinux.h"
#endif


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4100) // "'identifier' : unreferenced formal parameter"
	PL_WARNING_DISABLE(4244) // "'conversion' conversion from 'type1' to 'type2', possible loss of data"
	PL_WARNING_DISABLE(4512) // "'class' : assignment operator could not be generated"
	#include <NxPhysics.h>
PL_WARNING_POP


#endif // __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
