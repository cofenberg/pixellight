#*********************************************************#
#*  File: Check.cmake                                    *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


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
			set(md5sum "60fef42d5933223a1c9cb64d175ed3cf")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "810b21ec9fb5c3978dd0a58f86961a16")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "eb6d6891881b8002883e3ecb46c35192")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "62fbecf35c8175b1aa73a8d712bb2d10")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "539fd5c63f385381cb216811b8c5b705")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "2b7bb23054d98ac564cbc864cb9008ce")
		endif()
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
