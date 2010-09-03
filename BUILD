/*********************************************************\
 *  File: BUILD                                          *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


This document describes how to build PixelLight from the sources.


1. Windows
----------

If you want to build PixelLight on Windows, you have two choices:
- Use the provided Visual Studio solutions to build the engine
- Use the cmake based build system

If you want to create SDK packages or documentation or intend to e.g. use the mingw compiler or something
like that, stick to the CMake path.

If you want to build only a local version of PixelLight but do not intend to create documentations or SDK packes,
you can just use the MSVC solutions files which are much easier to use. Note however, that you need to install
the needed external packages first (see below).


1.1.  MSVC solutions
--------------------

1.1.1 External packages
-----------------------

In order to build the PixelLight engine with MSVC, all the external packages used by the engine need to be in the
right place for the build. Have a look at the 'External' directory, there you can find a readme file for every library,
that describes what files are needed. 

You can find the libraries pre-packed in the files-section on our homepage: http://dev.pixellight.org/files/externals/.
Unfortunately, we can't provide some of those libraries due to their licensing terms. Have a look at the according
Readme.txt to determine where to obtain those libraries and where to put the resulting files into your source tree.

The library packages must be unpacked and need to be at the right position for your specific build type, e.g. on Windows
and 32 Bit, put everything into the directory 'External\_Windows_x86_32'.

The easiest way to install at least the public packages is to use the CMake based build and make the project "External"
(see next section). This will download and unpack all public externals for you in the right directory. The non-public
externals must still be installed manually.


1.1.2 Build
-----------

Open the solution 'pixellight.sln' with Microsoft Visual Studio, which includes all projects of the PixelLight framework.

Then start 'Build'.


1.2.  CMake
-----------

1.2.1. Prerequisites
--------------------

Here's a list of required programs that you need to fully build the SDK on Windows. 
- cmake-2.8.2-win32-x86.exe (http://www.cmake.org)
	- Cross platform build tool used to build the SDK

- nsis-2.46-setup.exe
	- Used to create the Windows installer

- doxygen-1.7.1-setup.exe
	- Doxygen (http://www.doxygen.org)
	- Used to create the code documentations.

- graphviz-2.26.3.msi
	- Graphviz (http://www.graphviz.org)
	  Used from Doxygen to create diagrams.
	- Ensure that the Graphviz binaries directory is correctly set in the PATH and/or DOT_PATH environment variables,
	  otherwise Doxygen can't find Graphviz and as a result there will be no graphs within the generated document.

- htmlhelp.exe
	- MS HTML Help Workshop (http://msdn.microsoft.com/library/default.asp?url=/library/en-us/htmlhelp/html/hwMicrosoftHTMLHelpDownloads.asp)
	  Used to create chm documentations from the html help files created by Doxygen.
	-> The Doxygen files refer to "htmlhelp/hhc.exe" inside this directory, therefore the unpacked exe is also in the repository

- "UsedTools\sfk\sfk.exe" (http://sourceforge.net/projects/swissfileknife/)
	- "Swiss File Knife": file management, search, text processing
	- Directly used by the CMake scripts

- "UsedTools\diff"-directory
	- Some diff binaries directly used by the CMake scripts


1.2.2. Create MSVC solutions and build
--------------------------------------

Here's how to compile PixelLight by using the CMake-GUI:

- Start "CMake (cmake-gui)"

- "Where is the source code"-field: e.g. "C:\PixelLight"

- "Where to build the binaries"-field: e.g. "C:\PixelLight\build-Release"

- Configure

- Choose the generator, for instance "Visual Studio 9 2008"

- Generate

- Open "build-Release/PixelLight.sln" with Microsoft Visual Studio

- To build the documentation, choose "Docs"

- To create a PixelLight SDK, choose "Pack-SDK", please note that you are free to compile projects individually as well


2. Linux
----------

To build PixelLight on linux, use the CMake based (www.cmake.org) cross-platform build system of PixelLight.


2.1.  Prerequisites
-------------------

You need to install certain dependencies on your system that are needed build PixelLight,
including build tools and used development libraries.

The following package list applies to the linux distribution "Ubuntu 10.04 - Lucid Lynx".
If you use another distribution, please have a look at their package repository to find out which
packages you need (in most cases, the package names will not be that different).  

The following packages are required in order to be able to compile everything (Ubuntu):
- build-essential (GNU C++ compiler and other important build tools)
- git-core (version control)
- cmake (build tool)
- doxygen (required to compile the automatic code documentation)
- graphviz (required to create the diagrams of the automatic code documentation)
- texlive (LaTeX system for compiling the documentation)
- texlive-science (LaTeX package for compiling the documentation)
- texlive-latex-extra (LaTeX package for compiling the documentation)
- libncurses5-dev (required by PLGeneral)
- libzip-dev (required by libpng used by PLGraphics)
- libxcursor-dev (required by PLGui)
- libxext-dev (required by PLGui)
- libdbus-1-dev (required by PLInput)
- libxxf86vm-dev (required by PLRendererOpenGL)
- libglu1-mesa-dev (required by PLRendererOpenGL)

To install all required packages at once, just use:

  apt-get install build-essential git-core cmake doxygen graphviz texlive texlive-science texlive-latex-extra libncurses5-dev libzip-dev libxcursor-dev libxext-dev libdbus-1-dev libxxf86vm-dev libglu1-mesa-dev

When using the maketool flag '--syslibs', you also need the following packages:
- libpcre3-de (required by PLGeneral)
- libjpeg62-dev (required by PLGraphics)
- libpng12-dev (required by PLGraphics)
- libfreetype6-dev (required by PLRendererOpenGL and PLRendererOpenGLES)
- nvidia-cg-toolkit (required by PLRendererOpenGL - >= Cg Toookit 3.0 - July 2010 required)
	- "nvidia-cg-toolkit" may be out-of-date, install a newer Cg SDK: http://developer.download.nvidia.com/cg/Cg_3.0/Cg-3.0_July2010_x86.deb
- libopenal-dev (required by PLSoundOpenAL)
- libogg-dev (PLSoundOpenAL)
- libvorbis-dev (PLSoundOpenAL)
To install all required packages at once, just use:

  apt-get install libpcre3-de libjpeg62-dev libpng12-dev libfreetype6-dev libopenal-dev libogg-dev libvorbis-dev


2.2.  Maketool
--------------

The shell script "maketool" performs the required build steps automatically.

After cloning the git repository, you first have to call
  chmod +x maketool
in order to make the script executable.

To generate the project files just call
  ./maketool setup [--release] [--syslibs]

On linux, it is generally recommended to use the flag '--syslibs', this will cause the build system to use
and depend on the libraries found on your system, rather than using our own externals.

After the project files were generated, the project can be compiled by writing
  ./maketool build [--release]

Here's a list of the most important "maketool"-commands:
- Create project files:		 		./maketool setup
- Compile the project:				./maketool build
- Compile the documentation:		./maketool doc
- Generate an installable package:	./maketool pack
- Delete the build directories:		./maketool clean

Here's a list of the most important "maketool"-options:
--debug:			Create a debug version (default)
--release:			Create a release version
--suffix <suffix>:	Add a suffix to all library names
--externals:		Repository URL were to download the packages with the external dependencies from (e.g. "developer.pixellight.org/files/externals")
--username:			User name for access to restricted packages within the repository
--password:			User password for access to restricted packages within the repository
--arch:				Architecture (e.g. "x86")
--bitsize:			Bit size (e.g. "32" or "64")
--syslibs:			Use system libs
--minimal:			Do only compile the most important projects

To avoid setting the parameters "--externals", "--username" and "--password" over and over again:
- Within the home directory, create a file called "pl_config.cfg" (Perl-Script, included and just executed) with the following content:
	$pl_external_url = "";
	$pl_external_user = "";
	$pl_external_pass = "";


1.1.1 External packages
-----------------------

Just as with the Windows build, it is necessary to obtain all the external packages used by the engine and install
them in the right place for the build. Have a look at the 'External' directory, there you find a readme file for every
library that describes what files are needed. 

You can find the libraries pre-packed in our files-section on our homepage: http://dev.pixellight.org/files/externals/.
Unfortunately, we can't provide some of those libraries due to their licensing terms. Have a look at the according
Readme.txt to determine where to obtain those libraries and where to put the resulting files into your source tree.

The library packages need to be unpacked and at the right position for your specific build type, e.g. on Linux
and 32 Bit, put everything in the directory 'External\_Linux_x86_32'.

The cmake based build will try to download the needed packages automatically from our homepage when you build a project
that depends on an external. This will download and unpack all public externals for you in the right directory. The non-public
externals must still be installed manually. You should also use the maketool flag '--syslibs' to use the libraries installed
on your system rather than our own external packages whenever that is possible (however, not all externals can be used
that way).


2.3.  Build
-----------

To build PixelLight, either use maketool to do everything automatically:
  ./maketool build [--release]

Or change into the build-directory for your configuration (e.g. 'build-Debug' or 'build-Release') and run make yourself:
  cd build-Release
  make

The latter option has the advantage that you can also build individual projects rather than only the whole SDK.
To build projects individually, change into the "build-Debug" or "build-Release" directory and type
  make <project name>
  (for example: "make PLEngine")

In order to use make options, change into the "build-Debug" or "build-Release" directory and type for example
  make -j 4
  (to "make all" projects using 4 CPU cores to speed up the make process)


2.4.  Create documentation and packages
---------------------------------------

To create the documentation, build project 'Docs':
  cd build-Release
  make Docs

Or use maketool to do it for you:
  ./maketool doc


The create the PixelLight SDK and create a debian installation file, build project 'Pack':
  cd build-Release
  make Pack

Or use maketool to do it for you:
  ./maketool pack


2.5.  Running from a local build and installing
-----------------------------------------------

Once you have built PixelLight, you may want to run e.g. the samples or demo applications.
In order for this to work correctly, PixelLight must know where to search for data files and plugins, which is not
always an easy task on linux systems.


You have several options here:

1. Run from a your local source directory.

This means that everything stays in your source directory. All libraries and apps have already been copied
into the directory 'Bin-Linux' by means of post-build commands.

Now you only have to tell PixelLight where it can find the runtime and data files. This can be done by setting
the environment variable PL_RUNTIME to the 'Runtime' directory.

If you're in the root of the source tree, you can use the script 'profile' to do this for you:
  source ./profile
  (sets the environment variable "PL_RUNTIME")

To inspect the content of PL_RUNTIME, call
  echo $PL_RUNTIME

To delete the environment variable PL_RUNTIME, call
  unset PL_RUNTIME

Of course you can also set this variable e.g. inside your profile or bash-scripts so that they are always available.

2. Install the PixelLight SDK locally

Installing means copying the files built by the project into your local linux system so that the libraries and apps
can be found there. The cmake build script therefore provides you with an 'install' target that installs everything
on your local machine into the '/usr/local' directory.

Change into the build directory, e.g.:
  cd build-Release

Install: (This has to be done as root! Use e.g. sudo or su for this task)
  make install

Update libraries: (This has to be done as root! Use e.g. sudo or su for this task)
  ldconfig /usr/local/lib
  (if this is not done, new dynamic libs may not be found correctly)

If you used this way, you will find the PixelLight runtime in /usr/local/share/pixellight/Runtime,
and the demos e.g. in /usr/local/share/pixellight/Demos.


Now you should be able to run the applications built by the PixelLight project, e.g. run one of the samples:

  cd Bin-Linux/Demos
  ./PLDemoRendererTriangle
