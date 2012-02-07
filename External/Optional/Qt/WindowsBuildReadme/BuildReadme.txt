Qt 4.8.0 - but only the parts really required for this project because Qt is huge and we only need a small portion of it
-> Shared libraries build for x86 and x64 Visual Studio 2010


Building Qt on MS Windows for Visual Studio 2010
	x86
	1. Copy "build_dll_x86.bat" into your Qt directory (e.g. "C:\Qt\4.8.0")
	2. To make the 32-bit build of Qt, go to Visual Studio 2010->Visual Studio tools in the start menu and click on "Visual Studio Command Prompt (2010)" and change into your Qt directory (e.g. "C:\Qt\4.8.0")
	3. Type "build_dll_x86.bat" within the "Visual Studio Command Prompt (2010)"
	4. ... go for a long walk while compiling...

	x64
	1. Copy "build_dll_x64.bat" into your Qt directory (e.g. "C:\Qt\4.8.0")
	2. To make the 64-bit build of Qt, go to Visual Studio 2010->Visual Studio tools in the start menu and click on "Visual Studio x64 Win64 Command Prompt (2010)" and change into your Qt directory (e.g. "C:\Qt\4.8.0")
	3. Type "build_dll_x64.bat" within the "Visual Studio x64 Win64 Command Prompt (2010)"
	4. ... go for a long walk while compiling...

	Configurated Qt include files
	- The official Qt include files redirect to files within another directory
	- In case you only want to have one include files directory, add a prefix path by using "-prefix <path>" within "configure" inside "build_dll_x86.bat" or "build_dll_x64.bat" (e.g. "configure -prefix "C:\Qt" ...")
	- When the build is complete, type "nmake install"


Qt 4.8.0 issues:
- When runnig "build_dll_x86.bat"/"build_dll_x64.bat" and getting "NMAKE : fatal error U1064: MAKEFILE not found and no target specified"
  Check whether or not there's also the error message "Perl not found in environment - cannot run syncqt.". If the error message is there, you have two options:
  1. Delete/Rename "bin/syncqt" and "bin/syncqt.bat" within your Qt directory *the easy way*
  2. Download and install Perl from ActivePerl (http://www.activestate.com/activeperl/downloads), close and open the command prompt, again
