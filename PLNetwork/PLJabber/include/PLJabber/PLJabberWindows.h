/*********************************************************\
 *  PLJabber Library                                     *
 *  ----------------------------------------------------
 *  File: PLJabberWindows.h
 *      Windows definitions for PLJabber
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


#ifndef __PLJABBER_WINDOWS_H__
#define __PLJABBER_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLJABBER_EXPORTS
	// To export classes, methods and variables
	#define PLJABBER_API __declspec(dllexport)

	// To export explicit template instanciations
	#define PLJABBER_TEMPLATE
#else
	// To import classes, methods and variables
	#define PLJABBER_API __declspec(dllimport)

	// To import explicit template instanciations
	#define PLJABBER_TEMPLATE extern
#endif

// To export/import class templates
#define PLJABBER_TMPL

// To export plugin functions
#define PLJABBER_PLUGIN_API __declspec(dllexport)


#endif // __PLJABBER_WINDOWS_H__
