#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
cmaketools_doc_project(PixelLightAPI)

##################################################
## Prerequisites
##################################################

# Create footer file used within the PixelLight API documentation
configure_file("${CMAKE_SOURCE_DIR}/Docs/PixelLightAPI/footer.html.in" "${CMAKE_SOURCE_DIR}/Docs/PixelLightAPI/footer.html")

##################################################
## Doxygen documentation
##################################################
cmaketools_add_doxygen_docs(${CMAKETOOLS_CURRENT_TARGET} doxyfile.in)

##################################################
## Html help compiler
##################################################
# The compressed PixelLight API document can only be build when the Microsoft Html Help Compiler (http://msdn.microsoft.com/en-us/library/ms669985) has been found by CMake,
# if CMake was unable to find it, ignore the following document in order to avoid confusing confusing errors when building the project.
# The following macro is internally checking for the "HTML_HELP_COMPILER"-variable and set's the "CMAKETOOLS_CURRENT_TARGET_CHM"-variable on success.
cmaketools_add_chm_document(${CMAKETOOLS_CURRENT_TARGET} ${CMAKETOOLS_CURRENT_TARGET_HHP})

##################################################
## Dependencies
##################################################
if(CMAKETOOLS_CURRENT_TARGET_CHM)
	add_dependencies(Docs-PixelLightAPI-CHM	Docs-PixelLightAPI-Doxygen)
endif()
add_dependencies(Docs						Docs-PixelLightAPI)

##################################################
## Post-Build
##################################################

# CHM
if(CMAKETOOLS_CURRENT_TARGET_CHM)
	add_custom_command(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_CHM} ${PL_DOCS_DIR}
	)
endif()

##################################################
## Install
##################################################

# CHM
if(CMAKETOOLS_CURRENT_TARGET_CHM)
	install(FILES ${CMAKETOOLS_CURRENT_TARGET_CHM}
		DESTINATION ${PL_INSTALL_DOCS}		COMPONENT Docs
	)
endif()
