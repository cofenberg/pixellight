/*********************************************************\
 *  File: PLFrontendQt.h                                 *
 *      Main header file of this project
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
*  @mainpage PLFrontendQt
*
*  @section intro_sec Introduction
*
*  This is the PLFrontendQt reference. The PLFrontendQt adapter project fulfils multiple purposes.
*
*  There are generic helpers like the static adapter class for mapping Qt strings to PixelLight
*  strings and vice versa. By using those helpers as well as provided data models and so on it's
*  possible to add PixelLight functionality into Qt applications. In other words: Qt is the master,
*  PixelLight is the slave.
*
*  On the other hand this project also supports the other way around were PixelLight is the master
*  and Qt the slave. This is accomplished by adding an "PLCore::FrontendImpl"-implementation using
*  Qt. Internally Qt has the main loop, but due to the frontend approach this is nothing the user
*  has to care about. One is just using PixelLight. When using "PLFrontend::Frontend" as PixelLight
*  frontend, it's possible to access Qt functionality easily to add a GUI. Additionally, there are
*  advanced features like the RTTI dock widgets making it possible to add new dock widgets to the
*  main window in an universal way, even by implementing them in seperate plugins.
*/


#ifndef __PLFRONTENDQT_H__
#define __PLFRONTENDQT_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLFrontendQt/PLFrontendQtWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLFrontendQt/PLFrontendQtLinux.h"
#endif


#endif // __PLFRONTENDQT_H__
