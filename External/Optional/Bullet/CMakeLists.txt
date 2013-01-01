#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
define_external_project(Bullet)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for Bullet?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(BULLET)
#	set(BULLET_INCLUDE_DIRS ${BULLET_INCLUDE_DIR_BULLET} CACHE INTERNAL "")
#	set(BULLET_LIBRARIES ${BULLET_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(BULLET_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Bullet CACHE INTERNAL "")
	if(WIN32)
		set(BULLET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/BulletDynamics.lib
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/BulletCollision.lib
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/LinearMath.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(BULLET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libBulletDynamics.a
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/libBulletCollision.a
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/libLinearMath.a CACHE INTERNAL "")
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

# [TODO] System libs possible for Newton?
#endif()
