/*********************************************************\
 *  File: BufferedReaderString.h                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_BUFFEREDREADER_STRING_H__
#define __PLCORE_BUFFEREDREADER_STRING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/BufferedReader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
		virtual void Close() override;
		virtual bool IsEof() const override;
		virtual String::EFormat GetStringFormat() const override;
		virtual int GetChar() override;
		virtual String GetString(uint32 nSize) override;
		virtual int ReadChar() override;
		virtual String ReadString(uint32 nSize) override;
		virtual bool IsString(const String &sString) override;
		virtual bool IsStringNoCase(const String &sString) override;
		virtual uint32 Tell() const override;
		virtual bool Seek(uint32 nPos) override;


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
} // PLCore


#endif // __PLCORE_BUFFEREDREADER_STRING_H__
