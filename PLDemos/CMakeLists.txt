##################################################
## Project
##################################################
project(Demos)

##################################################
## Target
##################################################
add_custom_target(Demos)

##################################################
## Prerequisites
##################################################

# Create PLDemos directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLDemos)
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLDemos/Data)

# Copy runtime data
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLDemos/Data/*" "${PL_BIN_DIR}/PLDemos/Data" EXCLUDE "\\\\.svn")

##################################################
## Projects
##################################################
add_subdirectory(PLDemoRendererTriangle)
add_subdirectory(PLDemoRendererTexturing)
add_subdirectory(PLDemoRendererRTT)
add_subdirectory(PLDemoRendererMultiView)
add_subdirectory(PLDemoMeshTeapot)
add_subdirectory(PLDemoSimpleScene)
add_subdirectory(PLDemoPicking)
add_subdirectory(PLDemoPhysicsBasic)
add_subdirectory(PLDemoPhysicsRagdoll)
add_subdirectory(PLDemoNetworkChat)
add_subdirectory(PLDemoSoundBasic)
add_subdirectory(PLDemoPostProcess)
add_subdirectory(PLDemo2DGame)
add_subdirectory(PLDemoIngameGUI)
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(PLDemoSPARK_PL)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Demos)

##################################################
## Install
##################################################

# "WhereIsTheLog.txt"-file
install(FILES ${CMAKE_SOURCE_DIR}/Bin/PLDemos/WhereIsTheLog.txt
	DESTINATION ${PL_INSTALL_DEMOS}/Bin	COMPONENT SDK
)

# Data
install(DIRECTORY ${PL_BIN_DIR}/PLDemos/Data
	DESTINATION ${PL_INSTALL_DEMOS_BIN}	COMPONENT SDK	PATTERN ".svn" EXCLUDE
)

# Microsoft Visual Studio Solution
if(WIN32)
	install(FILES ${CMAKE_SOURCE_DIR}/PLDemos/PLDemos.sln
		DESTINATION ${PL_INSTALL_DEMOS}	COMPONENT SDK
	)
endif()
