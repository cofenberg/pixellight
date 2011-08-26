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
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Windows package
			set(md5sum "a2b840bbe6f8f586a8037a38995ab126")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "0716f321493e69d1804a28847b46b649")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "56bf6238eb7d57a90f3d5c6e8d6a2899")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
