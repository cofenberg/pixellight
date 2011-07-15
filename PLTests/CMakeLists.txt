##################################################
## Project
##################################################
project(Tests)

##################################################
## Prerequisites
##################################################

# Create PLTests directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLTests)

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
