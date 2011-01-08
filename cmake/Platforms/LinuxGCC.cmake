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

# Check if an 32Bit build should be made on an 64Bit host (CMAKE_SIZEOF_VOID_P has the value 8 on 64Bit Systems at least on x86 systems )
if ((CMAKETOOLS_TARGET_BITSIZE MATCHES 32) AND (CMAKE_SIZEOF_VOID_P MATCHES 8))
	message(STATUS "Add compiler and linker flags for 32Bit on 64Bit host")
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-m32
	)
	
	set(LINUX_LINKER_FLAGS
		${LINUX_LINKER_FLAGS}
		-m32
	)
endif()

# Compiler flags
set(LINUX_COMPILE_FLAGS
	-pthread												# Use pthreads
	-fno-rtti												# No C++ RTTI
	-fno-exceptions											# No C++ exception handling
	-pipe													# Use Pipes
	-msse3													# Use SSE3 instruction set / code might not run on CPUs with no sse3 instruction
	# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
	-ffast-math												# Perform floating point transformations that may break IEEE/ISO rules regarding floating point arithmetic
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
		-O3														# Very aggressive transformations (long compile times, but usally best runtime performance!)
		# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
		-fomit-frame-pointer									# Don't keep the frame pointer in a register for functions that don't need one
		-funroll-all-loops										# Perform the optimization of loop unrolling
		-fpeel-loops											# Peels the loops for that there is enough information that they do not roll much (from profile feedback)
		-ftree-vectorize										# Enable the vectorizer
		# The following flag usage is basing on information from http://software.intel.com/en-us/forums/showthread.php?t=66902
		--param max-unroll-times=4
	)
endif()
