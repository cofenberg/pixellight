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
			set(md5sum "0adf1f5da70faf989e2277153396a05b")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "dd6db4f89fbad7159a94a1e311279c87")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "4586f5c56e6a7f7bf2b2d8a6c9edb5b4")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "fa004a27f3cf97d5f3cb46c3d0166198")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "d51cddf52b2e44dde353569466d9429b")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "24ef5becbd6ec5173f958dde34cda569")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
