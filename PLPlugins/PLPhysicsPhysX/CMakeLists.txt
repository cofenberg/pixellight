##################################################
## Project
##################################################
define_project(PLPhysicsPhysX)

##################################################
## Source files
##################################################
add_sources(
	src/PLPhysicsPhysX.cpp
	src/JointBall.cpp
	src/JointHinge.cpp
	src/BodyImpl.cpp
	src/JointUniversal.cpp
	src/BodySphere.cpp
	src/JointImpl.cpp
	src/BodyBox.cpp
	src/JointSlider.cpp
	src/World.cpp
	src/BodyMesh.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLBase/PLScene/include
	${CMAKE_SOURCE_DIR}/PLBase/PLPhysics/include
	${PHYSX_INCLUDE_DIRS}
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
	PLMath
	PLRenderer
	PLMesh
	PLScene
	PLPhysics
	${PHYSX_LIBRARIES}
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLPHYSICSPHYSX_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-PhysX PLGeneral PLCore PLMath PLRenderer PLMesh PLScene PLPhysics)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

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
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLPhysics/PhysXLoader.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/"
		)
	endif()
#endif()

##################################################
## Install
##################################################

# [TODO] Not within the official SDK because it's currenly just a proof-of-concept

# Library
#install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
#	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics	COMPONENT Runtime
#	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics	COMPONENT Runtime
#	ARCHIVE DESTINATION ${PL_INSTALL_LIB}						COMPONENT SDK
#)

# Include files
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
#	DESTINATION ${PL_INSTALL_INCLUDE}	 						COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
#)

# Plugin file
#install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/${CMAKETOOLS_CURRENT_PLUGIN}
#	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics			COMPONENT Runtime
#)

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
#	if(WIN32)
#		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics/PhysXLoader.dll
#			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLPhysics	COMPONENT Runtime
#		)
#	endif()
#endif()
