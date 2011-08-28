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
			set(md5sum "29ad1f7f620b69f614cb133030ccfede")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "65ad0df18e43abd255075f2621247929")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "c6f8bacb0b0a4a978b0cd5080d4ee69e")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "faa7e0f7a295a7c06af4e0a9950db6a2")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	# [TODO]
	if(WIN32)
		#external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		#external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_DIR})		# Bin-Windows
	endif()
endif()

# Done
external_check_done()
