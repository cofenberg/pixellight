##################################################
## Project
##################################################
define_project(PLQt)

##################################################
## Special Qt stuff (see http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake for more information)
##################################################
# Include files with Qt relevant information
SET(INC_FILES
	include/PLQt/QPLContext.h
	include/PLQt/Application.h
	include/PLQt/QPLDebugDialog.h
	include/PLQt/QPLRenderWindow.h
	include/PLQt/QPLSceneContext.h
	include/PLQt/QPLInputHandler.h
	include/PLQt/DataModels/TreeItemBase.h
	include/PLQt/DataModels/TreeModelBase.h
	include/PLQt/DataModels/SceneNodeInfoModel.h
	include/PLQt/DataModels/SceneGraphTreeModel.h
	include/PLQt/DataModels/PLIntrospectionModel.h
	include/PLQt/DataModels/SceneNodeInfoDelegate.h
	include/PLQt/DataModels/SceneGraphNodeTreeItemBase.h
	include/PLQt/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.h
	include/PLQt/DataModels/PLTreeItems/PLDynVarFloatTreeItem.h
	include/PLQt/DataModels/PLTreeItems/PLDynVarColorTreeItem.h
	include/PLQt/DataModels/PLTreeItems/PLDynVarStringTreeItem.h
	include/PLQt/DataModels/PLTreeItems/PLDynVarVector3TreeItem.h
	include/PLQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h
	include/PLQt/DataModels/SceneRendererDataModel/SceneRendererPassTreeItem.h
	include/PLQt/DataModels/SceneRendererDataModel/SceneRendererHeaderTreeItem.h
	include/PLQt/External/qtcolorbutton.h
)

# Qt .ui files
SET(UI_FILES
	include/PLQt/QPLDebugDialog.ui
)

# When not using system libraries, the following stuff will only be defined once in the external Qt cmake file
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	# Find Qt4 libraries and set all required variables
	FIND_PACKAGE(Qt4 REQUIRED)

	# Add Qt CMake macros and variables
	# (QT_USE_FILE is a variable defined by FIND_PACKAGE(Qt4) that contains a path to CMake script)
	INCLUDE(${QT_USE_FILE})
endif()

# Run uic on .ui files
QT4_WRAP_UI(UI_SRCS ${UI_FILES})

# Run moc
QT4_WRAP_CPP(MOC_SRCS ${INC_FILES})

##################################################
## Source files
##################################################
add_sources(
	src/PLQt.cpp
	src/QPLContext.cpp
	src/Application.cpp
	src/QPLSceneContext.cpp
	src/QPLRenderWindow.cpp
	src/QPLInputHandler.cpp
	src/QPLDebugDialog.cpp
	src/DataModels/TreeItemBase.cpp
	src/DataModels/TreeModelBase.cpp
	src/DataModels/SceneNodeInfoModel.cpp
	src/DataModels/SceneGraphTreeModel.cpp
	src/DataModels/PLIntrospectionModel.cpp
	src/DataModels/SceneNodeInfoDelegate.cpp
	src/DataModels/SceneGraphNodeTreeItemBase.cpp
	src/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.cpp
	src/DataModels/PLTreeItems/PLDynVarFloatTreeItem.cpp
	src/DataModels/PLTreeItems/PLDynVarColorTreeItem.cpp
	src/DataModels/PLTreeItems/PLDynVarStringTreeItem.cpp
	src/DataModels/PLTreeItems/PLDynVarVector3TreeItem.cpp
	src/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.cpp
	src/DataModels/SceneRendererDataModel/SceneRendererDataModel.cpp
	src/DataModels/SceneRendererDataModel/SceneRendererPassTreeItem.cpp
	src/DataModels/SceneRendererDataModel/SceneRendererHeaderTreeItem.cpp
	src/External/qtcolorbutton.cpp
	${UI_SRCS}	# Add source produced by uic
	${MOC_SRCS}	# Add source produced by moc
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

	# We need the following to be able to include headers produced by uic in our code
	# (CMAKE_CURRENT_BINARY_DIR holds a path to the build directory of the current project, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
	${CMAKE_CURRENT_BINARY_DIR}
)

if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	add_include_directories(
		${QT_INCLUDE_DIRS}
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
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../bin/QtCore4.dll "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../bin/QtGui4.dll "${PL_BIN_DIR}/PLRuntime"
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
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/QtCore4.dll "${PL_BIN_DIR}/PLRuntime/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/QtGui4.dll "${PL_BIN_DIR}/PLRuntime/"
		)
	endif()
	if(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			 COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/libQtCore.so "${PL_BIN_DIR}/PLRuntime"
			 COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/libQtGui.so "${PL_BIN_DIR}/PLRuntime"
		)
	endif()
endif()

# Copy the QT libraries so that the user can use everything "out of the box"
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/QtCore4.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/QtGui4.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/qtmain.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/qtmaind.lib "${PL_BIN_DIR}/Lib"
	)
endif()
if(LINUX)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/libQtCore.so "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_INCLUDE_DIRS}/../../lib/libQtGui.so "${PL_BIN_DIR}/Lib"
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
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	# Copy the QT stuff into the SDK so that the user can use everything "out of the box"
	install(DIRECTORY "${QT_INCLUDE_DIRS}/.."
		DESTINATION "${PL_INSTALL_INCLUDE}/Qt/Qt" 	COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
	)

	# Copy the copyright information into the include directory
	install(FILES	"${QT_INCLUDE_DIRS}/../../Readme.txt"
					"${QT_INCLUDE_DIRS}/../../LICENSE.LGPL"
		DESTINATION "${PL_INSTALL_INCLUDE}/Qt"	COMPONENT SDK
	)
endif(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
if(WIN32)
	# Copy shared libraries
	install(FILES	${PL_BIN_DIR}/PLRuntime/QtCore4.dll
					${PL_BIN_DIR}/PLRuntime/QtGui4.dll
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)

	# Copy libraries
	install(FILES	${PL_BIN_DIR}/Lib/QtCore4.lib
					${PL_BIN_DIR}/Lib/QtGui4.lib
					${PL_BIN_DIR}/Lib/qtmain.lib
					${PL_BIN_DIR}/Lib/qtmaind.lib
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)

	# Copy tools
	install(FILES	"${QT_INCLUDE_DIRS}/../../bin/moc.exe"
					"${QT_INCLUDE_DIRS}/../../bin/uic.exe"
					"${QT_INCLUDE_DIRS}/../../Readme.txt"
					"${QT_INCLUDE_DIRS}/../../LICENSE.LGPL"
		DESTINATION ${PL_INSTALL_TOOLS_BIN}/Qt	COMPONENT SDK
	)
endif()
if(LINUX)
	# Copy shared libraries
	install(FILES	${PL_BIN_DIR}/PLRuntime/libQtCore.so
					${PL_BIN_DIR}/PLRuntime/libQtGui.so
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)

	# Copy libraries
	install(FILES	${PL_BIN_DIR}/PLRuntime/libQtCore.so
					${PL_BIN_DIR}/PLRuntime/libQtGui.so
		DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)

	# Copy tools
	install(FILES	"${QT_INCLUDE_DIRS}/../../bin/moc"
					"${QT_INCLUDE_DIRS}/../../bin/uic"
					"${QT_INCLUDE_DIRS}/../../Readme.txt"
					"${QT_INCLUDE_DIRS}/../../LICENSE.LGPL"
		DESTINATION ${PL_INSTALL_TOOLS_BIN}/Qt	COMPONENT SDK
	)
endif()
