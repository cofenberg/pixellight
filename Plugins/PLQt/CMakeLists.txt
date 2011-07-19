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
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLGui/include
	${CMAKE_SOURCE_DIR}/Base/PLInput/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Base/PLEngine/include

	# We need the following to be able to include headers produced by uic in our code
	# (CMAKE_CURRENT_BINARY_DIR holds a path to the build directory of the current project, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
	${CMAKE_CURRENT_BINARY_DIR}
	${QT_INCLUDE_DIRS}
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Qt PLCore PLMath PLGraphics PLGui PLInput PLRenderer PLMesh PLScene PLEngine)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Runtime"
)
if(WIN32)
	# Copy the Qt dlls so that the user can use everything "out of the box"
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/bin/QtCore4.dll "${PL_BIN_DIR}/Runtime"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/bin/QtGui4.dll "${PL_BIN_DIR}/Runtime"
	)
endif()

if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime"
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
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/QtCore4.dll "${PL_BIN_DIR}/Runtime/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/QtGui4.dll "${PL_BIN_DIR}/Runtime/"
		)
	endif()
	if(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtCore.so"			"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtCore.so.4"		"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtCore.so.4.7"		"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtCore.so.4.7.3"	"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtGui.so"			"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtGui.so.4"			"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtGui.so.4.7"		"${PL_BIN_DIR}/Runtime"
			COMMAND ${CMAKE_COMMAND} -E copy "${QT_EXTERNAL_DIR}/lib/libQtGui.so.4.7.3"		"${PL_BIN_DIR}/Runtime"
		)
	endif()
endif()

# Copy the QT libraries so that the user can use everything "out of the box"
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/lib/QtCore4.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/lib/QtGui4.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/lib/qtmain.lib "${PL_BIN_DIR}/Lib"
		COMMAND ${CMAKE_COMMAND} -E copy ${QT_EXTERNAL_DIR}/lib/qtmaind.lib "${PL_BIN_DIR}/Lib"
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

# Copy the QT stuff into the SDK so that the user can use everything "out of the box", but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	install(DIRECTORY "${QT_EXTERNAL_DIR}/include/Qt"
		DESTINATION "${PL_INSTALL_INCLUDE}/Qt" 	COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
	)

	# Copy the copyright information into the include directory
	install(FILES	"${QT_EXTERNAL_DIR}/Readme.txt"
					"${QT_EXTERNAL_DIR}/LICENSE.LGPL"
		DESTINATION "${PL_INSTALL_INCLUDE}/Qt"	COMPONENT SDK
	)
endif(NOT CMAKETOOLS_USE_SYSTEM_LIBS)

if(WIN32)
	# Copy shared libraries
	install(FILES	${PL_BIN_DIR}/Runtime/QtCore4.dll
					${PL_BIN_DIR}/Runtime/QtGui4.dll
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
	install(FILES	"${QT_EXTERNAL_DIR}/bin/moc.exe"
					"${QT_EXTERNAL_DIR}/bin/uic.exe"
					"${QT_EXTERNAL_DIR}/Readme.txt"
					"${QT_EXTERNAL_DIR}/LICENSE.LGPL"
		DESTINATION ${PL_INSTALL_TOOLS_BIN}/Qt	COMPONENT SDK
	)
endif()
if(LINUX)
	# Copy shared libraries
	install(FILES	${QT_EXTERNAL_DIR}/lib/libQtCore.so.4
					${QT_EXTERNAL_DIR}/lib/libQtGui.so.4
					${QT_EXTERNAL_DIR}/lib/libQtCore.so.4.7.3
					${QT_EXTERNAL_DIR}/lib/libQtGui.so.4.7.3
		DESTINATION ${PL_INSTALL_SHARED}		COMPONENT SDK
	)

	# Copy tools
	install(FILES	"${QT_EXTERNAL_DIR}/bin/moc"
					"${QT_EXTERNAL_DIR}/bin/uic"
					"${QT_EXTERNAL_DIR}/Readme.txt"
					"${QT_EXTERNAL_DIR}/LICENSE.LGPL"
		DESTINATION ${PL_INSTALL_TOOLS_BIN}/Qt	COMPONENT SDK
	)
endif()
