##################################################
## Project
##################################################
define_project(98GuiTest NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/SimpleTest/SimpleTestWindow.cpp
	src/SimpleTest/TestWidget.cpp
	src/SimpleTest/TestWidgetImage.cpp
	src/SimpleTest/TestWidgetTimer.cpp
	src/MouseOver/MouseOverWindow.cpp
	src/MouseOver/MouseOverWidget.cpp
	src/Focus/FocusWindow.cpp
	src/Focus/FocusWidget.cpp
	src/Window/TestWindow.cpp
	src/WidgetTest/WidgetTestWindow.cpp
#	src/DragDrop/DragDropWindow.cpp
#	src/DragDrop/DragDropWidget.cpp
	src/TabsAndMenu/TabsAndMenuWindow.cpp
#	src/SlimTest/SlimTestWindow.cpp
	src/ThemeTest/ThemeTestWindow.cpp
	src/ThemeTest/ThemeTestWidget.cpp
	src/GuiTestWindow.cpp
	src/Application.cpp
	src/Main.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLGui/PLGui/include
	src
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
	PLGeneral
	PLMath
	PLGraphics
	PLCore
	PLGui
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET} PLGeneral PLCore PLGui)
add_dependencies(Samples ${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Executable
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} "${PL_BIN_DIR}/PLSamples"
)

##################################################
## Install
##################################################

# Executable
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT SDK
)
