##################################################
## Project
##################################################
cmaketools_doc_project(DocSample)

##################################################
## Latex document
##################################################
cmaketools_add_dvi_document(${CMAKETOOLS_CURRENT_TARGET} DocSample.tex)

##################################################
## PDF document
##################################################
cmaketools_add_pdf_document(${CMAKETOOLS_CURRENT_TARGET} ${CMAKETOOLS_CURRENT_TARGET_DVI})

##################################################
## Dependencies
##################################################
add_dependencies(Docs Docs-DocSample)

##################################################
## Post-Build
##################################################

# PDF
#ADD_CUSTOM_COMMAND(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
#  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_PDF} "${PL_BIN_DIR}/Docs"
#)

##################################################
## Install
##################################################

# PDF
#install(FILES ${CMAKETOOLS_CURRENT_TARGET_PDF}
#	DESTINATION ${PL_INSTALL_DOCS}		COMPONENT Docs
#)
