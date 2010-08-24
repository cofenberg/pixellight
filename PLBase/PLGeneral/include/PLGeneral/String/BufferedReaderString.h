/*********************************************************\
 *  File: BufferedReaderString.h                         *
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


#ifndef __PLGENERAL_BUFFEREDREADER_STRING_H__
#define __PLGENERAL_BUFFEREDREADER_STRING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/BufferedReader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Buffered reader that reads from a string or character buffer
*/
class BufferedReaderString : public BufferedReader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sBuffer
		*    String to read from
		*/
		BufferedReaderString(const String &sBuffer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BufferedReaderString();


	//[-------------------------------------------------------]
	//[ Public virtual BufferedReader functions               ]
	//[-------------------------------------------------------]
	public:
		virtual void Close();
		virtual bool IsEof() const;
		virtual char GetChar();
		virtual String GetString(uint32 nSize);
		virtual char ReadChar();
		virtual String ReadString(uint32 nSize);
		virtual bool IsString(const String &sString);
		virtual bool IsStringNoCase(const String &sString);
		virtual uint32 Tell() const;
		virtual bool Seek(uint32 nPos);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sBuffer;	/**< String that holds the character buffer */
		uint32 m_nCurrent;	/**< The current character index */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_BUFFEREDREADER_STRING_H__
