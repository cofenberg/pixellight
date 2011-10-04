Qt 4.7.0 - but only the parts really required for this project because Qt is huge and we only need a small portion of it
-> Shared libraries build for x86 and x64 Visual Studio 2010


Building Qt on MS Windows for Visual Studio 2010
	x86
	1. Copy "build_dll_x86.bat" into your Qt directory (e.g. "C:\Qt\4.7.0")
	2. Copy "qtvars.bat" into your Qt directory (e.g. "C:\Qt\4.7.0\bin\" - "Qt command prompt" is now using VC 2010 instead of VC 2008)
	3. Open "Qt command prompt" (e.g. from the Windows start menu)
	4. Type "build_dll_x86.bat" within the "Qt command prompt" (the current directory should already be e.g. "C:\Qt\4.7.0")
	5. ... go for a long walk while compiling...

	x64 (http://en.wikibooks.org/wiki/Opticks_Developer_Guide/Getting_Started/Building_Qt_From_Source)
	1. Copy "build_dll_x64.bat" into your Qt directory (e.g. "C:\Qt\4.7.0")
	2. To make the 64-bit build of Qt, go to Visual Studio 2010->Visual Studio tools in the start menu and click on Visual Studio 2010 x64 Win64 Command Prompt and change into your Qt directory (e.g. "C:\Qt\4.7.0")
	3. Type "build_dll_x64.bat" within the "Visual Studio 2010 x64 Win64 Command Prompt"
	4. ... go for a long walk while compiling...

	Configurated Qt include files
	- The official Qt include files redirect to files within another directory
	- In case you only want to have one include files directory, add a prefix path by using "-prefix <path>" within "configure" inside "build_dll_x86.bat" or "build_dll_x64.bat" (e.g. "configure -prefix "C:\Qt" ...")
	- When the build is complete, type "nmake install"
