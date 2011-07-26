/*********************************************************\
 *  File: IOStream.cpp                                   *
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
#include "PLAssimp/IOStream.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
IOStream::~IOStream()
{
	// Are we responsible for the file object?
	if (m_bTakeOver)
		delete m_pFile;	// Destroy the file object (this also automatically closes the file)
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IOStream::IOStream(File &cFile, bool bTakeOver) :
	m_pFile(&cFile),
	m_bTakeOver(bTakeOver)
{
}


//[-------------------------------------------------------]
//[ Public virtual Assimp::IOStream functions             ]
//[------------------------------------------------------]
size_t IOStream::Read(void *pvBuffer, size_t pSize, size_t pCount)
{
	return m_pFile->Read(pvBuffer, pSize, pCount);
}

size_t IOStream::Write(const void *pvBuffer, size_t pSize, size_t pCount)
{
	return m_pFile->Write(pvBuffer, pSize, pCount);
}

aiReturn IOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
	File::ESeek nLocation = File::SeekSet;
	switch (pOrigin) {
		case aiOrigin_SET:
			nLocation = File::SeekSet;
			break;

		case aiOrigin_CUR:
			nLocation = File::SeekCurrent;
			break;

		case aiOrigin_END:
			nLocation = File::SeekEnd;
			break;
	}
	return m_pFile->Seek(pOffset, nLocation) ? aiReturn_SUCCESS : aiReturn_FAILURE;
}

size_t IOStream::Tell() const
{
	return m_pFile->Tell();
}

size_t IOStream::FileSize() const
{
	return m_pFile->GetSize();
}

void IOStream::Flush()
{
	m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IOStream::IOStream() :
	m_pFile(nullptr),
	m_bTakeOver(false)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy constructor
*/
IOStream::IOStream(const IOStream &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
IOStream &IOStream::operator =(const IOStream &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
