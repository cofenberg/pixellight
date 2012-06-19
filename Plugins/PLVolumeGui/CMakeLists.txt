#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Master thesis
#*    "Scalable Realtime Volume Rendering"
#*
#*  At
#*    Fachhochschule Würzburg-Schweinfurt
#*    Fakultät Informatik, Wirtschaftsinformatik (FIW)
#*    http://www.fh-wuerzburg.de/
#*
#*  Author
#*    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
#*    Copyright (C) 2011-2012
#*********************************************************#


[TODO] Bring me into PixelLight form


cmake_minimum_required(VERSION 2.8.3)


##################################################
## Define the project
##################################################
set(CURRENT_TARGET_NAME PLVolumeGui)
project(${CURRENT_TARGET_NAME})


##################################################
## Find packages
##################################################
find_package(PixelLight REQUIRED)


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)				# The current source directory
include_directories(${PL_PLCORE_INCLUDE_DIR})							# PLCore headers
include_directories(${PL_PLMATH_INCLUDE_DIR})							# PLMath headers
include_directories(${PL_PLGRAPHICS_INCLUDE_DIR})						# PLGraphics headers
include_directories(${PL_PLRENDERER_INCLUDE_DIR})						# PLRenderer headers
include_directories(${PL_PLMESH_INCLUDE_DIR})							# PLMesh headers
include_directories(${PL_PLSCENE_INCLUDE_DIR})							# PLScene headers
include_directories(${PL_PLENGINE_INCLUDE_DIR})							# PLEngine headers
include_directories(${PL_PLFRONTENDQT_INCLUDE_DIR})						# PLFrontendQt headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../PLVolume/include/)	# PLVolume


##################################################
## Special Qt stuff (see http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake for more information)
##################################################
# Qt location within the PixelLight externals directory
set(PL_EXTERNAL_QT_INCLUDE_DIR "${PL_ROOT}/External/_${CMAKE_SYSTEM_NAME}_${PL_ARCHBITSIZE}_${PL_BITSIZE}/Qt/include/")
set(PL_EXTERNAL_QT_LIB_DIR "${PL_ROOT}/External/_${CMAKE_SYSTEM_NAME}_${PL_ARCHBITSIZE}_${PL_BITSIZE}/Qt/lib/")

# Build external
get_filename_component(QT_EXTERNAL_ABS "${PL_EXTERNAL_QT_LIB_DIR}/.." ABSOLUTE)
set(QT_EXTERNAL_DIR ${QT_EXTERNAL_ABS} CACHE INTERNAL "")

# Directory for Qt stuff directly within PL's Git repository
set(LOCAL_QT_DIR "${PL_ROOT}/External/Optional/Qt/${CMAKE_SYSTEM_NAME}_x86" CACHE INTERNAL "")	# Always "x86"


##################################################
## Build external
##################################################
set(QT_INCLUDE_DIRS ${PL_EXTERNAL_QT_INCLUDE_DIR}/Qt/QtCore ${PL_EXTERNAL_QT_INCLUDE_DIR}/Qt/QtGui ${PL_EXTERNAL_QT_INCLUDE_DIR}/Qt CACHE INTERNAL "")
if(WIN32)
	set(QT_LIBRARIES ${PL_EXTERNAL_QT_LIB_DIR}/QtCore4.lib ${PL_EXTERNAL_QT_LIB_DIR}/QtGui4.lib ${PL_EXTERNAL_QT_LIB_DIR}/qtmain.lib CACHE INTERNAL "")

	# Set "FindQt4.cmake"-variables
	set(QT_QMAKE_EXECUTABLE ${LOCAL_QT_DIR}/qmake.exe)	# Tell Qt were to find qmake
elseif(LINUX)
	set(QT_LIBRARIES ${PL_EXTERNAL_QT_LIB_DIR}/libQtCore.so ${PL_EXTERNAL_QT_LIB_DIR}/libQtGui.so CACHE INTERNAL "")

	# Set "FindQt4.cmake"-variables
	set(QT_QMAKE_EXECUTABLE ${LOCAL_QT_DIR}/qmake)	# Tell Qt were to find qmake
endif()

# Unset QT_QMAKE_EXECUTABLE_LAST otherwise FindQt4.cmake triggers a query to qmake for the Qt library path.
# The Qt library path is hardcoded into qmake, but we can't relay on the reported path of qmake because the harcoded path is absolute
# and will not always match with the location of the Qt libraries which are bundled with PixelLight as an external package.
unset(QT_QMAKE_EXECUTABLE_LAST CACHE)

