##################################################
## Project
##################################################
project(Samples)

##################################################
## Prerequisites
##################################################

# Create Samples directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Samples)
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Samples/Data)

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Samples/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/Samples/Data/*.*" "${PL_BIN_DIR}/Samples/Data")

##################################################
## Target
##################################################
add_custom_target(Samples)

##################################################
## Projects
##################################################
add_subdirectory(01Application)
add_subdirectory(02CommandLine)
add_subdirectory(03Signals)
add_subdirectory(04Dirs)
add_subdirectory(05NetworkChat)
add_subdirectory(20Gui)
#	add_subdirectory(21GuiWidgets) # [TODO]
add_subdirectory(30Input)
add_subdirectory(40ScriptHelloWorld)
add_subdirectory(41ScriptGlobalVariables)
add_subdirectory(42ScriptFunctors)
add_subdirectory(43ScriptBindings)
add_subdirectory(44ScriptOOP)
add_subdirectory(45ScriptApplication)
add_subdirectory(50RendererTriangle)
add_subdirectory(51RendererTexturing)
add_subdirectory(52RendererMesh)
add_subdirectory(53RendererMultiView)
add_subdirectory(54RendererRTT)
add_subdirectory(60Scene)
add_subdirectory(61Sound)
add_subdirectory(62Physics)
add_subdirectory(63PhysicsRagdoll)
add_subdirectory(64Picking)
add_subdirectory(65PostProcess)
add_subdirectory(66IngameGUI)
add_subdirectory(67Game2D)
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(70SPARK)
endif()
if(PL_PLUGIN_ENGINE_LIBROCKET)
	add_subdirectory(71libRocket)
endif()
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
install(FILES ${CMAKE_SOURCE_DIR}/Bin/Samples/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_SAMPLES}/Bin	COMPONENT SDK
)

# Data
install(DIRECTORY ${PL_BIN_DIR}/Samples/Data
	DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT SDK	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Microsoft Visual Studio Solution
if(WIN32)
	install(FILES ${CMAKE_SOURCE_DIR}/Samples/Samples.sln
		DESTINATION ${PL_INSTALL_SAMPLES}	COMPONENT SDK
	)
endif()
