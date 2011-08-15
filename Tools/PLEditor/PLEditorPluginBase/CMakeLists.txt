##################################################
## Project
##################################################
define_project(PLEditorPluginBase NOSUFFIX)

##################################################
## Include directories
##################################################
add_include_directories(
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLInput/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Base/PLEngine/include
	${CMAKE_SOURCE_DIR}/Plugins/PLFrontendQt/include
	${CMAKE_SOURCE_DIR}/Tools/PLEditor
	${CMAKE_SOURCE_DIR}/Tools/PLEditor/PLEditorPluginBase
	${QT_INCLUDE_DIRS}
)

##################################################
## Special Qt stuff (see http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake for more information)
##################################################
# Include files with Qt relevant information
SET(INC_FILES
	IPluginDockWidget/Inspector.h
	IPluginDockWidget/Project.h
	PluginFactory.h
)
SET(UI_FILES
)

# Run moc
QT4_WRAP_CPP(MOC_SRCS ${INC_FILES})

# Run ui
QT4_WRAP_UI(UI_SRCS ${UI_FILES})

##################################################
## Source files
##################################################
add_sources(
	PluginFactory.cpp
	IPluginDockWidget/Inspector.cpp
	IPluginDockWidget/Project.cpp
	${MOC_SRCS}
	${UI_SRCS}
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
	PLInput
	PLRenderer
	PLMesh
	PLScene
	PLEngine
	PLFrontendQt
	${QT_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLEDITORPLUGINBASE_LIBRARY
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

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} External-Qt PLCore PLMath PLGraphics PLInput PLRenderer PLMesh PLScene PLEngine PLFrontendQt)
add_dependencies(Samples ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Tools/PLEditor"
)

##################################################
## Install
##################################################

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	DESTINATION ${PL_INSTALL_ROOT}/Tools/PLEditor	COMPONENT SDK
)
