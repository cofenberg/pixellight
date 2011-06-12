##################################################
## Project
##################################################
define_project(PLCompositing)

##################################################
## Source files
##################################################
add_sources(
	src/PLCompositing.cpp
	src/FullscreenQuad.cpp
	src/SRPBegin.cpp
	src/SRPEnd.cpp
	src/SRPBackground.cpp
	src/SRPBackgroundBitmap.cpp
	src/SRPBackgroundColorGradient.cpp
	src/SRPBackgroundSky.cpp
	src/SRPDiffuseOnly.cpp
	src/SRPDirectionalLighting.cpp
	src/SRPLightEffects.cpp
	src/SRPPostProcessing.cpp
	src/SRPFunctions.cpp
	src/SRPFunctionsPre.cpp
	src/SRPFunctionsSolid.cpp
	src/SRPFunctionsTransparent.cpp
	src/SRPFunctionsPost.cpp
	src/SRPDebug.cpp
	src/SRPDebugFunctions.cpp
	src/SRPDebugWireframes.cpp
	src/SRPDebugHierarchies.cpp
	src/SRPDebugSceneNodeIcons.cpp
	src/SRPDebugSceneNodeNames.cpp
	src/SRPDebugContainerScissorRectangles.cpp
	src/FixedFunctions/SRPDebugWireframesFixedFunctions.cpp
	src/FixedFunctions/SRPDiffuseOnlyFixedFunctions.cpp
	src/FixedFunctions/SRPDirectionalLightingFixedFunctions.cpp
	src/FixedFunctions/SRPEmissiveFixedFunctions.cpp
	src/FixedFunctions/SRPLightEffectsFixedFunctions.cpp
	src/Shaders/General/SRPDiffuseOnlyShaders.cpp
	src/Shaders/General/SRPDirectionalLightingShaders.cpp
	src/Shaders/General/SRPDirectionalLightingShadersMaterial.cpp
	src/Shaders/General/SRPLighting.cpp
	src/Shaders/General/SRPLightingMaterial.cpp
	src/Shaders/General/SRPVolumetricFog.cpp
	src/Shaders/General/SRPDebugWireframesShaders.cpp
	src/Shaders/Deferred/SRPDeferred.cpp
	src/Shaders/Deferred/SRPDeferredGBuffer.cpp
	src/Shaders/Deferred/SRPDeferredGBufferMaterial.cpp
	src/Shaders/Deferred/SRPDeferredSSAO.cpp
	src/Shaders/Deferred/SRPDeferredHBAO.cpp
	src/Shaders/Deferred/SRPDeferredHDAO.cpp
	src/Shaders/Deferred/SRPDeferredSPAAO.cpp
	src/Shaders/Deferred/SRPDeferredAmbient.cpp
	src/Shaders/Deferred/SRPDeferredGlow.cpp
	src/Shaders/Deferred/SRPDeferredDOF.cpp
	src/Shaders/Deferred/SRPDeferredLighting.cpp
	src/Shaders/Deferred/SRPDeferredEdgeAA.cpp
	src/Shaders/Deferred/SRPDeferredDepthFog.cpp
	src/Shaders/Deferred/SRPDeferredGodRays.cpp
	src/Shaders/Deferred/SRPDeferredGBufferDebug.cpp
	src/Shaders/Deferred/SRPDeferredVolumetricFog.cpp
	src/Shaders/HDR/SRPEndHDR.cpp
	src/Shaders/HDR/HDRBloom.cpp
	src/Shaders/HDR/HDRLightAdaptation.cpp
	src/Shaders/HDR/HDRAverageLuminance.cpp
	src/Shaders/ShadowMapping/SRPShadowMapping.cpp
	src/Shaders/ShadowMapping/ShadowMapping.cpp
	src/Shaders/ShadowMapping/ShadowMappingUSM.cpp
	src/Shaders/ShadowMapping/ShadowMappingPSM.cpp
	src/Shaders/ShadowMapping/ShadowMappingLiSPSM.cpp
	src/Shaders/PostProcessing/PostProcess.cpp
	src/Shaders/PostProcessing/PostProcessor.cpp
	src/Shaders/PostProcessing/PostProcessHandler.cpp
	src/Shaders/PostProcessing/PostProcessManager.cpp
	src/Shaders/PostProcessing/PostProcessLoader.cpp
	src/Shaders/PostProcessing/PostProcessLoaderPL.cpp
	src/SceneNodeModifiers/SNMPostProcess.cpp
	src/SceneNodeModifiers/SNMPostProcessDepthOfField.cpp
	src/SceneNodeModifiers/SNMPostProcessGlow.cpp
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLScene)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral PLGraphics PLCore PLMath PLGui PLInput PLRenderer PLMesh PLScene)
add_dependencies(Plugins                     	${CMAKETOOLS_CURRENT_TARGET})

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
	DESTINATION ${PL_INSTALL_INCLUDE} 							COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLScene/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene			COMPONENT Runtime
)
