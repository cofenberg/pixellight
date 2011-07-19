/*********************************************************\
 *  File: File.cpp                                       *
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
#include <stdio.h>
#include "PLCore/Core/MemoryManager.h"
#include "PLCore/File/FileImpl.h"
#include "PLCore/File/File.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
File File::StandardInput (stdin,  File::FileRead);
File File::StandardOutput(stdout, File::FileWrite);
File File::StandardError (stderr, File::FileWrite);


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
File::File() :
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(0)
{
}

/**
*  @brief
*    Constructor
*/
File::File(const String &sUrl, const FileAccess *pAccess) : FileObject(sUrl, pAccess),
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(0)
{
}

/**
*  @brief
*    Constructor
*/
File::File(const Url &cUrl, const FileAccess *pAccess) : FileObject(cUrl, pAccess),
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(0)
{
}

/**
*  @brief
*    Constructor for a standard OS stream
*/
File::File(FILE *pFile, uint32 nAccess) : FileObject(pFile, nAccess),
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(0)
{
}

/**
*  @brief
*    Constructor
*/
File::File(handle hFile) : FileObject(hFile),
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(0)
{
}

/**
*  @brief
*    Constructor
*/
File::File(uint8 *pnData, uint32 nNumOfBytes, bool bCopy, const String &sUrl) :
	m_pMemBuf(nullptr),
	m_nMemBufSize(0),
	m_nMemBufPos(0),
	m_nMemBufAccess(FileRead)
{
	// File data given?
	if (pnData && nNumOfBytes) {
		// Copy the file data?
		if (bCopy) {
			m_pMemBuf = new uint8[nNumOfBytes];
			MemoryManager::Copy(m_pMemBuf, pnData, nNumOfBytes);
		} else {
			m_pMemBuf        = pnData;
			m_nMemBufAccess |= FileMemBufShared;
		}

		// Set the buffer size in bytes
		m_nMemBufSize = nNumOfBytes;
	}

	// Set URL
	m_cNullUrl = sUrl;
}

/**
*  @brief
*    Destructor
*/
File::~File()
{
	// Close memory buffered
	MemBufClose();
}

/**
*  @brief
*    Create file
*/
bool File::Create(bool bAlways)
{
	// Memory buffered file?
	if (m_pMemBuf)
		MemBufClose();

	// Create file
	return m_pFileImpl ? m_pFileImpl->CreateNewFile(bAlways) : false;
}

/**
*  @brief
*    Delete file
*/
bool File::Delete()
{
	// Memory buffered file?
	if (m_pMemBuf)
		MemBufClose();

	// Delete file
	return m_pFileImpl ? m_pFileImpl->Delete() : false;
}

/**
*  @brief
*    Open the file for reading and/or writing
*/
bool File::Open(uint32 nAccess)
{
	// Memory buffered file?
	if (m_pMemBuf)
		MemBufClose();

	// Open file
	if (nAccess & File::FileMemBuf)
		return MemBufOpen(nAccess);
	else if (m_pFileImpl)
		return m_pFileImpl->Open(nAccess);
	else
		return false; // Error!
}

/**
*  @brief
*    Close the file
*/
void File::Close()
{
	// Memory buffered file?
	if (m_pMemBuf)
		MemBufClose();

	// Close file
	if (m_pFileImpl)
		m_pFileImpl->Close();
}

/**
*  @brief
*    Returns whether the file is memory buffered (opened with flag FileMemBuf)
*/
bool File::IsMemoryBuffered() const
{
	return (m_pMemBuf != nullptr);
}

/**
*  @brief
*    Returns whether the file is open
*/
bool File::IsOpen() const
{
	// Check if file is open
	if (m_pMemBuf)
		return true;
	else if (m_pFileImpl)
		return m_pFileImpl->IsOpen();
	else
		return false;
}

/**
*  @brief
*    Returns whether the file is readable
*/
bool File::IsReadable() const
{
	// Check readable
	if (m_pMemBuf)
		return true;
	else if (m_pFileImpl)
		return m_pFileImpl->IsReadable();
	else
		return false;
}

/**
*  @brief
*    Returns whether the file is writable
*/
bool File::IsWritable() const
{
	// Check writable
	if (m_pMemBuf)
		return false;
	else if (m_pFileImpl)
		return m_pFileImpl->IsWritable();
	else
		return false;
}

