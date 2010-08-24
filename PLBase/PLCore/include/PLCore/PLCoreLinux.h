/*********************************************************\
 *  File: PLCoreLinux.h                                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_LINUX_H__
#define __PLCORE_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLCORE_EXPORTS
	#if defined(PLCORE_STATIC)
		// To export classes, methods and variables
		#define PLCORE_API

		// To export explicit template instanciations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#elif defined(HAVE_VISIBILITY_ATTR)
		// To export classes, methods and variables
		#define PLCORE_API __attribute__ ((visibility("default")))

		// To export explicit template instanciations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#else
		// To export classes, methods and variables
		#define PLCORE_API

		// To export explicit template instanciations
		#define PLCORE_TEMPLATE

		// To export RTTI elements
		#define PLCORE_RTTI_EXPORT 1
	#endif
#else
	// To import classes, methods and variables
	#define PLCORE_API

	// To import explicit template instanciations
	#define PLCORE_TEMPLATE extern

	// To import RTTI elements
	#define PLCORE_RTTI_EXPORT 0
#endif

#if defined(HAVE_VISIBILITY_ATTR) && !defined(PLCORE_STATIC)
		// To import/export class templates
		#define PLCORE_TMPL __attribute__ ((visibility("default")))

		// To export plugin functions
		#define PLCORE_PLUGIN_API __attribute__ ((visibility("default")))
#else
		// To import/export class templates
		#define PLCORE_TMPL

		// To export plugin functions
		#define PLCORE_PLUGIN_API
#endif


#endif // __PLCORE_LINUX_H__
