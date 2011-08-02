/*********************************************************\
 *  File: PLGuiXmlTextWindows.h                          *
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


#ifndef __PLGUIXMLTEXT_WINDOWS_H__
#define __PLGUIXMLTEXT_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLGUIXMLTEXT_EXPORTS
	// To export classes, methods and variables
	#define PLGUIXMLTEXT_API __declspec(dllexport)

	// To export RTTI elements
	#define PLGUIXMLTEXT_RTTI_EXPORT 1

	// To export explicit template instanciations
	#define PLGUIXMLTEXT_TEMPLATE
#else
	// To import classes, methods and variables
	#define PLGUIXMLTEXT_API __declspec(dllimport)

	// To import RTTI elements
	#define PLGUIXMLTEXT_RTTI_EXPORT 0

	// To import explicit template instanciations (C++0x, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLGUIXMLTEXT_TEMPLATE extern
#endif


#endif // __PLGUIXMLTEXT_WINDOWS_H__
