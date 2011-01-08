/*********************************************************\
 *  File: BufferedReader.h                               *
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


#ifndef __PLGENERAL_BUFFEREDREADER_H__
#define __PLGENERAL_BUFFEREDREADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract buffered reader base class
*
*  @remarks
*    A buffered reader is used to access a buffer or stream directly without the need to seek within the
*    stream too often. Therefore the reader stores the read data inside a buffer until it is no longer needed.
*/
class BufferedReader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BufferedReader() {};

		/**
		*  @brief
		*    Closes the reader
		*/
		virtual void Close() = 0;

		/**
		*  @brief
		*    Check if the end of the stream has been reached
		*
		*  @return
		*    'true' if the end of the buffer has been reached
		*/
		virtual bool IsEof() const = 0;

		/**
		*  @brief
		*    Returns a character read at the current position
		*
		*  @return
		*    Character that has been read, '\0' on error
		*/
		virtual char GetChar() = 0;

		/**
		*  @brief
		*    Returns a string of a given size read at the current position
		*
		*  @param[in] nSize
		*    Number of characters to read
		*
		*  @return
		*    String that has been read, "" on error
		*/
		virtual String GetString(uint32 nSize) = 0;

		/**
		*  @brief
		*    Reads a character at the current position and moves to the position after that
		*
		*  @return
		*    Character that has been read, '\0' on error
		*/
		virtual char ReadChar() = 0;

		/**
		*  @brief
		*    Reads a string at the current position and moves to the position after that
		*
		*  @param[in] nSize
		*    Number of characters to read
		*
		*  @return
		*    String that has been read, "" on error
		*/
		virtual String ReadString(uint32 nSize) = 0;

		/**
		*  @brief
		*    Checks if the next string equals the given one (case sensitive)
		*
		*  @param[in] sString
		*    String to compare with (length of this string is used to compare)
		*
		*  @return
		*    'true' if the next string equals the given one, else 'false'
		*/
		virtual bool IsString(const String &sString) = 0;

		/**
		*  @brief
		*    Checks if the next string equals the given one (not case sensitive)
		*
		*  @param[in] sString
		*    String to compare with (length of this string is used to compare)
		*
		*  @return
		*    'true' if the next string equals the given one, else 'false'
		*/
		virtual bool IsStringNoCase(const String &sString) = 0;

		/**
		*  @brief
		*    Returns the current position
		*
		*  @return
		*    Current position
		*/
		virtual uint32 Tell() const = 0;

		/**
		*  @brief
		*    Set the current position
		*
		*  @param[in] nPos
		*    New position
		*
		*  @return
		*    'true' if the seek has been successful
		*/
		virtual bool Seek(uint32 nPos) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		BufferedReader() {};

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGENERAL_API BufferedReader(const BufferedReader &cSource) {};

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
		PLGENERAL_API BufferedReader &operator =(const BufferedReader &cSource) { return *this; };


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_BUFFEREDREADER_H__
