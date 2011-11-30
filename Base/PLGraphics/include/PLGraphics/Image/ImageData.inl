/*********************************************************\
 *  File: ImageData.inl                                  *
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
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline ImageData::ImageData() :
	m_nDataFormat(DataByte),
	m_nColorFormat(ColorRGB),
	m_nCompression(CompressionNone),
	m_pData(nullptr),
	m_nDataSize(0),
	m_bDataShared(false),
	m_pCompressedData(nullptr),
	m_nCompressedSize(0),
	m_pPalette(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
inline ImageData::~ImageData()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Get data format
*/
inline EDataFormat ImageData::GetDataFormat() const
{
	// Return format
	return m_nDataFormat;
}

/**
*  @brief
*    Get color format
*/
inline EColorFormat ImageData::GetColorFormat() const
{
	// Return color format
	return m_nColorFormat;
}

/**
*  @brief
*    Get compression type
*/
inline ECompression ImageData::GetCompression() const
{
	// Return compression type
	return m_nCompression;
}

/**
*  @brief
*    Get image size
*/
inline PLMath::Vector3i ImageData::GetSize() const
{
	// Return size
	return m_vSize;
}

/**
*  @brief
*    Check if uncompressed or compressed data is available
*/
inline bool ImageData::HasAnyData() const
{
	// Check if image buffer is valid
	return (m_pData != nullptr || m_pCompressedData != nullptr);
}

/**
*  @brief
*    Check if uncompressed data is available
*/
inline bool ImageData::HasData() const
{
	// Check if image buffer is valid
	return (m_pData != nullptr);
}

/**
*  @brief
*    Get size of image data
*/
inline PLCore::uint32 ImageData::GetDataSize() const
{
	// Return size of image data
	return m_nDataSize;
}

/**
*  @brief
*    Check if compressed data is available
*/
inline bool ImageData::HasCompressedData() const
{
	// Check if compressed image buffer is valid
	return (m_pCompressedData != nullptr);
}

/**
*  @brief
*    Get size of compressed image data
*/
inline PLCore::uint32 ImageData::GetCompressedDataSize() const
{
	// Return size of compressed image data
	return m_nCompressedSize;
}

/**
*  @brief
*    Get color palette
*/
inline const ImagePalette *ImageData::GetPalette() const
{
	// Return palette
	return m_pPalette;
}

/**
*  @brief
*    Get color palette
*/
inline ImagePalette *ImageData::GetPalette()
{
	// Return palette
	return m_pPalette;
}

/**
*  @brief
*    Create image buffer
*/
inline void ImageData::CreateBuffer()
{
	// Check if size is valid and buffer has not been created before
	if (m_nDataSize > 0 && !m_pData) {
		// Create image buffer
		m_pData = new PLCore::uint8[m_nDataSize];
	}
}


/**
*  @brief
*    Create compressed image buffer
*/
inline void ImageData::CreateCompressedBuffer()
{
	// Check if size is valid and buffer has not been created before
	if (m_nCompressedSize > 0 && !m_pCompressedData) {
		// Create compressed image buffer
		m_pCompressedData = new PLCore::uint8[m_nCompressedSize];
	}
}

/**
*  @brief
*    Destroy image buffer
*/
inline void ImageData::DestroyBuffer()
{
	// Destroy image data
	if (m_pData) {
		// Do we own the image data?
		if (m_bDataShared)
			m_bDataShared = false;
		else
			delete [] m_pData;

		// Reset data pointer
		m_pData = nullptr;
	}
}

/**
*  @brief
*    Destroy compressed image buffer
*/
inline void ImageData::DestroyCompressedBuffer()
{
	// Destroy compressed image data
	if (m_pCompressedData) {
		delete [] m_pCompressedData;
		m_pCompressedData = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
