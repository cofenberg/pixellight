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
			set(md5sum "73f431107b157b35aab635956012f036")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "b044bd4da6ce6e4e315710d706da85a9")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "5f96e4e4c1e2e762fbb1af9ef6703049")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "046ab2ac72678d950ef46292f6d23e52")
		endif()
	elseif(APPLE)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Apple package
			set(md5sum "dd63f352e657f6c756bc535e34949cc6")
		else()
			# md5sum of the 32bit Apple package
			set(md5sum "5f33aade0834421e3dce3313a3dc276c")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "d1c286c90dce11f79c131e3b6ceb199d")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "f2fb04d440974fb02a916ca0a238f8c5")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
