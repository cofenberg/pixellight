#*********************************************************#
#*  File: Check.cmake                                    *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
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
			set(md5sum "4ae1b4a79b3f8187c1dcec10dba70d70")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "eaab385d7c85136ae07cf6eb3832181e")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "6893ee174fd384dd2741f1826e728bff")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "e4fcfa036d57da0950db15772308ca41")
		endif()
	elseif(NACL)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# [TODO] md5sum of the 64bit NaCL package
			set(md5sum "e95d83ce7116d45c76d4313fa11d59e7")
		else()
			# [TODO] md5sum of the 32bit NaCL package
			set(md5sum "e95d83ce7116d45c76d4313fa11d59e7")
		endif()
	elseif(APPLE)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Apple package
			set(md5sum "4d57ddce9daf16ea5a9ce9f06aab51f2")
		else()
			# md5sum of the 32bit Apple package
			set(md5sum "6f6d911fa45f58ae072f295a7bcb8ddd")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "b095f242d078514870b9649cba209a12")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "4da23023d4f12193e9753be1e314924d")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()
endif()

# Done
external_check_done()
