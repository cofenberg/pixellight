#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
define_project(PLInstall NOSUFFIX)

##################################################
## Include directories
##################################################
add_include_directories(
	src
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Plugins/PLFrontendQt/include	# We only need the headers and not linking against this library

	# We need the following to be able to include headers produced by uic in our code
	# (CMAKE_CURRENT_BINARY_DIR holds a path to the build directory of the current project, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
	${CMAKE_CURRENT_BINARY_DIR}
	${QT_INCLUDE_DIRS}
)

##################################################
## Special Qt stuff (see http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake for more information)
##################################################
# Include files with Qt relevant information
set(INC_FILES
	src/MainWindow.h
)

# Qt .ui files
set(UI_FILES
	src/MainWindow.ui
)

# Qt .qrc files
set(QRC_FILES
	res/qtresources.qrc
)

# Run uic on .ui files
QT4_WRAP_UI(UI_SRCS ${UI_FILES})

# Run moc
QT4_WRAP_CPP(MOC_SRCS ${INC_FILES})

# Run rcc
QT4_ADD_RESOURCES(QRC_SRCS ${QRC_FILES})

##################################################
## Source files
##################################################
add_sources(
	src/main.cpp
	src/MainWindow.cpp
	src/InstallerFunctions.cpp
	${UI_SRCS}	# Add source produced by uic
	${MOC_SRCS}	# Add source produced by moc
	${QRC_SRCS}	# Add sources produced by rcc
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_sources(
		PLInstall.rc
	)
endif()

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
	PLCoreStat
	${QT_LIBRARIES}
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_STANDARD_LIBS}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLCORE_STATIC
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()

##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
	)
endif()

##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()

##################################################
## Build
##################################################
build_executable(${CMAKETOOLS_CURRENT_TARGET} WIN32)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Qt PLCoreStat)
add_dependencies(Tools							${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} ${PL_RUNTIME_BIN_DIR}
)

##################################################
## Install
##################################################

# Executable
# [TODO] Enable this when PLInstall is ready for the public PixelLight SDK
#install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
#	DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
#)
