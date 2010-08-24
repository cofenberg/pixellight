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
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/tinyxml_2_5_3.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Get patch file
	set(patch "${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/tinyxml.patch")
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Convert line endings to Windows format (CRLF)
		external_copy(${patch} "${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/tinyxml.patch-win32")
		set(patch "${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/tinyxml.patch-win32")
		external_convert_lineendings("${patch}" "lf-to-crlf")
	endif()

	# Apply patch
	external_patch("${patch}" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/tinyxml/")

	# Configure project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Update VC project files
		external_vcproj_upgrade("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/tinyxml/tinyxml_lib.vcproj")
	endif()
endif()

# Done
external_configure_done()
