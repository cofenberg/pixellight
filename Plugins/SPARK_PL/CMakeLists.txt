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
define_project(SPARK_PL)

##################################################
## Source files
##################################################
add_sources(
	src/SPARK_PL.cpp
	src/Core/SPK_BufferHandler.cpp
	src/Core/SPK_DEF.cpp
	src/Core/SPK_Emitter.cpp
	src/Core/SPK_Factory.cpp
	src/Core/SPK_Group.cpp
	src/Core/SPK_Interpolator.cpp
	src/Core/SPK_Model.cpp
	src/Core/SPK_Modifier.cpp
	src/Core/SPK_Particle.cpp
	src/Core/SPK_Registerable.cpp
	src/Core/SPK_Renderer.cpp
	src/Core/SPK_System.cpp
	src/Core/SPK_Transformable.cpp
	src/Core/SPK_Vector3D.cpp
	src/Core/SPK_Zone.cpp
	src/Extensions/Emitters/SPK_NormalEmitter.cpp
	src/Extensions/Emitters/SPK_RandomEmitter.cpp
	src/Extensions/Emitters/SPK_SphericEmitter.cpp
	src/Extensions/Emitters/SPK_StraightEmitter.cpp
	src/Extensions/Modifiers/SPK_Collision.cpp
	src/Extensions/Modifiers/SPK_Destroyer.cpp
	src/Extensions/Modifiers/SPK_LinearForce.cpp
	src/Extensions/Modifiers/SPK_ModifierGroup.cpp
	src/Extensions/Modifiers/SPK_Obstacle.cpp
	src/Extensions/Modifiers/SPK_PointMass.cpp
	src/Extensions/Modifiers/SPK_Vortex.cpp
	src/Extensions/Zones/SPK_AABox.cpp
	src/Extensions/Zones/SPK_Line.cpp
	src/Extensions/Zones/SPK_Plane.cpp
	src/Extensions/Zones/SPK_Point.cpp
	src/Extensions/Zones/SPK_Ring.cpp
	src/Extensions/Zones/SPK_Sphere.cpp
	src/Extensions/Zones/SPK_Cylinder.cpp
	src/Extensions/Renderers/SPK_Oriented3DRendererInterface.cpp
	src/Extensions/Renderers/SPK_QuadRendererInterface.cpp
	src/PLSceneNodes/SNSystem.cpp
	src/PLSceneNodes/SNFire.cpp
	src/PLSceneNodes/SNBasicDemo.cpp
	src/PLSceneNodes/SNGalaxyDemo.cpp
	src/PLSceneNodes/SNGravitationDemo.cpp
	src/RenderingAPIs/PixelLight/SPK_PLBuffer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLRenderer.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	include/SPARK_PL
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
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
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	SPARK_PL_EXPORTS
	SPK_CORE_EXPORT
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
	if(ANDROID)
		add_linker_flags(
			-L${STL_LIBRARIES_PATH}	# SPARK is using stl, adding this line results in slightly bigger executables so we don't do this within "LinuxNDK.cmake"
		)
	endif()
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLMesh PLScene)
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
