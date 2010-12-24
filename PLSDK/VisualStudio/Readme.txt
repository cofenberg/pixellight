This directory contains two files for Microsoft Visual Studio that can make it easier
to debug PixelLight applications using Microsoft Visual Studio. Those files contain settings
for the MSVC debugger that allow it e.g. to directly display PixelLight data types
in the debugger or to avoid stepping into certain functions that are considered internal
to the API.


autoexp.dat
-----------
Contains rules on how to display custom data types in the debugger.

Install (MSVC10):
- Copy 'autoexp.dat' to  'C:\Program Files\Microsoft Visual Studio 10\Common7\Packages\Debugger'

Description:
- Contains rules on how to display PixelLight data types, e.g. a PLGeneral::String will be displayed
  just as "<String>" (Length=<Length> Type=<Type>) instead of the class structure, in which you have
  to extend m_pStringBuffer in order to see the actual string content.
- Supported classes:
  - PLGeneral::String


VC.reg
------
Contains rules that exclude certain functions from "step into" while debugging.

Install:
- 'VC.reg' is a registry file, import it's content into the registry e.g. by "executing" the file or by
  using 'regedit.exe' and choosing "Import Registry File".

Description:
- When using "step into" while debugging your application, you automatically step into every function present
  in the current statement, including functions that you just intended to use but didn't want to debug them.
  E.g. when you have a function named 'Test', which you want to debug, and that functions takes a PLGeneral::String
  as an argument:
    Test("Hello")
  By "stepping into" this expression, the debugger will first jump into the constructor of PLGeneral::String,
  which is annoying if you just wanted to debug Test().
  The registry settings contained in this file exclude functions like those from the debugger.
- Supported classes:
  - PLGeneral::String
  - PLGeneral::Singleton
  - PLGeneral::MemoryManager and global operators new, new[], delete, delete[]
