##################################################
## Project
##################################################
define_project(62Physics NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/Application.cpp
	src/Main.cpp
)

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
	${CMAKE_SOURCE_DIR}/Base/PLPhysics/include
	${CMAKE_SOURCE_DIR}/Base/PLEngine/include
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLInput PLRenderer PLMesh PLScene PLPhysics PLEngine)
add_dependencies(Samples						${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/Samples/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
)

##################################################
## Install
##################################################

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT SDK
)

# Source files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	DESTINATION ${PL_INSTALL_SAMPLES} 				COMPONENT SDK
	PATTERN "build" EXCLUDE
	PATTERN "enc_temp_folder" EXCLUDE
	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
	PATTERN "CMakeLists.txt" EXCLUDE
	PATTERN "62PhysicsInternal.sln" EXCLUDE
	PATTERN "62PhysicsInternal.vcxproj" EXCLUDE
	PATTERN "62PhysicsInternal.vcfiltersproj" EXCLUDE
)
