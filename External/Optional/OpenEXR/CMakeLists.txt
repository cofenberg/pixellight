#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
define_external_project(OpenEXR)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for OpenEXR?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(OPENEXR)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	if(WIN32)
		set(OPENEXR_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../include/Iex ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../include/IlmImf ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../include/Imath CACHE INTERNAL "")
		set(OPENEXR_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/zlib.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/Half.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/Iex.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/Imath.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/IlmImf.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../lib/IlmThread.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(OPENEXR_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
		set(OPENEXR_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libIlmImf.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libImath.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libHalf.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libIex.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libIlmThread.a ${CMAKETOOLS_CURRENT_LIB_DIR}/../../zlib/lib/libz.a CACHE INTERNAL "")
	endif()

	##################################################
	## Check
	##################################################
	external_check()

	##################################################
	## Fetch
	##################################################
	external_fetch()

	##################################################
	## Configure
	##################################################
	external_configure()

	##################################################
	## Build
	##################################################
	external_build()

	##################################################
	## Install
	##################################################
	external_install()

	##################################################
	## Clean
	##################################################
	external_clean()
# [TODO] System libs possible for OpenEXR?
#endif()
