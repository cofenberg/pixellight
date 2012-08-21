#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


##################################################
## Project
##################################################
define_external_project(zlib)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# Android hasn't that many public shared libraries on it's system, but zlib is there, so do always use the system version to save memory
# (just in case you may say "Why the heck don't you use "CMAKETOOLS_USE_SYSTEM_LIBS" in the first place?" -> right now, "CMAKETOOLS_USE_SYSTEM_LIBS"
#  means "use system library or just fail", to fail is no option just because we want to use this single system library in here... maybe when
#  using "CMAKETOOLS_USE_SYSTEM_LIBS" there should be a fallback in case there's no such system library?)
if(CMAKETOOLS_USE_SYSTEM_LIBS OR ANDROID)
	##################################################
	## Use system libraries
	##################################################
	find_package(ZLIB)

	# The find module from CMake itself doesn't add the XXX_LIBRARIES variable and XXX_INCLUDE_DIR variable to the cache, which is the correct behaviour.
	# These variables should normaly only be visible within the cmake file in which the find module was called.
	# Otherwise the variables would be visible for all other projects if wanted or not
	# We want this, because this variables are used in other CMake files, which doesn't include this file, so we add the variables to the cache
	set(ZLIB_LIBRARIES ${ZLIB_LIBRARIES} CACHE INTERNAL "")
	set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Base ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(ZLIB_INCLUDE_DIR ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/zlib CACHE INTERNAL "")
	if(WIN32)
		set(ZLIB_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/zlib.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(ZLIB_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libz.a CACHE INTERNAL "")
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
endif()
