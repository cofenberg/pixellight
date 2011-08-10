##################################################
## Prerequisites
##################################################

# Create Tools directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tools/PLEditor)

##################################################
## Projects
##################################################
add_subdirectory(PLEditor)
add_subdirectory(PLEditorPluginBase)
