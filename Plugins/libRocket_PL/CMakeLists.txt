##################################################
## Project
##################################################
define_project(libRocket_PL)

##################################################
## Source files
##################################################
add_sources(
	src/libRocket_PL.cpp
	src/libRocketAdapter.cpp
	src/RenderInterfacePL.cpp
	src/RenderInterfacePLShaders.cpp
	src/SystemInterfacePL.cpp
	src/FileInterfacePL.cpp
	src/SRPlibRocket.cpp
	src/MessageFilterRocket.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	include/libRocket_PL
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLGui/include
	${CMAKE_SOURCE_DIR}/Base/PLInput/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${LIBROCKET_INCLUDE_DIRS}
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
	PLInput
	PLRenderer
	PLMesh
	PLScene
	${LIBROCKET_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	LIBROCKET_PL_EXPORTS
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-libRocket PLCore PLMath PLGraphics PLGui PLInput PLRenderer PLMesh PLScene)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Runtime"
)
if(WIN32)
	# Copy the libRocket dlls so that the user can use everything "out of the box"
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketCore.dll "${PL_BIN_DIR}/Runtime"
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketControls.dll "${PL_BIN_DIR}/Runtime"
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketDebugger.dll "${PL_BIN_DIR}/Runtime"
	)
endif()

if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/RocketCore.dll "${PL_BIN_DIR}/Runtime/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/RocketControls.dll "${PL_BIN_DIR}/Runtime/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/RocketDebugger.dll "${PL_BIN_DIR}/Runtime/"
		)
	endif()
	if(LINUX)
		# Set COPY_SOURCE to files which should be copied. This var is used by the copy.cmake script
		set(COPY_SOURCE ${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so.1
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so.1.2.1
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so.1
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so.1.2.1
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so.1
					${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so.1.2.1)
		# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied. This var is used by the copy.cmake script
		set(COPY_DEST "${PL_BIN_DIR}/Runtime")
		
		# Create the copy_to_runtime.cmake in the build directory of the current target (configure file replaces the vars references with the value of the vars)
		configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_runtime.cmake)
		
		# add custom command to call the created copy_to_runtime.cmake after target was built
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_runtime.cmake")
	endif()
#endif()

# Copy the libRocket libraries so that the user can use everything "out of the box"
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketCore.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketControls.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketDebugger.lib "${PL_BIN_DIR}/Lib"
	)
endif()
if(LINUX)
	# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied. This var is used by the copy.cmake script
	set(COPY_DEST "${PL_BIN_DIR}/Lib")

	# Create the copy_to_lib.cmake in the build directory of the current target (configure file replaces the vars references with the value of the vars)
	configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_lib.cmake)

	# add custom command to call the created copy_to_runtime.cmake after target was built
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_lib.cmake")
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}		COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Copy the libRocket stuff into the SDK so that the user can use everything "out of the box"
install(DIRECTORY ${LIBROCKET_INCLUDE_DIRS}/Rocket
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
if(WIN32)
	install(FILES	${PL_BIN_DIR}/Runtime/RocketCore.dll
					${PL_BIN_DIR}/Runtime/RocketControls.dll
					${PL_BIN_DIR}/Runtime/RocketDebugger.dll
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)
	install(FILES	${PL_BIN_DIR}/Lib/RocketCore.lib
					${PL_BIN_DIR}/Lib/RocketControls.lib
					${PL_BIN_DIR}/Lib/RocketDebugger.lib
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)
endif()
if(LINUX)
	install(FILES	${PL_BIN_DIR}/Runtime/libRocketCore.so
					${PL_BIN_DIR}/Runtime/libRocketCore.so.1
					${PL_BIN_DIR}/Runtime/libRocketCore.so.1.2.1
					${PL_BIN_DIR}/Runtime/libRocketControls.so
					${PL_BIN_DIR}/Runtime/libRocketControls.so.1
					${PL_BIN_DIR}/Runtime/libRocketControls.so.1.2.1
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so.1
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so.1.2.1
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)
	install(FILES	${PL_BIN_DIR}/Runtime/libRocketCore.so
					${PL_BIN_DIR}/Runtime/libRocketCore.so.1
					${PL_BIN_DIR}/Runtime/libRocketCore.so.1.2.1
					${PL_BIN_DIR}/Runtime/libRocketControls.so
					${PL_BIN_DIR}/Runtime/libRocketControls.so.1
					${PL_BIN_DIR}/Runtime/libRocketControls.so.1.2.1
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so.1
					${PL_BIN_DIR}/Runtime/libRocketDebugger.so.1.2.1
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)
endif()
