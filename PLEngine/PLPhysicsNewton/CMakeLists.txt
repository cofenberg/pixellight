##################################################
## Project
##################################################
define_project(PLPhysicsNewton)

##################################################
## Source files
##################################################
add_sources(
	src/SensorRaycast.cpp
	src/SensorAABoundingBox.cpp
	src/JointHinge.cpp
	src/BodySphere.cpp
	src/BodyCone.cpp
	src/BodyChamferCylinder.cpp
	src/BodyEllipsoid.cpp
	src/BodyConvexHull.cpp
	src/JointImpl.cpp
	src/JointCorkscrew.cpp
	src/BodyBox.cpp
	src/PLPhysicsNewton.cpp
	src/BodyMesh.cpp
	src/BodyCapsule.cpp
	src/JointUpVector.cpp
	src/JointUniversal.cpp
	src/JointBall.cpp
	src/BodyImpl.cpp
	src/WorldThread.cpp
	src/BodyTerrain.cpp
	src/World.cpp
	src/JointSlider.cpp
	src/BodyCylinder.cpp
	src/WorldUpdate.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLScene/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLPhysics/include
	${NEWTON_INCLUDE_DIRS}
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
	PLRenderer
	PLMesh
	PLScene
	PLPhysics
	${NEWTON_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLPHYSICSNEWTON_EXPORTS
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
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Newton PLGeneral PLCore PLMath PLGraphics PLRenderer PLMesh PLScene PLPhysics)
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLPhysics/newton.dll   "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLPhysics/newton64.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/"
		)
	elseif(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/Newton/lib/libNewton.so   "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/"
		)
	endif()
#endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics		COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics		COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE}								COMPONENT SDK		PATTERN ".svn" EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics				COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/newton.dll
			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics		COMPONENT Runtime
		)
	elseif(LINUX)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/libNewton.so
			DESTINATION ${PL_INSTALL_SHARED}						COMPONENT Runtime
		)
	endif()
#endif()
