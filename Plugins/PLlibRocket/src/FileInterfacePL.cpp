/*********************************************************\
 *  File: FileInterfacePL.cpp                            *
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
#include <PLCore/File/File.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLlibRocket/FileInterfacePL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLlibRocket {


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

		// Try to open the file
		if (LoadableManager::GetInstance()->OpenFile(*pFile, String::FromUTF8(path.CString()), false))
			return reinterpret_cast<Rocket::Core::FileHandle>(pFile); // Return opened file object

		// Cleanup on error
		delete pFile;
	}

	// Error!
	return static_cast<Rocket::Core::FileHandle>(0);	// nullptr may cause some compiler issues in here
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
} // PLlibRocket
