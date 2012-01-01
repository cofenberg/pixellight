#*********************************************************#
#*  File: CMakeTools_Docs.cmake                          *
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
## CMakeTools documentations
##
## These macros can be used to build documentation
## projects, e.g. with LaTeX and Windows Help Compiler
##################################################


##################################################
## MACRO: cmaketools_doc_project
##
## Define a documentation project
##   name		name of the project (e.g. "TestProject")
##################################################
macro(cmaketools_doc_project name)
	# Begin project
	project(Docs-${name})

	# Set project variables
	set(CMAKETOOLS_CURRENT_PROJECT ${name})
	set(CMAKETOOLS_CURRENT_TARGET  ${name})
	set(CMAKETOOLS_CURRENT_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

	# Declare a target for the project
	add_custom_target(Docs-${CMAKETOOLS_CURRENT_TARGET})
endmacro(cmaketools_doc_project name)

##################################################
## MACRO: cmaketools_add_dvi_document
##
## Compile a .tex file into a .dvi document
##   target   Name of target
##   texfile  Filename of .tex file
##################################################
macro(cmaketools_add_dvi_document target texfile)
	# Set project variables
	set(CMAKETOOLS_CURRENT_TARGET_TEX ${texfile})
	set(CMAKETOOLS_CURRENT_TARGET_DVI ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${target}.dvi)

	# Check if LaTeX compiler is available
	if(LATEX_COMPILER)
		# Invoke LaTeX compiler (three times needed actually to get everything right)
		add_custom_command(
			OUTPUT				${CMAKETOOLS_CURRENT_TARGET_DVI}
			DEPENDS				${CMAKETOOLS_CURRENT_TARGET_TEX}
			WORKING_DIRECTORY	${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND				${LATEX_COMPILER}
			ARGS				-halt-on-error -quiet -output-directory=${CMAKETOOLS_CURRENT_OUTPUT_DIR} ${CMAKETOOLS_CURRENT_TARGET_TEX}
			COMMAND				${LATEX_COMPILER}
			ARGS				-halt-on-error -quiet -output-directory=${CMAKETOOLS_CURRENT_OUTPUT_DIR} ${CMAKETOOLS_CURRENT_TARGET_TEX}
			COMMAND				${LATEX_COMPILER}
			ARGS				-halt-on-error -quiet -output-directory=${CMAKETOOLS_CURRENT_OUTPUT_DIR} ${CMAKETOOLS_CURRENT_TARGET_TEX}
			COMMENT				"Compiling LaTeX: ${target}.dvi"
		)

		# Declare a target
		add_custom_target(Docs-${target}-DVI
			DEPENDS ${CMAKETOOLS_CURRENT_TARGET_DVI}
		)

		# Depend Docs-target on DVI-target
		add_dependencies(Docs-${CMAKETOOLS_CURRENT_TARGET} Docs-${target}-DVI)
	endif()
endmacro(cmaketools_add_dvi_document target texfile)

##################################################
## MACRO: cmaketools_add_pdf_document
##
## Compile a .dvi file into a .pdf document
##   target   Name of target
##   dvifile  Filename of .dvi file
##################################################
macro(cmaketools_add_pdf_document target dvifile)
	# Set project variables
	set(CMAKETOOLS_CURRENT_TARGET_DVI ${dvifile})
	set(CMAKETOOLS_CURRENT_TARGET_PDF ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${target}.pdf)

	# Check if LaTeX compiler and PDF converter are available
	if(LATEX_COMPILER AND DVIPDF_CONVERTER)
		# Invoke PDF converter
		add_custom_command( 
			OUTPUT				${CMAKETOOLS_CURRENT_TARGET_PDF}
			DEPENDS				${CMAKETOOLS_CURRENT_TARGET_DVI}
			WORKING_DIRECTORY	${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND				${DVIPDF_CONVERTER}
			ARGS				-o ${CMAKETOOLS_CURRENT_TARGET_PDF} ${CMAKETOOLS_CURRENT_TARGET_DVI}
			COMMENT				"Converting to pdf: ${target}.pdf"
		)

		# Declare a target
		add_custom_target(Docs-${target}-PDF
			DEPENDS ${CMAKETOOLS_CURRENT_TARGET_PDF}
		)

		# Depend Docs-target on PDF-target (which itself depends on the DVI-target)
		add_dependencies(Docs-${target}-PDF                Docs-${target}-DVI)
		add_dependencies(Docs-${CMAKETOOLS_CURRENT_TARGET} Docs-${target}-PDF)
	endif()
endmacro(cmaketools_add_pdf_document target name)

##################################################
## MACRO: cmaketools_add_doxygen_docs
##
## Generate a docygen documentation
##   target   Name of target
##   dvifile  Filename of doxygen configuration file
##################################################
macro(cmaketools_add_doxygen_docs target doxyfile)
	# Set project variables
	set(CMAKETOOLS_CURRENT_TARGET_DOXYFILE ${doxyfile})
	set(CMAKETOOLS_CURRENT_TARGET_HHP  ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/html/index.hhp)
	set(CMAKETOOLS_CURRENT_TARGET_DOXYFILE_CONF ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/doxyfile)

	# Check if doxygen is available
	if(DOXYGEN_FOUND)
		# Get filename and path of doxyfile
		get_filename_component(name ${doxyfile} NAME)
		get_filename_component(path ${doxyfile} PATH)
		if(NOT path)
			set(path ${CMAKE_CURRENT_SOURCE_DIR})
		endif()

		# Configure doxyfile (if it is a real doxyfile already, it should simply copy the file)
		set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKETOOLS_CURRENT_OUTPUT_DIR})
		configure_file(${CMAKETOOLS_CURRENT_TARGET_DOXYFILE} ${CMAKETOOLS_CURRENT_TARGET_DOXYFILE_CONF})

		# Invoke doxygen
		add_custom_command(
			OUTPUT				${CMAKETOOLS_CURRENT_TARGET_HHP}
			DEPENDS				${CMAKETOOLS_CURRENT_TARGET_DOXYFILE_CONF}
			WORKING_DIRECTORY	${path}
			COMMAND				${CMAKE_COMMAND} -E copy_directory ${path} ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/html
			COMMAND				${DOXYGEN} \"${CMAKETOOLS_CURRENT_TARGET_DOXYFILE_CONF}\"
			COMMENT				"Creating doxygen documentation for ${target}"
		)

		# Declare a target
		add_custom_target(Docs-${target}-Doxygen
			DEPENDS ${CMAKETOOLS_CURRENT_TARGET_HHP}
		)

		# Depend Docs-target on Doxygen-target
		add_dependencies(Docs-${CMAKETOOLS_CURRENT_TARGET} Docs-${target}-Doxygen)
	endif()
endmacro(cmaketools_add_doxygen_docs target doxyfile)

##################################################
## MACRO: cmaketools_add_chm_document
##
## Generate a HTML help file (.chm)
##   target   Name of target
##   dvifile  Filename of hhp configuration file
##################################################
macro(cmaketools_add_chm_document target hhpfile)
	# Check if HTML Help Compiler is available
	if(HTML_HELP_COMPILER)
		# Set project variables
		set(CMAKETOOLS_CURRENT_TARGET_HHP ${hhpfile})
		set(CMAKETOOLS_CURRENT_TARGET_CHM ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${target}.chm)

		# Get filename and path of HHP file
		get_filename_component(name ${hhpfile} NAME)
		get_filename_component(path ${hhpfile} PATH)
		if(NOT path)
			set(path ${CMAKE_CURRENT_SOURCE_DIR})
		endif()

		# Invoke hhc
		add_custom_command(
			OUTPUT				${CMAKETOOLS_CURRENT_TARGET_CHM}
			DEPENDS				${CMAKETOOLS_CURRENT_TARGET_HHP}
			WORKING_DIRECTORY	${CMAKETOOLS_CURRENT_OUTPUT_DIR}
			COMMAND				${CMAKE_COMMAND} -E copy_directory ${path} ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/tempchm
			COMMAND				${CMAKE_COMMAND} -DHTML_HELP_COMPILER:STRING=${HTML_HELP_COMPILER} -DSRC="${name}" -DDIR=${CMAKETOOLS_CURRENT_OUTPUT_DIR}/tempchm -P ${CMAKETOOLS_DIR}/Scripts/hhc.cmake
			COMMAND				${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/tempchm/${target}.chm ${CMAKETOOLS_CURRENT_OUTPUT_DIR}
			COMMAND				${CMAKE_COMMAND} -E remove_directory ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/tempchm
			COMMENT				"Creating chm file for ${target}"
		)

		# Declare a target
		add_custom_target(Docs-${target}-CHM
			DEPENDS ${CMAKETOOLS_CURRENT_TARGET_CHM}
		)

		# Depend Docs-target on CHM-target
		add_dependencies(Docs-${CMAKETOOLS_CURRENT_TARGET} Docs-${target}-CHM)
	endif()
endmacro(cmaketools_add_chm_document target htmlfile)


##################################################
## CMakeTools documentations initialization 
##################################################

# Search for LaTeX compiler
find_package(LATEX)

# Check if LaTeX has been found
message(STATUS "Looking for LaTeX...")
if(LATEX_COMPILER)
	message(STATUS "Looking for LaTeX... - found ${LATEX_COMPILER}")

	# Check if dvipdf has been found, but only if LaTeX has been found (avoid errors overkill within the log)
	message(STATUS "Looking for dvipdf...")
	if(DVIPDF_CONVERTER)
		message(STATUS "Looking for dvipdf... - found ${DVIPDF_CONVERTER}")
	else()
		message(STATUS "Looking for dvipdf... - NOT found")
	endif()
else()
	message(STATUS "Looking for LaTeX... - NOT found")
endif()

# Search for doxygen
find_package(Doxygen)

# Search for Html Help Compiler
find_package(HTMLHelp)

# Check if Microsoft Html Help Compiler (http://msdn.microsoft.com/en-us/library/ms669985) has been found
message(STATUS "Looking for Microsoft Html Help Compiler...")
if(HTML_HELP_COMPILER)
	message(STATUS "Looking for Microsoft Html Help Compiler... - found ${HTML_HELP_COMPILER}")
else()
	message(STATUS "Looking for Microsoft Html Help Compiler (http://msdn.microsoft.com/en-us/library/ms669985)... - NOT found")
endif()