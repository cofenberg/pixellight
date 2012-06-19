#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Master thesis
#*    "Scalable Realtime Volume Rendering"
#*
#*  At
#*    Fachhochschule Würzburg-Schweinfurt
#*    Fakultät Informatik, Wirtschaftsinformatik (FIW)
#*    http://www.fh-wuerzburg.de/
#*
#*  Author
#*    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
#*    Copyright (C) 2011-2012
#*********************************************************#


cmake_minimum_required(VERSION 2.8.3)


##################################################
## Define the project
##################################################
set(CURRENT_TARGET_NAME PLVolume)
project(${CURRENT_TARGET_NAME})


##################################################
## Find packages
##################################################
if(ANDROID)
	find_host_package(PixelLight)	# "find_package"-variant provided by "android.toolchain.cmake", required for PixelLight CMake variables like "PL_PLCORE_INCLUDE_DIR"
else()
	find_package(PixelLight REQUIRED)
endif()


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)	# The current source directory
include_directories(${PL_PLCORE_INCLUDE_DIR})				# PLCore headers
include_directories(${PL_PLMATH_INCLUDE_DIR})				# PLMath headers
include_directories(${PL_PLGRAPHICS_INCLUDE_DIR})			# PLGraphics headers
include_directories(${PL_PLRENDERER_INCLUDE_DIR})			# PLRenderer headers
include_directories(${PL_PLMESH_INCLUDE_DIR})				# PLMesh headers
include_directories(${PL_PLSCENE_INCLUDE_DIR})				# PLScene headers
include_directories(${PL_PLENGINE_INCLUDE_DIR})				# PLEngine headers


##################################################
## Source codes
##################################################
set(CURRENT_SRC
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
## Additional libraries
##################################################
add_libs(
	${PL_PLCORE_LIBRARY}
	${PL_PLMATH_LIBRARY}
	${PL_PLGRAPHICS_LIBRARY}
	${PL_PLRENDERER_LIBRARY}
	${PL_PLMESH_LIBRARY}
	${PL_PLSCENE_LIBRARY}
	${PL_PLENGINE_LIBRARY}
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
add_library(${CURRENT_TARGET_NAME} SHARED ${CURRENT_SRC})
target_link_libraries (${CURRENT_TARGET_NAME} ${libs})
set_project_properties(${CURRENT_TARGET_NAME})


##################################################
## Post-Build
##################################################
# Executable
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CURRENT_TARGET_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}"
)

# Plugin file
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND "${PL_ROOT}/Bin/Tools/${PL_ARCHBITSIZE}/PLProject${CMAKE_EXECUTABLE_SUFFIX}" ${CMAKE_CURRENT_SOURCE_DIR} --output-path "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}" --write-plugin
	WORKING_DIRECTORY ${dir}
)
