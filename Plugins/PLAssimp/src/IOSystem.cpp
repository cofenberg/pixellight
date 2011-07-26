/*********************************************************\
 *  File: IOSystem.cpp                                   *
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
#include <PLCore/File/File.h>
#include <PLCore/System/System.h>
#include "PLAssimp/IOStream.h"
#include "PLAssimp/IOSystem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Public definitions                                    ]
//[-------------------------------------------------------]
const char *IOSystem::MagicDefaultFilename       = "$$$___magic___$$$";
const int   IOSystem::MagicDefaultFilenameLength = 17;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IOSystem::IOSystem(File &cFile, const char *pszMagicDefaultFilename, int nMagicDefaultFilenameLength) :
	m_pFile(&cFile),
	m_pszMagicDefaultFilename(pszMagicDefaultFilename),
	m_nMagicDefaultFilenameLength(nMagicDefaultFilenameLength)
{
}

/**
*  @brief
*    Destructor
*/
IOSystem::~IOSystem()
{
}


//[-------------------------------------------------------]
//[ Public virtual Assimp::IOSystem functions             ]
//[-------------------------------------------------------]
bool IOSystem::Exists(const char *pFile) const
{
	// Is it the default file? (concept based on "Assimp::MemoryIOSystem")
	if (!strncmp(pFile, m_pszMagicDefaultFilename, m_nMagicDefaultFilenameLength)) {
		// Jap, it's the default file
		return true;
	} else {
		// Check whether or not the requested file exists
		return File(GetRealFilename(pFile)).Exists();
	}
}

char IOSystem::getOsSeparator() const
{
	static const char nSeparator = System::GetInstance()->GetSeparator();
	return nSeparator;
}

Assimp::IOStream *IOSystem::Open(const char *pFile, const char *pMode)
{
	// Is it the default file? (concept based on "Assimp::MemoryIOSystem")
	if (!strncmp(pFile, m_pszMagicDefaultFilename, m_nMagicDefaultFilenameLength)) {
		// Jap, it's the default file

		// Reset file reading
		m_pFile->Seek();

		// Wrap the file into an Assimp IO stream and return the IO stream
		return new IOStream(*m_pFile, false);
	} else {
		// Get access flags
		uint32 nAccess = 0;
		{
			const String sMode = pMode;

			// Read, write and file must exist
			if (sMode.IsSubstring("r+")) {
				nAccess |= File::FileRead;		// File can be read
				nAccess |= File::FileWrite;		// File can be written

			// Read, write and create new empty file (content of previous file is destroyed)
			} else if (sMode.IsSubstring("w+")) {
				nAccess |= File::FileRead;		// File can be read
				nAccess |= File::FileWrite;		// File can be written
				nAccess |= File::FileCreate;	// File will be created

			// Read and append
			} else if (sMode.IsSubstring("a+")) {
				nAccess |= File::FileRead;		// File can be read
				nAccess |= File::FileAppend;	// File will be appended

			// Read and file must exist
			} else if (sMode.IsSubstring("r")) {
				nAccess |= File::FileRead;		// File can be read

			// Write and create new empty file (content of previous file is destroyed)
			} else if (sMode.IsSubstring("w")) {
				nAccess |= File::FileWrite;		// File can be written
				nAccess |= File::FileCreate;	// File will be created

			// Append
			} else if (sMode.IsSubstring("a")) {
				nAccess |= File::FileAppend;	// File will be appended
			}

			// Text mode
			if (sMode.IsSubstring("t"))
				nAccess |= File::FileText;		// File will be opened in text mode

			// Check for "b" not required, this is default if text mode is not set
		}

		// Create the file object
		File *pFileObject = new File(GetRealFilename(pFile));

		// Open the file, or at least try it
		if (pFileObject->Open(nAccess)) {
			// Wrap the file into an Assimp IO stream and return the IO stream
			return new IOStream(*pFileObject, true);
		}

		// Error! Destroy the file object and get us out of here..
		delete pFileObject;
		return nullptr;
	}
}

void IOSystem::Close(Assimp::IOStream *pFile)
{
	// Is there a valid Assimp IO stream?
	if (pFile) {
		// Destroy the file object (this also automatically closes the file) - but only if it's not the default file!
		File *pFileObject = reinterpret_cast<IOStream*>(pFile)->m_pFile;
		if (m_pFile != pFileObject)
			delete pFileObject;

		// Destroy the Assimp IO stream
		delete pFile;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IOSystem::IOSystem() :
	m_pFile(nullptr),
	m_pszMagicDefaultFilename(nullptr),
	m_nMagicDefaultFilenameLength(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy constructor
*/
IOSystem::IOSystem(const IOSystem &cSource) :
	m_pFile(nullptr),
	m_pszMagicDefaultFilename(nullptr),
	m_nMagicDefaultFilenameLength(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
IOSystem &IOSystem::operator =(const IOSystem &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Returns a real filename
*/
String IOSystem::GetRealFilename(const char *pszAssimpFile) const
{
	// Is the filename using the basename of the default?
	if (!strncmp(pszAssimpFile, MagicDefaultFilename, MagicDefaultFilenameLength)) {
		// Ok... we need to construct the real filename
		String sFilename = String::FromUTF8(pszAssimpFile);	// Get given filenname
		sFilename.Delete(0, MagicDefaultFilenameLength);	// Cut of the magic thingy
		sFilename.Insert(m_pFile->GetUrl().GetTitle(), 0);	// Insert the title of the complete filename

		// Return the real filename
		return sFilename;
	} else {
		// Return the given filename
		return String::FromUTF8(pszAssimpFile);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
