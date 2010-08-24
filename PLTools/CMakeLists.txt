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

# Create PLTools directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLTools)

##################################################
## Projects
##################################################
add_subdirectory(PLViewer)
if(WIN32)
	if(PL_EXPORTER_3DSMAX_2008)
		add_subdirectory(PL3dsMaxSceneExport_2008)
	endif()
	if(PL_EXPORTER_3DSMAX_2009)
		add_subdirectory(PL3dsMaxSceneExport_2009)
	endif()
	if(PL_EXPORTER_3DSMAX_2010)
		add_subdirectory(PL3dsMaxSceneExport_2010)
	endif()
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tools)

##################################################
## Install
##################################################
