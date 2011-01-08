/*********************************************************\
 *  File: PLPluginWin32.h                                *
 *      Win32 definitions for PLPlugin
\*********************************************************/


#ifndef __PLPLUGIN_WIN32_H__
#define __PLPLUGIN_WIN32_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLPLUGIN_EXPORTS
	// To export classes, methods and variables
	#define PLPLUGIN_API __declspec(dllexport)

	// To export explicit template instanciations
	#define PLPLUGIN_TEMPLATE

	// To export RTTI elements
	#define PLPLUGIN_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLPLUGIN_API __declspec(dllimport)

	// To import explicit template instanciations
	#define PLPLUGIN_TEMPLATE extern

	// To import RTTI elements
	#define PLPLUGIN_RTTI_EXPORT 0
#endif

// To export/import class templates
#define PLPLUGIN_TMPL


#endif // __PLPLUGIN_WIN32_H__
