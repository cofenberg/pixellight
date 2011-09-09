##################################################
## Project
##################################################
define_project(PLFrontendOS)

##################################################
## Source files
##################################################
add_sources(
	src/PLFrontendOS.cpp
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_sources(
		src/Frontend.cpp
		src/OSWindow.cpp
		PLFrontendOS.rc
		src/OSWindowWindows.cpp
	)
elseif(ANDROID)
	##################################################
	## Android
	##################################################
	add_sources(
	#	src/FrontendAndroid.cpp
		${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_sources(
		src/Frontend.cpp
		src/OSWindow.cpp
		src/OSWindowLinux.cpp
		src/XDnDFileDropHelper.cpp
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
)
if(ANDROID)
	##################################################
	## Android
	##################################################
	add_include_directories(
		# For the "android_native_app_glue.h"-header include
		"${ANDROID_NDK}/sources/android/native_app_glue"
	)
endif()

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
)
if(ANDROID)
	##################################################
	## Android
	##################################################
	add_libs(
		log
		android
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
		${LINUX_X11_LIBS}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLFRONTENDOS_EXPORTS
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)

# Create relative symbolic links?
if(LINUX AND CMAKETOOLS_DETAILED_VERSION_INFORMATION)
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

# Create/copy Android apk related files
if(ANDROID)
	# Follow the package naming conventions (http://en.wikipedia.org/wiki/Java_package#Package_naming_conventions)
	set(CMAKETOOLS_CURRENT_TARGET_TOP_LEVEL_DOMAIN	"org")			# Top level domain name of the organization 
	set(CMAKETOOLS_CURRENT_TARGET_DOMAIN			"pixellight")	# Organization's domain
	set(CMAKETOOLS_CURRENT_TARGET_SUBDOMAIN			"frontend")		# Any subdomains

	# Create "AndroidManifest.xml"
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/AndroidManifest.xml.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/AndroidManifest.xml")

	# Create "res/values/strings.xml"
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/res/values/strings.xml.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/res/values/strings.xml")

	# Create Java file
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/src/org/pixellight/frontend/LoadLibraries.java.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/src/${CMAKETOOLS_CURRENT_TARGET_TOP_LEVEL_DOMAIN}/${CMAKETOOLS_CURRENT_TARGET_DOMAIN}/${CMAKETOOLS_CURRENT_TARGET_SUBDOMAIN}/LoadLibraries.java")
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
