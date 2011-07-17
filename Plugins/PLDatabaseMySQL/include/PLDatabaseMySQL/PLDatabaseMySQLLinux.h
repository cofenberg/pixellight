/*********************************************************\
 *  File: PLDatabaseMySQLLinux.h                         *
 *      Linux definitions for PL MySQL database
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLDATABASEMYSQL_LINUX_H__
#define __PLDATABASEMYSQL_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLDATABASEMYSQL_EXPORTS
	#ifdef HAVE_VISIBILITY_ATTR
		// To export classes, methods and variables
		#define PLDATABASEMYSQL_API __attribute__ ((visibility("default")))
	#else
		// To export classes, methods and variables
		#define PLDATABASEMYSQL_API
	#endif

	// To export RTTI elements
	#define PLDATABASEMYSQL_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLDATABASEMYSQL_API

	// To import RTTI elements
	#define PLDATABASEMYSQL_RTTI_EXPORT 0
#endif


#endif // __PLDATABASEMYSQL_LINUX_H__
