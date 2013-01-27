/*********************************************************\
 *  File: PLTextFile.h                                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PL_TEXTFILE_H__
#define __PL_TEXTFILE_H__
#pragma once


//[-------------------------------------------------------]
//[ Include                                               ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  brief
*    Text file
*/
class PLTextFile {


	//[-------------------------------------------------------]
	//[ Public static definitions                             ]
	//[-------------------------------------------------------]
	public:
		static const int TabSize;	/**< Number of spaces per tab */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sFilename
		*    Name of the file to write in
		*  @param[in] bFlush
		*    Flush file every time something is written in?
		*/
		PLTextFile(const PLCore::String &sFilename, bool bFlush = false);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLTextFile();

		/**
		*  @brief
		*    Close the file
		*/
		void Close();

		/**
		*  @brief
		*    Returns the name of the file we write in
		*
		*  @return
		*    The name of the file we write in
		*/
		PLCore::String GetFilename() const;

		/**
		*  @brief
		*    Returns whether or not this text file is valid
		*
		*  @return
		*    'true' if this text file is valid, else 'false'
		*/
		bool IsValid() const;

		/**
		*  @brief
		*    Returns the number of front spaces
		*
		*  @return
		*    Number of front spaces
		*/
		int GetNumOfSpaces() const;

		/**
		*  @brief
		*    Adds a number of spaces to the current number of front spaces
		*
		*  @param[in] nSpaces
		*    Number of spaces to add
		*/
		void AddSpaces(int nSpaces);

		/**
		*  @brief
		*    Prints spaces into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - AddSpaces()
		*/
		bool PrintSpaces();

		/**
		*  @brief
		*    Prints a string into the file
		*
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Print(const char szString[]);

		/**
		*  @brief
		*    Prints a formated string into the file
		*
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool PrintF(const char szString[], ...);

		/**
		*  @brief
		*    Prints a string line into the file
		*
		*  @param[in] szString
		*    String line to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    At the front spaces may be added automatically, at the end a '\n' is added.
		*
		*  @see
		*    - AddSpaces()
		*/
		bool PrintLine(const char szString[]);

		/**
		*  @brief
		*    Prints a formated string line into the file
		*
		*  @param[in] szString
		*    String line to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    At the front spaces may be added automatically, at the end a '\n' is added.
		*
		*  @see
		*    - AddSpaces()
		*/
		bool PrintFLine(const char szString[], ...);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Updates the string buffer
		*
		*  @param[in] nLength
		*    Required length (including '\0')
		*/
		void UpdateStringBuffer(unsigned int nLength);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String   m_sFilename;		/**< Name of the file we write in */
		FILE			*m_pFile;			/**< File we write in, can be a null pointer */
		bool			 m_bFlush;			/**< Flush file every time something is written in? */
		unsigned int	 m_nSpaces;			/**< Number of spaces added in front of each row */
		unsigned int	 m_nBufferLength;	/**< Current length of the string buffer (including '\0') */
		char			*m_pszBuffer;		/**< String buffer, can be a null pointer */


};


#endif // __PL_TEXTFILE_H__
