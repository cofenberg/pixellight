##################################################
## Project
##################################################
cmaketools_doc_project(PLMath)

##################################################
## Latex document
##################################################
cmaketools_add_dvi_document(${CMAKETOOLS_CURRENT_TARGET} PLMath.tex)

##################################################
## PDF document
##################################################
cmaketools_add_pdf_document(${CMAKETOOLS_CURRENT_TARGET} ${CMAKETOOLS_CURRENT_TARGET_DVI})

##################################################
## Dependencies
##################################################
add_dependencies(Docs Docs-PLMath)

##################################################
## Post-Build
##################################################

# PDF
add_custom_command(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_PDF} "${PL_BIN_DIR}/Doc"
)

##################################################
## Install
##################################################

# PDF
install(FILES ${CMAKETOOLS_CURRENT_TARGET_PDF}
	DESTINATION ${PL_INSTALL_DOC}		COMPONENT Docs
)
