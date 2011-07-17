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

	# Copy the required dlls into the runtime directory
	file(MAKE_DIRECTORY "${PL_BIN_DIR}/../Bin/Runtime/VC2010_Redistributable")	# Bin
	file(MAKE_DIRECTORY "${PL_BIN_DIR}/Runtime/VC2010_Redistributable")			# Bin-Windows
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcr100.dll"	"${PL_BIN_DIR}/../Bin/Runtime/VC2010_Redistributable")	# Bin
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcr100.dll"	"${PL_BIN_DIR}/Runtime/VC2010_Redistributable")			# Bin-Windows
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcp100.dll"	"${PL_BIN_DIR}/../Bin/Runtime/VC2010_Redistributable")	# Bin
	external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/msvcp100.dll" "${PL_BIN_DIR}/Runtime/VC2010_Redistributable")			# Bin-Windows
endif()

# Done
external_check_done()
