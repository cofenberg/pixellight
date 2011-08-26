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
			set(md5sum "70c2be21c5587eefd2260b4049eeae9c")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package [TODO]
			set(md5sum "")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit Linux package
			set(md5sum "99fe4618e39350b62679e4ac8e5e7f69")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/ssleay32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/ssleay32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/msvcr80.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/msvcr80.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/Microsoft.VC80.CRT.manifest"	${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/Microsoft.VC80.CRT.manifest"	${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/msvcr71.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/msvcr71.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libpq.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libpq.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libintl3.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libintl3.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libiconv2.dll"				${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libiconv2.dll"				${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libeay32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/libeay32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/krb5_32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/krb5_32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/k5sprt32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/k5sprt32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/gssapi32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/gssapi32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/comerr32.dll"					${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/comerr32.dll"					${PL_RUNTIME_BIN_DIR})		# Bin-Windows
	endif()
endif()

# Done
external_check_done()
