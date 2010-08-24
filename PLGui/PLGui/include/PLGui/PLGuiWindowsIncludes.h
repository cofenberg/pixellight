/*********************************************************\
 *  File: PLGuiWindowsIncludes.h                         *
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


#ifndef __PLGUI_WINDOWSINCLUDES_H__
#define __PLGUI_WINDOWSINCLUDES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// Set windows version to Windows XP
#ifdef WINVER
	#undef WINVER
#endif
#define WINVER			0x0501
#ifdef _WIN32_WINNT
	#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT	0x0501

// Exclude some stuff from windows.h to speed up compilation a bit
//#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOMENUS
//#define NOICONS
#define NOKEYSTATES
//#define NOSYSCOMMANDS
//#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOMEMMGR
//#define NOMETAFILE
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

// Include headers
#include <windows.h>

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
#undef CreateFont
#undef Yield
#undef SendMessage
#undef PostMessage


#endif // __PLGUI_WINDOWSINCLUDES_H__
