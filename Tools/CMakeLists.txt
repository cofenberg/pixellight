##################################################
## Project
##################################################
project(Tools)

##################################################
## Target
##################################################
add_custom_target(Tools)

##################################################
## Prerequisites
##################################################

# Create Tools directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools)

##################################################
## Projects
##################################################
add_subdirectory(PLProject)
add_subdirectory(PLUpgrade)
if(WIN32)
	add_subdirectory(PLInstall)
endif()
add_subdirectory(PLViewer)
if(PL_EXPORTER_3DSMAX_2008)
	add_subdirectory(PL3dsMaxSceneExport_2008)
endif()
if(PL_EXPORTER_3DSMAX_2009)
	add_subdirectory(PL3dsMaxSceneExport_2009)
endif()
if(PL_EXPORTER_3DSMAX_2010)
	add_subdirectory(PL3dsMaxSceneExport_2010)
endif()
if(PL_EXPORTER_3DSMAX_2011)
	add_subdirectory(PL3dsMaxSceneExport_2011)
endif()
if(PL_EXPORTER_3DSMAX_2012)
	add_subdirectory(PL3dsMaxSceneExport_2012)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tools)

##################################################
## Install
##################################################

install(FILES	${CMAKE_SOURCE_DIR}/Tools/FindPixelLight.cmake
	DESTINATION ${PL_INSTALL_ROOT}/Tools		COMPONENT SDK
)
