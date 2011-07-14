##################################################
## CMake
##################################################
cmake_minimum_required(VERSION 2.6)

##################################################
## Project
##################################################
project(PixelLight)

##################################################
## Includes
##################################################
include(cmake/CMakeTools.cmake)
include(cmake/CMakeTools_Apps.cmake)
include(cmake/CMakeTools_Docs.cmake)
include(cmake/CMakeTools_Externals.cmake)
include(PixelLight/PixelLight.cmake)

##################################################
## Prerequisites
##################################################

# Create PixelLight header file
configure_file("PixelLight/PixelLight.h.in" "${CMAKE_BINARY_DIR}/PixelLight.h")

# Create 'Bin' directory
set(PL_BIN_DIR "${CMAKE_SOURCE_DIR}/Bin-${CMAKETOOLS_CONFIG_NAME}")
file(MAKE_DIRECTORY ${PL_BIN_DIR})
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Lib)
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLRuntime)
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLRuntime/Plugins)

# Copy copyright and notes
copy_file(${CMAKE_SOURCE_DIR}/AUTHORS			${PL_BIN_DIR})
copy_file(${CMAKE_SOURCE_DIR}/COPYING			${PL_BIN_DIR})
copy_file(${CMAKE_SOURCE_DIR}/gpl-3.0.txt		${PL_BIN_DIR})
copy_file(${CMAKE_SOURCE_DIR}/lgpl-3.0.txt		${PL_BIN_DIR})
copy_file(${CMAKE_SOURCE_DIR}/cc-by-nc-sa-3.txt	${PL_BIN_DIR})
copy_file(${CMAKE_SOURCE_DIR}/ReleaseNotes.txt	${PL_BIN_DIR})

# Copy Microsoft Visual C++ Redistributables
if(WIN32)
	file(MAKE_DIRECTORY ${PL_BIN_DIR}/VC2010_Redistributable)
	copy_files("${CMAKE_SOURCE_DIR}/Bin/VC2010_Redistributable/*.*" "${PL_BIN_DIR}/VC2010_Redistributable")
endif()

##################################################
## Target
##################################################
add_custom_target(PixelLight)

##################################################
## Projects
##################################################
add_subdirectory(External)
add_subdirectory(PLBase)
add_subdirectory(PLPlugins)
add_subdirectory(PLSamples)
add_subdirectory(PLDemos)
add_subdirectory(PLTests)
add_subdirectory(PLTools)
add_subdirectory(PLDocs)

##################################################
## Install
##################################################

# Copyright and notes
install(FILES	${CMAKE_SOURCE_DIR}/AUTHORS
				${CMAKE_SOURCE_DIR}/COPYING
				${CMAKE_SOURCE_DIR}/gpl-3.0.txt
				${CMAKE_SOURCE_DIR}/lgpl-3.0.txt
				${CMAKE_SOURCE_DIR}/cc-by-nc-sa-3.txt
				${CMAKE_SOURCE_DIR}/ReleaseNotes.txt
	DESTINATION ${PL_INSTALL_ROOT}			COMPONENT SDK
)

# Microsoft Visual C++ Redistributables
if(WIN32)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/VC2010_Redistributable
		DESTINATION ${PL_INSTALL_ROOT}		COMPONENT SDK
	)
endif()

##################################################
## Packages
##################################################
if(CMAKE_BUILD_TYPE MATCHES Release)
	add_subdirectory(Packages)
endif()

##################################################
## Testing
##################################################
if(CMAKETOOLS_CONFIG_NIGHTLY)
	include(CTest)
endif()
