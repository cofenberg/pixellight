##################################################
## Linux/GCC platform definitions
##
## This file contains variables and macros that can be used when you build your project for
## Linux using the GCC compiler framework. It contains e.g. default compiler and linker settings
## and provides variables for important libraries a.s.o.
##################################################


##################################################
## Libraries 
##################################################

# X11 libraries
set(LINUX_X11_LIBS
	X11														# X-Lib
	Xext													# X extentions library
	Xcursor													# X cursor library
)
set(LINUX_X11_LIB		X11)								# X-Lib
set(LINUX_XEXT_LIB		Xext)								# X extentions library
set(LINUX_XCURSOR_LIB	Xcursor)							# X cursor library


##################################################
## Preprocessor definitions 
##################################################

# Preprocessor definitions
set(LINUX_COMPILE_DEFS
	LINUX													# Linux system
	GCC														# We are using the gcc/g++ compiler
	PIC														# Position-independent code
	_REENTRANT												# Reentrant code
)
if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug 
	##################################################
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		_DEBUG												# Debug build
	)
else()
	##################################################
	## Release 
	##################################################
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		NDEBUG												# Release build
	)
endif()


##################################################
## Compiler flags 
##################################################

# Compiler flags
set(LINUX_COMPILE_FLAGS
	-pthread												# Use pthreads
	-fno-rtti												# No C++ RTTI
	-fno-exceptions											# No C++ exception handling
	-pipe													# Use Pipes
	-O3														# Very aggressive transformations (long compile times, but usally best runtime performance!)
	-msse3													# Use SSE3 instruction set
	# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
	-fomit-frame-pointer									# Don't keep the frame pointer in a register for functions that don't need one
	-funroll-all-loops										# Perform the optimization of loop unrolling
	-ffast-math												# Perform floating point transformations that may break IEEE/ISO rules regarding floating point arithmetic
	-fpeel-loops											# Peels the loops for that there is enough information that they do not roll much (from profile feedback)
	-ftree-vectorize										# Enable the vectorizer
	# The following flag usage is basing on information from http://software.intel.com/en-us/forums/showthread.php?t=66902
	--param max-unroll-times=4
)
if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug 
	##################################################
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-ggdb												# Use gdb debugger
		-g3													# Debug level 3
	)
else()
	##################################################
	## Release 
	##################################################
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
	)
endif()
