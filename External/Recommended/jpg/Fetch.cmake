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
		"http://www.ijg.org/files/jpegsrc.v8c.tar.gz"
		"a2c10c04f396a9ce72894beb18b4e1f9"
		${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/
	)
endif()

# Done
external_fetch_done()
