/*********************************************************\
 *  File: PLParticleGroups.h                            *
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
*  @mainpage PLParticleGroups
*
*  @section intro_sec Introduction
*
*  This is the PLParticleGroups reference.
*/


#ifndef __PLPG1_PLPARTICLEGROUPS_H__
#define __PLPG1_PLPARTICLEGROUPS_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLParticleGroups/PLParticleGroupsWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLParticleGroups/PLParticleGroupsLinux.h"
#endif


#endif // __PLPG1_PLPARTICLEGROUPS_H__
