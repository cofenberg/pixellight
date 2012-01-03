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
project(Docs)

##################################################
## Prerequisites
##################################################

# Create 'Docs'-directory
set(PL_DOCS_DIR "${PL_BIN_DIR}/Docs")
file(MAKE_DIRECTORY ${PL_DOCS_DIR})

# Create temp dir
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Common)

# Copy file format samples
file(MAKE_DIRECTORY "${PL_DOCS_DIR}/FileFormats")
copy_files("${CMAKE_SOURCE_DIR}/Docs/FileFormats/*.*" "${PL_DOCS_DIR}/FileFormats")

# Create title file used within the PixelLight documentations
configure_file("${CMAKE_SOURCE_DIR}/Docs/Common/Title.tex.in" "${CMAKE_SOURCE_DIR}/Docs/Common/Title.tex")

##################################################
## Target
##################################################
add_custom_target(Docs)
set_target_properties(Docs PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

add_custom_target(Docs-install)
set_target_properties(Docs-install PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Projects
##################################################
# The following documents require LaTex and dvipdf,
# if CMake was unable to find it, ignore the following documents in order to avoid confusing confusing errors when building the project
if(LATEX_COMPILER)
	if(DVIPDF_CONVERTER)
		add_subdirectory(PixelLightFeatures)
		add_subdirectory(PixelLightBase)
		add_subdirectory(PixelLightCompositing)
		add_subdirectory(PixelLightConventions)
		add_subdirectory(PixelLightBuild)
		add_subdirectory(PixelLightScript)
		add_subdirectory(PixelLight3dsMaxSceneExport)
	else()
		message(STATUS "Ignoring PixelLightFeatures, PixelLightBase, PixelLightCompositing, PixelLightConventions, PixelLightBuild, PixelLightScript and PixelLight3dsMaxSceneExport documentation because dvipdf was not found")
	endif()
else()
	message(STATUS "Ignoring PixelLightFeatures, PixelLightBase, PixelLightCompositing, PixelLightConventions, PixelLightBuild, PixelLightScript and PixelLight3dsMaxSceneExport documentation because LaTeX was not found")
endif()

# The PixelLight API documentation requires Doxygen (http://www.doxygen.org),
# if CMake was unable to find it, ignore the following document in order to avoid confusing confusing errors when building the project
if(DOXYGEN_FOUND)
	add_subdirectory(PixelLightAPI)
else()
	message(STATUS "Ignoring PixelLight API documentation because Doxygen (http://www.doxygen.org) was not found")
endif()

# The SDK browser can only be build when the Microsoft Html Help Compiler (http://msdn.microsoft.com/en-us/library/ms669985) has been found by CMake,
# if CMake was unable to find it, ignore the following document in order to avoid confusing confusing errors when building the project
if(HTML_HELP_COMPILER)
	add_subdirectory(SDKBrowser)
else()
	message(STATUS "Ignoring PixelLight SDK browser because Microsoft Html Help Compiler (http://msdn.microsoft.com/en-us/library/ms669985) was not found")
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Docs)

##################################################
## Install
##################################################

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Docs/FileFormats
	DESTINATION ${PL_INSTALL_DOCS}		COMPONENT Docs		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

add_custom_command(TARGET Docs-install
 	COMMAND ${CMAKE_COMMAND} -P cmake_install.cmake
)
