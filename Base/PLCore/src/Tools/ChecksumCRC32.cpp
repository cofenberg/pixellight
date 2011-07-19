/*********************************************************\
 *  File: ChecksumCRC32.cpp                              *
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
#include "PLCore/Tools/ChecksumCRC32.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
Array<uint32> ChecksumCRC32::m_lstCRC32Table;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ChecksumCRC32::ChecksumCRC32() :
	m_nCRC32(0xFFFFFFFF)
{
}

/**
*  @brief
*    Destructor
*/
ChecksumCRC32::~ChecksumCRC32()
{
}

/**
*  @brief
*    Initializes the CRC32 table
*/
void ChecksumCRC32::Init()
{
	uint32 nPolynomial = 0x04C11DB7;

	m_lstCRC32Table.Resize(256);
	for (int i=0; i<256; i++) {
		m_lstCRC32Table[i] = Reflect(i, 8) << 24;
		for (int j=0; j<8; j++)
			m_lstCRC32Table[i] = (m_lstCRC32Table[i] << 1) ^ (m_lstCRC32Table[i] & (1 << 31) ? nPolynomial : 0);
		m_lstCRC32Table[i] = Reflect(m_lstCRC32Table[i], 32);
	}
}

/**
*  @brief
*    Reflection part of the the CRC32 table initialization
*/
uint32 ChecksumCRC32::Reflect(uint32 nReflection, char nCharacter) const
{
	uint32 nValue = 0;

	// Swap bit 0 for bit 7 bit 1 for bit 6, etc.
	for (int i=1; i<(nCharacter+1); i++) {
		if (nReflection & 1)
			nValue |= 1 << (nCharacter - i);
		nReflection >>= 1;
	}

	// Done
	return nValue;
}


//[-------------------------------------------------------]
//[ Private virtual Checksum functions                    ]
//[-------------------------------------------------------]
void ChecksumCRC32::Update(const uint8 nInput[], uint32 nInputLen)
{
	// Initialize the CRC32 table?
	if (!m_lstCRC32Table.GetNumOfElements())
		Init();

	// Update current checksum
	const uint8 *pInput = nInput;
	for (uint32 i=0; i<nInputLen; i++)
		m_nCRC32 = (m_nCRC32 >> 8) ^ m_lstCRC32Table[(m_nCRC32 & 0xFF) ^ *pInput++];
}

String ChecksumCRC32::Final()
{
	// Exclusive OR the result with the beginning value
	return String::Format("%x", m_nCRC32^0xFFFFFFFF);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
