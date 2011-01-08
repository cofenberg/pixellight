/*********************************************************\
 *  File: FileObject.cpp                                 *
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
#include "PLGeneral/File/FileZip.h"
#include "PLGeneral/File/FileHttp.h"
#if defined(WIN32)
	#include "PLGeneral/File/FileWindows.h"
#elif defined(LINUX)
	#include "PLGeneral/File/FileLinux.h"
#endif
#include "PLGeneral/File/FileStdStream.h"
#include "PLGeneral/File/FileObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FileObject::FileObject() :
	m_pFileImpl(nullptr)
{
}

/**
*  @brief
*    Constructor
*/
FileObject::FileObject(const String &sUrl, const FileAccess *pAccess) :
	m_pFileImpl(nullptr)
{
	Assign(sUrl, pAccess);
}

/**
*  @brief
*    Constructor
*/
FileObject::FileObject(const Url &cUrl, const FileAccess *pAccess) :
	m_pFileImpl(nullptr)
{
	Assign(cUrl, pAccess);
}

/**
*  @brief
*    Constructor for a standard OS stream
*/
FileObject::FileObject(FILE *pFile, uint32 nAccess) :
	m_pFileImpl(nullptr)
{
	Assign(pFile, nAccess);
}

/**
*  @brief
*    Constructor for a OS file handle
*/
FileObject::FileObject(handle hFile) :
	m_pFileImpl(nullptr)
{
	Assign(hFile);
}

/**
*  @brief
*    Destructor
*/
FileObject::~FileObject()
{
	// Delete file implementation
	if (m_pFileImpl)
		delete m_pFileImpl;
}

/**
*  @brief
*    Assign a new URL
*/
void FileObject::Assign(const String &sUrl, const FileAccess *pAccess)
{
	Assign(Url(sUrl), pAccess);
}

/**
*  @brief
*    Assign a new URL
*/
void FileObject::Assign(const Url &cUrl, const FileAccess *pAccess)
{
	// Get URL
	Url cFinalUrl;
	if (cUrl.IsDirectory() && cUrl.GetPath() != "") {
		const String sUrl = cUrl.GetUrl();
		cFinalUrl = sUrl.GetSubstring(0, sUrl.GetLength() - 1);
	} else {
		cFinalUrl = cUrl;
	}
	cFinalUrl.Collapse();

	// Delete existing file implementation
	if (m_pFileImpl) {
		delete m_pFileImpl;
		m_pFileImpl = nullptr;
	}

	// Create file implementation

	// ZIP
	const String sUrlLower = cFinalUrl.GetUrl().ToLower();
	const int nPos = sUrlLower.LastIndexOf(".zip/");
	if (nPos > -1) {
		const String sZipFile   = cFinalUrl.GetUrl().GetSubstring(0, nPos+4);
		const String sPathInZip = cFinalUrl.GetUrl().GetSubstring(nPos+5);
		m_pFileImpl = new FileZip(cFinalUrl, sZipFile, sPathInZip, pAccess);
	}

	// HTTP
	else if (cFinalUrl.GetProtocol() == "http://") {
		m_pFileImpl = new FileHttp(cUrl, pAccess);
	}

	// System file
	else {
		#if defined(WIN32)
			m_pFileImpl = new FileWindows(cFinalUrl, pAccess);
		#elif defined(LINUX)
			m_pFileImpl = new FileLinux(cFinalUrl, pAccess);
		#else
			#error "Unsupported platform"
		#endif
	}
}

/**
*  @brief
*    Assign a new file
*/
void FileObject::Assign(FILE *pFile, uint32 nAccess)
{
	// Delete existing file implementation
	if (m_pFileImpl) {
		delete m_pFileImpl;
		m_pFileImpl = nullptr;
	}

	// Create file implementation
	m_pFileImpl = new FileStdStream((FILE*)pFile, nAccess);
}

/**
*  @brief
*    Assign a new file
*/
void FileObject::Assign(handle hFile)
{
	// Delete existing file implementation
	if (m_pFileImpl) {
		delete m_pFileImpl;
		m_pFileImpl = nullptr;
	}

	// Create file implementation
	m_pFileImpl = new FileStdStream(hFile);
}

