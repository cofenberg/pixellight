/*********************************************************\
 *  File: PLDatabasePostgreSQL.cpp                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/ModuleMain.h>


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module_plugin("PLDatabasePostgreSQL")
	pl_module_vendor("Copyright (C) 2002-2013 by The PixelLight Team")
	pl_module_license("GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PostgreSQL 8.3.0-2 (http://www.postgresql.org/) database implementation")
	pl_module_dependencies_windows_32_release("comerr32.dll gssapi32.dll k5sprt32.dll krb5_32.dll libeay32.dll libiconv2.dll libintl3.dll libpq.dll ssleay32.dll")
	pl_module_dependencies_windows_32_debug("comerr32.dll gssapi32.dll k5sprt32.dll krb5_32.dll libeay32.dll libiconv2.dll libintl3.dll libpq.dll ssleay32.dll")
	pl_module_dependencies_windows_64_release("comerr32.dll gssapi32.dll k5sprt32.dll krb5_32.dll libeay32.dll libiconv2.dll libintl3.dll libpq.dll ssleay32.dll") // [TODO] 64 bit dll
	pl_module_dependencies_windows_64_debug("comerr32.dll gssapi32.dll k5sprt32.dll krb5_32.dll libeay32.dll libiconv2.dll libintl3.dll libpq.dll ssleay32.dll") // [TODO] 64 bit dll
pl_module_end
