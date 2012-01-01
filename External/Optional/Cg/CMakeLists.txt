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
define_external_project(Cg)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	find_package(Cg)
	set(CG_INCLUDE_DIRS ${CG_INCLUDE_PATH} CACHE INTERNAL "")
	set(CG_OPENGL_LIBRARIES ${CG_LIBRARY} ${CG_GL_LIBRARY} CACHE INTERNAL "")
	set(CG_DIRECTX9_LIBRARIES ${CG_LIBRARY} ${CG_D3D9_LIBRARY} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(CG_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(CG_OPENGL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/cg.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/cgGL.lib CACHE INTERNAL "")
		set(CG_DIRECTX9_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/cg.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/cgD3D9.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(CG_OPENGL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libCg.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libCgGL.so CACHE INTERNAL "")
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
