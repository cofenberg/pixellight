/*********************************************************\
 *  File: FileStdStream.cpp                              *
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
#if defined(WIN32)
	#include <io.h>
	#include <Fcntl.h>
#elif defined(LINUX)
	#include "PLGeneral/PLGeneralLinuxWrapper.h"
#endif
#include <stdio.h>
#include <string.h>
#include "PLGeneral/File/FileStdStream.h"


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
FileStdStream::FileStdStream(FILE *pFile, uint32 nAccess) : FileImpl(Url(), nullptr),
	m_bStream(true),
	m_pFile(pFile),
	m_hFile(0),
	m_nAccess(nAccess)
{
}

/**
*  @brief
*    Constructor
*/
FileStdStream::FileStdStream(handle hFile) : FileImpl(Url(), nullptr),
	m_bStream(false),
	m_pFile(nullptr),
	m_hFile(hFile),
	m_nAccess(0)
{
}

/**
*  @brief
*    Destructor
*/
FileStdStream::~FileStdStream()
{
	Close();
}


//[-------------------------------------------------------]
//[ Private virtual FileImpl functions                    ]
//[-------------------------------------------------------]
bool FileStdStream::Exists() const
{
	return true;
}

bool FileStdStream::IsFile() const
{
	return true;
}

bool FileStdStream::IsDirectory() const
{
	return false;
}

bool FileStdStream::CopyTo(const String &sDest, bool bOverwrite) const
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::MoveTo(const String &sDest)
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::Rename(const String &sName)
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::CreateNewFile(bool bAlways)
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::CreateNewDirectory()
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::Delete()
{
	// Not implemented - error!
	return false;
}

bool FileStdStream::DeleteDirectory()
{
	// Not implemented - error!
	return false;
}

void FileStdStream::Close()
{
	// Close stream handle
	if (m_pFile) {
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}

bool FileStdStream::Open(uint32 nAccess)
{
	// If a standard stream has been used, we cannot open/reopen it
	if (m_bStream)
		return false;

	// Close file
	Close();

	// Set file mode
	char szMode[4];
	if ((nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && (nAccess & File::FileAppend)) {
		// Append at the end of the file
		if (nAccess & File::FileRead)
			strcpy(szMode, "a+");	// Append, read and write
		else
			strcpy(szMode, "a");	// Append, write only
	} else if ((nAccess & File::FileWrite) && (nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Create and open writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "w+");	// Create, read and write
		else
			strcpy(szMode, "w");	// Create, write only
	} else if ((nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Open writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "r+");	// Open, read and write

		// We need to check whether the file already exist, if so, we can go on...
		else {
			if (Exists())
				strcpy(szMode, "w");	// Open, write only
			else
				return false;			// Invalid
		}
	} else if (!(nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Open not writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "r");	// Open, read only
		else
			return false;			// Invalid
	} else {
		// Invalid combination
		return false;
	}

	// Set text or binary mode
	strcat(szMode, (nAccess & File::FileText) ? "t" : "b");

	// Save access modes
	m_nAccess = nAccess;

	// Get OS file handle
	#if defined(WIN32)
		const int nFile = _open_osfhandle(m_hFile, 0);
	#elif defined(LINUX)
		const int nFile = m_hFile;
	#endif

	// Open file
	if (nFile > -1)
		m_pFile = _fdopen(nFile, szMode);

	// Done
	return (m_pFile != nullptr);
}

bool FileStdStream::IsOpen() const
{
	// Check whether the file is opened
	return (m_pFile != nullptr);
}

bool FileStdStream::IsReadable() const
{
	// Check whether the file is readable
	return (m_pFile && (m_nAccess & File::FileRead));
}

bool FileStdStream::IsWritable() const
{
	// Check whether the file is writable
	return (m_pFile && (m_nAccess & File::FileWrite));
}

bool FileStdStream::IsEof() const
{
	// Check end of file
	return (!m_pFile || feof(m_pFile));
}

int FileStdStream::GetC()
{
	// Read character
	return m_pFile ? getc(m_pFile) : -1;
}

bool FileStdStream::PutC(int nChar)
{
	// Write character
	return (m_pFile && IsWritable() && putc(nChar, m_pFile) != EOF);
}

String FileStdStream::GetS()
{
	// Read string
	if (m_pFile) {
		char szTemp[2048] = "";
		if (fgets(szTemp, 2048, m_pFile))
			return szTemp;
	}

	// Error!
	return "";
}

int FileStdStream::PutS(const String &sString)
{
	// Write string
	if (m_pFile && IsWritable()) {
		#ifdef WIN32
			const int nSize = (sString.GetFormat() == String::ASCII) ? fputs(sString.GetASCII(), m_pFile) : fputws(sString.GetUnicode(), m_pFile);
		#else
			const int nSize = fputs((sString.GetFormat() == String::ASCII) ? sString.GetASCII() : sString.GetUTF8(), m_pFile);
		#endif
		if (nSize >= 0)
			return sString.GetLength();
	}

	// Error!
	return -1;
}

uint32 FileStdStream::Read(void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Read buffer
	return m_pFile ? static_cast<uint32>(fread(pBuffer, nSize, nCount, m_pFile)) : 0;
}

uint32 FileStdStream::Write(const void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Write buffer
	return m_pFile && IsWritable() ? static_cast<uint32>(fwrite(pBuffer, nSize, nCount, m_pFile)) : 0;
}

bool FileStdStream::Flush()
{
	// Flush buffer
	return (m_pFile && !fflush(m_pFile));
}

bool FileStdStream::Seek(int32 nOffset, File::ESeek nLocation)
{
	// Check file pointer
	if (m_pFile) {
		// Convert seek position to Windows value
		int nSeek;
		switch (nLocation) {
			case File::SeekCurrent:
				nSeek = SEEK_CUR;
				break;

			case File::SeekEnd:
				nSeek = SEEK_END;
				break;

			case File::SeekSet:
				nSeek = SEEK_SET;
				break;

			default:
				return false; // Error!
		}

		// Seek file
		return !fseek(m_pFile, nOffset, nSeek);
	} else {
		// Error!
		return false;
	}
}

int32 FileStdStream::Tell() const
{
	// Get file position
	return m_pFile ? ftell(m_pFile) : -1;
}

uint32 FileStdStream::GetSize() const
{
	// Check file pointer
	if (m_pFile) {
		// Get file size
		const int32 nPos = Tell();
		fseek(m_pFile, 0, SEEK_END);
		const int32 nSize = ftell(m_pFile);
		fseek(m_pFile, nPos, SEEK_SET);
		return nSize;
	} else {
		// Error!
		return 0;
	}
}

FileSearchImpl *FileStdStream::CreateSearch()
{
	// Not implemented
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
