/*********************************************************\
 *  File: SPARK_PL.h                                     *
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
*  @mainpage SPARK_PL
*
*  @section intro_sec Introduction
*
*  This is the SPARK_PL reference. Please note that is no 100% loose dynamic plugin
*  and that one has to use the SPARK-API instead of an abstract PixelLight wrapper.
*/


#ifndef __SPARK_PL_H__
#define __SPARK_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "SPARK_PL/SPARK_PLWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "SPARK_PL/SPARK_PLLinux.h"
#endif


#endif // __SPARK_PL_H__
