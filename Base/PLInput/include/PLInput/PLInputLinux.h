/*********************************************************\
 *  File: PLInputLinux.h                                 *
 *      Linux definitions for PLInput
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


#ifndef __PLINPUT_LINUX_H__
#define __PLINPUT_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLINPUT_EXPORTS
	#ifdef HAVE_VISIBILITY_ATTR
		// To export classes, methods and variables
		#define PLINPUT_API __attribute__ ((visibility("default")))

		// To export explicit template instanciations
		#define PLINPUT_TEMPLATE
	#else
		// To export classes, methods and variables
		#define PLINPUT_API

		// To export explicit template instanciations
		#define PLINPUT_TEMPLATE
	#endif
#else
	// To import classes, methods and variables
	#define PLINPUT_API

	// To import explicit template instanciations (C++0x, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLINPUT_TEMPLATE extern
#endif

#ifdef HAVE_VISIBILITY_ATTR
	// To import/export class templates
	#define PLINPUT_TMPL __attribute__ ((visibility("default")))
#else
	// To import/export class templates
	#define PLINPUT_TMPL
#endif

// To export RTTI elements - unlike in MSVC for Microsoft Windows, this in here must always be 1 or the RTTI may not work correctly
#define PLINPUT_RTTI_EXPORT 1


#endif // __PLINPUT_LINUX_H__
