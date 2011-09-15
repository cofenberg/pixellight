#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
define_external_project(PhysX)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for PhysX?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(PhysX)
#	set(PHYSX_INCLUDE_DIRS ${PHYSX_INCLUDE_DIR_PHYSX} CACHE INTERNAL "")
#	set(PHYSX_LIBRARIES ${PHYSX_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(PHYSX_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/Foundation/include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/Physics/include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/PhysXLoader/include CACHE INTERNAL "")
	if(WIN32)
		set(PHYSX_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/PhysXLoader.lib CACHE INTERNAL "")
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

# [TODO] System libs possible for PhysX?
#endif()
