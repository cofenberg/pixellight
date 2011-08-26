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
			set(md5sum "0578e258e93ae27076a38896b1d0324d")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package [TODO]
			set(md5sum "")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "c3f9e0b10a5682cb5e0a09e11575d207")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/ode.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/ode.dll" ${PL_RUNTIME_BIN_DIR})		# Bin-Windows
	endif()
endif()

# Done
external_check_done()
