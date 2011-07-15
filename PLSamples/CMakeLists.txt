##################################################
## Project
##################################################
project(Samples)

##################################################
## Prerequisites
##################################################

# Create PLSamples directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLSamples)

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/PLSamples/PLGui")
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLSamples/PLGui/*.*" "${PL_BIN_DIR}/PLSamples/PLGui")
file(MAKE_DIRECTORY "${PL_BIN_DIR}/PLSamples/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLSamples/Data/*.*" "${PL_BIN_DIR}/PLSamples/Data")

##################################################
## Target
##################################################
add_custom_target(Samples)

##################################################
## Projects
##################################################
add_subdirectory(01Application)
add_subdirectory(02CommandLine)
add_subdirectory(98GuiTest)
#if(NOT CMAKETOOLS_MINIMAL)
	add_subdirectory(03Signals)
	add_subdirectory(04Dirs)
	add_subdirectory(20Gui)
#	add_subdirectory(21GuiWidgets)
	add_subdirectory(30Input)
	add_subdirectory(40ScriptHelloWorld)
	add_subdirectory(41ScriptGlobalVariables)
	add_subdirectory(42ScriptFunctors)
	add_subdirectory(43ScriptBindings)
	add_subdirectory(44ScriptOOP)
#endif()
if(PL_PLUGIN_ENGINE_QT)
	add_subdirectory(80QtHelloWorld)
	add_subdirectory(81QtScene)
	add_subdirectory(82QtInputHandling)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Samples)

##################################################
## Install
##################################################

# "WhereIsTheLog.txt"-file
install(FILES ${CMAKE_SOURCE_DIR}/Bin/PLSamples/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_SAMPLES}/Bin	COMPONENT SDK
)

# Data
install(DIRECTORY ${PL_BIN_DIR}/PLSamples/Data
	DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT SDK	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Microsoft Visual Studio Solution
if(WIN32)
	install(FILES ${CMAKE_SOURCE_DIR}/PLSamples/PLSamples.sln
		DESTINATION ${PL_INSTALL_SAMPLES}	COMPONENT SDK
	)
endif()
