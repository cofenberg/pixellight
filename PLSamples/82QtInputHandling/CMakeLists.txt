##################################################
## Project
##################################################
define_project(82QtInputHandling NOSUFFIX)

##################################################
## Special Qt stuff (see http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake for more information)
##################################################
# Find Qt4 libraries and set all required variables
FIND_PACKAGE(Qt4 REQUIRED)

if(CMAKETOOLS_USE_SYSTEM_LIBS)
	# Only use QT_USE_FILE when using the system version of Qt4 otherwise the var QT_LIBRARIES (set by the Qt external project) gets overwritten
	# when the cmake module FindQt4.cmake finds qt4 libs in the system.
	# Add Qt CMake macros and variables
	# (QT_USE_FILE is a variable defined by FIND_PACKAGE(Qt4) that contains a path to CMake script)
	INCLUDE(${QT_USE_FILE})
endif()

# Include files with Qt relevant information
SET(INC_FILES
	src/MyRenderWindow.h
)

# Run moc
QT4_WRAP_CPP(MOC_SRCS ${INC_FILES})

##################################################
## Source files
##################################################
add_sources(
	src/Main.cpp
	src/MySceneContext.cpp
	src/MyRenderWindow.cpp
	${MOC_SRCS}
)

##################################################
## Include directories
##################################################
add_include_directories(
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLGui/PLGui/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLInput/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLScene/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLEngine/include
	${CMAKE_SOURCE_DIR}/PLPlugins/PLQt/include
)

if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	add_include_directories(
		${QT_INCLUDE_DIRS}
	)
endif()

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
	PLMath
	PLGraphics
	PLGui
	PLInput
	PLRenderer
	PLMesh
	PLScene
	PLEngine
	PLQt
	${QT_LIBRARIES}
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} External-Qt PLGeneral PLCore PLMath PLGraphics PLGui PLInput PLRenderer PLMesh PLScene PLEngine PLQt)
add_dependencies(Samples ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/PLSamples"
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
	PATTERN "82QtInputHandlingInternal.sln" EXCLUDE
	PATTERN "82QtInputHandlingInternal.vcxproj" EXCLUDE
	PATTERN "82QtInputHandlingInternal.vcxproj.filters" EXCLUDE
)
