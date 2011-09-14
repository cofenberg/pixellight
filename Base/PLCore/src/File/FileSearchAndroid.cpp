/*********************************************************\
 *  File: FileSearchAndroid.cpp                          *
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
#include <stdio.h>	// For e.g. "off_t"
#include <stdint.h>	// For e.g. "size_t"
#include <android/asset_manager.h>
#include "PLCore/System/SystemAndroid.h"
#include "PLCore/File/FileSearchAndroid.h"


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
FileSearchAndroid::FileSearchAndroid(const String &sPath, const FileAccess *pAccess) : FileSearchImpl(pAccess),
	m_pAAssetDir(nullptr),
	m_sPath(sPath),
	m_pszNextFilename(nullptr)
{
	// Get the Android asset manager instance
	AAssetManager *pAAssetManager = SystemAndroid::GetAssetManager();
	if (pAAssetManager) {
		// Start search
		m_pAAssetDir = AAssetManager_openDir(pAAssetManager, (m_sPath.GetFormat() == String::ASCII) ? m_sPath.GetASCII() : m_sPath.GetUTF8());
		if (m_pAAssetDir) {
			// Something has been found
			m_pszNextFilename = AAssetDir_getNextFileName(m_pAAssetDir);
		}
	}
}

/**
*  @brief
*    Destructor
*/
FileSearchAndroid::~FileSearchAndroid()
{
	// Close the search
	if (m_pAAssetDir)
		AAssetDir_close(m_pAAssetDir);
}


//[-------------------------------------------------------]
//[ Private virtual FileSearchImpl functions              ]
//[-------------------------------------------------------]
bool FileSearchAndroid::HasNextFile()
{
	return (m_pszNextFilename != nullptr);
}

String FileSearchAndroid::GetNextFile()
{	
	if (m_pszNextFilename) {
		m_sFilename	= m_pszNextFilename;
		m_pszNextFilename = AAssetDir_getNextFileName(m_pAAssetDir);
		return m_sFilename;
	} else {
		return "";
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
