"cmake\UsedTools\make\make.exe" (http://gnuwin32.sourceforge.net/packages/make.htm)
- "Make for Windows": Make: GNU make utility to maintain groups of programs
- Directly used by the CMake scripts under MS Windows when using the Android NDK toolchain
- This tool can't be set within a CMake file automatically, there are two options:
	- Add "<PixelLight root path>\cmake\UsedTools\make\" to the MS Windows PATH environment variable *recommended*
	- Use a MinGW installer from e.g. http://www.tdragon.net/recentgcc/ which can set the PATH environment variable *overkill because only the 171 KiB "make" is required*
	- Use CMake from inside a command prompt by typing for example ("DCMAKE_TOOLCHAIN_FILE" is only required when using a toolchain) *not really comfortable when working with it on a regular basis*
		cmake.exe -G"Unix Makefiles" -DCMAKE_MAKE_PROGRAM="<PixelLight root path>\cmake\UsedTools\make\make.exe" -DCMAKE_TOOLCHAIN_FILE="<PixelLight root path>\cmake\Toolchains\Toolchain-ndk.cmake"
