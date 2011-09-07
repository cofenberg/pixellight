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
			set(md5sum "56fdb8bdfdb52bc6c3fd7a4f2b0cf1ea")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "87932dda81921c3b380e274efeccb070")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "f41437f5b1306fd809fb91fcac229a4b")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "a8159a07bb5ef50ee3d775ae99c78e4d")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "8ceabcbbc494dbf0239a4919a779bbbf")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "142d670f6da135f48aa32c24bcea1521")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
