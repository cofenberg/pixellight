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
#*********************************************************/


##################################################
## Project
##################################################
define_project(PLVolume)

##################################################
## Source files
##################################################
add_sources(
	src/PLVolume.cpp										# Project main file
	src/Volume.cpp											# Volume resource
	src/VolumeHandler.cpp									# Volume resource handler
	src/VolumeManager.cpp									# Volume resource manager
	src/TransferFunction.cpp								# Transfer function
	src/TransferFunctionLoader.cpp							# Abstract transfer function loader base class
	# Creator
	src/Creator/MeshCreatorCube.cpp							# Creates a color cube mesh
	src/Creator/SceneCreatorLoadableTypeVolume.cpp			# Creates a volume scene
	src/Creator/TextureCreatorPyroclasticCloud3D.cpp		# Creates a pyroclastic cloud
	# Loader
	src/Loader/VolumeLoader.cpp								# Abstract volume loader base class
	src/Loader/ImageLoaderRAW.cpp							# Image loader for volume file format "raw" -> Blank raw volume data *chunk of a certain data type*
	src/Loader/ImageLoaderDAT.cpp							# Image loader for volume file format "dat"
	src/Loader/VolumeLoaderPL.cpp							# Volume loader for volume file format "volume" of PixelLight
	src/Loader/VolumeLoaderDDS.cpp							# Volume loader for volume file format "dds"
	src/Loader/VolumeLoaderRAW.cpp							# Volume loader for volume file format "raw" -> Blank raw volume data *chunk of a certain data type*
	src/Loader/VolumeLoaderDAT.cpp							# Volume loader for volume file format "dat"
	src/Loader/TransferFunctionLoaderTABLE.cpp				# Transfer function loader for file format "table"
	# Scene
	src/Scene/SNVolume.cpp									# Volume scene node
	src/Scene/SNClip.cpp									# Abstract clip scene node
	src/Scene/SNClipPrimitive.cpp							# Abstract clip primitive scene node
	src/Scene/SNClipPrimitivePlane.cpp						# Clip primitive plane scene node
	src/Scene/SNClipPrimitiveEllipsoid.cpp					# Clip primitive ellipsoid scene node
	src/Scene/SNClipPrimitiveBox.cpp						# Clip primitive box scene node
	src/Scene/SNClipVolumeTexture.cpp						# Clip volume texture scene node
	src/Scene/SRPVolume.cpp									# Abstract volume scene renderer base class
	# Transfer function control
	src/TransferFunctionControl/ImageTools.cpp				# Image tools
	src/TransferFunctionControl/Histogram.cpp				# Histogram
	src/TransferFunctionControl/CubicSpline.cpp				# Cubic spline
	src/TransferFunctionControl/TransferFunctionControl.cpp	# Transfer function control
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Base/PLPhysics/include
	${CMAKE_SOURCE_DIR}/Base/PLEngine/include
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
	PLMath
	PLGraphics
	PLRenderer
	PLMesh
	PLScene
	PLPhysics
	PLEngine
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLVOLUME_EXPORTS
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
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLMesh PLScene PLPhysics PLEngine)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)

# Create relative symbolic links?
if(LINUX AND CMAKETOOLS_DETAILED_VERSION_INFORMATION)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} ${PL_LIB_DIR}
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 				COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_BIN}			COMPONENT Runtime
)
