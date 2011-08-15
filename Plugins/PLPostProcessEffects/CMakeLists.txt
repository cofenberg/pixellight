##################################################
## Project
##################################################
define_project(PLPostProcessEffects)

##################################################
## Source files
##################################################
add_sources(
	src/PLPostProcessEffects.cpp
	src/SNMPostProcessASCII.cpp
	src/SNMPostProcessBlackAndWhite.cpp
	src/SNMPostProcessBleach.cpp
	src/SNMPostProcessBloom.cpp
	src/SNMPostProcessBloomToneMap.cpp
	src/SNMPostProcessBlur.cpp
	src/SNMPostProcessBrighten.cpp
	src/SNMPostProcessBrightPass.cpp
	src/SNMPostProcessChalk.cpp
	src/SNMPostProcessClipper.cpp
	src/SNMPostProcessColorFilter.cpp
	src/SNMPostProcessCombineMultiplicate.cpp
	src/SNMPostProcessCrazyBars.cpp
	src/SNMPostProcessCrazyColors.cpp
	src/SNMPostProcessDiagonalBlur.cpp
	src/SNMPostProcessEdgeDetect.cpp
	src/SNMPostProcessEmbossed.cpp
	src/SNMPostProcessInverse.cpp
	src/SNMPostProcessLayer.cpp
	src/SNMPostProcessMonochrome.cpp
	src/SNMPostProcessOldFilm.cpp
	src/SNMPostProcessPixel.cpp
	src/SNMPostProcessPosterize.cpp
	src/SNMPostProcessPull.cpp
	src/SNMPostProcessRadialBlur.cpp
	src/SNMPostProcessSepia.cpp
	src/SNMPostProcessSepia2.cpp
	src/SNMPostProcessSquisher.cpp
	src/SNMPostProcessThermal.cpp
	src/SNMPostProcessTiles.cpp
	src/SNMPostProcessToneMap.cpp
	src/SNMPostProcessWaves.cpp
	src/SNMPostProcessSharpen.cpp
	src/SNMPostProcessLaplaceSharpen.cpp
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
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Plugins/PLCompositing/include
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
	PLScene
	PLCompositing
)

##################################################
## Preprocessor definitions
##################################################
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLScene)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)
if(LINUX)
	# Create relative symbolic links
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
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene		COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene		COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
)

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene				COMPONENT Runtime
)
