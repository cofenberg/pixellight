##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Fetch.cmake)

##################################################
## Fetch
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Download PCRE
	external_fetch_http(
		"http://freefr.dl.sourceforge.net/project/pcre/pcre/8.12/pcre-8.12.tar.gz"
		"fa69e4c5d8971544acd71d1f10d59193"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
