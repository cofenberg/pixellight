#*********************************************************#
#*  File: Pack-Runtime.cmake                             *
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
## CPack configuration
##################################################
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	##################################################
	## Package specific options
	##################################################
	set(CMAKE_MODULE_PATH		${CMAKE_SOURCE_DIR}/Packages/SDK)
	set(CPACK_PL_PACKAGE_PATH	${CMAKE_SOURCE_DIR}/Packages)
	if(MSVC10)
		include(${CMAKE_SOURCE_DIR}/External/Base/VC2010/Package.cmake  ${CMAKETOOLS_DIR}/CMakeTools_Packs.cmake)
	endif()

	##################################################
	## Includes
	##################################################
	include(${CMAKETOOLS_DIR}/CMakeTools_Packs.cmake)

	##################################################
	## Package information
	##################################################
	set(CPACK_PACKAGE_NAME					"PixelLight-Runtime")
	set(CPACK_PACKAGE_VENDOR				"PixelLight")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY	"PixelLight Runtime")
	set(CPACK_PACKAGE_VERSION_MAJOR			"${CMAKETOOLS_PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR			"${CMAKETOOLS_PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH			"${CMAKETOOLS_PROJECT_VERSION_PATCH}")
	set(CPACK_RESOURCE_FILE_LICENSE			"${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt")
	set(CPACK_RESOURCE_FILE_README			"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_RESOURCE_FILE_WELCOME			"${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt")
	set(CPACK_PACKAGE_DESCRIPTION_FILE		"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_PACKAGE_ICON					"${CMAKE_SOURCE_DIR}/Packages/Files/pl_logo.bmp")
	set(CPACK_NSIS_DISPLAY_NAME				"PixelLight Runtime")
	set(CPACK_NSIS_INSTALLED_ICON_NAME		"bin\\\\InstallD.exe")
	set(CPACK_NSIS_HELP_LINK				"http://www.pixellight.org")
	set(CPACK_NSIS_URL_INFO_ABOUT			"http://www.pixellight.org")
	set(CPACK_NSIS_CONTACT					"pixellight3d@gmail.com")
	if(WIN32)
		make_windows_path(CPACK_PACKAGE_ICON)
	endif()

	##################################################
	## Package name
	##################################################
	# Use name convention "PixelLight-MAJOR.MINOR.PATCH-RELEASE-SYSTEM-Package"
	set(CPACK_PACKAGE_FILE_NAME "PixelLight-${CMAKETOOLS_PROJECT_VERSION_MAJOR}.${CMAKETOOLS_PROJECT_VERSION_MINOR}.${CMAKETOOLS_PROJECT_VERSION_PATCH}-${CMAKETOOLS_PROJECT_VERSION_RELEASE}-${CMAKETOOLS_TARGET_SYSTEM}-Runtime")

	##################################################
	## Start menu icons
	##################################################
	set(CPACK_NSIS_CREATE_ICONS "")
	set(CPACK_NSIS_DELETE_ICONS "")

	##################################################
	## Extra install commands
	##################################################
	# Registry key
	if(CMAKETOOLS_CONFIG_SUFFIX)
		set(regkey "\\\"Software\\\\${CPACK_PACKAGE_VENDOR}\\\\${CPACK_PACKAGE_NAME}-${CMAKETOOLS_CONFIG_SUFFIX}\\\"")
	else()
		set(regkey "\\\"Software\\\\${CPACK_PACKAGE_VENDOR}\\\\${CPACK_PACKAGE_NAME}\\\"")
	endif()

	# Install
	set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
		WriteRegStr HKLM ${regkey} \\\"Runtime\\\" \\\"$INSTDIR\\\\Runtime\\\"
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call AddToPath
	")

	# Un-Install
	set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
		DeleteRegKey HKLM ${regkey}
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call un.RemoveFromPath
	")

	##################################################
	## Install files
	##################################################
	set(CPACK_INSTALL_CMAKE_PROJECTS		"${CMAKE_BINARY_DIR};PixelLight;Runtime;/")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY		"PixelLight-Runtime")
	set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY	"PixelLight-Runtime")

	##################################################
	## Set generator
	##################################################
	set(CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CPackConfig-PL_Runtime.cmake")
	if(WIN32)
		set(CPACK_GENERATOR		"NSIS")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.exe")
	elseif(LINUX)
		set(CPACK_GENERATOR		"TGZ")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.tar.gz")
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
	Pack-Runtime
	COMMAND ${CPACK_COMMAND} -C ${CMAKE_BUILD_TYPE} --config ${CMAKE_BINARY_DIR}/CPackConfig-PL_Runtime.cmake
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_target_properties(Pack-Runtime PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Dependencies
##################################################
add_dependencies(Pack-Runtime		PixelLight Docs)
if(WIN32)
	add_dependencies(Pack-Runtime	External-VC2010)
endif()
add_dependencies(Pack				Pack-Runtime)

##################################################
## Post-Build
##################################################
add_custom_command(TARGET Pack-Runtime
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PL_BIN_DIR}/Packages"
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_OUTPUT_FILE} "${PL_BIN_DIR}/Packages"
)