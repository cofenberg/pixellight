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
define_project(PLPhysics)

##################################################
## Source files
##################################################
add_sources(
	src/SceneNodes/RagdollLoaderPL.cpp
	src/SceneNodes/RagdollLoader.cpp
	src/SceneNodes/SCPhysicsWorld.cpp
	src/SceneNodes/RagdollBody.cpp
	src/SceneNodes/SNRagdoll.cpp
	src/SceneNodes/RagdollJoint.cpp
	src/SceneNodeModifiers/SNMPhysics.cpp
	src/SceneNodeModifiers/SNMPhysicsBody.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyBox.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyCapsule.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyChamferCylinder.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyCone.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyConvexHull.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyCylinder.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyEllipsoid.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyMesh.cpp
	src/SceneNodeModifiers/SNMPhysicsBodySphere.cpp
	src/SceneNodeModifiers/SNMPhysicsBodyTerrain.cpp
	src/SceneNodeModifiers/SNMPhysicsCorrectDistance.cpp
	src/SceneNodeModifiers/SNMPhysicsForce.cpp
	src/SceneNodeModifiers/SNMPhysicsJoint.cpp
	src/SceneNodeModifiers/SNMPhysicsJointBall.cpp
	src/SceneNodeModifiers/SNMPhysicsJointCorkscrew.cpp
	src/SceneNodeModifiers/SNMPhysicsJointHinge.cpp
	src/SceneNodeModifiers/SNMPhysicsJointSlider.cpp
	src/SceneNodeModifiers/SNMPhysicsJointUniversal.cpp
	src/SceneNodeModifiers/SNMPhysicsJointUpVector.cpp
	src/SceneNodeModifiers/SNMPhysicsTorque.cpp
	src/SceneNodeModifiers/SNMPhysicsUpdateVelocity.cpp
	src/Sensor.cpp
	src/SensorRaycast.cpp
	src/SensorAABoundingBox.cpp
	src/JointHinge.cpp
	src/BodyChamferCylinder.cpp
	src/BodyEllipsoid.cpp
	src/BodyCone.cpp
	src/BodySphere.cpp
	src/BodyConvexHull.cpp
	src/JointCorkscrew.cpp
	src/BodyBox.cpp
	src/BodyMesh.cpp
	src/BodyCapsule.cpp
	src/JointUpVector.cpp
	src/JointUniversal.cpp
	src/ElementHandler.cpp
	src/JointBall.cpp
	src/PLPhysics.cpp
	src/BodyTerrain.cpp
	src/Joint.cpp
	src/JointSlider.cpp
	src/BodyCylinder.cpp
	src/World.cpp
	src/Element.cpp
	src/Body.cpp
	src/ContactInformation.cpp
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
	PLPHYSICS_EXPORTS
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLMesh PLScene)
add_dependencies(Base             	         	${CMAKETOOLS_CURRENT_TARGET})

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
