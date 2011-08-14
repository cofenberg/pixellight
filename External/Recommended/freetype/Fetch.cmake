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
		"http://freefr.dl.sourceforge.net/project/freetype/freetype2/2.4.6/freetype-2.4.6.tar.gz"
		"1dc4af24a86e2f78a49ac6b520a81ec5"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
