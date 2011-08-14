##################################################
## Project
##################################################
define_project(PLEngine)

##################################################
## Source files
##################################################
add_sources(
	src/Application/EngineApplication.cpp
	src/Application/ScriptApplication.cpp
	src/Application/Config.cpp
	src/Picking/Picking.cpp
	src/Picking/PickingResult.cpp
	# src/Picking/MousePicking.cpp # [TODO] Frontend update: PLEngine is no longer allowed to directly access a GUI system
	src/Controller/PhysicsMouseInteraction.cpp
	src/Controller/SNPhysicsMouseInteraction.cpp
	src/Controller/SNMPhysicsCharacter.cpp
	src/Controller/SNMPhysicsCharacterController.cpp
	src/Controller/PhysicsCharacterController.cpp
	src/Controller/SNMLookController.cpp
	src/Controller/LookController.cpp
	src/Controller/SNMMoveController.cpp
	src/Controller/MoveController.cpp
	src/Controller/SNMOrbitingController.cpp
	src/Controller/OrbitingController.cpp
	src/Controller/SNMCameraZoomController.cpp
	src/Controller/CameraZoomController.cpp
	src/Tools/Screenshot.cpp
	src/Tools/SceneRendererTool.cpp
    src/Tools/Camcorder.cpp
    src/Tools/SNMPositionKeyframeRecord.cpp
    src/Tools/SNMRotationKeyframeRecord.cpp
	src/Compositing/SNEngineInformation.cpp
	src/Compositing/LoadScreen/SNLoadScreenBase.cpp
	src/Compositing/LoadScreen/SNLoadScreenPL.cpp
	src/Compositing/LoadScreen/SNLoadScreen.cpp
	src/Compositing/Console/SNConsoleBase.cpp
	src/Compositing/Console/SNConsole.cpp
	src/Compositing/Console/ConsoleCommand.cpp
	src/Compositing/Console/ConsoleDefaultCommands.cpp
	src/PLEngine.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLInput/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Base/PLPhysics/include
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_BIN_DIR}/Lib/${CMAKETOOLS_TARGET_ARCHBITSIZE}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCore
	PLMath
	PLGraphics
	PLInput
	PLRenderer
	PLMesh
	PLScene
	PLPhysics
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_ADVAPI32_LIB}
		${WIN32_WINMM_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLENGINE_EXPORTS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLInput PLRenderer PLMesh PLScene PLPhysics)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
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
install(FILES ${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_SHARED}			COMPONENT Runtime
)
