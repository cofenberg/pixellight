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
			set(md5sum "6a261e49e7f699a549ad0a8816070a8c")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "1792f25047faed90f7a11da95f0162ee")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "f57d7a310f0298e2e2083ffa199c4ed6")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_DIR})	# Bin-Windows
	endif()
endif()

# Done
external_check_done()
