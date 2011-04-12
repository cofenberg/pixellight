/*********************************************************\
 *  File: FileInterfacePL.cpp                            *
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
#include <PLGeneral/File/File.h>
#include <PLCore/Tools/LoadableManager.h>
#include "libRocket_PL/FileInterfacePL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
FileInterfacePL::FileInterfacePL()
{
}

/**
*  @brief
*    Destructor
*/
FileInterfacePL::~FileInterfacePL()
{
}


//[-------------------------------------------------------]
//[ Public virtual Rocket::Core::FileInterface functions  ]
//[-------------------------------------------------------]
Rocket::Core::FileHandle FileInterfacePL::Open(const Rocket::Core::String& path)
{
	if (path.Length()) {
		// Create the file object
		File *pFile = new File();

		// Because absolute filenames can be accessed fastest by the file system, we first give
		// the file system an absolute filename which is hopefully the correct one... if
		// not, we must search the file which is quite slow...
		String sUrl = String::FromUTF8(path.CString());
		Url cUrl(sUrl);
		if (cUrl.IsAbsolute()) {
			// The given filename is already absolute! :)
			pFile->Assign(sUrl);
		} else {
			// Loop through all base directories
			for (uint32 nBaseDir=0; nBaseDir<LoadableManager::GetInstance()->GetNumOfBaseDirs() && !pFile->IsFile(); nBaseDir++) {
				String sBaseDir = LoadableManager::GetInstance()->GetBaseDir(nBaseDir);

				// Construct absolute filename and check file
				String sAbsFilename = sBaseDir + sUrl;
				pFile->Assign(sAbsFilename);

				// Is this a correct file?
				if (!pFile->IsFile()) {
					// Try to open the file directly
					sAbsFilename = sBaseDir + sUrl;
					pFile->Assign(sAbsFilename);
				}
			}
		}

		// Try to open the file
		if (pFile->Open(File::FileRead))
			return reinterpret_cast<Rocket::Core::FileHandle>(pFile); // Return opend file object

		// Cleanup on error
		delete pFile;
	}

	// Error!
	return NULL;	// nullptr may cause some compiler issues in here
}

void FileInterfacePL::Close(Rocket::Core::FileHandle file)
{
	if (file) {
		reinterpret_cast<File*>(file)->Close();
		delete reinterpret_cast<File*>(file);
	}
}

size_t FileInterfacePL::Read(void* buffer, size_t size, Rocket::Core::FileHandle file)
{
	return file ? reinterpret_cast<File*>(file)->Read(buffer, 1, size) : -1;
}

bool FileInterfacePL::Seek(Rocket::Core::FileHandle file, long offset, int origin)
{
	if (file) {
		switch (origin) {
			case SEEK_SET:
				return reinterpret_cast<File*>(file)->Seek(offset, File::SeekSet);

			case SEEK_CUR:
				return reinterpret_cast<File*>(file)->Seek(offset, File::SeekCurrent);

			case SEEK_END:
				return reinterpret_cast<File*>(file)->Seek(offset, File::SeekEnd);
		}
	}

	// Error!
	return false;
}

size_t FileInterfacePL::Tell(Rocket::Core::FileHandle file)
{
	return file ? reinterpret_cast<File*>(file)->Tell() : -1;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
FileInterfacePL::FileInterfacePL(const FileInterfacePL &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
FileInterfacePL &FileInterfacePL::operator =(const FileInterfacePL &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL
