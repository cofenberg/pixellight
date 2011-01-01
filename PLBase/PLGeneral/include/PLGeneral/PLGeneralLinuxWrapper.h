/*********************************************************\
 *  PLGeneral Library                                    *
 *  ----------------------------------------------------
 *  File: PLGeneralLinuxWrapper.h
 *      Linux wrapper definitions for PLGeneral (use them ONLY if REALLY required!)
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


#ifndef __PLGENERAL_LINUXWRAPPER_H__
#define __PLGENERAL_LINUXWRAPPER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
PLGENERAL_API char *_strupr(char *s);
PLGENERAL_API char *strlwr(char *s);
PLGENERAL_API int _vscprintf(const char *format, va_list ap);

// wchar functions
PLGENERAL_API int _vscwprintf(const wchar_t *fmt,va_list ap);
PLGENERAL_API int _vsnwprintf(wchar_t *buf, size_t cnt, const wchar_t *fmt, va_list args);
PLGENERAL_API int _wtoi( const wchar_t *str );
PLGENERAL_API long _wtol( const wchar_t *str );
PLGENERAL_API float _wtof( const wchar_t *str );
PLGENERAL_API wchar_t *_wcsupr(wchar_t *s);
PLGENERAL_API wchar_t *_wcslwr(wchar_t *s);


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#define stricmp(a, b)		strcasecmp(a, b)
#define _stricmp(a, b)		strcasecmp(a, b)
#define _strnicmp(a, b, n)	strncasecmp(a, b, n)
#define strnicmp(a, b, n)	strncasecmp(a, b, n)
#define _strlwr(a)			strlwr(a)
#define _atoi64(a)			atoll(a)
#define _snprintf			snprintf

// wchar functions definitions
#define _wcsicmp(a, b)		wcscasecmp(a, b)
#define _wcsnicmp(a, b, c)	wcsncasecmp(a, b, c)
#undef  vswprintf
#define vswprintf			_vsnwprintf

// system functions
#define _fdopen(a, b)		fdopen(a, b)


#endif // __PLGENERAL_LINUXWRAPPER_H__