# We have to set following variables otherwise the FindQt4.cmake won't find either the executables uic, rcc, moc and the qt library path
# The QT_INCLUDE_DIR path has also be set, because this var is an additional condition that FindQt4.cmake sets QT_FOUND to true
set(QT_INCLUDE_DIR	${QT_EXTERNAL_DIR}/include/	)	# Path to "include" of Qt4
set(QT_BINARY_DIR 	${LOCAL_QT_DIR}/			)	# Path to "bin" of Qt4
set(QT_LIBRARY_DIR	${QT_EXTERNAL_DIR}/lib/		)	# Path to "lib" of Qt4

# We have to set both, QT_QTCORE_LIBRARY and QT_QTCORE_LIBRARY_RELEASE (we could also set QT_QTCORE_LIBRARY_DEBUG instead of QT_QTCORE_LIBRARY_RELEASE).
# QT_QTCORE_LIBRARY is used to determine if qmake should be queried for the library path to the Qt libraries (which has the problems described above why unsetting QT_QMAKE_EXECUTABLE_LAST).
# QT_QTCORE_LIBRARY_RELEASE must be set because this variable is used in FindQt4.cmake in order to determine whether or not the path to the Qt libraries has been found.
if(WIN32)
	set(QT_QTCORE_LIBRARY			${PL_EXTERNAL_QT_LIB_DIR}/QtCore4.lib)	# Path to QtCore library
	set(QT_QTCORE_LIBRARY_RELEASE	${PL_EXTERNAL_QT_LIB_DIR}/QtCore4.lib)	# Path to QtCore library (release version)
elseif(LINUX)
	set(QT_QTCORE_LIBRARY			${PL_EXTERNAL_QT_LIB_DIR}/libQtCore.so)	# Path to QtCore library
	set(QT_QTCORE_LIBRARY_RELEASE	${PL_EXTERNAL_QT_LIB_DIR}/libQtCore.so)	# Path to QtCore library (release version)
endif()

# Find Qt4 libraries and set all required variables
find_package(Qt4 REQUIRED)

# Include files with Qt relevant information
SET(INC_FILES
	include/PLVolumeGui/DockWidgetVolumeTransferFunctionQObject.h
)

# Qt .ui files
SET(UI_FILES
)

# Qt .qrc files
SET(QRC_FILES
)

# Run uic on .ui files
QT4_WRAP_UI(UI_SRCS ${UI_FILES})

# Run moc
QT4_WRAP_CPP(MOC_SRCS ${INC_FILES})

# Run rcc
QT4_ADD_RESOURCES(QRC_SRCS ${QRC_FILES})

# We need the following to be able to include headers produced by uic in our code
# (CMAKE_CURRENT_BINARY_DIR holds a path to the build directory of the current project, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${QT_INCLUDE_DIRS})


##################################################
## Source codes
##################################################
set(CURRENT_SRC
	src/PLVolumeGui.cpp								# Project main file
	src/TransferFunctionWidget.cpp					# Transfer function widget
	src/DockWidgetVolume.cpp						# Volume dock widget base class
	src/DockWidgetVolumeInformation.cpp				# Volume dock widget for information
	src/DockWidgetVolumeTransferFunction.cpp		# Volume dock widget for transfer function
	src/DockWidgetVolumeTransferFunctionQObject.cpp	# Volume dock widget for transfer function, QObject
	${UI_SRCS}										# Add source produced by uic
	${MOC_SRCS}										# Add source produced by moc
	${QRC_SRCS}										# Add sources produced by rcc
)


##################################################
## Additional libraries
##################################################
add_libs(
	${PL_PLCORE_LIBRARY}
	${PL_PLMATH_LIBRARY}
	${PL_PLGRAPHICS_LIBRARY}
	${PL_PLRENDERER_LIBRARY}
	${PL_PLMESH_LIBRARY}
	${PL_PLSCENE_LIBRARY}
	${PL_PLENGINE_LIBRARY}
	${PL_PLFRONTENDQT_LIBRARY}
	${QT_LIBRARIES}
	PLVolume
)


##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLVOLUMEGUI_EXPORTS
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
add_library(${CURRENT_TARGET_NAME} SHARED ${CURRENT_SRC})
target_link_libraries (${CURRENT_TARGET_NAME} ${libs})
set_project_properties(${CURRENT_TARGET_NAME})


##################################################
## Post-Build
##################################################
# Executable
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CURRENT_TARGET_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}"
)

# Plugin file
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND "${PL_ROOT}/Bin/Tools/${PL_ARCHBITSIZE}/PLProject${CMAKE_EXECUTABLE_SUFFIX}" ${CMAKE_CURRENT_SOURCE_DIR} --output-path "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}" --write-plugin
	WORKING_DIRECTORY ${dir}
)


##################################################
## Dependencies
##################################################
add_dependencies(${CURRENT_TARGET_NAME}	PLVolume)
