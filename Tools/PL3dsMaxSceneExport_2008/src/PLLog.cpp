/*********************************************************\
 *  File: PLLog.cpp                                      *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdarg.h>
#include <string.h>
#include "PL3dsMaxSceneExport/PLLog.h"


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
PLLog *g_pLog = nullptr;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public definitions                                    ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLLog::PLLog(const String &sFilename) : PLTextFile(sFilename, true),
	m_nFlags(Error | Warning | Hint),
	m_nNumOfErrors(0),
	m_nNumOfWarnings(0),
	m_nNumOfHints(0)
{
	PrintLine(">> Log start <<");
	PrintLine(">> *If the 'application/viewer' you are using is writing a log, do ALSO have a look at it for application relevant information like performance/compatibility warnings* <<");
}

/**
*  @brief
*    Destructor
*/
PLLog::~PLLog()
{
	m_nSpaces = 0;
	PrintLine(">> Log end <<");
	PrintFLine("  - Errors: %d",   m_nNumOfErrors);
	PrintFLine("  - Warnings: %d", m_nNumOfWarnings);
	PrintFLine("  - Hints: %d",    m_nNumOfHints);
}

/**
*  @brief
*    Returns the log flags
*/
char PLLog::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the log flags
*/
void PLLog::SetFlags(char nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Prints a string into the file
*/
bool PLLog::Log(EFlags nType, const char szString[])
{
	// Ignore this string?
	if (!(m_nFlags & nType))
		return true; // Done, but ignored :)

	// Is there a file we can write in?
	if (m_pFile) {
		// Write the string
		fputs(szString, m_pFile);

		// Flush
		if (m_bFlush)
			fflush(m_pFile);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Prints a formated string into the file
*/
bool PLLog::LogF(EFlags nType, const char szString[], ...)
{
	// Ignore this string?
	if (!(m_nFlags & nType))
		return true; // Done, but ignored :)

	// Is there a file we can write in and is the given string valid?
	if (m_pFile && strlen(szString)) {
		// Start parameter list
		va_list vaList;
		va_start(vaList, szString);

		// Get the required buffer length
		unsigned int nLength = _vscprintf(szString, vaList);
		if (nLength > 0) {
			// Update our string buffer (+1 because we need to include the terminating zero character!)
			UpdateStringBuffer(nLength + 1);
			if (m_pszBuffer) {
				// Print the formatted string
				vsprintf(m_pszBuffer, szString, vaList);

				// Write the string
				fputs(m_pszBuffer, m_pFile);

				// Flush
				if (m_bFlush)
					fflush(m_pFile);

				// End parameter list
				va_end(vaList);

				// Done
				return true;
			}
		}

		// End parameter list
		va_end(vaList);
	}

	// Error!
	return false;
}

/**
*  @brief
*    Prints a string line into the file
*/
bool PLLog::LogLine(EFlags nType, const char szString[])
{
	// Ignore this string?
	if (!(m_nFlags & nType))
		return true; // Done, but ignored :)

	// Is there a file we can write in?
	if (m_pFile) {
		// Add spaces
		for (unsigned int i=0; i<m_nSpaces; i++)
			fputc(' ', m_pFile);

		// Add string type if required
		if (nType & Error) {
			m_nNumOfErrors++;
			fputs(">> Error: ", m_pFile);
		}
		if (nType & Warning) {
			m_nNumOfWarnings++;
			fputs(">> Warning: ", m_pFile);
		}
		if (nType & Hint) {
			m_nNumOfHints++;
			fputs(">> Hints: ", m_pFile);
		}

		// Write the string
		fputs(szString, m_pFile);

		// Add a new line
		putc('\n', m_pFile);

		// Flush
		if (m_bFlush)
			fflush(m_pFile);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Prints a formated string line into the file
*/
bool PLLog::LogFLine(EFlags nType, const char szString[], ...)
{
	// Ignore this string?
	if (!(m_nFlags & nType))
		return true; // Done, but ignored :)

	// Is there a file we can write in and is the given string valid?
	if (m_pFile && strlen(szString)) {
		// Start parameter list
		va_list vaList;
		va_start(vaList, szString);

		// Get the required buffer length
		unsigned int nLength = _vscprintf(szString, vaList);
		if (nLength > 0) {
			// Update our string buffer (+1 because we need to include the terminating zero character!)
			UpdateStringBuffer(nLength + 1);
			if (m_pszBuffer) {
				// Add spaces
				for (unsigned int i=0; i<m_nSpaces; i++)
					fputc(' ', m_pFile);

				// Add string type if required
				if (nType & Error) {
					m_nNumOfErrors++;
					fputs(">> Error: ", m_pFile);
				}
				if (nType & Warning) {
					m_nNumOfWarnings++;
					fputs(">> Warning: ", m_pFile);
				}
				if (nType & Hint) {
					m_nNumOfHints++;
					fputs(">> Hint: ", m_pFile);
				}

				// Print the formatted string
				vsprintf(m_pszBuffer, szString, vaList);

				// Write the string
				fputs(m_pszBuffer, m_pFile);

				// Add a new line
				putc('\n', m_pFile);

				// Flush
				if (m_bFlush)
					fflush(m_pFile);

				// End parameter list
				va_end(vaList);

				// Done
				return true;
			}
		}

		// End parameter list
		va_end(vaList);
	}

	// Error!
	return false;
}
