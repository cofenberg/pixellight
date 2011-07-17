##################################################
## Project
##################################################
define_project(PLInstall NOSUFFIX)

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
	${CMAKE_BINARY_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	${WIN32_STANDARD_LIBS}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	${WIN32_COMPILE_DEFS}
)

##################################################
## Compiler flags
##################################################
add_compile_flags(
	${WIN32_COMPILE_FLAGS}
)

##################################################
## Linker flags
##################################################
add_linker_flags(
	${WIN32_LINKER_FLAGS}
)

##################################################
## Build
##################################################
build_executable(${CMAKETOOLS_CURRENT_TARGET} WIN32)

##################################################
## Dependencies
##################################################
add_dependencies(Tools ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/Runtime"
)
