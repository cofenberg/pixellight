/*********************************************************\
 *  File: ConsoleLinux.cpp                               *
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
#include <unistd.h>
#include <term.h>
#include <sys/ioctl.h>
#include "PLGeneral/File/File.h"
#include "PLGeneral/System/ConsoleLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public virtual Console functions                      ]
//[-------------------------------------------------------]
void ConsoleLinux::Print(const String &sString) const
{
	fputs((sString.GetFormat() == String::ASCII) ? sString.GetASCII() : sString.GetUTF8(), stdout);
	fflush(stdout);
}

int ConsoleLinux::IsKeyHit() const
{
	// Linux (POSIX) implementation of _kbhit() written by Morgan McGuire, morgan@cs.brown.edu.
	// Published at flipcode's "Developer Toolbox collection": http://www.flipcode.org/archives/_kbhit_for_Linux.shtml

	static const int STDIN = 0;
	static bool initialized = false;

	if (! initialized) {
		// Use termios to turn off line buffering
		termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, nullptr);
		initialized = true;
	}

	int bytesWaiting;
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}

int ConsoleLinux::GetCharacter(bool bEcho) const
{
	// This code comes from: http://cboard.cprogramming.com/archive/index.php/t-27714.html
	// "This code sets the terminal into non-canonical mode, thus disabling line buffering, reads a character from stdin
	//  and then restores the old terminal status. For more info on what else you can do with termios, see ``man termios''.
	//  There's also a ``getch()'' function in the curses library, but it is /not/ equivalent to the DOS ``getch()'' and
	//  may only be used within real curses applications (ie: it only works in curses ``WINDOW''s).."

	struct termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	struct termios newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	const int nCharacter = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	// Echo on the console?
	if (bEcho)
		putc(nCharacter, stdout);

	// Return the character
	return nCharacter;
}

void ConsoleLinux::ClearScreen() const
{
	// Use curses lib
	setupterm(nullptr, 1, nullptr);
	putp(clear_screen); 

	// Another solution: Use ANSI-sequences to achieve the job
//	printf("\033[H\033[J");
//	fflush(stdout);
}

void ConsoleLinux::GetCursorPosition(uint16 &nX, uint16 &nY) const
{
	// [TODO] Check whether this works...
	// Use curses lib
	/*
	int x, y;
	setupterm(nullptr, 1, nullptr);
	getyx(stdscr, y, x);
	nX = x;
	nY = y;
	*/
	nX = 0;
	nY = 0;
}

void ConsoleLinux::SetCursorPosition(uint16 nX, uint16 nY) const
{
	// Use curses lib
	setupterm(nullptr, 1, nullptr);
	putp(tparm(cursor_address, nY, nX));

	// Another solution: Use ANSI-sequences to achieve the job
//	printf("\033[%d;%dH", nX, nY);
//	fflush(stdout);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ConsoleLinux::ConsoleLinux()
{
}

/**
*  @brief
*    Destructor
*/
ConsoleLinux::~ConsoleLinux()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
