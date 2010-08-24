##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Configure.cmake)

##################################################
## Configure
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Extract tar archive
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/freetype-2.3.12.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Install cmake project
	set(cmakelists "${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/CMakeLists.txt")
	external_copy(${cmakelists} "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.3.12")

	# Configure project
	external_run_cmake("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.3.12")
endif()

# Done
external_configure_done()
