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
		"http://cdnetworks-kr-2.dl.sourceforge.net/project/freetype/freetype2/2.3.12/freetype-2.3.12.tar.gz"
		"6fc690d9b34154b51a919ff466cea90c"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
