##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Fetch.cmake)

##################################################
## Fetch
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Download libjpeg
	external_fetch_http(
		"http://heanet.dl.sourceforge.net/project/libpng/libpng14/1.4.5/libpng-1.4.5.tar.gz"
		"dd4175393720ae041c67ace87cf6d212"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
