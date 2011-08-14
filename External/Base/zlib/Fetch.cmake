##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Fetch.cmake)

##################################################
## Fetch
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Download zlib
	external_fetch_http(
		"http://garr.dl.sourceforge.net/project/libpng/zlib/1.2.5/zlib-1.2.5.tar.gz"
		"c735eab2d659a96e5a594c9e8541ad63"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
