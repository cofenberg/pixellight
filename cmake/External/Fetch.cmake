##################################################
## CMakeTools externals - Fetch script
##
## Base for 'fetch'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## MACRO: external_fetch_done
##
## Mark the end of a 'fetch'-script
##################################################
macro(external_fetch_done)
	# Create 'done'-file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Fetch.done "done")
endmacro(external_fetch_done)


##################################################
## Default actions
##################################################

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Fetch.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Configure.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Build.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Fetch.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")

# Create source directory
file(MAKE_DIRECTORY ${CMAKETOOLS_CURRENT_DOWNLOAD_DIR})
