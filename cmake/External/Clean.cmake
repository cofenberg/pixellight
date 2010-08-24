##################################################
## CMakeTools externals - Clean script
##
## Base for 'clean'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## Default actions
##################################################

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Clean.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")

# Remove destination directory
external_removedir(${CMAKETOOLS_CURRENT_DEST_DIR})

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Check.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Fetch.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Configure.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Build.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)
