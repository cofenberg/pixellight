/*********************************************************\
 *  File: PLLog.h                                        *
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


#ifndef __PL_LOG_H__
#define __PL_LOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLTextFile.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Log
*/
class PLLog : public PLTextFile {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Log flags
		*/
		enum EFlags {
			Error   = 1,	/**< Print error strings into the log */
			Warning = 2,	/**< Print warning strings into the log */
			Hint    = 4,	/**< Some additional information that may be interessting/useful */
			Scene   = 8		/**< Print scene strings into the log */
		};


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
		*/
		PLLog(const std::string &sFilename);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLLog();

		/**
		*  @brief
		*    Returns the log flags
		*
		*  @return
		*    The log flags (see EFlags)
		*/
		char GetFlags() const;

		/**
		*  @brief
		*    Sets the log flags
		*
		*  @param[in] nFlags
		*    The log flags (see EFlags)
		*/
		void SetFlags(char nFlags = Error | Warning | Hint);

		/**
		*  @brief
		*    Prints a string into the file
		*
		*  @param[in] nType
		*    Type of the string (see EFlags)
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The string is only printed if the string type is set within GetFlags()
		*/
		bool Log(EFlags nType, const char szString[]);

		/**
		*  @brief
		*    Prints a formated string into the file
		*
		*  @param[in] nType
		*    Type of the string (see EFlags)
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - Log()
		*/
		bool LogF(EFlags nType, const char szString[], ...);

		/**
		*  @brief
		*    Prints a string into the file
		*
		*  @param[in] nType
		*    Type of the string (see EFlags)
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Spaces are added at the front
		*    - '>> Hint: ', Warning: ' or '>> Error: ' is added in front if the type is 'Warning' or 'Error'
		*    - '\n' is added at the end
		*
		*  @see
		*    - Log()
		*/
		bool LogLine(EFlags nType, const char szString[]);

		/**
		*  @brief
		*    Prints a formated string into the file
		*
		*  @param[in] nType
		*    Type of the string (see EFlags)
		*  @param[in] szString
		*    String to print into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - Log()
		*    - PrintLine() above
		*/
		bool LogFLine(EFlags nType, const char szString[], ...);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		char m_nFlags;			/**< Log flags (see EFlags) */
		int  m_nNumOfErrors;	/**< Number of errors */
		int  m_nNumOfWarnings;	/**< Number of warnings */
		int  m_nNumOfHints;		/**< Number of hints */


};


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
extern PLLog *g_pLog;


#endif // __PL_LOG_H__
