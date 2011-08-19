/*********************************************************\
 *  File: PLGuiXmlText.h                                 *
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


#ifndef __PLGUIXMLTEXT_H__
#define __PLGUIXMLTEXT_H__
#pragma once


/**
*  @mainpage PLGuiXmlText
*
*  @section intro_sec Introduction
*
*  This is the PLGuiXmlText API reference. Please note that is no 100%
*  loose dynamic plugin and that one has to use the provided API.
*/


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLGuiXmlText/PLGuiXmlTextWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLGuiXmlText/PLGuiXmlTextLinux.h"
#endif


#endif // __PLGUIXMLTEXT_H__
