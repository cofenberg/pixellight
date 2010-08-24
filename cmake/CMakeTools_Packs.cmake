##################################################
## CMakeTools packages
##
## These macros can be used to build packages
## of your project
##################################################


##################################################
## CMakeTools packages initialization 
##################################################

# Reset CPack configuration
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	set(CPACK_IGNORE_FILES "")
	set(CPACK_INSTALLED_DIRECTORIES "")
	set(CPACK_SOURCE_IGNORE_FILES "")
	set(CPACK_SOURCE_INSTALLED_DIRECTORIES "")
	set(CPACK_STRIP_FILES "")
	set(CPACK_SOURCE_TOPLEVEL_TAG "")
	set(CPACK_SOURCE_PACKAGE_FILE_NAME "")
endif()

# Find cpack executable
get_filename_component(CPACK_PATH ${CMAKE_COMMAND} PATH)
set(CPACK_COMMAND "${CPACK_PATH}/cpack")
