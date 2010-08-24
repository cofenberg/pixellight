/*********************************************************\
 *  File: PLPlugin.h                                     *
 *      Main header file of this project
\*********************************************************/


/**
*  @mainpage PLPlugin
*
*  @section intro_sec Introduction
*
*  This is the PLPlugin API reference.
*/


#ifndef __PLPLUGIN_PLPLUGIN_H__
#define __PLPLUGIN_PLPLUGIN_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Win32 platform
#ifdef WIN32
	#include "PLPlugin/PLPluginWin32.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPlugin/PLPluginLinux.h"
#endif


#endif // __PLPLUGIN_PLPLUGIN_H__
