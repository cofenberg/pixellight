/*********************************************************\
 *  File: PLPluginWin32Includes.h                        *
 *      Windows includes for PLPlugin
\*********************************************************/


#ifndef __PLPLUGIN_WIN32INCLUDES_H__
#define __PLPLUGIN_WIN32INCLUDES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// Set windows version to Windows XP
#ifndef WINVER
	#define WINVER			0x0501
	#define _WIN32_WINNT	0x0501
#endif

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

// Includes
#include <windows.h>


#endif // __PLPLUGIN_WIN32INCLUDES_H__
