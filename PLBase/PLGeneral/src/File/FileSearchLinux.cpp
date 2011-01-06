/*********************************************************\
 *  File: FileSearchLinux.cpp                            *
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
#include "PLGeneral/File/FileSearchLinux.h"


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
FileSearchLinux::FileSearchLinux(const String &sPath, const FileAccess *pAccess) : FileSearchImpl(pAccess),
	m_sPath(sPath)
{
	// Start search
	m_pDir = opendir((m_sPath.GetFormat() == String::ASCII) ? m_sPath.GetASCII() : (char*)m_sPath.GetUTF8());
	if (m_pDir) {
		// Something has been found
		m_pDirEntry	= readdir(m_pDir);
		m_bHasNext	= true;
	} else {
		// Error!
		m_pDirEntry	= nullptr;
		m_bHasNext	= false;
	}
}

/**
*  @brief
*    Destructor
*/
FileSearchLinux::~FileSearchLinux()
{
	// Close the search
	if (m_pDir)
		closedir(m_pDir);
}


//[-------------------------------------------------------]
//[ Private virtual FileSearchImpl functions              ]
//[-------------------------------------------------------]
bool FileSearchLinux::HasNextFile()
{
	return m_bHasNext;
}

String FileSearchLinux::GetNextFile()
{
	if (m_bHasNext) {
		m_sFilename = m_pDirEntry->d_name;
		m_pDirEntry = readdir(m_pDir);
		m_bHasNext  = (m_pDirEntry != nullptr);
		return m_sFilename;
	} else {
		return "";
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
