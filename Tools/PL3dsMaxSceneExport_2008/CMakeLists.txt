##################################################
## Project
##################################################
define_project(PL3dsMaxSceneExport_2008)

##################################################
## Prerequisites
##################################################

# Create 3dsMax directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools/3dsMax)

##################################################
## Source files
##################################################
add_sources(
	src/PL3dsMaxSceneExport.cpp
	src/PLLog.cpp
	src/PLScene.cpp
	src/PLSceneCamera.cpp
	src/PLSceneCell.cpp
	src/PLSceneContainer.cpp
	src/PLSceneEnumProc.cpp
	src/PLSceneExportDialogs.cpp
	src/PLSceneExportOptions.cpp
	src/PLSceneHelper.cpp
	src/PLSceneLight.cpp
	src/PLSceneMaterial.cpp
	src/PLSceneMaterialFX.cpp
	src/PLSceneMaterialColor.cpp
	src/PLSceneMaterialStandard.cpp
	src/PLSceneMaterialBakeShell.cpp
	src/PLSceneMaterialSRShaderLighting.cpp
	src/PLSceneMesh.cpp
	src/PLScenePLMesh.cpp
	src/PLSceneNode.cpp
	src/PLSceneObject.cpp
	src/PLScenePortal.cpp
	src/PLSceneAntiPortal.cpp
	src/PLSceneCellPortal.cpp
	src/PLSceneSpline.cpp
	src/PLSceneTexture.cpp
	src/PLSceneUnknown.cpp
	src/PLTextFile.cpp
	src/PLToolbar.cpp
	src/PLTools.cpp
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_sources(
		src/../PL3dsMaxSceneExport.rc
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/Base/PLCore/include/
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include/
	${MAX2008_INCLUDE_DIRS}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCoreStat
	${WIN32_ADVAPI32_LIB}
	${WIN32_SHELL32_LIB}
	${WIN32_USER32_LIB}
	${WIN32_COMCTL32_LIB}
	${WIN32_COMDLG32_LIB}
	${MAX2008_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	${WIN32_COMPILE_DEFS}
	PLCORE_STATIC
	_SECURE_SCL=0
)
remove_compile_defs(
	UNICODE										# Use unicode
	_UNICODE									# Use unicode
)

##################################################
## Compiler flags
##################################################
add_compile_flags(
	${WIN32_COMPILE_FLAGS}
	/EHsc										# Exceptions
	/GR											# Enable RTTI
)
remove_compile_flags(
	/GR-										# Disable RTTI
)

##################################################
## Linker flags
##################################################
add_linker_flags(
	${WIN32_LINKER_FLAGS}
	/NODEFAULTLIB:"libcp.lib"					# Ignore libraries
	/NODEFAULTLIB:"libci.lib"					# Ignore libraries
	/NODEFAULTLIB:"msvcirt.lib"					# Ignore libraries
	/NODEFAULTLIB:"libcmt.lib"					# Ignore libraries
	/NODEFAULTLIB:"libcmtd.lib"					# Ignore libraries
	/NODEFAULTLIB:"msvcrtd.lib"					# Ignore libraries
	/NODEFAULTLIB:"LIBC.lib"					# Ignore libraries
)

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Max2008 PLCoreStat)
add_dependencies(Tools                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Tools/3dsMax/${CMAKETOOLS_CURRENT_TARGET}.dle"
)

# FX shader
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Tools/3dsMax/PixelLight_SRShaderLighting.fx "${PL_BIN_DIR}/Tools/3dsMax"
)

##################################################
## Install
##################################################

# Library
install(FILES ${PL_BIN_DIR}/Tools/3dsMax/${CMAKETOOLS_CURRENT_PROJECT}.dle
	DESTINATION ${PL_INSTALL_ROOT}/Tools/3dsMax			COMPONENT SDK
)

# FX shader
install(FILES ${PL_BIN_DIR}/Tools/3dsMax/PixelLight_SRShaderLighting.fx
	DESTINATION ${PL_INSTALL_ROOT}/Tools/3dsMax			COMPONENT SDK
)
