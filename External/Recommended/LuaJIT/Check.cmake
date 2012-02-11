#*********************************************************#
#*  File: Check.cmake                                    *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
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
			set(md5sum "832b7e1d03c77922f2136ef3948442d6")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "26ac76bc51c9e902de53b0d5787d10da")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package [TODO]
			set(md5sum "")
		else()
			# md5sum of the 32bit armeabi package [TODO]
			set(md5sum "")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package [TODO]
			set(md5sum "")
		else()
			# md5sum of the 32bit Linux package [TODO]
			set(md5sum "")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/lua51.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/lua51.dll" ${PL_RUNTIME_BIN_DIR})		# Bin-Windows
	endif()
endif()

# Done
external_check_done()
