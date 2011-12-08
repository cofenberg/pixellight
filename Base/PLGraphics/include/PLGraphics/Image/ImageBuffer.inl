/*********************************************************\
 *  File: ImageBuffer.inl                                *
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
#include "PLGraphics/Image/ImageData.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of bytes per pixel
*/
inline PLCore::uint32 ImageBuffer::GetBytesPerPixel(EDataFormat nDataFormat, EColorFormat nColorFormat)
{
	// Get number of bytes of a whole pixel
	return GetComponentsPerPixel(nColorFormat) * GetBytesPerPixelComponent(nDataFormat);
}

/**
*  @brief
*    Returns whether or not the given color format has an alpha channel
*/
inline bool ImageBuffer::IsAlphaChannelColorFormat(EColorFormat nColorFormat)
{
	return (nColorFormat == ColorRGBA || nColorFormat == ColorBGRA || nColorFormat == ColorGrayscaleA);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline ImageBuffer::ImageBuffer() :
	m_pImageData(new ImageData())
{
	// Hold reference to image buffer
	m_pImageData->AddReference();
}

/**
*  @brief
*    Copy constructor
*/
inline ImageBuffer::ImageBuffer(const ImageBuffer &cSource) :
	m_pImageData(cSource.m_pImageData)
{
	// Reference same image data as source
	m_pImageData->AddReference();
}

/**
*  @brief
*    Destructor
*/
inline ImageBuffer::~ImageBuffer()
{
	// Release image data
	m_pImageData->Release();
}

/**
*  @brief
*    Assignment operator
*/
inline ImageBuffer &ImageBuffer::operator =(const ImageBuffer &cSource)
{
	// Release image data
	m_pImageData->Release();

	// Reference same image data as source
	m_pImageData = cSource.m_pImageData;
	m_pImageData->AddReference();

	// Return this
	return *this;
}

/**
*  @brief
*    Create image
*/
inline void ImageBuffer::CreateImage(EDataFormat nDataFormat, EColorFormat nColorFormat, const PLMath::Vector3i &vSize, ECompression nCompression)
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeNewBuffer();	// Do not use "MakeBufferUnique()" in here because we know that we're going to destroy the current image data anyway, no need to copy the image data!

	// Create image
	m_pImageData->CreateImage(nDataFormat, nColorFormat, vSize, nCompression);
}

/**
*  @brief
*    Clear data
*/
inline void ImageBuffer::Clear()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeNewBuffer();		// Do not use "MakeBufferUnique()" in here because we know that we're going to destroy the current image data anyway, no need to copy the image data!
	else
		m_pImageData->Clear();	// Clear image
}

/**
*  @brief
*    Create a test image
*/
inline void ImageBuffer::CreateTestImage(ETestImage nTestImage)
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeNewBuffer();	// Do not use "MakeBufferUnique()" in here because we know that we're going to destroy the current image data anyway, no need to copy the image data!

	// Create test image
	m_pImageData->CreateTestImage(nTestImage);
}

/**
*  @brief
*    Get data format
*/
inline EDataFormat ImageBuffer::GetDataFormat() const
{
	// Get data format
	return m_pImageData->GetDataFormat();
}

/**
*  @brief
*    Get color format
*/
inline EColorFormat ImageBuffer::GetColorFormat() const
{
	// Get color format
	return m_pImageData->GetColorFormat();
}

