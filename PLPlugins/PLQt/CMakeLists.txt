##################################################
## Project
##################################################
define_project(PLQt)

##################################################
## Source files
##################################################
add_sources(
	src/PLQt.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	include/PLQt
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
	${QT_INCLUDE_DIRS}
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
	PLGraphics
	PLGui
	PLInput
	PLRenderer
	PLMesh
	PLScene
	PLEngine
	${QT_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLQT_EXPORTS
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Qt PLGeneral PLCore PLMath PLGraphics PLGui PLInput PLRenderer PLMesh PLScene PLEngine)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime"
)
if(WIN32)
	# Copy the Qt dlls so that the user can use everything "out of the box"
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../bin/QtCore4.dll "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../bin/QtGui4.dll "${PL_BIN_DIR}/PLRuntime"
	)
endif()

if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
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
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/QtCore4.dll "${PL_BIN_DIR}/PLRuntime/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/QtGui4.dll "${PL_BIN_DIR}/PLRuntime/"
		)
	endif()
	if(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			# [TODO]
			# COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/libQtCore4.so "${PL_BIN_DIR}/PLRuntime"
			# COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/libQtGui4.so "${PL_BIN_DIR}/PLRuntime"
		)
	endif()
#endif()

# Copy the QT libraries so that the user can use everything "out of the box"
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/QtCore4.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/QtGui4.lib "${PL_BIN_DIR}/Lib"
	)
endif()
if(LINUX)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		# [TODO]
		# COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/libQtCore4.so "${PL_BIN_DIR}/Lib"
		# COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../lib/libQtGui4.so "${PL_BIN_DIR}/Lib"
	)
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

# Copy the QT stuff into the SDK so that the user can use everything "out of the box"
install(DIRECTORY ${QT_INCLUDE_DIRS}/Qt
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
if(WIN32)
	install(FILES	${PL_BIN_DIR}/PLRuntime/QtCore4.dll
					${PL_BIN_DIR}/PLRuntime/QtGui4.dll
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)
	install(FILES	${PL_BIN_DIR}/Lib/QtCore4.dll.lib
					${PL_BIN_DIR}/Lib/QtGui4.dll.lib
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)
endif()
if(LINUX)
					# [TODO]
	install(FILES	# ${PL_BIN_DIR}/PLRuntime/libQtCore4.so
					# ${PL_BIN_DIR}/PLRuntime/libQtGui4.so
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)
					# [TODO]
	install(FILES	# ${PL_BIN_DIR}/PLRuntime/libQtCore4.so
					# ${PL_BIN_DIR}/PLRuntime/libQtGui4.so
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)
endif()
