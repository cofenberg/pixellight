/*********************************************************\
 *  File: BufferedReaderFile.h                           *
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


#ifndef __PLCORE_BUFFEREDREADER_FILE_H__
#define __PLCORE_BUFFEREDREADER_FILE_H__
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
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class File;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Buffered reader that reads from a file
*/
class BufferedReaderFile : public BufferedReader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to read from, released automatically
		*/
		BufferedReaderFile(File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BufferedReaderFile();


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
		BufferedReaderFile(const BufferedReaderFile &cSource);

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
		BufferedReaderFile &operator =(const BufferedReaderFile &cSource);

		/**
		*  @brief
		*    Reads bytes from the stream
		*
		*  @param[in] nSize
		*    Number of bytes to read
		*
		*  @return
		*    'true' if all went fine, else 'true'
		*/
		bool ReadFromStream(uint32 nSize);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		File   *m_pFile;	/**< File to read from, can be a null pointer */
		String  m_sBuffer;	/**< Buffer that is used to store characters read from the file */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_BUFFEREDREADER_FILE_H__
