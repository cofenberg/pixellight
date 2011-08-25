##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Check.cmake)

##################################################
## Check
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	set(md5sum "")
	if(WIN32)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit windows package
			set(md5sum "0adf1f5da70faf989e2277153396a05b")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit windows package
			set(md5sum "dd6db4f89fbad7159a94a1e311279c87")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit linux package
			set(md5sum "d51cddf52b2e44dde353569466d9429b")
		else(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 32bit linux package
			set(md5sum "24ef5becbd6ec5173f958dde34cda569")
		endif(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
	endif()
	# Download prebuilt package from the repository
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
