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
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/jpegsrc.v8b.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Configure project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Copy configuration from sample file
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8b/jconfig.vc" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8b/jconfig.h")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use configure script
		external_run_configure2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8b")
	endif()
endif()

# Done
external_configure_done()
