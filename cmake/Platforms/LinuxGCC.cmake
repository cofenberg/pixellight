##################################################
## Linux/GCC platform definitions
##
## This file contains compiler and linker settings which are specific to the GCC compiler suit under linux
##################################################

##################################################
## Preprocessor definitions 
##################################################

# Preprocessor definitions
set(LINUX_COMPILE_DEFS
	${LINUX_COMPILE_DEFS}
	GCC														# We are using the gcc/g++ compiler
)

##################################################
## Compiler flags 
##################################################

set(LINUX_COMPILE_FLAGS
	${LINUX_COMPILE_FLAGS}
	-Wstrict-null-sentinel									# Warn also about the use of an uncasted NULL as sentinel
)

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-funroll-all-loops									# Perform the optimization of loop unrolling
		-fpeel-loops										# Peels the loops for that there is enough information that they do not roll much (from profile feedback)
		-ftree-vectorize									# Enable the vectorizer
		# The following flag usage is basing on information from http://software.intel.com/en-us/forums/showthread.php?t=66902
		--param max-unroll-times=4
	)
endif()
