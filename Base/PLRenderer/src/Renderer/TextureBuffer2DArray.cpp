/*********************************************************\
 *  File: TextureBuffer2DArray.cpp                       *
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
#include "PLRenderer/Renderer/TextureBuffer2DArray.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBuffer2DArray::~TextureBuffer2DArray()
{
}

/**
*  @brief
*    Returns the texture buffer size
*/
Vector3i TextureBuffer2DArray::GetSize(uint32 nMipmap) const
{
	// Check the given parameter
	if (nMipmap > m_nNumOfMipmaps)
		return Vector3i::Zero; // Error!

	// Get the size of the mipmap level
	Vector3i vSize = m_vSize;
	uint32 nCurrentMipmap = 0;
	while (nCurrentMipmap < nMipmap) {
		vSize.x >>= 1;
		vSize.y >>= 1;
		vSize.z >>= 1;
		nCurrentMipmap++;
	}
	if (vSize.x < 1)
		vSize.x = 1;
	if (vSize.y < 1)
		vSize.y = 1;
	if (vSize.z < 1)
		vSize.z = 1;

	// Return the size
	return vSize;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureBuffer2DArray::TextureBuffer2DArray(Renderer &cRenderer, uint32 nFlags) : TextureBuffer(cRenderer, TypeTextureBuffer2DArray, nFlags)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
TextureBuffer2DArray::TextureBuffer2DArray(const TextureBuffer2DArray &cSource) : TextureBuffer(cSource.GetRenderer(), cSource.GetType(), TypeTextureBuffer2DArray),
	m_vSize(cSource.m_vSize)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
TextureBuffer2DArray &TextureBuffer2DArray::operator =(const TextureBuffer2DArray &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual TextureBuffer functions                ]
//[-------------------------------------------------------]
uint32 TextureBuffer2DArray::GetNumOfPixels(uint32 nMipmap) const
{
	// Check the given parameter
	if (nMipmap <= m_nNumOfMipmaps) {
		// Get the size of the mipmap level
		const Vector3i vSize = GetSize(nMipmap);

		// Return the number of pixels of the mipmap level
		return vSize.x*vSize.y*vSize.z;
	}

	// Error!
	return 0;
}

uint32 TextureBuffer2DArray::GetNumOfBytes(uint32 nMipmap, EPixelFormat nFormat) const
{
	// Check the given parameter
	if (nMipmap <= m_nNumOfMipmaps) {
		// Get the size of the mipmap level
		const Vector3i vSize = GetSize(nMipmap);

		// Calculate the number of bytes
		if (nFormat == Unknown)
			nFormat = m_nFormat;
		if (IsCompressedFormat(nFormat)) {
			// DXT formats divide the texture buffer into 4x4 blocks, each block has a fixed number of bytes
			switch (nFormat) {
				case DXT1:
				case LATC1:
					return ((vSize.x+3)/4)*((vSize.y+3)/4)*8*vSize.z;

				case DXT3:
				case DXT5:
				case LATC2:
					return ((vSize.x+3)/4)*((vSize.y+3)/4)*16*vSize.z;
			}
		} else {
			return GetBytesPerPixel(nFormat)*vSize.x*vSize.y*vSize.z;
		}
	}

	// Error!
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
