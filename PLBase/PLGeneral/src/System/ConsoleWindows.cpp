/*********************************************************\
 *  File: ConsoleWindows.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Tchar.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <shellapi.h>
#include "PLGeneral/File/Url.h"
#include "PLGeneral/System/ConsoleWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public virtual Console functions                      ]
//[-------------------------------------------------------]
void ConsoleWindows::Print(const String &sString) const
{
	(sString.GetFormat() == String::ASCII) ? fputs(sString.GetASCII(), stdout) : fputws(sString.GetUnicode(), stdout);
}

int ConsoleWindows::IsKeyHit() const
{
	return _kbhit();
}

int ConsoleWindows::GetCharacter(bool bEcho) const
{
	return bEcho ? _getche() : _getch();
}

void ConsoleWindows::ClearScreen() const
{
	// This implementation comes from: http://www.cprogramming.com/faq/cgi-bin/smartfaq.cgi?answer=1031963460&id=1043284385
	//                                 "OPTION 6 (Credit: Sunlight)"

	// Get a handle to the console
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	// Find the number of characters to overwrite
	const DWORD nSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Overwrite the screen buffer with whitespace
	COORD sCoord = { 0, 0 };	// Top left screen position
	DWORD n		 = 0;			// Number of characters written
	FillConsoleOutputCharacter(h, TEXT (' '), nSize, sCoord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, nSize, sCoord, &n);

	// Reset the cursor to the top left position
	::SetConsoleCursorPosition(h, sCoord);
}

void ConsoleWindows::GetCursorPosition(uint16 &nX, uint16 &nY) const
{
	CONSOLE_SCREEN_BUFFER_INFO sConsoleScreenBufferInfo;

	// Get the cursor position
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sConsoleScreenBufferInfo);
	nX = sConsoleScreenBufferInfo.dwCursorPosition.X;
	nY = sConsoleScreenBufferInfo.dwCursorPosition.Y;
}

void ConsoleWindows::SetCursorPosition(uint16 nX, uint16 nY) const
{
	// Get a handle to the console
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the cursor position
	const COORD sCoord = { nX, nY };
	::SetConsoleCursorPosition(h, sCoord);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ConsoleWindows::ConsoleWindows()
{
}

/**
*  @brief
*    Destructor
*/
ConsoleWindows::~ConsoleWindows()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
