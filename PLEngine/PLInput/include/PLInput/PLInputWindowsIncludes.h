/*********************************************************\
 *  File: PLInputWindowsIncludes.h                       *
 *      Windows includes for PLInput
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


#ifndef __PLINPUT_WINDOWSINCLUDES_H__
#define __PLINPUT_WINDOWSINCLUDES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// Set windows version to Windows XP
#define WINVER			0x0501
#define _WIN32_WINNT	0x0501

// Exclude some stuff from windows.h to speed up compilation a bit
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define OEMRESOURCE
#define NOATOM
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

// Include windows header
__pragma(warning(push))
	__pragma(warning(disable: 4201)) // "nonstandard extension used : nameless struct/union"
	#include <windows.h>
	#include <mmsystem.h>
	extern "C" {
		#include <setupapi.h> 
		#include <hidsdi.h>
	}
__pragma(warning(pop))

// Raw Input definitions
#ifndef HID_USAGE_PAGE_GENERIC
	#define HID_USAGE_PAGE_GENERIC		((USHORT) 0x01)
	#define HID_USAGE_GENERIC_MOUSE		((USHORT) 0x02)
	#define HID_USAGE_GENERIC_JOYSTICK	((USHORT) 0x04)
	#define HID_USAGE_GENERIC_GAMEPAD	((USHORT) 0x05)
	#define HID_USAGE_GENERIC_KEYBOARD	((USHORT) 0x06)
#endif


// We undef these to avoid name conflicts
#undef DrawText
#undef LoadImage
#undef MessageBox
#undef GetClassName
#undef CreateDirectory
#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef GetEnvironmentVariable
#undef SetEnvironmentVariable
#undef GetComputerName
#undef GetUserName
#undef Yield


#endif // __PLINPUT_WINDOWSINCLUDES_H__
