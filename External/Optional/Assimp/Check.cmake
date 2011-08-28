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
			set(md5sum "a6f98e0790b6eefe6585be75e1612217")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "d740c4f50ca6889b093f37bec416b61f")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "ba721e8316e0f9142ed795b1b4e61bdd")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
