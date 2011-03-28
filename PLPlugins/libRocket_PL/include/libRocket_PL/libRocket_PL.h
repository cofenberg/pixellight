/*********************************************************\
 *  File: libRocket_PL.h                                 *
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
*  @mainpage libRocket_PL
*
*  @section intro_sec Introduction
*
*  This is the libRocket_PL reference.
*/


#ifndef __LIBROCKET_PL_H__
#define __LIBROCKET_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "libRocket_PL/libRocket_PLWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "libRocket_PL/libRocket_PLLinux.h"
#endif


#endif // __LIBROCKET_PL_H__