/*********************************************************\
 *  File: PLPhysicsNewton.h                              *
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
*  @mainpage PLPhysicsNewton
*
*  @section intro_sec Introduction
*
*  This is the PLPhysicsNewton reference. Some parts of the class documentation are taken from the
*  Newton documentation. The plugin is no Newton wrapper, it only offers plugins which will make your
*  work using PixelLight and Newton more comfortable.
*
*  Newton uses the matrixes in row-major/left-handed order (this is the way DirectX stores matrices).
*  If you are using PL matrices (column-major/right-handed, like OpenGL does) you will need to transpose
*  the matrices into a local array, before you pass them to Newton.
*/


#ifndef __PLPHYSICSNEWTON_PLPHYSICSNEWTON_H__
#define __PLPHYSICSNEWTON_PLPHYSICSNEWTON_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLPhysicsNewton/PLPhysicsNewtonWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPhysicsNewton/PLPhysicsNewtonLinux.h"
#endif


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
namespace Newton {
	#include <Newton/Newton.h>
}


#endif // __PLPHYSICSNEWTON_PLPHYSICSNEWTON_H__
