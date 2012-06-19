/*********************************************************\
 *  File: PLVolumeGui.h                                  *
 *      Main header file of this project
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


/**
*  @mainpage PLVolumeGui
*
*  @section intro_sec Introduction
*
*  This is the PLVolumeGui reference.
*/


#ifndef __PLVOLUMEGUI_PLVOLUMEGUI_H__
#define __PLVOLUMEGUI_PLVOLUMEGUI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLVOLUMEGUI_EXPORTS
	// To export classes, methods and variables
	#define PLVOLUMEGUI_API			PL_GENERIC_API_EXPORT

	// To export RTTI elements
	#define PLVOLUMEGUI_RTTI_EXPORT	PL_GENERIC_RTTI_EXPORT
#else
	// To import classes, methods and variables
	#define PLVOLUMEGUI_API			PL_GENERIC_API_IMPORT

	// To import RTTI elements
	#define PLVOLUMEGUI_RTTI_EXPORT	PL_GENERIC_RTTI_IMPORT
#endif


#endif // __PLVOLUMEGUI_PLVOLUMEGUI_H__