/**
*  @brief
*    Returns whether end of file has been reached
*/
bool File::IsEof() const
{
	// Check EOF
	if (m_pMemBuf)
		return m_nMemBufPos >= m_nMemBufSize;
	else if (m_pFileImpl)
		return m_pFileImpl->IsEof();
	else
		return false;
}

/**
*  @brief
*    Reads a character
*/
int File::GetC()
{
	// Read character
	if (m_pMemBuf)
		return MemBufGetC();
	else if (m_pFileImpl)
		return m_pFileImpl->GetC();
	else
		return 0;
}

/**
*  @brief
*    Writes a character
*/
bool File::PutC(int nChar)
{
	// Open file
	if (m_pMemBuf)
		return false;
	else if (m_pFileImpl)
		return m_pFileImpl->PutC(nChar);
	else
		return false;
}

/**
*  @brief
*    Reads a string
*/
String File::GetS()
{
	// Read string
	if (m_pMemBuf)
		return MemBufGetS();
	else if (m_pFileImpl)
		return m_pFileImpl->GetS();
	else
		return "";
}

/**
*  @brief
*    Writes a string
*/
int File::PutS(const String &sString)
{
	// Write string
	if (m_pMemBuf)
		return false;
	else if (m_pFileImpl)
		return m_pFileImpl->PutS(sString);
	else
		return 0;
}

/**
*  @brief
*    Reads the given number of bytes
*/
uint32 File::Read(void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Read data
	if (m_pMemBuf)
		return MemBufRead(pBuffer, nSize, nCount);
	else if (m_pFileImpl)
		return m_pFileImpl->Read(pBuffer, nSize, nCount);
	else
		return 0;
}

/**
*  @brief
*    Writes the given number of bytes
*/
uint32 File::Write(const void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Write data
	if (m_pMemBuf)
		return false;
	else if (m_pFileImpl)
		return m_pFileImpl->Write(pBuffer, nSize, nCount);
	else
		return 0;
}

/**
*  @brief
*    Flushs the file buffer
*/
bool File::Flush()
{
	// Flush buffer
	if (m_pMemBuf)
		return false;
	else if (m_pFileImpl)
		return m_pFileImpl->Flush();
	else
		return false;
}

/**
*  @brief
*    Sets the starting position
*/
bool File::Seek(int32 nOffset, ESeek nLocation)
{
	// Seek
	if (m_pMemBuf)
		return MemBufSeek(nOffset, nLocation);
	else if (m_pFileImpl)
		return m_pFileImpl->Seek(nOffset, nLocation);
	else
		return false;
}

/**
*  @brief
*    Gets the current position of the file pointer
*/
int32 File::Tell() const
{
	// Get seek position
	if (m_pMemBuf)
		return m_nMemBufPos;
	else if (m_pFileImpl)
		return m_pFileImpl->Tell();
	else
		return 0;
}

/**
*  @brief
*    Returns the file size
*/
uint32 File::GetSize() const
{
	// Get file size
	if (m_pMemBuf)
		return m_nMemBufSize;
	else if (m_pFileImpl)
		return m_pFileImpl->GetSize();
	else
		return 0;
}

/**
*  @brief
*    Writes a string into the file
*/
bool File::Print(const String &sString)
{
	// Write string
	return (PutS(sString) == static_cast<int>(sString.GetLength()));
}

/**
*  @brief
*    Writes a string and a newline into the file
*/
bool File::PrintLn(const String &sString)
{
	// Write string and newline
	PutS(sString);
	return PutC('\n');
}

/**
*  @brief
*    Returns a pointer to the buffer for memory buffered file
*/
const uint8 *File::GetMemoryBuffer() const
{
	return m_pMemBuf;
}

