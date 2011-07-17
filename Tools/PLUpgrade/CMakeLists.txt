##################################################
## Project
##################################################
define_project(PLUpgrade NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/main.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	src
	${CMAKE_SOURCE_DIR}/Base/PLGeneral/include
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
	PLGeneralStat
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_STANDARD_LIBS}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLGENERAL_STATIC
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
build_executable(${CMAKETOOLS_CURRENT_TARGET} WIN32)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} PLGeneralStat)
add_dependencies(Tools ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/Tools"
)

##################################################
## Install
##################################################

if(WIN32)
	# Executable
	install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
		RUNTIME DESTINATION "${PL_INSTALL_ROOT}/Tools"		COMPONENT SDK
	)
endif()
