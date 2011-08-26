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
			# md5sum of the 64bit Windows package
			set(md5sum "e09eef52020af5df4c272101e9e9f82a")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Windows package
			set(md5sum "10d2c7a565d21bf7a4f338643631402a")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "b00636844525f16fc22368000812cf72")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "df65ce352600dd98010055ad5aee3a62")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
