/*********************************************************\
 *  File: FileWindows.cpp                                *
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
#include <io.h>
#include <stdio.h>
#include "PLCore/PLCoreWindowsIncludes.h"
#include "PLCore/File/FileSearchWindows.h"
#include "PLCore/File/FileWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FileWindows::FileWindows(const Url &cUrl, const FileAccess *pAccess) : FileImpl(cUrl, pAccess),
	m_sFilename(cUrl.GetWindowsPath()),
	m_nAccess(0),
	m_pFile(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
FileWindows::~FileWindows()
{
	// Close file
	Close();
}


//[-------------------------------------------------------]
//[ Private virtual FileImpl functions                    ]
//[-------------------------------------------------------]
bool FileWindows::Exists() const
{
	// Check file attributes
	if (m_sFilename.GetFormat() == String::ASCII)
		return (GetFileAttributesA(m_sFilename.GetASCII()) != INVALID_FILE_ATTRIBUTES);
	else
		return (GetFileAttributesW(m_sFilename.GetUnicode()) != INVALID_FILE_ATTRIBUTES);
}

bool FileWindows::IsFile() const
{
	// Check file attributes
	DWORD nAttributes;
	if (m_sFilename.GetFormat() == String::ASCII)
		nAttributes = GetFileAttributesA(m_sFilename.GetASCII());
	else
		nAttributes = GetFileAttributesW(m_sFilename.GetUnicode());

	// Is it a regular file?
	return (nAttributes != INVALID_FILE_ATTRIBUTES && !(nAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileWindows::IsDirectory() const
{
	// Check file attributes
	DWORD nAttributes;
	if (m_sFilename.GetFormat() == String::ASCII)
		nAttributes = GetFileAttributesA(m_sFilename.GetASCII());
	else
		nAttributes = GetFileAttributesW(m_sFilename.GetUnicode());

	// Is it a regular file?
	return (nAttributes != INVALID_FILE_ATTRIBUTES && (nAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileWindows::CopyTo(const String &sDest, bool bOverwrite) const
{
	// Get destination as a windows path
	const Url cDestUrl = Url(sDest);
	if (cDestUrl.IsValid() && cDestUrl.IsValidWindowsPath()) {
		// Get absolute path of old and new filename (in Windows notation)
		const String sNewFilename = Url(cDestUrl.CutFilename() + Url(m_sFilename).GetFilename()).GetWindowsPath();

		// Note: See MoveTo, same applies here

		// Copy file (if the old absolute filename was Unicode, the new absolute one is also Unicode)
		if (sNewFilename.GetFormat() == String::ASCII)
			return (CopyFileA(m_sFilename.GetASCII(), sNewFilename.GetASCII(), !bOverwrite) != 0);
		else
			return (CopyFileW(m_sFilename.GetUnicode(), sNewFilename.GetUnicode(), !bOverwrite) != 0);
	}

	// Error
	return false;
}

bool FileWindows::MoveTo(const String &sDest)
{
	// Close file before moving it
	Close();

	// Get destination as a windows path
	const Url cDestUrl = Url(sDest);
	if (cDestUrl.IsValid() && cDestUrl.IsValidWindowsPath()) {
		// Get absolute path of old and new filename (in Windows notation)
		const String sNewFilename = Url(cDestUrl.CutFilename()).GetWindowsPath();

		// Note: This might be dangerous, because the destination URL is blindly used, so if e.g.
		// the user tries to move "C:\test.txt" to "C:\test.zip\test2.txt", this will be passed
		// over to MoveFile and we can only hope that the OS does nothing bad and returns a failure.
		// The only other option would be to check beforehand, whether the destination URL is a valid
		// local filename and return false otherwise without calling MoveFile. But this would mean
		// that an expansive check would have to be done every time this function is called, even if
		// in 90% of all cases both the URLs are on the local file system anyway.

		// Move file (if the old absolute filename was Unicode, the new absolute one is also Unicode)
		bool bSuccess;
		if (sNewFilename.GetFormat() == String::ASCII)
			bSuccess = (MoveFileA(m_sFilename.GetASCII(), sNewFilename.GetASCII()) != 0);
		else
			bSuccess = (MoveFileW(m_sFilename.GetUnicode(), sNewFilename.GetUnicode()) != 0);

		// Set new file name
		if (bSuccess) {
			m_cUrl = sNewFilename;
			return true;
		}
	}

	// Error
	return false;
}

bool FileWindows::Rename(const String &sName)
{
	// Close file before renaming it
	Close();

	// Check parameter: No path is allowed ('/' or '\')
	if (sName.IsSubstring('\\') || sName.IsSubstring('/'))
		return false; // Error!

	// Get absolute path of old and new name (in Windows notation)
	const String sNewFilename = Url(m_cUrl.CutFilename() + sName).GetWindowsPath();

	// Rename file (if the old absolute filename was Unicode, the new absolute one is also Unicode)
	bool bSuccess;
	if (sNewFilename.GetFormat() == String::ASCII)
		bSuccess = (MoveFileA(m_sFilename.GetASCII(), sNewFilename.GetASCII()) != 0);
	else
		bSuccess = (MoveFileW(m_sFilename.GetUnicode(), sNewFilename.GetUnicode()) != 0);

	// Set new file name
	if (bSuccess)
		m_cUrl = sNewFilename;

	// Done
	return bSuccess;
}

bool FileWindows::CreateNewFile(bool bAlways)
{
	// Close file if open
	Close();

	// Create file
	HANDLE hFile;
	if (m_sFilename.GetFormat() == String::ASCII)
		hFile = CreateFileA(m_sFilename.GetASCII(), 0, 0, nullptr, bAlways ? CREATE_ALWAYS : CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	else
		hFile = CreateFileW(m_sFilename.GetUnicode(), 0, 0, nullptr, bAlways ? CREATE_ALWAYS : CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);

	// Check return value
	if (hFile != INVALID_HANDLE_VALUE) {
		// Success
		CloseHandle(hFile);
		return true;
	}

	// Error
	return false;
}

bool FileWindows::CreateNewDirectory()
{
	// Close file if open
	Close();

	// Create directory
	if (m_sFilename.GetFormat() == String::ASCII)
		return (CreateDirectoryA(m_sFilename.GetASCII(), nullptr) != 0);
	else
		return (CreateDirectoryW(m_sFilename.GetUnicode(), nullptr) != 0);
}

bool FileWindows::Delete()
{
	// Close file before deleting it
	Close();

	// Delete file
	if (m_sFilename.GetFormat() == String::ASCII)
		return (DeleteFileA(m_sFilename.GetASCII()) != 0);
	else
		return (DeleteFileW(m_sFilename.GetUnicode()) != 0);
}

bool FileWindows::DeleteDirectory()
{
	// Close if open
	Close();

	// Delete directory
	if (m_sFilename.GetFormat() == String::ASCII)
		return (RemoveDirectoryA(m_sFilename.GetASCII()) != 0);
	else
		return (RemoveDirectoryW(m_sFilename.GetUnicode()) != 0);
}

void FileWindows::Close()
{
	// Check file pointer
	if (m_pFile) {
		// Close file
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}

bool FileWindows::Open(uint32 nAccess)
{
	// Close file first
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

	// Open file using ASCII/unicode filename
	if (m_sFilename.GetFormat() == String::ASCII) {
		// ASCII filename
		m_pFile = fopen(m_sFilename.GetASCII(), szMode);
	} else {
		// Unicode filename
		const wchar_t szModeUnicode[4] = {szMode[0], szMode[1], szMode[2], szMode[3]};
		m_pFile = _wfopen(m_sFilename.GetUnicode(), szModeUnicode);
	}

	// Done
	return (m_pFile != nullptr);
}

bool FileWindows::IsOpen() const
{
	// Check whether the file is open
	return (m_pFile != nullptr);
}

bool FileWindows::IsReadable() const
{
	// Check whether the file is readable
	return (m_pFile && (m_nAccess & File::FileRead));
}

bool FileWindows::IsWritable() const
{
	// Check whether the file is writable
	return (m_pFile && (m_nAccess & File::FileWrite));
}

bool FileWindows::IsEof() const
{
	// Check end of file
	return (!m_pFile || feof(m_pFile));
}

int FileWindows::GetC()
{
	// Read character
	return IsReadable() ? getc(m_pFile) : -1;
}

bool FileWindows::PutC(int nChar)
{
	// Write character
	return (IsWritable() && putc(nChar, m_pFile) != EOF);
}

String FileWindows::GetS()
{
	// Read string
	if (IsReadable()) {
		// ASCII... using "GetS()" is not recommended...
		char szTemp[2048] = "";
		if (fgets(szTemp, 2048, m_pFile))
			return szTemp;
	}

	// Error!
	return "";
}

int FileWindows::PutS(const String &sString)
{
	// Write string
	if (IsWritable()) {
		const int nSize = (m_sFilename.GetFormat() == String::ASCII) ? fputs(sString.GetASCII(), m_pFile) : fputws(sString.GetUnicode(), m_pFile);
		if (nSize >= 0)
			return sString.GetLength();
	}

	// Error!
	return -1;
}

uint32 FileWindows::Read(void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Read buffer
	return IsReadable() ? static_cast<uint32>(fread(pBuffer, nSize, nCount, m_pFile)) : 0;
}

uint32 FileWindows::Write(const void *pBuffer, uint32 nSize, uint32 nCount)
{
	// Write buffer
	return IsWritable() ? static_cast<uint32>(fwrite(pBuffer, nSize, nCount, m_pFile)) : 0;
}

bool FileWindows::Flush()
{
	// Flush buffer
	return (m_pFile && !fflush(m_pFile));
}

bool FileWindows::Seek(int32 nOffset, File::ESeek nLocation)
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

int32 FileWindows::Tell() const
{
	// Get file position
	return m_pFile ? ftell(m_pFile) : -1;
}

uint32 FileWindows::GetSize() const
{
	// Check file pointer
	if (m_pFile) {
		/* // Without using special Windows API functions the implementation of this method would be:
		// Get file size
		const int32 nPos = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_END);
		const int32 nSize = ftell(m_pFile);
		fseek(m_pFile, nPos, SEEK_SET);
		return nSize;
		*/

		// Get the file descriptor associated with our stream and then request the length of the file
		return _filelength(_fileno(m_pFile));
	} else {
		// Error!
		return 0;
	}
}

FileSearchImpl *FileWindows::CreateSearch()
{
	// Create a file searcher
	return new FileSearchWindows(m_cUrl.GetWindowsPath(), m_pAccess);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
