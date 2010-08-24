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
		"http://netcologne.dl.sourceforge.net/project/pcre/pcre/8.10/pcre-8.10.tar.gz"
		"9524f0ff50b9093c02c81f911e41b066"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
