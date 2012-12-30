/*********************************************************\
 *  File: FileInterfacePL.cpp                            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
