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
			set(md5sum "c34adb114742bca4fd4e1a1c963b6e63")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package [TODO]
			set(md5sum "")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "286b2df13829de9897f092c3b88403fa")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