/**
*  @brief
*    Get URL
*/
const Url &FileObject::GetUrl() const
{
	return m_pFileImpl ? m_pFileImpl->m_cUrl : m_cNullUrl;
}

/**
*  @brief
*    Check if the file or directory exists
*/
bool FileObject::Exists() const
{
	return m_pFileImpl ? m_pFileImpl->Exists() : false;
}

/**
*  @brief
*    Returns if the object is a file
*/
bool FileObject::IsFile() const
{
	return m_pFileImpl ? m_pFileImpl->IsFile() : false;
}

/**
*  @brief
*    Returns if the object is a directory
*/
bool FileObject::IsDirectory() const
{
	return m_pFileImpl ? m_pFileImpl->IsDirectory() : false;
}

/**
*  @brief
*    Copy the file or directory to a new location
*/
bool FileObject::Copy(const String &sDest, bool bOverwrite) const
{
	if (m_pFileImpl) {
		// Try system-implementation
		if (m_pFileImpl->CopyTo(sDest, bOverwrite))
			return true; // Done

		// Fallback: Use generic function (e.g. if the files exist in different file-systems)
		return GenericCopy(sDest, bOverwrite);
	} else {
		return false;
	}
}

/**
*  @brief
*    Move the file or directory to a new location
*/
bool FileObject::Move(const String &sDest)
{
	if (m_pFileImpl) {
		// Try system-implementation
		if (m_pFileImpl->MoveTo(sDest))
			return true; // Done

		// Fallback: Use generic function (e.g. if the files exist in different file-systems)
		return GenericMove(sDest);
	} else {
		return false;
	}
}

/**
*  @brief
*    Rename the file or directory
*/
bool FileObject::Rename(const String &sName)
{
	return m_pFileImpl ? m_pFileImpl->Rename(sName) : false;
}

/**
*  @brief
*    Close the file or directory
*/
void FileObject::Close()
{
	if (m_pFileImpl)
		m_pFileImpl->Close();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Generic implementation of Copy (if system-implementation does not work)
*/
bool FileObject::GenericCopy(const String &sDest, bool bOverwrite) const
{
	// Check input file
	File cInput(GetUrl());
	if (cInput.Exists()) {
		// Check output file
		File cOutput(sDest);
		if (!cOutput.Exists() || bOverwrite) {
			// Try to copy
			bool bSuccess = false;
			if (cInput.Open(File::FileRead)) {
				if (cOutput.Open(File::FileWrite | File::FileCreate)) {
					// Copy file
					char szBuffer[4096];
					while (!cInput.IsEof()) {
						const uint32 nSize = cInput.Read(szBuffer, 1, 4096);
						cOutput.Write(szBuffer, 1, nSize);
					}

					// Close output
					cOutput.Close();
				}

				// Close input
				cInput.Close();
			}

			// Return result
			return bSuccess;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Generic implementation of Move (if system-implementation does not work)
*/
bool FileObject::GenericMove(const String &sDest)
{
	// Check input file
	File cInput(GetUrl());
	if (cInput.Exists()) {
		// Check output file
		File cOutput(sDest);
		if (!cOutput.Exists()) {
			// Try to copy
			bool bSuccess = false;
			if (cInput.Open(File::FileRead)) {
				if (cOutput.Open(File::FileWrite | File::FileCreate)) {
					// Copy file
					char szBuffer[4096];
					while (!cInput.IsEof()) {
						const uint32 nSize = cInput.Read(szBuffer, 1, 4096);
						cOutput.Write(szBuffer, 1, nSize);
					}

					// Close output
					cOutput.Close();
				}

				// Close input
				cInput.Close();
			}

			// Delete input file
			if (bSuccess) {
				bSuccess = cInput.Delete();
			}

			// Return result
			return bSuccess;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
FileObject::FileObject(const FileObject &cSource) :
	m_pFileImpl(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
FileObject &FileObject::operator =(const FileObject &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
