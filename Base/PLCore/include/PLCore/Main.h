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


#ifndef __PLCORE_MAIN_H__
#define __PLCORE_MAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/System.h"
#include "PLCore/Tools/CommandLine.h"


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLCore/PLCoreWindowsIncludes.h"
#endif

// Linux platform
#ifdef LINUX
	#include <locale.h>
	#include "PLCore/PLCoreLinuxIncludes.h"
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
int PLMain(const PLCore::String &sFilename, const PLCore::Array<PLCore::String> &lstArguments);


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
			return PLMain( PLCore::System::GetInstance()->GetExecutableFilename(),
						   PLCore::CommandLine::StringToArguments(pszCmdLine) );
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
			PLCore::Array<PLCore::String> lstArguments;
			for (int i=1; i<argc; i++)
				lstArguments.Add(argv[i]);
			return PLMain(PLCore::System::GetInstance()->GetExecutableFilename(), lstArguments);
		}
#endif


#endif // __PLCORE_MAIN_H__
