/*********************************************************\
 *  File: PLTextFile.h                                   *
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


#ifndef __PL_TEXTFILE_H__
#define __PL_TEXTFILE_H__
#pragma once


//[-------------------------------------------------------]
//[ Include                                               ]
//[-------------------------------------------------------]
#include <string>
#include <stdio.h>


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
		PLTextFile(const std::string &sFilename, bool bFlush = false);

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
		const std::string &GetFilename() const;

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
		std::string   m_sFilename;		/**< Name of the file we write in */
		FILE		 *m_pFile;			/**< File we write in, can be a null pointer */
		bool		  m_bFlush;			/**< Flush file every time something is written in? */
		unsigned int  m_nSpaces;		/**< Number of spaces added in front of each row */
		unsigned int  m_nBufferLength;	/**< Current length of the string buffer (including '\0') */
		char		 *m_pszBuffer;		/**< String buffer, can be a null pointer */


};


#endif // __PL_TEXTFILE_H__
