/*********************************************************\
 *  File: FileSearchZip.cpp                              *
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
#include "PLCore/File/FileAccess.h"
#include "PLCore/File/FileSearchZip.h"


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
FileSearchZip::FileSearchZip(const String &sZipFile, const String &sPathInZip, const FileAccess *pAccess) : FileSearchImpl(pAccess),
	m_sZipFile(sZipFile),
	m_sPathInZip(sPathInZip)
{
	// Get options from access-information
	String sPassword;
	bool bCaseSensitive = true;
	bool bMemBuf        = true;
	if (m_pAccess && m_pAccess->HasEntry(sZipFile)) {
		const FileAccess::Entry &cZipAccess = m_pAccess->GetEntry(sZipFile);
		sPassword      = cZipAccess.GetPassword();
		bCaseSensitive = cZipAccess.GetCaseSensitive();
		if (cZipAccess.GetFlagsMask() & File::FileMemBuf)
			bMemBuf = ((cZipAccess.GetFlagsValue() & File::FileMemBuf) != 0);
	}

	// Open ZIP-file
	m_cZipFile.Open(sZipFile, sPassword, bCaseSensitive, bMemBuf, m_pAccess);

	// Jump to first entry in ZIP-file
	m_cZipFile.LocateFirstFile();

	// Find the next file that matches the path-in-zip
	FindNextFile();
}

/**
*  @brief
*    Destructor
*/
FileSearchZip::~FileSearchZip()
{
}


//[-------------------------------------------------------]
//[ Private virtual FileSearchImpl functions              ]
//[-------------------------------------------------------]
bool FileSearchZip::HasNextFile()
{
	// Return if the current file is valid
	return m_cZipFile.GetCurrentFile().m_bValid;
}

String FileSearchZip::GetNextFile()
{
	// Check if the current file is valid
	if (m_cZipFile.GetCurrentFile().m_bValid) {
		// Get name of file without the path prefix
		String sName = (m_sPathInZip.Compare('/') ?
							m_cZipFile.GetCurrentFile().m_sFilename :
							m_cZipFile.GetCurrentFile().m_sFilename.GetSubstring(m_sPathInZip.GetLength()));

		// Remove "/" at the end
		if (sName.GetSubstring(sName.GetLength()-1) == '/')
			sName = sName.GetSubstring(0, sName.GetLength()-1);

		// Go to next file
		m_cZipFile.LocateNextFile();

		// Find the next file that matches the path-in-zip
		FindNextFile();

		// Return filename
		return sName;
	}

	// No more valid files found
	return "";
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Find next file in the selected directory
*/
bool FileSearchZip::FindNextFile()
{
	while (m_cZipFile.GetCurrentFile().m_bValid) {
		// Is this file in the right directory?
		if (CheckFile(m_cZipFile.GetCurrentFile().m_sFilename)) {
			// Yep, file found
			return true;
		}

		// Go to next file
		m_cZipFile.LocateNextFile();
	}

	// No valid file found
	return false;
}

bool FileSearchZip::CheckFile(const String &sFilename)
{
	// Check if m_sPathInZip is a prefix of the filename or "/"
	if (m_sPathInZip.Compare('/') ||
		(m_sPathInZip.GetLength() < sFilename.GetLength() &&
		(m_cZipFile.IsCaseSensitive() ? sFilename.Compare(m_sPathInZip, 0, m_sPathInZip.GetLength()) :
										sFilename.CompareNoCase(m_sPathInZip, 0, m_sPathInZip.GetLength()))))
	{
		// After that prefix, '/' must only appear at the end of the string or not at all
		const int nStart = m_sPathInZip.Compare('/') ? 0 : m_sPathInZip.GetLength();
		const int nSlash = sFilename.IndexOf('/', nStart);
		return (nSlash < 0 || nSlash == static_cast<int>(sFilename.GetLength())-1);
	}

	// Not in the current directory
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
