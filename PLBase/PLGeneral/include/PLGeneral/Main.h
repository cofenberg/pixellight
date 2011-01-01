/*********************************************************\
 *  File: Main.h                                         *
 *      Platform independent main function. This header can ONLY be includes once per project!
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_MAIN_H__
#define __PLGENERAL_MAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/System/System.h"
#include "PLGeneral/Tools/CommandLine.h"


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLGeneral/PLGeneralWindowsIncludes.h"
#endif

// Linux platform
#ifdef LINUX
	#include <locale.h>
	#include "PLGeneral/PLGeneralLinuxIncludes.h"
#endif


//[-------------------------------------------------------]
//[ PL main function                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Program entry point
*
*  @param[in] sFilename
*    Absolute executable filename
*  @param[in] lstArguments
*    List of program arguments
*
*  @return
*    Exit code of the application (usually 0 means no error)
*/
int PLMain(const PLGeneral::String &sFilename, const PLGeneral::Array<PLGeneral::String> &lstArguments);


//[-------------------------------------------------------]
//[ Windows implementation                                ]
//[-------------------------------------------------------]
#if defined(WIN32) && !defined(_CONSOLE)
	#ifdef UNICODE
		int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR pszCmdLine, int nShow)
	#else
		int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pszCmdLine, int nShow)
	#endif
		{
			return PLMain( PLGeneral::System::GetInstance()->GetExecutableFilename(),
						   PLGeneral::CommandLine::StringToArguments(pszCmdLine) );
		}
#endif


//[-------------------------------------------------------]
//[ Linux/Console implementation                          ]
//[-------------------------------------------------------]
#if defined(LINUX) || (defined(WIN32) && defined(_CONSOLE))
	#if defined(WIN32) && defined(UNICODE)
		int wmain(int argc, wchar_t **argv)
	#else
		int main(int argc, char **argv)
	#endif
		{
	#ifdef LINUX
			// Load the system locale into the process
			setlocale(LC_ALL, "");
	#endif
			PLGeneral::Array<PLGeneral::String> lstArguments;
			for (int i=1; i<argc; i++)
				lstArguments.Add(argv[i]);
			return PLMain(PLGeneral::System::GetInstance()->GetExecutableFilename(), lstArguments);
		}
#endif


#endif // __PLGENERAL_MAIN_H__
