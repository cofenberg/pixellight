##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Check.cmake)

##################################################
## Check
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Download prebuilt package from the repository
	set(md5sum "")
	if(WIN32)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Windows package [TODO]
			set(md5sum "")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "b98673354f0479464f6702f08d1659ac")
		endif()
	endif()
	external_check_download("nonpublic" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
