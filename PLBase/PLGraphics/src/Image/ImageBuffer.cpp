/*********************************************************\
 *  File: ImageBuffer.cpp                                *
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
#include "PLGraphics/Image/ImageEffect.h"
#include "PLGraphics/Image/ImageData.h"
#include "PLGraphics/Image/ImagePalette.h"
#include "PLGraphics/Image/ImageBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of components per pixel
*/
uint32 ImageBuffer::GetComponentsPerPixel(EColorFormat nColorFormat)
{
	// Get number of components depending on color format
	switch (nColorFormat) {
		case ColorRGB:			return 3;
		case ColorRGBA:			return 4;
		case ColorBGR:			return 3;
		case ColorBGRA:			return 4;
		case ColorGrayscale:	return 1;
		case ColorGrayscaleA:	return 2;
		case ColorPalette:		return 1;
		default:				return 0;
	}
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
uint32 ImageBuffer::GetBytesPerPixelComponent(EDataFormat nDataFormat)
{
	// Get number of bytes depending on data format
	switch (nDataFormat) {
		case DataByte:		return 1;
		case DataWord:		return 2;
		case DataHalf:		return 2;
		case DataFloat:		return 4;
		case DataDouble:	return 8;
		default:			return 0;
	}
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
uint32 ImageBuffer::GetBytesPerPixel(EDataFormat nDataFormat, EColorFormat nColorFormat)
{
	// Get number of bytes of a whole pixel
	return GetComponentsPerPixel(nColorFormat) * GetBytesPerPixelComponent(nDataFormat);
}

/**
*  @brief
*    Returns the size of a certain mipmap
*/
uint32 ImageBuffer::GetMipmapSize(uint32 nBaseSize, uint32 nMipmap)
{
	// Get the size of the mipmap level
	uint32 nSize          = nBaseSize;
	uint32 nCurrentMipmap = 0;
	while (nCurrentMipmap < nMipmap && nSize > 1) {
		nSize >>= 1;
		nCurrentMipmap++;
	}

	// Return the size
	return nSize;
}

/**
*  @brief
*    Returns whether or not the given color format has an alpha channel
*/
bool ImageBuffer::IsAlphaChannelColorFormat(EColorFormat nColorFormat)
{
	return (nColorFormat == ColorRGBA || nColorFormat == ColorBGRA || nColorFormat == ColorGrayscaleA);
}

/**
*  @brief
*    Returns a version with alpha channel of the given color format
*/
EColorFormat ImageBuffer::GetAlphaChannelColorFormat(EColorFormat nColorFormat)
{
	// Convert
	switch (nColorFormat) {
		case ColorRGB:
			return ColorRGBA;

		case ColorBGR:
			return ColorBGRA;

		case ColorGrayscale:
			return ColorGrayscaleA;

		default:
			return nColorFormat;
	}
}

/**
*  @brief
*    Returns a version without alpha channel of the given color format
*/
EColorFormat ImageBuffer::GetNoneAlphaChannelColorFormat(EColorFormat nColorFormat)
{
	// Convert
	switch (nColorFormat) {
		case ColorRGBA:
			return ColorRGB;

		case ColorBGRA:
			return ColorBGR;

		case ColorGrayscaleA:
			return ColorGrayscale;

		default:
			return nColorFormat;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageBuffer::ImageBuffer() :
	m_pImageData(new ImageData())
{
	// Hold reference to image buffer
	m_pImageData->AddReference();
}

/**
*  @brief
*    Copy constructor
*/
ImageBuffer::ImageBuffer(const ImageBuffer &cSource) :
	m_pImageData(cSource.m_pImageData)
{
	// Reference same image data as source
	m_pImageData->AddReference();
}

/**
*  @brief
*    Destructor
*/
ImageBuffer::~ImageBuffer()
{
	// Release image data
	m_pImageData->Release();
}

/**
*  @brief
*    Assignment operator
*/
ImageBuffer &ImageBuffer::operator =(const ImageBuffer &cSource)
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
void ImageBuffer::CreateImage(EDataFormat nDataFormat, EColorFormat nColorFormat, const Vector3i &vSize, ECompression nCompression)
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Create image
	m_pImageData->CreateImage(nDataFormat, nColorFormat, vSize, nCompression);
}

/**
*  @brief
*    Clear data
*/
void ImageBuffer::Clear()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Clear image
	m_pImageData->Clear();
}

/**
*  @brief
*    Apply image effect
*/
void ImageBuffer::ApplyEffect(const ImageEffect &cEffect)
{
	cEffect.Apply(*this);
}

/**
*  @brief
*    Check image for possible problems
*/
ECheckConsistency ImageBuffer::CheckConsistency() const
{
	// Check if image size is valid
	const Vector3i vSize = m_pImageData->GetSize();
	if (vSize.x <= 0 || vSize.y <= 0 || vSize.z <= 0) {
		// Image size is not valid
		return CheckImageBufferInvalidSize;
	}

	// Check if any image data is available (compressed or uncompressed)
	if (!m_pImageData->HasData() && !m_pImageData->HasCompressedData()) {
		// No image data available
		return CheckImageBufferNoData;
	}

	// Check color palette
	if (m_pImageData->GetColorFormat() == ColorPalette) {
		// Check if palette is defined
		const ImagePalette *pPalette = m_pImageData->GetPalette();
		if (!pPalette) {
			// No palette assigned
			return CheckPaletteNotAssigned;
		}

		// Check if palette is empty
		if (pPalette->GetNumOfColors() == 0 || !pPalette->GetData()) {
			// Palette is empty
			return CheckPaletteEmpty;
		}
	}

	// No problem found
	return CheckOk;
}

/**
*  @brief
*    Create a test image
*/
void ImageBuffer::CreateTestImage(ETestImage nTestImage)
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Create test image
	m_pImageData->CreateTestImage(nTestImage);
}

/**
*  @brief
*    Get data format
*/
EDataFormat ImageBuffer::GetDataFormat() const
{
	// Get data format
	return m_pImageData->GetDataFormat();
}

/**
*  @brief
*    Get color format
*/
EColorFormat ImageBuffer::GetColorFormat() const
{
	// Get color format
	return m_pImageData->GetColorFormat();
}

/**
*  @brief
*    Returns the number of components per pixel
*/
uint32 ImageBuffer::GetComponentsPerPixel() const
{
	// Get from color format
	return GetComponentsPerPixel(m_pImageData->m_nColorFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
uint32 ImageBuffer::GetBytesPerPixelComponent() const
{
	// Get from data format
	return GetBytesPerPixelComponent(m_pImageData->m_nDataFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
uint32 ImageBuffer::GetBytesPerPixel() const
{
	// Get from color and data format
	return GetBytesPerPixel(m_pImageData->m_nDataFormat, m_pImageData->m_nColorFormat);
}

/**
*  @brief
*    Get compression type
*/
ECompression ImageBuffer::GetCompression() const
{
	// Get compression type
	return m_pImageData->GetCompression();
}

/**
*  @brief
*    Set compression type
*/
void ImageBuffer::SetCompression(ECompression nCompression)
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
Vector3i ImageBuffer::GetSize() const
{
	// Get image size
	return m_pImageData->GetSize();
}

/**
*  @brief
*    Returns the number of pixels
*/
uint32 ImageBuffer::GetNumOfPixels() const
{
	// Get number of pixels
	return m_pImageData->GetSize().x * m_pImageData->GetSize().y;
}

/**
*  @brief
*    Check if uncompressed data is available
*/
bool ImageBuffer::HasData() const
{
	// Check if uncompressed data is available
	return m_pImageData->HasData();
}

/**
*  @brief
*    Get size of image data in bytes
*/
uint32 ImageBuffer::GetDataSize() const
{
	// Get uncompressed data size
	return m_pImageData->GetDataSize();
}

/**
*  @brief
*    Get size of one row of image data in bytes
*/
uint32 ImageBuffer::GetRowSize() const
{
	// Get size of a single row
	return m_pImageData->GetSize().x * GetBytesPerPixelComponent() * GetComponentsPerPixel();
}

/**
*  @brief
*    Get image data
*/
const uint8 *ImageBuffer::GetData() const
{
	// Get uncompressed data
	return m_pImageData->GetData();
}

uint8 *ImageBuffer::GetData()
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
bool ImageBuffer::HasCompressedData() const
{
	// Check if compressed data is available
	return m_pImageData->HasCompressedData();
}

/**
*  @brief
*    Get size of compressed image data in bytes
*/
uint32 ImageBuffer::GetCompressedDataSize() const
{
	// Get compressed data size
	return m_pImageData->GetCompressedDataSize();
}

/**
*  @brief
*    Get compressed image data
*/
const uint8 *ImageBuffer::GetCompressedData() const
{
	// Get compressed data
	return m_pImageData->GetCompressedData();
}

uint8 *ImageBuffer::GetCompressedData()
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
bool ImageBuffer::Compress()
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
bool ImageBuffer::Decompress()
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
void ImageBuffer::SetPalette(ImagePalette *pPalette)
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
const ImagePalette *ImageBuffer::GetPalette() const
{
	// Get palette
	return m_pImageData->GetPalette();
}

ImagePalette *ImageBuffer::GetPalette()
{
	// Image is going to be changed, so make image data unique
	if (m_pImageData->GetRefCount() > 1)
		MakeBufferUnique();

	// Get palette
	return m_pImageData->GetPalette();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Make image data unique
*/
void ImageBuffer::MakeBufferUnique()
{
	// If the image data is used more than once
	if (m_pImageData->GetRefCount() > 1) {
		// Create new image data and copy data from old one
		ImageData *pImageData = new ImageData(*m_pImageData);

		// Release old image data
		m_pImageData->Release();

		// Set pointer to new image data
		m_pImageData = pImageData;
		m_pImageData->AddReference();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
