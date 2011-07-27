##################################################
## Windows/MSVC platform definitions
##
## This file contains variables and macros that can be used when you build your project for
## Windows using the Microsoft Visual C++ compiler framework. It contains e.g. default
## compiler and linker settings and provides variables for important libraries a.s.o.
##################################################


##################################################
## Libraries
##################################################

# Standard libraries
set(WIN32_STANDARD_LIBS
	advapi32.lib						# Advanced Win32 API
	shell32.lib							# Shell API
	user32.lib							# User API
	Userenv.lib							# User environment and profiles API
)
set(WIN32_ADVAPI32_LIB	advapi32.lib)	# Advanced Win32 API
set(WIN32_SHELL32_LIB	shell32.lib)	# Shell API
set(WIN32_USER32_LIB	user32.lib)		# User API
set(WIN32_USERENV_LIB	userenv.lib)	# User environment and profiles API
set(WIN32_WINMM_LIB		winmm.lib)		# Windows multimedia API
set(WIN32_VFW32_LIB		vfw32.lib)		# Video for Windows API
set(WIN32_SETUPAPI_LIB	setupapi.lib)	# Setup API

# GDI libraries
set(WIN32_GDI_LIBS
	gdi32.lib							# GDI library
	gdiplus.lib							# GDI+ library
	msimg32.lib							# GDI img32 library
)
set(WIN32_GDI32_LIB		gdi32.lib)		# GDI library
set(WIN32_GDIPLUS_LIB	gdiplus.lib)	# GDI+ library
set(WIN32_MSIMG32_LIB	msimg32.lib)	# GDI img32 library

# Common controls
set(WIN32_COMCTL32_LIB	comctl32.lib)	# Common controls
set(WIN32_COMDLG32_LIB	comdlg32.lib)	# Common dialogs

# Network libraries
set(WIN32_WSOCK32_LIB	wsock32.lib)	# Winsock library
set(WIN32_WS2_32_LIB	ws2_32.lib)		# Winsock2 library

# OpenGL
set(WIN32_OPENGL32_LIB	opengl32.lib)	# OpenGL library
set(WIN32_GLU32_LIB		glu32.lib)		# GLU library


##################################################
## Preprocessor definitions
##################################################
set(WIN32_COMPILE_DEFS
	WIN32								# Windows system
	UNICODE								# Use unicode
	_UNICODE							# Use unicode
	_CRT_SECURE_NO_DEPRECATE			# Disable CRT deprecation warnings
)

if((NOT CMAKETOOLS_TARGET_BITSIZE MATCHES 32) AND (CMAKE_SIZEOF_VOID_P MATCHES 8))
	message(STATUS "Setting x64 build preprocessor definitions")
	set(WIN32_COMPILE_DEFS
		${WIN32_COMPILE_DEFS}
		X64_ARCHITECTURE				# We are building for a 64Bit architecture
	)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug
	##################################################
	set(WIN32_COMPILE_DEFS
		${WIN32_COMPILE_DEFS}
		_DEBUG							# Debug build
	)
else()
	##################################################
	## Release
	##################################################
	set(WIN32_COMPILE_DEFS
		${WIN32_COMPILE_DEFS}
		NDEBUG							# Release build
	)
endif()


##################################################
## Compiler flags
##################################################
set(WIN32_COMPILE_FLAGS
	/nologo								# No logo
	/Zc:wchar_t							# Treat wchar_t as built-in type: Yes
	/Zc:forScope						# Force Conformance In For Loop Scope: Yes
	/GR-								# Disable RTTI
	/Zi									# Debug information Format: Program Database
	/MP									# Multi-processor Compilation
	/fp:precise							# Floating Point Model: Precise
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug
	##################################################
	set(WIN32_COMPILE_FLAGS
		${WIN32_COMPILE_FLAGS}
		/W4								# Warn level 4
		/MDd							# Runtime Library: Multithreaded Debug DLL
		/Od								# Optimization: none
		/RTC1							# Runtime error checks
	)
else()
	##################################################
	## Release
	##################################################
	set(WIN32_COMPILE_FLAGS
		${WIN32_COMPILE_FLAGS}
		/W3								# Warn level 3
		/MD								# Runtime Library: Multithreaded DLL
		/Ox								# Optimization: Full Optimization 
		/Ob2							# Inline Function Expansion: Any Suitable
		/Oi 							# Enable Intrinsic Functions: Yes
		/Ot 							# Favor Size or Speed: Favor Fast Code
		/Oy 							# Omit Frame Pointers: Yes
		/GL				 				# Whole Program Optimization: Enable link-time code generation
		/GF								# Enable String Pooling
		/GS-							# Buffer Security Check: No 
		/arch:SSE2						# Enable Enhanced Instruction Set: Streaming SIMD Extensions 2
	)
endif()


##################################################
## Linker flags
##################################################
set(WIN32_LINKER_FLAGS
	/NOLOGO								# Suppress logo
	/INCREMENTAL:NO						# Enable Incremental Linking: No
	/MANIFEST							# Generate Manifest: Yes
	/NXCOMPAT							# Data Execution Prevention (DEP): Image is compatible with DEP
	/DYNAMICBASE:NO						# Randomized Base Address: Disable Image Randomization
)
if(CMAKE_BUILD_TYPE MATCHES Debug)
	##################################################
	## Debug
	##################################################
	set(WIN32_LINKER_FLAGS
		${WIN32_LINKER_FLAGS}
		/DEBUG							# Create debug info
	)
else()
	##################################################
	## Release
	##################################################
	set(WIN32_LINKER_FLAGS
		${WIN32_LINKER_FLAGS}
		/OPT:REF						# References: Eliminate Unreferenced Data
		/OPT:ICF						# Enable COMDAT Folding: Remove Redundant COMDATs
		/LTCG							# Link Time Code Generation: Use Link Time Code Generation
		/DELAY:UNLOAD					# Delay Loaded DLL: Support Unload
	)
endif()
