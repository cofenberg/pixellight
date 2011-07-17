##################################################
## Project
##################################################
project(Tests)

##################################################
## Prerequisites
##################################################

# Create Tests directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tests)

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Tests/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/Tests/Data/*.*" "${PL_BIN_DIR}/Tests/Data")

##################################################
## Target
##################################################
add_custom_target(Tests)

##################################################
## Projects
##################################################
add_subdirectory(PLTest)
add_subdirectory(PLTestBase)
#	add_subdirectory(98GuiTest)
#	add_subdirectory(99Test)
#	add_subdirectory(99TestPlugin)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tests)
