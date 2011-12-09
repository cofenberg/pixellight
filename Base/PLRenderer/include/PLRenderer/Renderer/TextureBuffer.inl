/*********************************************************\
 *  File: TextureBuffer.inl                              *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture buffer flags
*/
inline PLCore::uint32 TextureBuffer::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Returns the texture buffer pixel format
*/
inline TextureBuffer::EPixelFormat TextureBuffer::GetFormat() const
{
	return m_nFormat;
}

/**
*  @brief
*    Returns whether or not the used texture buffer format is compressed
*/
inline bool TextureBuffer::IsCompressedFormat() const
{
	return IsCompressedFormat(m_nFormat);
}

/**
*  @brief
*    Returns whether or not the used texture buffer format is a depth buffer format
*/
inline bool TextureBuffer::IsDepthFormat() const
{
	return IsDepthFormat(m_nFormat);
}

/**
*  @brief
*    If the used texture buffer format is compressed, a proper uncompressed texture buffer format will be returned
*/
inline TextureBuffer::EPixelFormat TextureBuffer::GetUncompressedFormat() const
{
	return GetUncompressedFormat(m_nFormat);
}

/**
*  @brief
*    Returns whether or not the used texture buffer format is a floating point format
*/
inline bool TextureBuffer::IsFloatingPointFormat() const
{
	return IsFloatingPointFormat(m_nFormat);
}

/**
*  @brief
*    Returns the number of components per pixel
*/
inline PLCore::uint32 TextureBuffer::GetComponentsPerPixel() const
{
	return GetComponentsPerPixel(m_nFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
inline PLCore::uint32 TextureBuffer::GetBytesPerPixelComponent() const
{
	return GetBytesPerPixelComponent(m_nFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
inline PLCore::uint32 TextureBuffer::GetBytesPerPixel() const
{
	return GetBytesPerPixel(m_nFormat);
}

/**
*  @brief
*    Returns the number of mipmap levels
*/
inline PLCore::uint32 TextureBuffer::GetNumOfMipmaps() const
{
	return m_nNumOfMipmaps;
}

/**
*  @brief
*    Returns the number of faces
*/
inline PLCore::uint8 TextureBuffer::GetNumOfFaces() const
{
	return (GetType() == TypeTextureBufferCube) ? 6 : 1;
}

/**
*  @brief
*    Returns the total number of bytes required for the texture buffer data including all mipmaps
*/
inline PLCore::uint32 TextureBuffer::GetTotalNumOfBytes() const
{
	return m_nTotalNumOfBytes;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
