#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
define_project(PLTestBase NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/Graphics/ImageTest.cpp
	src/Graphics/Graphics.cpp
	src/Database/DatabaseTest.cpp
	src/Database/Database.cpp
	src/Database/DatabaseTestPostgreSQL.cpp
	src/Database/DatabaseTestSQLite.cpp
	src/Database/DatabaseTestMySQL.cpp
	src/Math/GraphPathTest.cpp
	src/Math/MathClassTest.cpp
	src/Math/GraphTest.cpp
	src/Math/Matrix3x3Test.cpp
	src/Math/Matrix3x4Test.cpp
	src/Math/Vector2Test.cpp
	src/Math/Matrix4x4Test.cpp
	src/Math/Vector3Test.cpp
	src/Math/QuaternionTest.cpp
	src/Math/Vector4Test.cpp
	src/Math/MathTest.cpp
	src/Math/Math.cpp
	src/Math/MiscTest.cpp
	src/Math/EulerAnglesTest.cpp
	src/General/XmlTest.cpp
	src/General/FibonacciHeapTest.cpp
	src/General/PerformanceTest.cpp
	src/General/StackTest.cpp
	src/General/StringTest.cpp
	src/General/UTF8ToolsTest.cpp
	src/General/HeapTestCase.cpp
	src/General/ArrayTest.cpp
	src/General/General.cpp
	src/General/FileSystemTest.cpp
	src/General/HashMapTest.cpp
	src/General/SystemTest.cpp
	src/General/BinominalHeapTest.cpp
	src/General/SimpleMapTest.cpp
	src/General/FastPoolTest.cpp
	src/General/TimeTest.cpp
	src/General/SingletonTest.cpp
	src/General/TokenizerTest.cpp
	src/General/MapTestCase.cpp
	src/General/PoolTest.cpp
	src/General/QueueTest.cpp
	src/General/ListTest.cpp
	src/General/SimpleListTest.cpp
	src/General/MultiThreadingTest.cpp
	src/General/BinaryHeapTest.cpp
	src/General/QuickSortTest.cpp
	src/General/BitsetTest.cpp
	src/General/ChecksumTest.cpp
	src/General/LogTest.cpp
	src/Core/Core.cpp
	src/Core/ChunkTest.cpp
	src/Core/ConfigTest.cpp
	src/Core/LocalizationTest.cpp
	src/Core/ResourceManagerTest.cpp
	src/Core/ResourceManagementTest.cpp
	src/main.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLDatabase/include
	${CMAKE_SOURCE_DIR}/Tests/PLTest/include
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
	PLGraphics
	PLDatabase
	PLTest
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
build_executable(${CMAKETOOLS_CURRENT_TARGET} CONSOLE)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLDatabase PLTest)
add_dependencies(Tests							${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} ${PL_TESTS_BIN_DIR}
)
