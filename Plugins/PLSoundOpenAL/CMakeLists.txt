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
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLSound/include
	${OPENAL_INCLUDE_DIRS}
	${LIBOGG_INCLUDE_DIRS}
	${LIBVORBIS_INCLUDE_DIRS}
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-OpenAL External-libogg External-libvorbis PLCore PLMath PLSound)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} ${PL_LIB_DIR}
	)
endif()

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/OpenAL32.dll ${PL_RUNTIME_BIN_DIR}
			COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/wrap_oal.dll ${PL_RUNTIME_BIN_DIR}
		)
	elseif(LINUX)
		# Set COPY_SOURCE to files which should be copied (this variable is used by the "copy.cmake"-script)
		set(COPY_SOURCE ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so.1
						${CMAKETOOLS_CURRENT_EXT_DIR}/OpenAL/lib/libopenal.so.1.13.0
						${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so.0
						${CMAKETOOLS_CURRENT_EXT_DIR}/libogg/lib/libogg.so.0.7.1
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so.0
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbis.so.0.4.5
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so.3
						${CMAKETOOLS_CURRENT_EXT_DIR}/libvorbis/lib/libvorbisfile.so.3.3.4)

		# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied into (this variable is used by the "copy.cmake"-script)
		set(COPY_DEST ${PL_RUNTIME_BIN_DIR})

		# Create the "copy_to_runtime.cmake"-file in the build directory of the current target (the configure file replaces the variable references with the value of the variable)
		configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_runtime.cmake)

		# Add custom command to call the created "copy_to_runtime.cmake"-file after the target was built
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_runtime.cmake")
	endif()
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 				COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_BIN}			COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		install(FILES ${PL_RUNTIME_BIN_DIR}/OpenAL32.dll
					  ${PL_RUNTIME_BIN_DIR}/wrap_oal.dll
			DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
		)
	elseif(LINUX)
		install(FILES ${PL_RUNTIME_BIN_DIR}/libopenal.so
					  ${PL_RUNTIME_BIN_DIR}/libopenal.so.1
					  ${PL_RUNTIME_BIN_DIR}/libopenal.so.1.13.0
					  ${PL_RUNTIME_BIN_DIR}/libogg.so
					  ${PL_RUNTIME_BIN_DIR}/libogg.so.0
					  ${PL_RUNTIME_BIN_DIR}/libogg.so.0.7.1
					  ${PL_RUNTIME_BIN_DIR}/libvorbis.so
					  ${PL_RUNTIME_BIN_DIR}/libvorbis.so.0
					  ${PL_RUNTIME_BIN_DIR}/libvorbis.so.0.4.5
					  ${PL_RUNTIME_BIN_DIR}/libvorbisfile.so
					  ${PL_RUNTIME_BIN_DIR}/libvorbisfile.so.3
					  ${PL_RUNTIME_BIN_DIR}/libvorbisfile.so.3.3.4
			DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
		)
	endif()
endif()
