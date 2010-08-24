/*********************************************************\
 *  File: Checksum.h                                     *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_CHECKSUM_H__
#define __PLGENERAL_CHECKSUM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class File;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract checksum ("digital fingerprint") base class
*
*  @remarks
*    Normally a checksum is used to detect errors after transmission or storage. Before transmission
*    or storage of data, a checksum of the data is calculated and send/saved. Afterwards the received
*    data is verified by using the checksum to confirm that no changes occurred on transit.
*
*  @note
*    - Each time a checksum is calculated, an instance of the class is created and destroyed at the end
*/
class Checksum {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the checksum of a given buffer
		*
		*  @param[in] nBuffer
		*    Buffer to create the checksum from
		*  @param[in] nNumOfBytes
		*    Number of bytes of the given buffer (MUST be valid!)
		*
		*  @return
		*    The checksum of the given buffer, empty on error (maybe empty buffer?)
		*/
		PLGENERAL_API String Get(const uint8 nBuffer[], uint32 nNumOfBytes);

		/**
		*  @brief
		*    Returns the checksum of a given string
		*
		*  @param[in] sString
		*    String to create the checksum from, the original internal format is used -
		*    if it's a Unicode string, Unicode will be used to get the checksum
		*
		*  @return
		*    The checksum of the given string, empty on error (maybe unknown class?)
		*
		*  @note
		*     - sString: "My text" != L"My text" (ASCII != Unicode even if the text itself is the same!)
		*/
		PLGENERAL_API String Get(const String &sString);

		/**
		*  @brief
		*    Returns the checksum of a given file
		*
		*  @param[in] cFile
		*    File to create the checksum from (MUST be opened and readable!)
		*
		*  @return
		*    The checksum of the given file, empty string on error
		*    (maybe unknown class or the given file is invalid?)
		*
		*  @note
		*    - The current file offset is not changed
		*/
		PLGENERAL_API String Get(File &cFile);

		/**
		*  @brief
		*    Returns the checksum of a given file
		*
		*  @param[in] sFilename
		*    Name of the file to create the checksum from
		*
		*  @return
		*    The checksum of the given file, empty on error (maybe unknown class or invalid file?)
		*/
		PLGENERAL_API String GetFile(const String &sFilename);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGENERAL_API Checksum();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~Checksum();


	//[-------------------------------------------------------]
	//[ Protected virtual Checksum functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Implementation of main checksum algorithm
		*
		*  @param[in] nInput
		*    Input block
		*  @param[in] nInputLen
		*    Length of input block in bytes
		*
		*  @remarks
		*    Computes the partial checksum for 'nInputLen' bytes of data in 'Input'.
		*/
		virtual void Update(const uint8 nInput[], uint32 nInputLen) = 0;

		/**
		*  @brief
		*    Implementation of main checksum algorithm; ends the checksum calculation.
		*
		*  @return
		*    The final hexadecimal checksum result
		*    (without the 0x prefix and with lower case hex characters)
		*
		*  @remarks
		*    Performs the final checksum calculation. 'Update' does most of the work,
		*    this function just finishes the calculation.
		*/
		virtual String Final() = 0;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Checksum(const Checksum &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Checksum &operator =(const Checksum &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_CHECKSUM_H__
