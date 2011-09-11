##################################################
## CheckGCC
##
## Additional checks for the GCC compiler
##
##
## Variables:
##   CMAKETOOLS_GCC_VISIBILITY_FLAG     Set if GCC has the visibility flag available (http://gcc.gnu.org/wiki/Visibility)
##################################################


##################################################
## Includes
##################################################
INCLUDE (CheckCXXSourceCompiles)


##################################################
## Macro: Check if GCC visibility flag is available
##################################################
macro(cmaketools_check_cxx_visibility_flag var)
   set(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
   set(CMAKE_REQUIRED_DEFINITIONS "-fvisibility=hidden -fvisibility-inlines-hidden")
   set(CODE "__attribute__ ((visibility(\"default\"))) void testfunc(){} int main() {return 0;}")
   check_cxx_source_compiles("${CODE}" ${var})
   set(CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
endmacro(cmaketools_check_cxx_visibility_flag)


##################################################
## Check GCC compatibilities
##################################################

# Check GCC visibility flag
if(CMAKE_COMPILER_IS_GNUCXX)
  cmaketools_check_cxx_visibility_flag(CMAKETOOLS_GCC_VISIBILITY_FLAG)
  if(CMAKETOOLS_GCC_VISIBILITY_FLAG)
    ADD_DEFINITIONS(-fvisibility=hidden -fvisibility-inlines-hidden -DHAVE_VISIBILITY_ATTR)
  endif()
endif(CMAKE_COMPILER_IS_GNUCXX)
