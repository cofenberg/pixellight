/*********************************************************\
 *  File: StdIo.h                                        *
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


#ifndef __PLCORE_STDIO_H__
#define __PLCORE_STDIO_H__
#pragma once


//[-------------------------------------------------------]
//[ Windows                                               ]
//[-------------------------------------------------------]
#ifdef WIN32
	// Hmmmpf, not nice. But better than to include <stdio.h>, and as it must only work on Windows, it might be ok :-)
	struct _iobuf;
	typedef struct _iobuf FILE;
#endif


//[-------------------------------------------------------]
//[ Linux                                                 ]
//[-------------------------------------------------------]
#ifdef LINUX
	// Is it possible to make a forward declaration also under Linux/*nix?
	#include <stdio.h>
#endif


#endif // __PLCORE_STDIO_H__
