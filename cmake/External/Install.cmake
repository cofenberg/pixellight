#*********************************************************#
#*  File: Install.cmake                                  *
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
## CMakeTools externals - Install script
##
## Base for 'install'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## MACRO: external_install_pack
##
## Pack the result of the 'install'-script
##################################################
macro(external_install_pack)
	# Pack tar archive
	external_pack_tar(TARGZ "${CMAKETOOLS_CURRENT_EXT_DIR}/${CMAKETOOLS_CURRENT_NAME}.tar.gz" "${CMAKETOOLS_CURRENT_DEST_DIR}")
endmacro(external_install_pack)

##################################################
## MACRO: external_install_done
##
## Mark the end of a 'install'-script
##################################################
macro(external_install_done)
	# Create 'done'-file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done "done")
endmacro(external_install_done)


##################################################
## Default actions
##################################################

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Install.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")

# Create include and lib directories
file(MAKE_DIRECTORY ${CMAKETOOLS_CURRENT_INCLUDE_DIR})
file(MAKE_DIRECTORY ${CMAKETOOLS_CURRENT_LIB_DIR})
