/*********************************************************\
 *  File: BufferedReaderString.cpp                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/BufferedReaderString.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BufferedReaderString::BufferedReaderString(const String &sBuffer) :
	m_sBuffer(sBuffer),
	m_nCurrent(0)
{
}

/**
*  @brief
*    Destructor
*/
BufferedReaderString::~BufferedReaderString()
{
	// Nothing to do in here :)
}


//[-------------------------------------------------------]
//[ Public virtual BufferedReader functions               ]
//[-------------------------------------------------------]
void BufferedReaderString::Close()
{
	// Close stream
	m_sBuffer  = "";
	m_nCurrent = 0;
}

bool BufferedReaderString::IsEof() const
{
	// Return if the stream is valid and there is more data to read
	return (m_nCurrent >= m_sBuffer.GetLength());
}

String::EFormat BufferedReaderString::GetStringFormat() const
{
	return m_sBuffer.GetFormat();
}

int BufferedReaderString::GetChar()
{
	// Return the current character, the string class performs the range check for us :)
	return (m_sBuffer.GetFormat() == String::ASCII) ? m_sBuffer.GetASCII()[m_nCurrent] : m_sBuffer.GetUnicode()[m_nCurrent];
}

String BufferedReaderString::GetString(uint32 nSize)
{
	// Check whether we can read the requested number of characters
	if (m_nCurrent+nSize <= m_sBuffer.GetLength()) {
		// Get the requested substring
		return m_sBuffer.GetSubstring(m_nCurrent, nSize);
	}

	// Error!
	return "";
}

int BufferedReaderString::ReadChar()
{
	// Check whether we can read a character
	if (m_nCurrent+1 <= m_sBuffer.GetLength()) {
		// Get the requested character and update the current character index
		return (m_sBuffer.GetFormat() == String::ASCII) ? m_sBuffer.GetASCII()[m_nCurrent++] : m_sBuffer.GetUnicode()[m_nCurrent++];
	}

	// Error!
	return '\0';
}

String BufferedReaderString::ReadString(uint32 nSize)
{
	// Check whether we can read the requested number of characters
	if (m_nCurrent+nSize <= m_sBuffer.GetLength()) {
		// Update the current character index
		m_nCurrent += nSize;

		// Get the requested substring
		return m_sBuffer.GetSubstring(m_nCurrent - nSize, nSize);
	}

	// Error!
	return "";
}

bool BufferedReaderString::IsString(const String &sString)
{
	return m_sBuffer.Compare(sString, m_nCurrent, sString.GetLength());
}

bool BufferedReaderString::IsStringNoCase(const String &sString)
{
	return m_sBuffer.CompareNoCase(sString, m_nCurrent, sString.GetLength());
}

uint32 BufferedReaderString::Tell() const
{
	return m_nCurrent;
}

bool BufferedReaderString::Seek(uint32 nPos)
{
	// Is the given position valid?
	if (nPos < m_sBuffer.GetLength()) {
		// Set the new position
		m_nCurrent = nPos;

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
