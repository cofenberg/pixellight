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
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/pcre-8.10.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Configure with CMake
	external_run_cmake(
		"${CMAKETOOLS_CURRENT_BUILD_DIR}/build/pcre-8.10"
		-DCMAKE_BUILD_TYPE:STRING=Release
		-DBUILD_SHARED_LIBS:STRING=OFF
		-DPCRE_BUILD_PCRECPP:STRING=OFF
		-DPCRE_SUPPORT_UNICODE_PROPERTIES:STRING=ON
		-DPCRE_SUPPORT_UTF8:STRING=ON
	)
endif()

# Done
external_configure_done()
