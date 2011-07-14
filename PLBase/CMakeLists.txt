##################################################
## Project
##################################################
project(Base)

##################################################
## Prerequisites
##################################################

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data/*.zip" "${PL_BIN_DIR}/PLRuntime/Data")

##################################################
## Target
##################################################
add_custom_target(Base)

##################################################
## Projects
##################################################
add_subdirectory(PLGeneral)
add_subdirectory(PLCore)
add_subdirectory(PLGraphics)
add_subdirectory(PLMath)
add_subdirectory(PLDatabase)
add_subdirectory(PLGui)
add_subdirectory(PLInput)
add_subdirectory(PLRenderer)
add_subdirectory(PLMesh)
add_subdirectory(PLScene)
add_subdirectory(PLPhysics)
add_subdirectory(PLSound)
add_subdirectory(PLEngine)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Base)

##################################################
## Install
##################################################

# Data
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data
	DESTINATION ${PL_INSTALL_RUNTIME}		COMPONENT Runtime	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
