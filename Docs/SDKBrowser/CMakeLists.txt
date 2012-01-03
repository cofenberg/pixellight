#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
cmaketools_doc_project(SDKBrowser)

##################################################
## Prerequisites
##################################################

# Create title file used within the PixelLight SDK browser
configure_file("${CMAKE_SOURCE_DIR}/Docs/SDKBrowser/index.html.in" "${CMAKE_SOURCE_DIR}/Docs/SDKBrowser/index.html")

##################################################
## Html help compiler
##################################################
cmaketools_add_chm_document(${CMAKETOOLS_CURRENT_TARGET} index.hhp)

##################################################
## Dependencies
##################################################
add_dependencies(Docs Docs-SDKBrowser)

##################################################
## Post-Build
##################################################

# CHM
add_custom_command(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_CHM} ${PL_BIN_DIR}
)

##################################################
## Install
##################################################

# CHM
install(FILES ${CMAKETOOLS_CURRENT_TARGET_CHM}
	DESTINATION ${PL_INSTALL_ROOT}		COMPONENT Docs
)
