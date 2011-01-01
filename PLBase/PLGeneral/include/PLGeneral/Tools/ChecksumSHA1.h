/*********************************************************\
 *  File: ChecksumSHA1.h                                 *
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


#ifndef __PLGENERAL_CHECKSUMSHA1_H__
#define __PLGENERAL_CHECKSUMSHA1_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    SHA-1 (Secure Hash Algorithm) checksum
*
*  @remarks
*    The Secure Hash Algorithm SHA-1 is a cryptographically secure one-way hash algorithm.
*    It was designed by the NIST (National Institute of Standards and Technology), along
*    with the NSA (National Security Agency). SHA-1 is based on the Message Digest MD4
*    algorithm design principles by Ronald L. Rivest of MIT.
*
*    This implementation is basing on the 100% free public domain implementation of the
*    SHA-1 algorithm by Dominik Reichl (http://www.dominik-reichl.de/)
*
*  @note
*    - SHA-1 produces a 160-bit/20-byte hash
*/
class ChecksumSHA1 : public Checksum {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API ChecksumSHA1();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~ChecksumSHA1();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    SHA-1 transformation
		*
		*  @param[in, out] nState
		*    State
		*  @param[in]      nBuffer
		*    Buffer
		*/
		void Transform(uint32 nState[], const uint8 nBuffer[]) const;


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Workspace block
		*/
		typedef union {
			uint8  c[64];
			uint32 l[16];
		} WorkspaceBlock;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32			m_nState[5];
		uint32			m_nCount[2];
		uint8			m_nBuffer[64];
		uint8			m_nWorkspace[64];
		WorkspaceBlock *m_pBlock;			/**< SHA1 pointer to the byte array above (always valid!) */


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


#endif // __PLGENERAL_CHECKSUMSHA1_H__

