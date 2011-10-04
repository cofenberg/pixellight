#*********************************************************#
#*  File: Pack-Docs.cmake                                *
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
## CPack configuration
##################################################
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	##################################################
	## Includes
	##################################################
	include(${CMAKETOOLS_DIR}/CMakeTools_Packs.cmake)

	##################################################
	## Package information
	##################################################
	set(CPACK_PACKAGE_NAME					"PixelLight-Docs")
	set(CPACK_PACKAGE_VENDOR				"PixelLight")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY	"PixelLight Docs")
	set(CPACK_PACKAGE_VERSION_MAJOR			"${CMAKETOOLS_PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR			"${CMAKETOOLS_PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH			"${CMAKETOOLS_PROJECT_VERSION_PATCH}")
	set(CPACK_RESOURCE_FILE_LICENSE			"${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt")
	set(CPACK_RESOURCE_FILE_README			"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_RESOURCE_FILE_WELCOME			"${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt")
	set(CPACK_PACKAGE_DESCRIPTION_FILE		"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_PACKAGE_ICON					"${CMAKE_SOURCE_DIR}/Packages/Files/pl_logo.bmp")
	if(WIN32)
		make_windows_path(CPACK_PACKAGE_ICON)
	endif()

	##################################################
	## Package name
	##################################################
	# Use name convention "PixelLight-MAJOR.MINOR.PATCH-RELEASE-Package"
	set(CPACK_PACKAGE_FILE_NAME "PixelLight-${CMAKETOOLS_PROJECT_VERSION_MAJOR}.${CMAKETOOLS_PROJECT_VERSION_MINOR}.${CMAKETOOLS_PROJECT_VERSION_PATCH}-${CMAKETOOLS_PROJECT_VERSION_RELEASE}-Docs")

	##################################################
	## Install files
	##################################################
	set(CPACK_INSTALL_CMAKE_PROJECTS		"${CMAKE_BINARY_DIR}/Docs;Docs;Docs;/")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY		"PixelLight-Docs")
	set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY	"PixelLight-Docs")

	##################################################
	## Set generator
	##################################################
	set(CPACK_OUTPUT_CONFIG_FILE	"${CMAKE_BINARY_DIR}/CPackConfig-PL_Docs.cmake")
	if(WIN32)
		set(CPACK_GENERATOR			"ZIP")
		set(CPACK_OUTPUT_FILE		"${CPACK_PACKAGE_FILE_NAME}.zip")
	elseif(LINUX)
		set(CPACK_GENERATOR			"TGZ")
		set(CPACK_OUTPUT_FILE		"${CPACK_PACKAGE_FILE_NAME}.tar.gz")
	endif()

	##################################################
	## CPack
	##################################################
	include(CPack)
endif()

##################################################
## Package target
##################################################
add_custom_target(
	Pack-Docs
	COMMAND ${CPACK_COMMAND} -C ${CMAKE_BUILD_TYPE} --config ${CMAKE_BINARY_DIR}/CPackConfig-PL_Docs.cmake
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_target_properties(Pack-Docs PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Dependencies
##################################################
add_dependencies(Pack-Docs	Docs)
add_dependencies(Pack		Pack-Docs)

##################################################
## Post-Build
##################################################
add_custom_command(TARGET Pack-Docs
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PL_BIN_DIR}/Packages"
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_OUTPUT_FILE} "${PL_BIN_DIR}/Packages"
)
