##################################################
## Project
##################################################
project(Engine)

##################################################
## Prerequisites
##################################################

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data/*.zip" "${PL_BIN_DIR}/PLRuntime/Data")

##################################################
## Target
##################################################
add_custom_target(Engine)

##################################################
## Projects
##################################################
add_subdirectory(PLRenderer)
add_subdirectory(PLInput)
add_subdirectory(PLMesh)
add_subdirectory(PLScene)
add_subdirectory(PLPhysics)
add_subdirectory(PLSound)
add_subdirectory(PLEngine)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Engine)

##################################################
## Install
##################################################

# Data
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data
	DESTINATION ${PL_INSTALL_RUNTIME}		COMPONENT Runtime	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
