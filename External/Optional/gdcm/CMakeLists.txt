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
define_external_project(gdcm)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for gdcm?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(gdcm)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	# The header design of GDCM is forcing us to add multiple include directories
	set(GDCM_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/gdcm/Common ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/gdcm/DataDictionary ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/gdcm/DataStructureAndEncodingDefinition ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/gdcm/InformationObjectDefinition ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/gdcm/MediaStorageAndFileFormat CACHE INTERNAL "")
	if(WIN32)
		set(GDCM_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmcharls.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmCommon.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmDICT.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmDSED.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmexpat.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmgetopt.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmIOD.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmjpeg8.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmjpeg12.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmjpeg16.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmMSFF.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmopenjpeg.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/gdcmzlib.lib wsock32.lib CACHE INTERNAL "")
	elseif(LINUX)
		# [TODO] Implement me
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
# [TODO] System libs possible for gdcm?
#endif()
