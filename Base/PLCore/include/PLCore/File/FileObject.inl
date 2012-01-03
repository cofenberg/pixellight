/*********************************************************\
 *  File: FileObject.inl                                 *
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
inline FileObject::FileObject() :
	m_pFileImpl(nullptr)
{
}

/**
*  @brief
*    Constructor
*/
inline FileObject::FileObject(const String &sUrl, const FileAccess *pAccess) :
	m_pFileImpl(nullptr)
{
	Assign(sUrl, pAccess);
}

/**
*  @brief
*    Constructor
*/
inline FileObject::FileObject(const Url &cUrl, const FileAccess *pAccess) :
	m_pFileImpl(nullptr)
{
	Assign(cUrl, pAccess);
}

/**
*  @brief
*    Constructor for a standard OS stream
*/
inline FileObject::FileObject(FILE *pFile, uint32 nAccess) :
	m_pFileImpl(nullptr)
{
	Assign(pFile, nAccess);
}

/**
*  @brief
*    Constructor for a OS file handle
*/
inline FileObject::FileObject(handle hFile) :
	m_pFileImpl(nullptr)
{
	Assign(hFile);
}

/**
*  @brief
*    Destructor
*/
inline FileObject::~FileObject()
{
	// Delete file implementation
	if (m_pFileImpl)
		delete m_pFileImpl;
}

/**
*  @brief
*    Assign a new URL
*/
inline void FileObject::Assign(const String &sUrl, const FileAccess *pAccess)
{
	Assign(Url(sUrl), pAccess);
}

/**
*  @brief
*    Get URL
*/
inline const Url &FileObject::GetUrl() const
{
	return m_pFileImpl ? m_pFileImpl->m_cUrl : m_cNullUrl;
}

/**
*  @brief
*    Check if the file or directory exists
*/
inline bool FileObject::Exists() const
{
	return m_pFileImpl ? m_pFileImpl->Exists() : false;
}

/**
*  @brief
*    Returns if the object is a file
*/
inline bool FileObject::IsFile() const
{
	return m_pFileImpl ? m_pFileImpl->IsFile() : false;
}

/**
*  @brief
*    Returns if the object is a directory
*/
inline bool FileObject::IsDirectory() const
{
	return m_pFileImpl ? m_pFileImpl->IsDirectory() : false;
}

/**
*  @brief
*    Copy the file or directory to a new location
*/
inline bool FileObject::Copy(const String &sDestination, bool bOverwrite) const
{
	if (m_pFileImpl) {
		// Try system-implementation
		if (m_pFileImpl->CopyTo(sDestination, bOverwrite))
			return true; // Done

		// Fallback: Use generic function (e.g. if the files exist in different file-systems)
		return GenericCopy(sDestination, bOverwrite);
	} else {
		return false;
	}
}

/**
*  @brief
*    Move the file or directory to a new location
*/
inline bool FileObject::Move(const String &sDestination)
{
	if (m_pFileImpl) {
		// Try system-implementation
		if (m_pFileImpl->MoveTo(sDestination))
			return true; // Done

		// Fallback: Use generic function (e.g. if the files exist in different file-systems)
		return GenericMove(sDestination);
	} else {
		return false;
	}
}

/**
*  @brief
*    Rename the file or directory
*/
inline bool FileObject::Rename(const String &sName)
{
	return m_pFileImpl ? m_pFileImpl->Rename(sName) : false;
}

/**
*  @brief
*    Close the file or directory
*/
inline void FileObject::Close()
{
	if (m_pFileImpl)
		m_pFileImpl->Close();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
