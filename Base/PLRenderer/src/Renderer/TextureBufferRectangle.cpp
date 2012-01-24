/*********************************************************\
 *  File: TextureBufferRectangle.cpp                     *
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
#include <PLMath/Math.h>
#include "PLRenderer/Renderer/TextureBufferRectangle.h"


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
TextureBufferRectangle::~TextureBufferRectangle()
{
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureBufferRectangle::TextureBufferRectangle(Renderer &cRenderer, uint32 nFlags) : TextureBuffer(cRenderer, TypeTextureBufferRectangle, nFlags)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
TextureBufferRectangle::TextureBufferRectangle(const TextureBufferRectangle &cSource) : TextureBuffer(cSource.GetRenderer(), cSource.GetType(), TypeTextureBufferRectangle),
	m_vSize(cSource.m_vSize)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
TextureBufferRectangle &TextureBufferRectangle::operator =(const TextureBufferRectangle &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual TextureBuffer functions                ]
//[-------------------------------------------------------]
bool TextureBufferRectangle::IsPowerOfTwo() const
{
	return (Math::IsPowerOfTwo(m_vSize.x) && Math::IsPowerOfTwo(m_vSize.y));
}

uint32 TextureBufferRectangle::GetNumOfPixels(uint32 nMipmap) const
{
	// Check the given parameter
	if (nMipmap <= m_nNumOfMipmaps) {
		// [TODO] Currently mipmaps are not supported for rectangle texture buffers

		// Get the size of the mipmap level
//		const Vector2i vSize = GetSize(nMipmap);

		// Return the number of pixels of the mipmap level
		return m_vSize.x*m_vSize.y;
	}

	// Error!
	return 0;
}

uint32 TextureBufferRectangle::GetNumOfBytes(uint32 nMipmap, EPixelFormat nFormat) const
{
	// Check the given parameter
	if (nMipmap <= m_nNumOfMipmaps) {

		// [TODO] Currently mipmaps are not supported for rectangle texture buffers

		if (nFormat == Unknown)
			nFormat = m_nFormat;
		if (IsCompressedFormat(nFormat)) {
			// DXT formats divide the texture buffer into 4x4 blocks, each block has a fixed number of bytes
			switch (nFormat) {
				case DXT1:
				case LATC1:
					return ((m_vSize.x+3)/4)*((m_vSize.y+3)/4)*8;

				case DXT3:
				case DXT5:
				case LATC2:
					return ((m_vSize.x+3)/4)*((m_vSize.y+3)/4)*16;
			}
		} else {
			return GetBytesPerPixel(nFormat)*m_vSize.x*m_vSize.y;
		}
	}

	// Error!
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
