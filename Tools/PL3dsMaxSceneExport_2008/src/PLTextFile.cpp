/*********************************************************\
 *  File: PLTextFile.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <PLCore/PLCoreWindows.h>	// Depending on the used compiler, nullptr has to be defined by this header
#include "PL3dsMaxSceneExport/PLTextFile.h"


//[-------------------------------------------------------]
//[ Public static definitions                             ]
//[-------------------------------------------------------]
const int PLTextFile::TabSize = 4;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLTextFile::PLTextFile(const String &sFilename, bool bFlush) :
	m_sFilename(sFilename),
	m_pFile(sFilename.GetLength() ? fopen(sFilename.GetASCII(), "wt") : nullptr),
	m_bFlush(bFlush),
	m_nSpaces(0),
	m_nBufferLength(0),
	m_pszBuffer(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
PLTextFile::~PLTextFile()
{
	Close();
}

/**
*  @brief
*    Close the file
*/
void PLTextFile::Close()
{
	if (m_pFile) {
		fclose(m_pFile);
		m_pFile = nullptr;
	}
	if (m_pszBuffer) {
		delete [] m_pszBuffer;
		m_pszBuffer = nullptr;
	}
}

/**
*  @brief
*    Returns the name of the file we write in
*/
String PLTextFile::GetFilename() const
{
	return m_sFilename;
}

/**
*  @brief
*    Returns whether or not this text file is valid
*/
bool PLTextFile::IsValid() const
{
	return (m_pFile != nullptr);
}

/**
*  @brief
*    Returns the number of front spaces
*/
int PLTextFile::GetNumOfSpaces() const
{
	return m_nSpaces;
}

/**
*  @brief
*    Adds a number of spaces to the current number of front spaces
*/
void PLTextFile::AddSpaces(int nSpaces)
{
	if (static_cast<int>(m_nSpaces)+nSpaces <= 0)
		m_nSpaces = 0;
	else
		m_nSpaces += nSpaces;
}

/**
*  @brief
*    Prints spaces into the file
*/
bool PLTextFile::PrintSpaces()
{
	// Is there a file we can write in?
	if (m_pFile) {
		// Add spaces
		for (unsigned int i=0; i<m_nSpaces; i++)
			fputc(' ', m_pFile);

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
*    Prints a string into the file
*/
bool PLTextFile::Print(const char szString[])
{
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
bool PLTextFile::PrintF(const char szString[], ...)
{
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
				if (m_bFlush) fflush(m_pFile);

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
bool PLTextFile::PrintLine(const char szString[])
{
	// Is there a file we can write in and is?
	if (m_pFile) {
		// Add spaces
		for (unsigned int i=0; i<m_nSpaces; i++)
			fputc(' ', m_pFile);

		// Write the string
		fputs(szString, m_pFile);

		// Add a new line
		fputc('\n', m_pFile);

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
bool PLTextFile::PrintFLine(const char szString[], ...)
{
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

				// Print the formatted string
				vsprintf(m_pszBuffer, szString, vaList);

				// Write the string
				fputs(m_pszBuffer, m_pFile);

				// Add a new line
				fputc('\n', m_pFile);

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


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the string buffer
*/
void PLTextFile::UpdateStringBuffer(unsigned int nLength)
{
	// Do we need to enlarge our string buffer?
	if (m_nBufferLength < nLength) {
		// Destroy the old buffer
		if (m_pszBuffer)
			delete [] m_pszBuffer;

		// And create a new, larger one - add some more characters so we do not need to recreate THAT often :)
		m_nBufferLength = nLength + 100;
		m_pszBuffer     = new char[m_nBufferLength];
	}
}
