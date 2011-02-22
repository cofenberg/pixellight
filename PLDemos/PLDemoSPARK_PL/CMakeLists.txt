##################################################
## Project
##################################################
define_project(PLDemoSPARK_PL NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/Main.cpp
	src/Application.cpp
	src/SNBasicDemo.cpp
	src/SNFireDemo.cpp
	src/SNGalaxyDemo.cpp
	src/SNGravitationDemo.cpp
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
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLScene/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLEngine/include
	${CMAKE_SOURCE_DIR}/PLPlugins/SPARK_PL/include
	${CMAKE_SOURCE_DIR}/PLPlugins/SPARK_PL/include/SPARK_PL
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
	PLMath
	PLGui
	PLRenderer
	PLMesh
	PLScene
	PLEngine
	SPARK_PL
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} PLGeneral PLCore PLMath PLGui PLRenderer PLMesh PLScene PLEngine SPARK_PL)
add_dependencies(Demos ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/PLDemos"
)

##################################################
## Install
##################################################

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_DEMOS_BIN}	COMPONENT SDK
)

# Source files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	DESTINATION ${PL_INSTALL_DEMOS} 			COMPONENT SDK
	PATTERN "build" EXCLUDE
	PATTERN "enc_temp_folder" EXCLUDE
	PATTERN ".svn" EXCLUDE
	PATTERN "*.ncb" EXCLUDE
	PATTERN "*.suo" EXCLUDE
	PATTERN "*.user" EXCLUDE
	PATTERN "CMakeLists.txt" EXCLUDE
	PATTERN "PLDemoSPARK_PLInternal.sln" EXCLUDE
	PATTERN "PLDemoSPARK_PLInternal.vcxproj" EXCLUDE
	PATTERN "PLDemoSPARK_PLInternal.vcxproj.filters" EXCLUDE
)
