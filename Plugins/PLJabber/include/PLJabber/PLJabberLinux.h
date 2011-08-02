/*********************************************************\
 *  PLJabber Library                                     *
 *  ----------------------------------------------------
 *  File: PLJabberLinux.h
 *      Linux definitions for PLJabber
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


#ifndef __PLJABBER_LINUX_H__
#define __PLJABBER_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLJABBER_EXPORTS
	#ifdef HAVE_VISIBILITY_ATTR
		// To export classes, methods and variables
		#define PLJABBER_API __attribute__ ((visibility("default")))
	#else
		// To export classes, methods and variables
		#define PLJABBER_API
	#endif
#else
	// To import classes, methods and variables
	#define PLJABBER_API
#endif

#ifdef HAVE_VISIBILITY_ATTR
		// To export plugin functions
		#define PLJABBER_PLUGIN_API __attribute__ ((visibility("default")))
#else
		// To export plugin functions
		#define PLJABBER_PLUGIN_API
#endif


#endif // __PLJABBER_LINUX_H__
