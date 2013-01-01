#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
define_project(PLInput)

##################################################
## Source files
##################################################
add_sources(
	src/PLInput.cpp
	src/Input/InputManager.cpp
	src/Input/Controller.cpp
	src/Input/Devices/Device.cpp
	src/Input/Devices/Mouse.cpp
	src/Input/Devices/SplitTouchPad.cpp
	src/Input/Devices/Keyboard.cpp
	src/Input/Devices/Joystick.cpp
	src/Input/Devices/SpaceMouse.cpp
	src/Input/Devices/WiiMote.cpp
	src/Input/Devices/SensorManager.cpp
	src/Input/Controls/Control.cpp
	src/Input/Controls/Button.cpp
	src/Input/Controls/Axis.cpp
	src/Input/Controls/Effect.cpp
	src/Input/Controls/LED.cpp
	src/Input/Connection/Connection.cpp
	src/Input/Virtual/VirtualController.cpp
	src/Input/Virtual/VirtualStandardController.cpp
	src/Backend/DeviceImpl.cpp
	src/Backend/UpdateDevice.cpp
	src/Backend/ConnectionDevice.cpp
	src/Backend/Provider.cpp
	src/Backend/HID/HIDProvider.cpp
	src/Backend/HID/HID.cpp
	src/Backend/HID/HIDImpl.cpp
	src/Backend/HID/HIDDevice.cpp
	src/Backend/HID/HIDCapability.cpp
	src/Backend/Bluetooth/BluetoothProvider.cpp
	src/Backend/Bluetooth/Bluetooth.cpp
	src/Backend/Bluetooth/BTImpl.cpp
	src/Backend/Bluetooth/BTDevice.cpp
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_sources(
		src/Backend/Windows/LegacyJoystickProvider.cpp
		src/Backend/Windows/LegacyJoystickDevice.cpp
		src/Backend/Windows/RawInputProvider.cpp
		src/Backend/Windows/RawInputDevice.cpp
		src/Backend/Windows/RawInput.cpp
		src/Backend/HID/HIDWindows.cpp
		src/Backend/HID/HIDDeviceWindows.cpp
	)
elseif(ANDROID)
	##################################################
	## Android
	##################################################
	add_sources(
		src/Backend/Android/AndroidProvider.cpp
		src/Backend/Android/AndroidKeyboardDevice.cpp
		src/Backend/Android/AndroidMouseDevice.cpp
		src/Backend/Android/AndroidSplitTouchPadDevice.cpp
		src/Backend/Android/AndroidSensorManagerDevice.cpp
		src/Backend/HID/HIDLinux.cpp
	)
elseif(APPLE)
	##################################################
	## Apple
	##################################################
	add_sources(
		src/Backend/MacOSX/MacOSXProvider.cpp
		src/Backend/MacOSX/MacOSXKeyboardDevice.cpp
		src/Backend/MacOSX/MacOSXMouseDevice.cpp
		src/Backend/HID/HIDLinux.cpp
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_sources(
		src/Backend/Linux/LinuxProvider.cpp
		src/Backend/Linux/LinuxEventDevice.cpp
		src/Backend/Linux/LinuxKeyboardDevice.cpp
		src/Backend/Linux/LinuxMouseDevice.cpp
		src/Backend/Bluetooth/BTLinux.cpp
		src/Backend/Bluetooth/BTDeviceLinux.cpp
		src/Backend/HID/HIDLinux.cpp
		src/Backend/HID/HIDDeviceLinux.cpp
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
)
if(ANDROID)
	##################################################
	## Android
	##################################################
	# For the "android_native_app_glue.h"-header include
	add_include_directories(
		${ANDROID_NDK}/sources/android/native_app_glue
	)
elseif(APPLE)
	# [TODO] Apple input implementation
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_include_directories(
		/usr/include/dbus-1.0
		/usr/lib/dbus-1.0/include
		# [TODO] check the dbus include dirs. This are the dirs 'pkg-config --cflags --libs dbus-1' returns on Ubuntu 11.10
		# Added this for Ubuntu includes and hopefully it will be the right location for most of ubuntu installations.
		/usr/include/dbus-1.0 
		/usr/lib/i386-linux-gnu/dbus-1.0/include
		# Ubuntu 11.10 64bit dbus include
		/usr/lib/x86_64-linux-gnu/dbus-1.0/include
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
	PLMath
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_WINMM_LIB}
		${WIN32_SETUPAPI_LIB}
	)
elseif(ANDROID)
	##################################################
	## Android
	##################################################
	add_libs(
		android
	)
elseif(APPLE)
	# [TODO] Apple input implementation
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
		${LINUX_X11_LIBS}
		dbus-1
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLINPUT_EXPORTS
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

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
