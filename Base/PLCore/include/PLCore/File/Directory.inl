/*********************************************************\
 *  File: Directory.inl                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLCore/File/FileImpl.h"


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
inline Directory::Directory()
{
}

/**
*  @brief
*    Constructor
*/
inline Directory::Directory(const String &sUrl, const FileAccess *pAccess) : FileObject(sUrl, pAccess)
{
}

/**
*  @brief
*    Constructor
*/
inline Directory::Directory(const Url &cUrl, const FileAccess *pAccess) : FileObject(cUrl, pAccess)
{
}

/**
*  @brief
*    Destructor
*/
inline Directory::~Directory()
{
}

/**
*  @brief
*    Create directory
*/
inline bool Directory::Create()
{
	return m_pFileImpl ? m_pFileImpl->CreateNewDirectory() : false;
}

/**
*  @brief
*    Delete directory
*/
inline bool Directory::Delete()
{
	return m_pFileImpl ? m_pFileImpl->DeleteDirectory() : false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
