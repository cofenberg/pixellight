##################################################
## Linux/Common platform definitions
##
## This file contains variables and macros that can be used when you build
## your project for Linux (either with GCC or Clang)
## It contains e.g. default compiler and linker settings (common to GCC and Clang)
## and provides variables for important libraries a.s.o.
##################################################


##################################################
## Libraries
##################################################

# X11 libraries
set(LINUX_X11_LIBS
	X11									# X-Lib
	Xext								# X extentions library
	Xcursor								# X cursor library
)
set(LINUX_X11_LIB		X11)			# X-Lib
set(LINUX_XEXT_LIB		Xext)			# X extentions library
set(LINUX_XCURSOR_LIB	Xcursor)		# X cursor library


##################################################
## Preprocessor definitions
##################################################

# Preprocessor definitions
set(LINUX_COMPILE_DEFS
	LINUX								# Linux system
	PIC									# Position-independent code
	_REENTRANT							# Reentrant code
)

if((NOT CMAKETOOLS_TARGET_BITSIZE MATCHES 32) AND (CMAKE_SIZEOF_VOID_P MATCHES 8))
	message(STATUS "Setting x64 build preprocessor definitions")
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		X64_ARCHITECTURE				# We are building for a 64Bit architecture
	)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug
	##################################################
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		_DEBUG							# Debug build
	)
else()
	##################################################
	## Release
	##################################################
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		NDEBUG							# Release build
	)
endif()


##################################################
## Compiler flags
##################################################

# Check if an 32Bit build should be made on an 64Bit host (CMAKE_SIZEOF_VOID_P has the value 8 on 64Bit Systems at least on x86 systems)
if((CMAKETOOLS_TARGET_BITSIZE MATCHES 32) AND (CMAKE_SIZEOF_VOID_P MATCHES 8))
	message(STATUS "Add compiler flags for 32Bit on 64Bit host")
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-m32
	)
endif()

# Compiler flags
set(LINUX_COMPILE_FLAGS
	${LINUX_COMPILE_FLAGS}
	-std=c++0x							# Enable experimental support for the upcoming ISO C++ standard C++0x (see http://gcc.gnu.org/gcc-4.6/cxx0x_status.html)
	-pthread							# Use pthreads
	-ffor-scope							# If -ffor-scope is specified, the scope of variables declared in a for-init-statement is limited to the `for' loop itself, as specified by the C++ standard
	-fno-rtti							# No C++ RTTI
	-fno-exceptions						# No C++ exception handling
	-pipe								# Use Pipes
	-msse3								# Use SSE3 instruction set / code might not run on CPUs with no sse3 instruction
	# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
	-ffast-math							# Perform floating point transformations that may break IEEE/ISO rules regarding floating point arithmetic
	# Some dialect-options of gcc: http://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
	-Wnon-virtual-dtor					# Warn when a class has virtual functions and accessible non-virtual destructor, in which case it would be possible but unsafe to delete an instance of a derived class through a pointer to the base class. This warning is also enabled if -Weffc++ is specified.
	-Wreorder							# Warn when the order of member initializers given in the code does not match the order in which they must be executed
	-Wsign-promo						# Warn when overload resolution chooses a promotion from unsigned or enumerated type to a signed type, over a conversion to an unsigned type of the same size
#	-Wold-style-cast					# Warn if an old-style (C-style) cast is used - just set it to look for c-style casts because some used libs produce c-style warnings and we can't change that
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug 
	##################################################
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-ggdb							# Use gdb debugger
		-g3								# Debug level 3
	)
else()
	##################################################
	## Release
	##################################################
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-O3								# Very aggressive transformations (long compile times, but usally best runtime performance!)
		# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
		-fomit-frame-pointer			# Don't keep the frame pointer in a register for functions that don't need one
	)
	
endif()


##################################################
## Linker flags
##################################################

# Check if an 32Bit build should be made on an 64Bit host (CMAKE_SIZEOF_VOID_P has the value 8 on 64Bit Systems at least on x86 systems)
if((CMAKETOOLS_TARGET_BITSIZE MATCHES 32) AND (CMAKE_SIZEOF_VOID_P MATCHES 8))
	message(STATUS "Add linker flags for 32Bit on 64Bit host")
	set(LINUX_LINKER_FLAGS
		${LINUX_LINKER_FLAGS}
		-m32
	)
endif()

# Linker flags
set(LINUX_LINKER_FLAGS
	${LINUX_LINKER_FLAGS}
	-Wl,--as-needed						# Quote from http://www.gentoo.org/proj/en/qa/asneeded.xml : "The flag tells the linker to link in the produced binary only the libraries containing symbols actually used by the binary itself"
)
