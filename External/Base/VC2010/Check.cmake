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
			set(md5sum "7a8a0c9c116ded9007af932c14279f39")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# Copy the required dlls into the runtime directory
	file(MAKE_DIRECTORY "${PL_RUNTIME_BIN_GITDIR}/VC2010_Redistributable")	# Bin
	file(MAKE_DIRECTORY "${PL_RUNTIME_BIN_DIR}/VC2010_Redistributable")		# Bin-Windows
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcr100.dll"	"${PL_RUNTIME_BIN_GITDIR}/VC2010_Redistributable")	# Bin
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcr100.dll"	"${PL_RUNTIME_BIN_DIR}/VC2010_Redistributable")		# Bin-Windows
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcp100.dll"	"${PL_RUNTIME_BIN_GITDIR}/VC2010_Redistributable")	# Bin
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcp100.dll" "${PL_RUNTIME_BIN_DIR}/VC2010_Redistributable")		# Bin-Windows
endif()

# Done
external_check_done()
