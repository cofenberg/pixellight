cmake_minimum_required(VERSION 2.8.3)

# Add the directory this "CMakeLists.txt" file is in as CMake module path in order to make it possible to find "FindPixelLight.cmake"
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/../../Tools)	# For this test, don't duplicate the "FindPixelLight.cmake"-file

# Determine debug suffix
set(suffix "")
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(suffix "D")
endif()

# Define the project, use the current directory name as project name
get_filename_component(CURRENT_TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME_WE)
set(CURRENT_TARGET_NAME ${CURRENT_TARGET_NAME}${suffix})
project(${CURRENT_TARGET_NAME})

# Add the source code directory
add_subdirectory(src)