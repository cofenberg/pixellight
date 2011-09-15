#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


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
#   Requires the following tools to be found automatically
#   - "android" (part of the Android SDK)
#   - "ant" (type e.g. "sudo apt-get install ant" on your Linux system to install Ant)
#   - "jarsigner" (part of the JDK)
#   - "zipalign" (part of the Android SDK)
if(ANDROID)
	# Follow the package naming conventions (http://en.wikipedia.org/wiki/Java_package#Package_naming_conventions)
	set(CMAKETOOLS_CURRENT_TARGET_TOP_LEVEL_DOMAIN	"org")							# Top level domain name of the organization 
	set(CMAKETOOLS_CURRENT_TARGET_DOMAIN			"pixellight")					# Organization's domain
	set(CMAKETOOLS_CURRENT_TARGET_SUBDOMAIN			"frontend")						# Any subdomains

	# [TODO] Make those to general CMake options?
	set(CMAKETOOLS_CURRENT_TARGET_SIGNER_KEYSTORE	"~/my-release-key.keystore")	# Keystore for signing the apk file ("~" means home directory)
	set(CMAKETOOLS_CURRENT_TARGET_SIGNER_ALIAS		"myalias")						# Alias for signing the apk file

	# Construct the current package name
	set(CMAKETOOLS_CURRENT_TARGET_PACKAGE "${CMAKETOOLS_CURRENT_TARGET_TOP_LEVEL_DOMAIN}.${CMAKETOOLS_CURRENT_TARGET_DOMAIN}.${CMAKETOOLS_CURRENT_TARGET_SUBDOMAIN}")

	# Create "AndroidManifest.xml"
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/AndroidManifest.xml.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/AndroidManifest.xml")

	# Create "res/values/strings.xml"
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/res/values/strings.xml.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/res/values/strings.xml")

	# Create Java file
	# [TODO] Do also automatically add required libraries to load in (currently fixed build in within the Java file)
	configure_file("${CMAKE_SOURCE_DIR}/Plugins/PLFrontendOS/AndroidApk/src/org/pixellight/frontend/LoadLibraries.java.in" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/src/${CMAKETOOLS_CURRENT_TARGET_TOP_LEVEL_DOMAIN}/${CMAKETOOLS_CURRENT_TARGET_DOMAIN}/${CMAKETOOLS_CURRENT_TARGET_SUBDOMAIN}/LoadLibraries.java")

	# Create the directory for the libraries
	file(MAKE_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/libs/${ARM_TARGET}")

	# Copy libraries
	# [TODO] Do this in the install step when all files are there?
	copy_files("${PL_RUNTIME_BIN_DIR}/*.*" "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk/libs/${ARM_TARGET}")

	# Create "build.xml", "default.properties", "local.properties" and "proguard.cfg" files
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND android update project -t android-${ANDROID_API_LEVEL} --name ${CMAKETOOLS_CURRENT_TARGET} --path "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
	)

	# Build the apk file
	if(CMAKE_BUILD_TYPE MATCHES Debug)
		##################################################
		## Debug
		##################################################
		# Let Ant create the unsigned apk file
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ant debug
			WORKING_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
		)
	else()
		##################################################
		## Release
		##################################################
		# Let Ant create the unsigned apk file
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ant release
			WORKING_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
		)

		# Sign the apk file
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND jarsigner -verbose -keystore ${CMAKETOOLS_CURRENT_TARGET_SIGNER_KEYSTORE} bin/${CMAKETOOLS_CURRENT_TARGET}-unsigned.apk ${CMAKETOOLS_CURRENT_TARGET_SIGNER_ALIAS}
			WORKING_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
		)

		# Align the apk file
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND zipalign -v -f 4 bin/${CMAKETOOLS_CURRENT_TARGET}-unsigned.apk bin/${CMAKETOOLS_CURRENT_TARGET}.apk
			WORKING_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
		)
	endif()

	# Uninstall previous version from the device/emulator (else we may get e.g. signature conflicts)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
 		COMMAND adb uninstall ${CMAKETOOLS_CURRENT_TARGET_PACKAGE}
	)

	# Install current version on the device/emulator
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
 		COMMAND adb install -r bin/${CMAKETOOLS_CURRENT_TARGET}.apk
		WORKING_DIRECTORY "${CMAKETOOLS_CURRENT_OUTPUT_DIR}/AndroidApk"
	)
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
