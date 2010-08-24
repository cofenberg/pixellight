##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Fetch.cmake)

##################################################
## Fetch
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Download tinyxml
	external_fetch_http(
		"http://freefr.dl.sourceforge.net/project/tinyxml/tinyxml/2.5.3/tinyxml_2_5_3.tar.gz"
		"84b605a31628e7f1a6694d47bf5999cc"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
