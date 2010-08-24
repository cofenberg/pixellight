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
	src/Input/Devices/Keyboard.cpp
	src/Input/Devices/Joystick.cpp
	src/Input/Devices/SpaceMouse.cpp
	src/Input/Devices/WiiMote.cpp
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
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_sources(
		src/Backend/Linux/LinuxProvider.cpp
		src/Backend/Linux/LinuxKeyboardDevice.cpp
		src/Backend/Linux/LinuxMouseDevice.cpp
		src/Backend/Linux/LinuxEventDevice.cpp
		src/Backend/HID/HIDLinux.cpp
		src/Backend/HID/HIDDeviceLinux.cpp
		src/Backend/Bluetooth/BTLinux.cpp
		src/Backend/Bluetooth/BTDeviceLinux.cpp
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_include_directories(
		${WINDOWSDDK_INCLUDE_DIRS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_include_directories(
		/usr/include/dbus-1.0
		/usr/lib/dbus-1.0/include
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
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_WINMM_LIB}
		${WIN32_SETUPAPI_LIB}
		${WINDOWSDDK_LIBRARIES}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
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
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral PLCore PLMath)
if(WIN32)
	add_dependencies(Engine                    	External-WindowsDDK)
endif()
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime"
)
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
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		PATTERN ".svn" EXCLUDE
)
