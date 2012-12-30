/*********************************************************\
 *  File: PLLog.h                                        *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		PLLog(const PLCore::String &sFilename);

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