/**
*  @brief
*    Returns the complete content of the file as string
*/
String File::GetContentAsString(String::EFormat nFormat)
{
	// Get the file size
	const uint32 nFileSize = GetSize();

	// ASCII or Unicode?
	if (nFormat == String::ASCII) {
		// We also take care of the terminating zero (\0)
		char *pData = new char[nFileSize + 1];
		Read(pData, nFileSize, 1);
		pData[nFileSize] = '\0';

		// The string class takes over the control of the memory
		return String(pData, false, nFileSize);
	} else {
		// We also take care of the terminating zero (\0)
		const uint32 nNumOfCharacters = nFileSize/sizeof(wchar_t);
		wchar_t *pData = new wchar_t[nNumOfCharacters + 1];
		Read(pData, nFileSize, 1);
		pData[nFileSize] = L'\0';

		// The string class takes over the control of the memory
		return String(pData, false, nFileSize);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
File::File(const File &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
File &File::operator =(const File &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Open the file (for memory buffered files)
*/
bool File::MemBufOpen(uint32 nAccess)
{
	// Check flags
	if ((nAccess & FileRead) && !(nAccess & FileWrite) && !(nAccess & FileAppend) && !(nAccess & FileCreate)) {
		// Just to be sure ...
		if (m_pMemBuf)
			MemBufClose();

		// Open file
		if (m_pFileImpl->Open(nAccess & ~static_cast<uint32>(FileMemBuf))) {
			// Get file size
			bool bSuccess = false;
			m_nMemBufSize = m_pFileImpl->GetSize();
			if (m_nMemBufSize > 0) {
				// Read file into memory buffer
				m_pMemBuf = new uint8[m_nMemBufSize];
				bSuccess = (m_pFileImpl->Read(m_pMemBuf, 1, m_nMemBufSize) == m_nMemBufSize);
			}

			// Close file
			m_pFileImpl->Close();

			// Check success
			if (bSuccess) {
				// Success!
				m_nMemBufPos    = 0;
				m_nMemBufAccess = nAccess;
				return true;
			} else {
				// Error!
				MemBufClose();
			}
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Close the file (for memory buffered files)
*/
void File::MemBufClose()
{
	// Destroy memory buffer
	if (m_pMemBuf) {
		if (!(m_nMemBufAccess & FileMemBufShared))
			delete [] m_pMemBuf;
		m_pMemBuf		= nullptr;
		m_nMemBufSize	= 0;
		m_nMemBufPos	= 0;
		m_nMemBufAccess	= 0;
	}
}

/**
*  @brief
*    Reads a character (for memory buffered files)
*/
int File::MemBufGetC()
{
	// Check memory buffer
	if (m_pMemBuf) {
		// Get next character
		if (m_nMemBufPos < m_nMemBufSize) {
			uint8 c = m_pMemBuf[m_nMemBufPos];
			m_nMemBufPos++;

			// Text mode: \r\n -> \n
			if ((m_nMemBufAccess & File::FileText) && c == 13) {
				if (m_nMemBufPos < m_nMemBufSize) {
					c = m_pMemBuf[m_nMemBufPos];
					m_nMemBufPos++;
				} else {
					return -1;
				}
			}
			return static_cast<int>(c);
		}
	}

	// Return error
	return -1;
}

/**
*  @brief
*    Reads a string (for memory buffered files)
*/
String File::MemBufGetS()
{
	// Check memory buffer
	if (m_pMemBuf) {
		// Read string
		char szString[2048];
		char *pszPos = szString;
		int   nChar = MemBufGetC();
		while (nChar >= 0 && nChar != 10) {
			// Concatenate char to string
			*pszPos = static_cast<char>(nChar);
			pszPos++;

			// Read next character
			nChar = MemBufGetC();
		}

		// Terminate string
		if (nChar == 10) {
			*pszPos = '\n';
			pszPos++;
		}
		*pszPos = 0;

		// Return string
		if (pszPos > szString || nChar != -1)
			return szString;
	}

	// Error!
	return "";
}

/**
*  @brief
*    Reads the given number of bytes (for memory buffered files)
*/
uint32 File::MemBufRead(void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Check parameters
	if (m_pMemBuf && pBuffer && nSize && nCount) {
		const uint32 nRead = ((nSize*nCount < m_nMemBufSize-m_nMemBufPos) ? nSize*nCount : m_nMemBufSize-m_nMemBufPos);
		if (nRead > 0) {
			MemoryManager::Copy(pBuffer, &m_pMemBuf[m_nMemBufPos], nRead);
			m_nMemBufPos += nRead;
			return nRead / nSize;
		}
	}

	// Error!
	return 0;
}

/**
*  @brief
*    Sets the starting position (for memory buffered files)
*/
bool File::MemBufSeek(int32 nOffset, ESeek nLocation)
{
	// Check memory buffer
	if (m_pMemBuf) {
		// Calculate offset
		int nOfs;
		if (nLocation == File::SeekCurrent)
			nOfs = m_nMemBufPos + nOffset;
		else if (nLocation == File::SeekEnd)
			nOfs = m_nMemBufSize + nOffset;
		else if (nLocation == File::SeekSet)
			nOfs = nOffset;
		else
			return false; // Error!

		// Set new position
		if (nOfs >= 0 && static_cast<uint32>(nOfs) < m_nMemBufSize) {
			m_nMemBufPos = nOfs;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
