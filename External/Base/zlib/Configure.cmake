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
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/zlib-1.2.5.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Configure project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Update VC project files
		external_vcproj_upgrade("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/zlib-1.2.5/projects/visualc6/zlib.dsp")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use configure script
		external_run_configure2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/zlib-1.2.5")
	endif()
endif()

# Done
external_configure_done()
