##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Check.cmake)

##################################################
## Check
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	set(md5sum "")
	if(WIN32)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit windows package [TODO]
			set(md5sum "")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit windows package
			set(md5sum "9f23ea8d68b4f4da1a67d97933ba4fac")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	# Download prebuilt package from the repository
	external_check_download("nonpublic" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
