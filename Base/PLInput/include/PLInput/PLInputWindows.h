/*********************************************************\
 *  File: PLInputWindows.h                               *
 *      Windows definitions for PLInput
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


#ifndef __PLINPUT_WINDOWS_H__
#define __PLINPUT_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLINPUT_EXPORTS
	// To export classes, methods and variables
	#define PLINPUT_API __declspec(dllexport)

	// To export explicit template instantiations
	#define PLINPUT_TEMPLATE

	// To export RTTI elements
	#define PLINPUT_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLINPUT_API __declspec(dllimport)

	// To import explicit template instantiations (C++0x, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLINPUT_TEMPLATE extern

	// To import RTTI elements
	#define PLINPUT_RTTI_EXPORT 0
#endif


#endif // __PLINPUT_WINDOWS_H__
