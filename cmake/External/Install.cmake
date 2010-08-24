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
