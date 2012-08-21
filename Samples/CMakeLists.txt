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
project(Samples)

##################################################
## Prerequisites
##################################################

# Create "Samples"-directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Samples)
set(PL_SAMPLES_BIN_DIR "${PL_BIN_DIR}/Samples/${CMAKETOOLS_TARGET_ARCHBITSIZE}")
file(MAKE_DIRECTORY ${PL_SAMPLES_BIN_DIR})
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Samples/Data)

# Copy samples data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Samples/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/Samples/Data/*.*" "${PL_BIN_DIR}/Samples/Data")

if(LINUX AND NOT ANDROID)
	# Setup executable suffix under Linux
	# This is needed so that the helper runner script works
	set(CMAKE_EXECUTABLE_SUFFIX "-bin")
	set(CMAKETOOLS_BASEPATH_GO_UPS "/../../../")
endif()

##################################################
## Target
##################################################
add_custom_target(Samples)

##################################################
## Projects
##################################################
add_subdirectory(01Application)
add_subdirectory(02CommandLine)
add_subdirectory(03Signals)
add_subdirectory(04Dirs)
add_subdirectory(05NetworkChat)
add_subdirectory(30Input)
add_subdirectory(40ScriptHelloWorld)
add_subdirectory(41ScriptGlobalVariables)
add_subdirectory(42ScriptFunctors)
add_subdirectory(43ScriptBindings)
add_subdirectory(44ScriptOOP)
add_subdirectory(45ScriptApplication)
add_subdirectory(50RendererTriangle)
add_subdirectory(51RendererTexturing)
add_subdirectory(52RendererMesh)
add_subdirectory(54RendererRTT)
add_subdirectory(55RendererTessellation)
add_subdirectory(56RendererInstancing)
add_subdirectory(60Scene)
add_subdirectory(61Sound)
add_subdirectory(62Physics)
add_subdirectory(63PhysicsRagdoll)
add_subdirectory(64Picking)
add_subdirectory(65PostProcess)
add_subdirectory(67Game2D)
# PLGui
if(PL_PLGUI)
	add_subdirectory(20Gui)
#	add_subdirectory(21GuiWidgets) # [TODO]
	# PLFrontendPLGui
	if(PL_PLUGIN_FRONTEND_PLGUI)
		add_subdirectory(53RendererMultiView)
		add_subdirectory(66IngameGUI)
	endif()
	# PLlibRocket
	if(PL_PLUGIN_ENGINE_LIBROCKET)
		add_subdirectory(71libRocket)
	endif()
endif()
# PLFrontendQt
if(PL_PLUGIN_FRONTEND_QT)
	add_subdirectory(80QtHelloWorld)
	add_subdirectory(81QtScene)
	add_subdirectory(82QtInputHandling)
endif()
# SPARK_PL
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(70SPARK)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Samples)

##################################################
## Install
##################################################

# "WhereIsTheLog.txt"-file
install(FILES ${CMAKE_SOURCE_DIR}/Bin/Samples/${CMAKETOOLS_TARGET_ARCHBITSIZE}/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_SAMPLES}/Bin/${CMAKETOOLS_TARGET_ARCHBITSIZE}	COMPONENT SDK
)

# Data
install(DIRECTORY ${PL_BIN_DIR}/Samples/Data
	DESTINATION ${PL_INSTALL_SAMPLES_DATA}	COMPONENT SDK	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Microsoft Visual Studio Solution
if(WIN32)
	install(FILES ${CMAKE_SOURCE_DIR}/Samples/Samples.sln
		DESTINATION ${PL_INSTALL_SAMPLES}	COMPONENT SDK
	)
endif()
