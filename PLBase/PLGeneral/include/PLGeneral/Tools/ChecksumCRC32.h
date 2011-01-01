/*********************************************************\
 *  File: ChecksumCRC32.h                                *
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


#ifndef __PLGENERAL_CHECKSUMCRC32_H__
#define __PLGENERAL_CHECKSUMCRC32_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Array.h"
#include "PLGeneral/Tools/Checksum.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    CRC32 (cyclic redundancy check) checksum
*
*  @remarks
*    This implementation is using the official polynomial (0x04C11DB7) used by CRC32 in
*    PKZip, WinZip and Ethernet. Often times the polynomial shown reversed as 0xEDB88320.
*
*  @note
*    - CRC32 produces a 32-bit/4-byte hash
*/
class ChecksumCRC32 : public Checksum {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API ChecksumCRC32();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~ChecksumCRC32();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes the CRC32 table
		*/
		void Init();

		/**
		*  @brief
		*    Reflection part of the the CRC32 table initialization
		*
		*  @param[in] nReflection
		*    Reflection value
		*  @param[in] nCharacter
		*    Character to reflect
		*
		*  @return
		*    The reflected character
		*
		*  @remarks
		*    Reflection is a requirement for the official CRC-32 standard.
		*/
		uint32 Reflect(uint32 nReflection, char nCharacter) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		static Array<uint32> m_lstCRC32Table;	/**< Static CRC32 table */
		uint32				 m_nCRC32;			/**< Current CRC32 checksum */


	//[-------------------------------------------------------]
	//[ Private virtual Checksum functions                    ]
	//[-------------------------------------------------------]
	private:
		virtual void Update(const uint8 nInput[], uint32 nInputLen);
		virtual String Final();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_CHECKSUMCRC32_H__

