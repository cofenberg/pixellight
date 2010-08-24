/*********************************************************\
 *  File: FileZip.cpp                                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGeneral/File/FileAccess.h"
#include "PLGeneral/File/FileSearchZip.h"
#include "PLGeneral/File/FileZip.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FileZip::FileZip(const Url &cUrl, const String &sZipFile, const String &sPathInZip, const FileAccess *pAccess) : FileImpl(cUrl, pAccess),
	m_sZipFile(sZipFile),
	m_sPathInZip(sPathInZip),
	m_nAccess(0)
{
	// Get options from access-information
	String sPassword;
	bool bCaseSensitive = true;
	bool bMemBuf = true;
	if (m_pAccess && m_pAccess->HasEntry(sZipFile)) {
		const FileAccess::Entry &cZipAccess = m_pAccess->GetEntry(sZipFile);
		sPassword = cZipAccess.GetPassword();
		bCaseSensitive = cZipAccess.GetCaseSensitive();
		if (cZipAccess.GetFlagsMask() & File::FileMemBuf) bMemBuf = ((cZipAccess.GetFlagsValue() & File::FileMemBuf) != 0);
	}

	// Open ZIP-file
	m_cZipFile.Open(sZipFile, sPassword, bCaseSensitive, bMemBuf, pAccess);

	// Locate entry
	if (sPathInZip.GetLength()) {
		m_cZipFile.LocateFile(sPathInZip);
	}
}

/**
*  @brief
*    Destructor
*/
FileZip::~FileZip()
{
	// Close file
	Close();
}


//[-------------------------------------------------------]
//[ Private virtual FileImpl functions                    ]
//[-------------------------------------------------------]
bool FileZip::Exists() const
{
	// Return true, if the ZIP-file exists and m_sPathInZip either points to the root ("") or to a valid entry
	return (m_cZipFile.IsOpen() && (m_sPathInZip.GetLength() == 0 || m_cZipFile.GetCurrentFile().m_bValid));
}

bool FileZip::IsFile() const
{
	// Check current entry
	if (m_cZipFile.IsOpen()) {
		if (m_sPathInZip.GetLength() == 0) {
			// Root directory
			return false;
		} else if (m_cZipFile.GetCurrentFile().m_bValid) {
			// Valid entry, check "/" at the end
			return (m_cZipFile.GetCurrentFile().m_sFilename.GetSubstring(m_cZipFile.GetCurrentFile().m_sFilename.GetLength()-1) != "/");
		}
	}

	// Error
	return false;
}

bool FileZip::IsDirectory() const
{
	// Check current entry
	if (m_cZipFile.IsOpen()) {
		if (m_sPathInZip.GetLength() == 0) {
			// Root directory
			return true;
		} else if (m_cZipFile.GetCurrentFile().m_bValid) {
			// Valid entry, check "/" at the end
			return (m_cZipFile.GetCurrentFile().m_sFilename.GetSubstring(m_cZipFile.GetCurrentFile().m_sFilename.GetLength()-1) == "/");
		}
	}

	// Error
	return false;
}

bool FileZip::CopyTo(const String &sDest, bool bOverwrite) const
{
	// Not implemented
	return false;
}

bool FileZip::MoveTo(const String &sDest)
{
	// Not implemented
	return false;
}

bool FileZip::Rename(const String &sName)
{
	// Not implemented
	return false;
}

bool FileZip::CreateNewFile(bool bAlways)
{
	// Not implemented
	return false;
}

bool FileZip::CreateNewDirectory()
{
	// Not implemented
	return false;
}

bool FileZip::Delete()
{
	// Not implemented
	return false;
}

bool FileZip::DeleteDirectory()
{
	// Not implemented
	return false;
}

void FileZip::Close()
{
	// Close ZIP-file
	m_cZipFile.CloseFile();
}

bool FileZip::Open(uint32 nAccess)
{
	// Check selected file
	if (IsFile()) {
		// Check flags: FileRead must be set, while FileWrite, FileAppend and FileCreate are not allowed!
		if ((nAccess & File::FileRead) && !(nAccess & File::FileWrite) && !(nAccess & File::FileAppend) && !(nAccess & File::FileCreate)) {
			// Save access modes
			m_nAccess = nAccess;

			// Close file first
			Close();

			// Open file
			return m_cZipFile.OpenFile();
		}
	}

	// Error!
	return false;
}

bool FileZip::IsOpen() const
{
	// Check whether the file is open
	return m_cZipFile.IsFileOpen();
}

bool FileZip::IsReadable() const
{
	// Check whether the file is readable
	return (m_cZipFile.IsFileOpen() && (m_nAccess & File::FileRead));
}

bool FileZip::IsWritable() const
{
	// Not implemented
	return false;
}

bool FileZip::IsEof() const
{
	// Check end of file
	return (!m_cZipFile.IsFileOpen() || m_cZipFile.IsEof());
}

int FileZip::GetC()
{
	// Check stream
	if (m_cZipFile.IsFileOpen()) {
		// Read character
		uint8 c;
		if (m_cZipFile.Read(&c, 1, 1) == 1) {
			// Text mode: \r\n -> \n
			if ((m_nAccess & File::FileText) && c == 13) {
				if (m_cZipFile.Read(&c, 1, 1) != 1) return -1;
			}
			return (int)c;
		}
	}

	// Return error
	return -1;
}

bool FileZip::PutC(int nChar)
{
	// Not implemented
	return false;
}

String FileZip::GetS()
{
	// Check parameters
	if (m_cZipFile.IsFileOpen()) {
		// Read string
		char szString[2048];
		char *pszPos = szString;
		int   nChar = GetC();
		while (nChar >= 0 && nChar != 10) {
			// Concatenate char to string
			*pszPos = (char)nChar;
			pszPos++;

			// Read next character
			nChar = GetC();
		}

		// Terminate string
		if (nChar == 10) {
			*pszPos = '\n';
			pszPos++;
		}
		*pszPos = 0;

		// Return string
		if (pszPos > szString || nChar != -1) return szString;
	}

	// Error!
	return "";
}

int FileZip::PutS(const String &sString)
{
	// Not implemented
	return -1;
}

uint32 FileZip::Read(void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Read buffer
	return (m_cZipFile.IsFileOpen() ? m_cZipFile.Read(pBuffer, nSize, nCount) : 0);
}

uint32 FileZip::Write(const void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Not implemented
	return 0;
}

bool FileZip::Flush()
{
	// Not implemented
	return false;
}

bool FileZip::Seek(int32 nOffset, File::ESeek nLocation)
{
	// Seek
	return m_cZipFile.IsFileOpen() ? m_cZipFile.Seek(nOffset, nLocation) : false;
}

int32 FileZip::Tell() const
{
	// Get file position
	return m_cZipFile.IsFileOpen() ? m_cZipFile.Tell() : -1;
}

uint32 FileZip::GetSize() const
{
	// Return size
	return m_cZipFile.IsFileOpen() ? m_cZipFile.GetCurrentFile().m_nUncompressedSize : 0;
}

FileSearchImpl *FileZip::CreateSearch()
{
	// Create a file searcher
	return new FileSearchZip(m_sZipFile, m_sPathInZip + "/", m_pAccess);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
