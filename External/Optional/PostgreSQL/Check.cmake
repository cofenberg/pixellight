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
	external_check_download("")

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
