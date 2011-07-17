/*********************************************************\
 *  File: Python.h                                       *
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


#ifndef __PLSCRIPTPYTHON_PYTHON_H__
#define __PLSCRIPTPYTHON_PYTHON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4211) // "nonstandard extension used : redefined extern to static"
	// Ensure that we never need a debug version of Python
	#ifdef _DEBUG
		#undef _DEBUG
		#include <Python/Python.h>
		#define _DEBUG
	#else
		#include <Python/Python.h>
	#endif
PL_WARNING_POP


#endif // __PLSCRIPTPYTHON_PYTHON_H__
