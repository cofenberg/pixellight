#*********************************************************#
#*  File: Check.cmake                                    *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
			set(md5sum "ce29006e5f0e2967094426a1d68f4b05")
		else()
			# md5sum of the 32bit Windows package
			set(md5sum "6a261e49e7f699a549ad0a8816070a8c")
		endif()
	elseif(ANDROID)
		if(ARMEABI_V7A)
			# md5sum of the 32bit armeabi-v7a package
			set(md5sum "64640b742ab1846ab5a7529e9173e315")
		else()
			# md5sum of the 32bit armeabi package
			set(md5sum "e19e56d701f6e21a5a47d8e0d51b3b6d")
		endif()
	elseif(LINUX)
		if(CMAKETOOLS_TARGET_BITSIZE MATCHES "64")
			# md5sum of the 64bit Linux package
			set(md5sum "1792f25047faed90f7a11da95f0162ee")
		else()
			# md5sum of the 32bit Linux package
			set(md5sum "f57d7a310f0298e2e2083ffa199c4ed6")
		endif()
	endif()
	external_check_download("" ${md5sum})

	# Unpack the package
	external_check_unpack()

	# For Windows, copy the required dlls into the runtime directory
	if(WIN32)
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_GITDIR})	# Bin
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/bin/newton.dll" ${PL_RUNTIME_BIN_DIR})	# Bin-Windows
	endif()
endif()

# Done
external_check_done()
