##################################################
## Project
##################################################
define_project(PLSoundOpenAL)

##################################################
## Source files
##################################################
add_sources(
	src/SoundManager.cpp
	src/Source.cpp
	src/PLSoundOpenAL.cpp
	src/StreamOgg.cpp
	src/StreamWav.cpp
	src/Buffer.cpp
	src/Stream.cpp
	src/Ogg.cpp
	src/Wav.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLSound/include
	${OPENAL_INCLUDE_DIRS}
	${LIBOGG_INCLUDE_DIRS}
	${LIBVORBIS_INCLUDE_DIRS}
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
	PLSound
	${OPENAL_LIBRARIES}
	${LIBOGG_LIBRARIES}
	${LIBVORBIS_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLSOUNDOPENAL_EXPORTS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-OpenAL External-libogg External-libvorbis PLGeneral PLCore PLMath PLSound)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLSound"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLSound"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLSound"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLSound/OpenAL32.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLSound/wrap_oal.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
		)
	elseif(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so				"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so.1			"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so.1.13.0		"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so					"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so.0				"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so.0.7.1			"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so			"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so.0			"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so.0.4.5		"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so		"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so.3		"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so.3.3.4	"${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/"
		)
	endif()
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLSound		COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLSound		COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 								COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLSound				COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/OpenAL32.dll
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/wrap_oal.dll
			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLSound		COMPONENT Runtime
		)
	elseif(LINUX)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libopenal.so
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libopenal.so.1
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libopenal.so.1.13.0
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libogg.so
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libogg.so.0
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libogg.so.0.7.1
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbis.so
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbis.so.0
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbis.so.0.4.5
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbisfile.so
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbisfile.so.3
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLSound/libvorbisfile.so.3.3.4
			DESTINATION ${PL_INSTALL_SHARED}						COMPONENT Runtime
		)
	endif()
endif()
