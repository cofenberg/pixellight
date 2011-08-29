##################################################
## Linux/GCC platform definitions
##
## This file contains compiler and linker settings which are specific to the GCC compiler suit under linux
##################################################


##################################################
## Version checks
##################################################
# Do only this check when using the Makefiles cmake generator
IF(CMAKE_GENERATOR MATCHES "Makefiles")
	MESSAGE(STATUS "Check for clang compiler version")
	SET(CMAKE_TEST_COMPILER ${CMAKE_C_COMPILER})
	IF (NOT CMAKE_C_COMPILER)
		SET(CMAKE_TEST_COMPILER ${CMAKE_CXX_COMPILER})
	ENDIF(NOT CMAKE_C_COMPILER)

	EXEC_PROGRAM(${CMAKE_TEST_COMPILER}
		ARGS --version
		OUTPUT_VARIABLE CMAKE_COMPILER_OUTPUT
		RETURN_VALUE CMAKE_COMPILER_RETURN
	)
	IF(NOT CMAKE_COMPILER_RETURN)
		FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
			"Determining the version of compiler passed with the following output:\n"
			"${CMAKE_COMPILER_OUTPUT}\n\n")
		STRING(REGEX REPLACE "\n" " " compilerVersion "${CMAKE_COMPILER_OUTPUT}")
		MESSAGE(STATUS "Check for clang compiler version - ${compilerVersion}")
		SET(Cang3)
		string(REGEX REPLACE "^.*[ ]([0-9]+)\\.[0-9].*$" "\\1" CLANG_MAJOR "${compilerVersion}")
		string(REGEX REPLACE "^.*[ ][0-9]+\\.([0-9]).*$" "\\1" CLANG_MINOR "${compilerVersion}")
		SET(Clang${CLANG_MAJOR} 1)
		SET(Clang_VERSION "${CLANG_MAJOR}.${CLANG_MINOR}")
	ELSE(NOT CMAKE_COMPILER_RETURN)
		MESSAGE(STATUS "Check for Clang compiler version - failed")
		FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
			"Determining the version of compiler failed with the following output:\n"
			"${CMAKE_COMPILER_OUTPUT}\n\n")
	ENDIF(NOT CMAKE_COMPILER_RETURN)

	SET(MIN_CLANG_VERSION "3.0")
	IF(Clang_VERSION VERSION_LESS MIN_CLANG_VERSION)
		Message(FATAL_ERROR "Clang version \"${Clang_VERSION}\" not supported at least Clang version ${MIN_CLANG_VERSION} is needed")
	endif()
ENDIF(CMAKE_GENERATOR MATCHES "Makefiles")


##################################################
## Compiler flags
##################################################

set(LINUX_COMPILE_FLAGS
	${LINUX_COMPILE_FLAGS}
	-msse3								# Use SSE3 instruction set / code might not run on CPUs with no sse3 instruction
)
