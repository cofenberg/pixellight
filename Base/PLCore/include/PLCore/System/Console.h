/*********************************************************\
 *  File: Console.h                                      *
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


#ifndef __PLCORE_CONSOLE_H__
#define __PLCORE_CONSOLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class String;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'Console' implementations
*/
class Console {


	//[-------------------------------------------------------]
	//[ Public virtual Console functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Print a string to the console
		*
		*  @param[in] sString
		*    String that shall be printed
		*/
		virtual void Print(const String &sString) const = 0;

		/**
		*  @brief
		*    Checks whether or not there's some keyboard input waiting on the console ('_kbhit()')
		*
		*  @return
		*    0 if no key has been pressed, else not null
		*/
		virtual int IsKeyHit() const = 0;

		/**
		*  @brief
		*    Reads a single character from the console ('_getch()')
		*
		*  @param[in] bEcho
		*    Echo on the console?
		*
		*  @return
		*    The read character - note that there's no error code
		*/
		virtual int GetCharacter(bool bEcho = false) const = 0;

		/**
		*  @brief
		*    Clears the console screen ('clrscr()')
		*/
		virtual void ClearScreen() const = 0;

		/**
		*  @brief
		*    Gets the absolute console cursor position ('wherex()' and 'wherey()')
		*
		*  @param[out] nX
		*    Receives the absolute x position of the console cursor, (0,0)=(left,top)
		*  @param[out] nY
		*    Receives the absolute y position of the console cursor, (0,0)=(left,top)
		*/
		virtual void GetCursorPosition(uint16 &nX, uint16 &nY) const = 0;

		/**
		*  @brief
		*    Sets the absolute console cursor position ('gotoxy()')
		*
		*  @param[in] nX
		*    New x absolute position of the console cursor, (0,0)=(left,top)
		*  @param[in] nY
		*    New y absolute position of the console cursor, (0,0)=(left,top)
		*/
		virtual void SetCursorPosition(uint16 nX, uint16 nY) const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		Console();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Console();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Console(const Console &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Console &operator =(const Console &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSOLE_H__
