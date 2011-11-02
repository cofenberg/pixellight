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
project(Tools)

##################################################
## Target
##################################################
add_custom_target(Tools)

##################################################
## Prerequisites
##################################################

# Create "Tools"-directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools)
set(PL_TOOLS_BIN_DIR "${PL_BIN_DIR}/Tools/${CMAKETOOLS_TARGET_ARCHBITSIZE}")
file(MAKE_DIRECTORY ${PL_TOOLS_BIN_DIR})

##################################################
## Projects
##################################################
if(PL_NATIVE_PLPROJECT)
	add_subdirectory(PLProject)
endif()
if(PL_TOOL_PLUPGRADE)
	add_subdirectory(PLUpgrade)
endif()
if(PL_TOOL_PLINSTALL)
	add_subdirectory(PLInstall)
endif()
add_subdirectory(PLViewer)
if(PL_EXPORTER_3DSMAX_2008)
	add_subdirectory(PL3dsMaxSceneExport_2008)
endif()
if(PL_EXPORTER_3DSMAX_2009)
	add_subdirectory(PL3dsMaxSceneExport_2009)
endif()
if(PL_EXPORTER_3DSMAX_2010)
	add_subdirectory(PL3dsMaxSceneExport_2010)
endif()
if(PL_EXPORTER_3DSMAX_2011)
	add_subdirectory(PL3dsMaxSceneExport_2011)
endif()
if(PL_EXPORTER_3DSMAX_2012)
	add_subdirectory(PL3dsMaxSceneExport_2012)
endif()
if(PL_PLUGIN_FRONTEND_QT AND PL_EDITOR)
	add_subdirectory(PLEditor)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tools)

##################################################
## Install
##################################################

install(FILES	${CMAKE_SOURCE_DIR}/Tools/FindPixelLight.cmake
	DESTINATION ${PL_INSTALL_ROOT}/Tools		COMPONENT SDK
)

# "WhereIsTheLog.txt"-file
install(FILES ${CMAKE_SOURCE_DIR}/Bin/Tools/${CMAKETOOLS_TARGET_ARCHBITSIZE}/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_TOOLS_BIN}	COMPONENT SDK
)
