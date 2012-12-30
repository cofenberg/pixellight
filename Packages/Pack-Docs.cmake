#*********************************************************#
#*  File: Pack-Docs.cmake                                *
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
	# We have to check whether or not CPack was already included, if this is not done CMake will give us warnings about multiple inclusion
	# (we include CPack in "Pack-Docs.cmake", "Pack-Runtime.cmake" and "Pack-SDK.cmake")
	if(NOT CPack_CMake_INCLUDED)
		include(CPack)
	endif()
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