/**
*  @brief
*    Returns the number of components per pixel
*/
inline PLCore::uint32 ImageBuffer::GetComponentsPerPixel() const
{
	// Get from color format
	return GetComponentsPerPixel(m_pImageData->GetColorFormat());
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
inline PLCore::uint32 ImageBuffer::GetBytesPerPixelComponent() const
{
	// Get from data format
	return GetBytesPerPixelComponent(m_pImageData->GetDataFormat());
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
inline PLCore::uint32 ImageBuffer::GetBytesPerPixel() const
{
	// Get from color and data format
	return GetBytesPerPixel(m_pImageData->GetDataFormat(), m_pImageData->GetColorFormat());
}

/**
*  @brief
*    Get compression type
*/
inline ECompression ImageBuffer::GetCompression() const
{
	// Get compression type
	return m_pImageData->GetCompression();
}

/**
*  @brief
*    Set compression type
*/
inline void ImageBuffer::SetCompression(ECompression nCompression)
{
	// Has the compression type actually changed?
	if (m_pImageData->GetCompression() != nCompression) {
		// Image is going to be changed, so make image data unique
		if (m_pImageData->GetRefCount() > 1)
			MakeBufferUnique();

		// Set compression type
		m_pImageData->SetCompression(nCompression);
	}
}

/**
*  @brief
*    Get image size
*/
inline PLMath::Vector3i ImageBuffer::GetSize() const
{
	// Get image size
	return m_pImageData->GetSize();
}

/**
*  @brief
*    Returns the number of pixels
*/
inline PLCore::uint32 ImageBuffer::GetNumOfPixels() const
{
	// Get number of pixels
	return m_pImageData->GetSize().x * m_pImageData->GetSize().y;
}

/**
*  @brief
*    Check if uncompressed or compressed data is available
*/
inline bool ImageBuffer::HasAnyData() const
{
	// Check if uncompressed or compressed data is available
	return m_pImageData->HasAnyData();
}

/**
*  @brief
*    Check if uncompressed data is available
*/
inline bool ImageBuffer::HasData() const
{
	// Check if uncompressed data is available
	return m_pImageData->HasData();
}

/**
*  @brief
*    Get size of image data in bytes
*/
inline PLCore::uint32 ImageBuffer::GetDataSize() const
{
	// Get uncompressed data size
	return m_pImageData->GetDataSize();
}

/**
*  @brief
*    Get size of one row of image data in bytes
*/
inline PLCore::uint32 ImageBuffer::GetRowSize() const
{
	// Get size of a single row
	return m_pImageData->GetSize().x * GetBytesPerPixelComponent() * GetComponentsPerPixel();
}

/**
*  @brief
*    Get image data
*/
inline const PLCore::uint8 *ImageBuffer::GetData() const
{
	// Get uncompressed data
	return m_pImageData->GetData();
}

inline PLCore::uint8 *ImageBuffer::GetData()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Get uncompressed data
	return m_pImageData->GetData();
}

/**
*  @brief
*    Check if compressed data is available
*/
inline bool ImageBuffer::HasCompressedData() const
{
	// Check if compressed data is available
	return m_pImageData->HasCompressedData();
}

/**
*  @brief
*    Get size of compressed image data in bytes
*/
inline PLCore::uint32 ImageBuffer::GetCompressedDataSize() const
{
	// Get compressed data size
	return m_pImageData->GetCompressedDataSize();
}

/**
*  @brief
*    Get compressed image data
*/
inline const PLCore::uint8 *ImageBuffer::GetCompressedData() const
{
	// Get compressed data
	return m_pImageData->GetCompressedData();
}

inline PLCore::uint8 *ImageBuffer::GetCompressedData()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Get compressed data
	return m_pImageData->GetCompressedData();
}

/**
*  @brief
*    Compress image data
*/
inline bool ImageBuffer::Compress()
{
	// This does not actually change the image data, so we don't use MakeBufferUnique() here. This also has
	// the benefit of other images being able to access the compressed/uncompressed data in subsequent calls

	// Compress data
	return m_pImageData->Compress();
}

/**
*  @brief
*    Decompress image data
*/
inline bool ImageBuffer::Decompress()
{
	// This does not actually change the image data, so we don't use MakeBufferUnique() here. This also has
	// the benefit of other images being able to access the compressed/uncompressed data in subsequent calls

	// Decompress data
	return m_pImageData->Decompress();
}

/**
*  @brief
*    Set color palette
*/
inline void ImageBuffer::SetPalette(ImagePalette *pPalette)
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Set palette
	m_pImageData->SetPalette(pPalette);
}

/**
*  @brief
*    Get color palette
*/
inline const ImagePalette *ImageBuffer::GetPalette() const
{
	// Get palette
	return m_pImageData->GetPalette();
}

inline ImagePalette *ImageBuffer::GetPalette()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Get palette
	return m_pImageData->GetPalette();
}

/**
*  @brief
*    Copy provided uncompressed image data into this image buffer
*/
inline void ImageBuffer::CopyData(const PLCore::uint8 *pnData)
{
	// Valid image data pointer given?
	if (pnData) {
		// Image is going to be changed, so make image data unique
		if (m_pImageData->GetRefCount() > 1)
			MakeBufferUnique();

		// Copy data
		return m_pImageData->CopyData(pnData);
	}
}

/**
*  @brief
*    Let this image buffer takeover provided uncompressed image data
*/
inline void ImageBuffer::TakeoverData(PLCore::uint8 *pnData)
{
	// Valid image data pointer given?
	if (pnData) {
		// Image is going to be changed, so make image data unique
		if (m_pImageData->GetRefCount() > 1)
			MakeBufferUnique();

		// Takeover data
		return m_pImageData->TakeoverData(pnData);
	}
}

/**
*  @brief
*    Let this image buffer share provided uncompressed image data
*/
inline void ImageBuffer::ShareData(PLCore::uint8 *pnData)
{
	// Valid image data pointer given?
	if (pnData) {
		// Image is going to be changed, so make image data unique
		if (m_pImageData->GetRefCount() > 1)
			MakeBufferUnique();

		// Share data
		return m_pImageData->ShareData(pnData);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
