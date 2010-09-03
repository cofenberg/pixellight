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
	external_check_download("nonpublic")

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" "${PL_BIN_DIR}/../Bin/PLRuntime/Plugins/PLPhysics")	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" "${PL_BIN_DIR}/PLRuntime/Plugins/PLPhysics")			# Bin-Windows
	endif()
endif()

# Done
external_check_done()
