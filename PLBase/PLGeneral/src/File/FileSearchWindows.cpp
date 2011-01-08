/*********************************************************\
 *  File: FileSearchWindows.cpp                          *
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
#include "PLGeneral/File/FileSearchWindows.h"


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
FileSearchWindows::FileSearchWindows(const String &sPath, const FileAccess *pAccess) : FileSearchImpl(pAccess),
	m_sPath(sPath),
	m_sFind(sPath + "\\*.*")
{
	// Start search
	m_hFind = FindFirstFile(m_sFind, &m_sFindData);
	if (m_hFind != INVALID_HANDLE_VALUE) {
		// Something has been found
		m_bHasNext = true;
	} else {
		// Error
		m_bHasNext = false;
		m_hFind    = nullptr;
	}
}

/**
*  @brief
*    Destructor
*/
FileSearchWindows::~FileSearchWindows()
{
	// Close the search
	if (m_hFind)
		FindClose(m_hFind);
}


//[-------------------------------------------------------]
//[ Private virtual FileSearchImpl functions              ]
//[-------------------------------------------------------]
bool FileSearchWindows::HasNextFile()
{
	return m_bHasNext;
}

String FileSearchWindows::GetNextFile()
{
	if (m_bHasNext) {
		m_sFilename = m_sFindData.cFileName;
		m_bHasNext  = (FindNextFile(m_hFind, &m_sFindData) > 0);
		return m_sFilename;
	} else {
		return "";
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
