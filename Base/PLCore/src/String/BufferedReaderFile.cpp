/*********************************************************\
 *  File: BufferedReaderFile.cpp                         *
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
#include "PLCore/File/File.h"
#include "PLCore/String/BufferedReaderFile.h"


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
BufferedReaderFile::BufferedReaderFile(File &cFile) :
	m_pFile(&cFile)
{
}

/**
*  @brief
*    Destructor
*/
BufferedReaderFile::~BufferedReaderFile()
{
	Close();
}


//[-------------------------------------------------------]
//[ Public virtual BufferedReader functions               ]
//[-------------------------------------------------------]
void BufferedReaderFile::Close()
{
	// Close stream
	if (m_pFile) {
		m_pFile   = nullptr;
		m_sBuffer = "";
	}
}

bool BufferedReaderFile::IsEof() const
{
	// Return if the stream is valid and there is more data to read
	if (m_sBuffer.GetLength())
		return false;
	else if (m_pFile)
		return m_pFile->IsEof();
	else
		return true;
}

char BufferedReaderFile::GetChar()
{
	// Does the buffer contain at least one char?
	if (!m_sBuffer.GetLength()) {
		// No, try to read it from the stream
		if (!ReadFromStream(1))
			return 0;
	}

	// Return the current char
	return m_sBuffer[static_cast<uint32>(0)];
}

String BufferedReaderFile::GetString(uint32 nSize)
{
	// Does the buffer contain enough chars?
	if (m_sBuffer.GetLength() < nSize) {
		// No, try to read it from the stream
		if (!ReadFromStream(nSize - m_sBuffer.GetLength()))
			return "";
	}

	// Return the buffered string
	return m_sBuffer.GetLength() > nSize ? m_sBuffer.GetSubstring(0, nSize) : m_sBuffer;
}

char BufferedReaderFile::ReadChar()
{
	if (m_sBuffer.GetLength()) {
		const char c = m_sBuffer[static_cast<uint32>(0)];
		m_sBuffer = m_sBuffer.GetSubstring(1);
		return c;
	} else if (m_pFile) {
		const int nChar = m_pFile->GetC();
		if (nChar >= 0)
			return static_cast<char>(nChar);
	}
	return 0;
}

String BufferedReaderFile::ReadString(uint32 nSize)
{
	String sString;
	if (m_sBuffer.GetLength() >= nSize) {
		sString   = m_sBuffer.GetSubstring(0, nSize);
		m_sBuffer = m_sBuffer.GetSubstring(nSize);
	} else if (ReadFromStream(nSize - m_sBuffer.GetLength())) {
		sString   = m_sBuffer;
		m_sBuffer = "";
	}
	return sString;
}

bool BufferedReaderFile::IsString(const String &sString)
{
	// Get the string length
	const uint32 nStringLength = sString.GetLength();

	// Does the buffer contain enough chars?
	if (m_sBuffer.GetLength() < nStringLength) {
		// No, try to read it from the stream
		if (!ReadFromStream(nStringLength - m_sBuffer.GetLength()))
			return false;
	}

	// Compare
	return m_sBuffer.Compare(sString, 0, nStringLength);
}

bool BufferedReaderFile::IsStringNoCase(const String &sString)
{
	// Get the string length
	const uint32 nStringLength = sString.GetLength();

	// Does the buffer contain enough chars?
	if (m_sBuffer.GetLength() < nStringLength) {
		// No, try to read it from the stream
		if (!ReadFromStream(nStringLength - m_sBuffer.GetLength()))
			return false;
	}

	// Compare
	return m_sBuffer.CompareNoCase(sString, 0, nStringLength);
}

uint32 BufferedReaderFile::Tell() const
{
	return m_pFile ? m_pFile->Tell() - m_sBuffer.GetLength() : 0;
}

bool BufferedReaderFile::Seek(uint32 nPos)
{
	if (m_pFile) {
		m_sBuffer = "";
		return m_pFile->Seek(nPos);
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
BufferedReaderFile::BufferedReaderFile(const BufferedReaderFile &cSource) :
	m_pFile(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
BufferedReaderFile &BufferedReaderFile::operator =(const BufferedReaderFile &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Reads bytes from the stream
*/
bool BufferedReaderFile::ReadFromStream(uint32 nSize)
{
	// [TODO] Take Unicode into account...
	// Check file
	if (nSize > 0 && m_pFile && !m_pFile->IsEof()) {
		if (nSize == 1) {
			// Read one char
			const int nChar = m_pFile->GetC();
			if (nChar > -1) {
				m_sBuffer += static_cast<char>(nChar);

				// Done
				return true;
			}
		} else {
			// Read more than one char
			char *pszString = new char[nSize+1];
			if (m_pFile->Read(pszString, 1, nSize) == nSize) {
				pszString[nSize] = '\0';
				m_sBuffer += pszString;
				delete [] pszString;

				// Done
				return true;
			}
			delete [] pszString;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
