##################################################
## Project
##################################################
define_project(PLViewer NOSUFFIX)

##################################################
## Prerequisites
##################################################

# Create Config directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools)
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools/PLViewer)

##################################################
## Source files
##################################################
add_sources(
	src/Application.cpp
	src/Config.cpp
	src/Main.cpp
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_sources(
		PLViewer.rc
	)
endif()


##################################################
## Include directories
##################################################
add_include_directories(
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLGui/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Base/PLEngine/include
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
	PLCore
	PLMath
	PLGraphics
	PLGui
	PLRenderer
	PLMesh
	PLScene
	PLEngine
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
build_executable(${CMAKETOOLS_CURRENT_TARGET} WIN32)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} PLCore PLMath PLGraphics PLGui PLRenderer PLMesh PLScene PLEngine)
add_dependencies(Tools                        ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/Tools/PLViewer"
)

##################################################
## Install
##################################################

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	DESTINATION ${PL_INSTALL_ROOT}/Tools/PLViewer	COMPONENT SDK
)

##################################################
## Build standalone executable
##################################################
add_compile_defs(STANDALONE)
build_executable(${CMAKETOOLS_CURRENT_TARGET}Standalone WIN32)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_PROJECT}Standalone	External-zlib External-libpcre)
add_dependencies(Base										${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Standalone executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/Tools/PLViewer"
)

##################################################
## Install
##################################################

# "WhereIsTheLog.txt"-file
install(FILES ${CMAKE_SOURCE_DIR}/Bin/Tools/PLViewer/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_ROOT}/Tools/PLViewer	COMPONENT SDK
)

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	DESTINATION ${PL_INSTALL_ROOT}/Tools/PLViewer	COMPONENT SDK
)
