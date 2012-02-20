/*********************************************************\
 *  File: Checksum.cpp                                   *
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
#include "PLCore/File/File.h"
#include "PLCore/Tools/Checksum.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the checksum of a given buffer
*/
String Checksum::Get(const uint8 *pnBuffer, uint32 nNumOfBytes)
{
	// Check buffer size
	if (nNumOfBytes) {
		// Get the checksum
		Update(pnBuffer, nNumOfBytes);
		String sChecksum = Final();

		// Return the checksum
		return sChecksum;
	}

	// Error!
	return "";
}

/**
*  @brief
*    Returns the checksum of a given string
*/
String Checksum::Get(const String &sString)
{
	// Get the checksum
	if (sString.GetFormat() == String::Unicode)
		Update(reinterpret_cast<const uint8*>(sString.GetUnicode()), sString.GetNumOfBytes(String::Unicode));
	else
		Update(reinterpret_cast<const uint8*>(sString.GetASCII()),   sString.GetNumOfBytes(String::ASCII));
	String sChecksum = Final();

	// Return the checksum
	return sChecksum;
}

/**
*  @brief
*    Returns the checksum of a given file
*/
String Checksum::Get(File &cFile)
{
	// First at all, check the given file
	if (cFile.IsReadable()) {
		// Backup the current file position
		int32 nFilePosition = cFile.Tell();

		// Checksum the file in blocks of 1024 bytes
		const uint32 nBufferSize = 1024;							// Checksum the file in blocks of 1024 bytes
		uint8		 nBuffer[nBufferSize];							// Buffer for data read from the file
		uint32		 nLength = cFile.Read(nBuffer, 1, nBufferSize);	// Number of bytes read from the file
		while (nLength > 0) {
			// Update the checksum
			Update(nBuffer, nLength);

			// Update the buffer
			nLength = cFile.Read(nBuffer, 1, nBufferSize);
		}
		String sChecksum = Final();

		// Reset the current file position
		cFile.Seek(nFilePosition);

		// Return the checksum
		return sChecksum;
	}

	// Error!
	return "";
}

/**
*  @brief
*    Returns the checksum of a given file
*/
String Checksum::GetFile(const String &sFilename)
{
	// Check parameters
	if (sFilename.GetLength()) {
		// Open the file
		File cFile(sFilename);
		if (cFile.Exists() && cFile.IsFile() && cFile.Open(File::FileRead)) {
			// Get the checksum
			const String sChecksum = Get(cFile);

			// Close the file
			cFile.Close();

			// Done
			return sChecksum;
		}
	}

	// Error!
	return "";
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Checksum::Checksum()
{
}

/**
*  @brief
*    Destructor
*/
Checksum::~Checksum()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Checksum::Checksum(const Checksum &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Checksum &Checksum::operator =(const Checksum &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
