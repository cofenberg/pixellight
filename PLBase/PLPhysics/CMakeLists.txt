##################################################
## Project
##################################################
define_project(PLPhysics)

##################################################
## Prerequisites
##################################################

# Create 'Plugins/PLScene' directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics)

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
	src/SceneNodes/PhysicsMouseInteraction.cpp
	src/SceneNodes/SNPhysicsMouseInteraction.cpp
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
	src/SceneNodeModifiers/SNMPhysicsCharacter.cpp
	src/SceneNodeModifiers/SNMPhysicsCharacterController.cpp
	src/SceneNodeModifiers/PhysicsCharacterController.cpp
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
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGui/include
	${CMAKE_SOURCE_DIR}/PLBase/PLInput/include
	${CMAKE_SOURCE_DIR}/PLBase/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLBase/PLScene/include
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_BIN_DIR}/Lib
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLGeneral
	PLCore
	PLGraphics
	PLMath
	PLGui
	PLInput
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral PLGraphics PLCore PLMath PLGui PLInput PLRenderer PLMesh PLScene)
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}		COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_SHARED}			COMPONENT Runtime
)
