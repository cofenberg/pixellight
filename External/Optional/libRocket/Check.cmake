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
			set(md5sum "810b21ec9fb5c3978dd0a58f86961a16")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "539fd5c63f385381cb216811b8c5b705")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "2b7bb23054d98ac564cbc864cb9008ce")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketCore.dll"     ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketCore.dll"     ${PL_RUNTIME_BIN_DIR})	# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketControls.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketControls.dll" ${PL_RUNTIME_BIN_DIR})	# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketDebugger.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/RocketDebugger.dll" ${PL_RUNTIME_BIN_DIR})	# Bin-Windows
	endif()
endif()

# Done
external_check_done()
