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
define_project(PLFrontendActiveX)

##################################################
## Prerequisites
##################################################
# Copy register.bat and unregister.bat
copy_files("${CMAKE_SOURCE_DIR}/Bin/BrowserPlugins/*.bat" "${PL_BIN_DIR}/BrowserPlugins")

##################################################
## Source files
##################################################
add_sources(
	src/dllmain.cpp
	src/PLFrontendActiveX.cpp
	src/PixelLightCtrl.cpp
	src/stdafx.cpp
	resource/PLFrontendActiveX.rc
	${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.c
	${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.h
)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.c PROPERTIES GENERATED TRUE)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.h PROPERTIES GENERATED TRUE)

##################################################
## Include directories
##################################################
add_include_directories(
	src
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_CURRENT_BINARY_DIR}
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCore
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	${WIN32_COMPILE_DEFS}
	_ATL_DLL
)

##################################################
## Compiler flags
##################################################
add_compile_flags(
	${WIN32_COMPILE_FLAGS}
)
remove_compile_flags(
	/TP
)

##################################################
## Linker flags
##################################################
add_linker_flags(
	${WIN32_LINKER_FLAGS}
	/DEF:${CMAKE_CURRENT_SOURCE_DIR}/PLFrontendActiveX.def	# Use export definitions file
	/DYNAMICBASE
)

##################################################
## Build
##################################################
add_activex_interface(${CMAKETOOLS_CURRENT_TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/src/PLFrontendActiveX.idl
  OPTIONS /char signed /env win32 /Oicf /error stub_data
)
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/BrowserPlugins"
)

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_BROWSER}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_BROWSER}	COMPONENT Runtime
)

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT Runtime
)

# register.bat and unregister.bat
install(FILES ${PL_BIN_DIR}/BrowserPlugins/register.bat
			  ${PL_BIN_DIR}/BrowserPlugins/unregister.bat
	DESTINATION ${PL_INSTALL_BROWSER}			COMPONENT Runtime
)
