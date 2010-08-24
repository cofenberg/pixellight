##################################################
## Project
##################################################
define_project(PLCompositing)

##################################################
## Source files
##################################################
add_sources(
	src/PLCompositing.cpp
	src/General/SRPDiffuseOnly.cpp
	src/General/SRPDirectionalLighting.cpp
	src/General/SRPLighting.cpp
	src/General/SRPVolumetricFog.cpp
	src/Deferred/SRPDeferred.cpp
	src/Deferred/SRPDeferredGBuffer.cpp
	src/Deferred/SRPDeferredSSAO.cpp
	src/Deferred/SRPDeferredHBAO.cpp
	src/Deferred/SRPDeferredHDAO.cpp
	src/Deferred/SRPDeferredAmbient.cpp
	src/Deferred/SRPDeferredGlow.cpp
	src/Deferred/SRPDeferredDOF.cpp
	src/Deferred/SRPDeferredLighting.cpp
	src/Deferred/SRPDeferredEdgeAA.cpp
	src/Deferred/SRPDeferredDepthFog.cpp
	src/Deferred/SRPDeferredGodRays.cpp
	src/Deferred/SRPDeferredGBufferDebug.cpp
	src/HDR/SRPEndHDR.cpp
	src/HDR/HDRBloom.cpp
	src/HDR/HDRLightAdaptation.cpp
	src/HDR/HDRAverageLuminance.cpp
	src/FixedFunctions/SRPDebugContainerScissorRectanglesFixedFunctions.cpp
	src/FixedFunctions/SRPDebugHierarchiesFixedFunctions.cpp
	src/FixedFunctions/SRPDebugWireframesFixedFunctions.cpp
	src/FixedFunctions/SRPDiffuseOnlyFixedFunctions.cpp
	src/FixedFunctions/SRPDirectionalLightingFixedFunctions.cpp
	src/FixedFunctions/SRPEmissiveFixedFunctions.cpp
	src/FixedFunctions/SRPLightEffectsFixedFunctions.cpp
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
	${CMAKE_SOURCE_DIR}/PLGui/PLGui/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLInput/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLScene/include
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
	PLCOMPOSITING_EXPORTS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLScene)

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
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLScene"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLScene"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLScene"
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
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}						COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 							COMPONENT SDK		PATTERN ".svn" EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLScene/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene			COMPONENT Runtime
)
