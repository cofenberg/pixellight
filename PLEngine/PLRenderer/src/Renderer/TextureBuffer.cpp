/*********************************************************\
 *  File: TextureBuffer.cpp                              *
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
#include <PLMath/Math.h>
#include <PLMath/Half.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/TextureBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture buffer pixel format of a given image (PLGraphics::Image)
*/
TextureBuffer::EPixelFormat TextureBuffer::GetFormatFromImage(const Image &cImage, bool bNoCompression)
{
	// Get the first image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer) {
		// Check for float format
		if (pImageBuffer->GetDataFormat() == DataFloat) {
			switch (pImageBuffer->GetComponentsPerPixel()) {
				// Luminance
				case 1:
					return L32F;

				// Luminance & alpha
				//   -> Not supported

				// RGB
				//   -> Not supported

				// RGBA
				case 4:
					return R32G32B32A32F;
			}
		} else {
			// Check for supported compressed/uncompressed
			ECompression nCompression = pImageBuffer->GetCompression();
			if (bNoCompression)
				nCompression = CompressionNone;
			if (nCompression == CompressionNone) {
				switch (pImageBuffer->GetComponentsPerPixel()) {
					// Luminance
					case 1:
						return L8;

					// Luminance & alpha
					case 2:
						return L8A8;

					// RGB
					case 3:
						return R8G8B8;

					// RGBA
					case 4:
						return R8G8B8A8;
				}
			} else {
				switch (nCompression) {
					case CompressionDXT1:
						return DXT1;

					case CompressionDXT3:
						return DXT3;

					case CompressionDXT5:
						return DXT5;

					case CompressionLATC1:
						return LATC1;

					case CompressionLATC2:
						return LATC2;
				}
			}
		}
	}

	// Error!
	return Unknown;
}

/**
*  @brief
*    Returns whether or not the given texture buffer format is compressed
*/
bool TextureBuffer::IsCompressedFormat(EPixelFormat nFormat)
{
	switch (nFormat) {
		case L8:			return false;
		case L16:			return false;
		case A8:			return false;
		case L4A4:			return false;
		case L8A8:			return false;
		case D16:			return false;
		case D24:			return false;
		case D32:			return false;
		case R3G3B2:		return false;
		case R5G6B5:		return false;
		case R5G5B5A1:		return false;
		case R4G4B4A4:		return false;
		case R8G8B8:		return false;
		case R8G8B8A8:		return false;
		case R10G10B10A2:	return false;
		case R16G16B16A16:	return false;
		case DXT1:			return true;
		case DXT3:			return true;
		case DXT5:			return true;
		case LATC1:			return true;
		case LATC2:			return true;
		case L16F:			return false;
		case L32F:			return false;
		case R16G16B16A16F:	return false;
		case R32G32B32A32F:	return false;
		default:			return false; // Error!
	}
}

/**
*  @brief
*    If the given texture buffer format is compressed, a proper uncompressed texture buffer format will be returned
*/
TextureBuffer::EPixelFormat TextureBuffer::GetUncompressedFormat(EPixelFormat nFormat)
{
	// Is the given format compressed?
	if (IsCompressedFormat(nFormat)) {
		// Return a proper uncompressed format
		switch (nFormat) {
			case DXT1:			return R8G8B8;
			case DXT3:			return R8G8B8A8;
			case DXT5:			return R8G8B8A8;
			case LATC1:			return L8;
			case LATC2:			return L8A8;
		}
	}

	// Pass through the given format
	return nFormat;
}

/**
*  @brief
*    Returns whether or not the given texture buffer format is a floating point format
*/
bool TextureBuffer::IsFloatingPointFormat(EPixelFormat nFormat)
{
	switch (nFormat) {
		case L8:			return false;
		case L16:			return false;
		case A8:			return false;
		case L4A4:			return false;
		case L8A8:			return false;
		case D16:			return false;
		case D24:			return false;
		case D32:			return false;
		case R3G3B2:		return false;
		case R5G6B5:		return false;
		case R5G5B5A1:		return false;
		case R4G4B4A4:		return false;
		case R8G8B8:		return false;
		case R8G8B8A8:		return false;
		case R10G10B10A2:	return false;
		case R16G16B16A16:	return false;
		case DXT1:			return false;
		case DXT3:			return false;
		case DXT5:			return false;
		case LATC1:			return false;
		case LATC2:			return false;
		case L16F:			return true;
		case L32F:			return true;
		case R16G16B16A16F:	return true;
		case R32G32B32A32F:	return true;
		default:			return false; // Error!
	}
}

/**
*  @brief
*    Returns the number of components per pixel
*/
uint32 TextureBuffer::GetComponentsPerPixel(EPixelFormat nFormat)
{
	switch (nFormat) {
		case L8:			return 1;
		case L16:			return 1;
		case A8:			return 1;
		case L4A4:			return 2;
		case L8A8:			return 2;
		case D16:			return 1;
		case D24:			return 1;
		case D32:			return 1;
		case R3G3B2:		return 3;
		case R5G6B5:		return 3;
		case R5G5B5A1:		return 4;
		case R4G4B4A4:		return 4;
		case R8G8B8:		return 3;
		case R8G8B8A8:		return 4;
		case R10G10B10A2:	return 4;
		case R16G16B16A16:	return 4;
		case DXT1:			return 3;
		case DXT3:			return 4;
		case DXT5:			return 4;
		case LATC1:			return 1;
		case LATC2:			return 2;
		case L16F:			return 1;
		case L32F:			return 1;
		case R16G16B16A16F:	return 4;
		case R32G32B32A32F:	return 4;
		default:			return 0; // Error!
	}
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
uint32 TextureBuffer::GetBytesPerPixelComponent(EPixelFormat nFormat)
{
	switch (nFormat) {
		case L8:			return 1;
		case L16:			return 2;
		case A8:			return 1;
		case L4A4:			return 0; // No full byte per component...
		case L8A8:			return 1;
		case D16:			return 2;
		case D24:			return 4; // Look out! 4 NOT 3 bytes!
		case D32:			return 4;
		case R3G3B2:		return 0; // No full byte per component...
		case R5G6B5:		return 0; // No full byte per component...
		case R5G5B5A1:		return 0; // No full byte per component...
		case R4G4B4A4:		return 0; // No full byte per component...
		case R8G8B8:		return 1;
		case R8G8B8A8:		return 1;
		case R10G10B10A2:	return 0; // No full byte per component...
		case R16G16B16A16:	return 2;
		case DXT1:			return 0; // No full byte per component...
		case DXT3:			return 0; // No full byte per component...
		case DXT5:			return 0; // No full byte per component...
		case LATC1:			return 0; // No full byte per component...
		case LATC2:			return 0; // No full byte per component...
		case L16F:			return 2;
		case L32F:			return 4;
		case R16G16B16A16F:	return 2;
		case R32G32B32A32F:	return 4;
		default:			return 0; // Error!
	}
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
uint32 TextureBuffer::GetBytesPerPixel(EPixelFormat nFormat)
{
	switch (nFormat) {
		case L8:			return 1;
		case L16:			return 2;
		case A8:			return 1;
		case L4A4:			return 1;
		case L8A8:			return 2;
		case D16:			return 2;
		case D24:			return 4; // Look out! 4 NOT 3 bytes!
		case D32:			return 4;
		case R3G3B2:		return 1;
		case R5G6B5:		return 2;
		case R5G5B5A1:		return 2;
		case R4G4B4A4:		return 2;
		case R8G8B8:		return 3;
		case R8G8B8A8:		return 4;
		case R10G10B10A2:	return 4;
		case R16G16B16A16:	return 8;
		case DXT1:			return 0; // No full byte per pixel...
		case DXT3:			return 0; // No full byte per pixel...
		case DXT5:			return 0; // No full byte per pixel...
		case LATC1:			return 0; // No full byte per pixel...
		case LATC2:			return 0; // No full byte per pixel...
		case L16F:			return 2;
		case L32F:			return 4;
		case R16G16B16A16F:	return 8;
		case R32G32B32A32F:	return 16;
		default:			return 0; // Error!
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBuffer::~TextureBuffer()
{
	// Check if this is the renderers current texture buffer
	for (uint32 nStage=0; nStage<GetRenderer().GetCapabilities().nMaxTextureUnits; nStage++) {
		if (GetRenderer().GetTextureBuffer(nStage) == this)
			GetRenderer().SetTextureBuffer(nStage);
	}
}

/**
*  @brief
*    Returns the texture buffer flags
*/
uint32 TextureBuffer::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Returns the texture buffer pixel format
*/
TextureBuffer::EPixelFormat TextureBuffer::GetFormat() const
{
	return m_nFormat;
}

/**
*  @brief
*    Returns whether or not the used texture buffer format is compressed
*/
bool TextureBuffer::IsCompressedFormat() const
{
	return IsCompressedFormat(m_nFormat);
}

/**
*  @brief
*    If the used texture buffer format is compressed, a proper uncompressed texture buffer format will be returned
*/
TextureBuffer::EPixelFormat TextureBuffer::GetUncompressedFormat() const
{
	return GetUncompressedFormat(m_nFormat);
}

/**
*  @brief
*    Returns whether or not the used texture buffer format is a floating point format
*/
bool TextureBuffer::IsFloatingPointFormat() const
{
	return IsFloatingPointFormat(m_nFormat);
}

/**
*  @brief
*    Returns the number of components per pixel
*/
uint32 TextureBuffer::GetComponentsPerPixel() const
{
	return GetComponentsPerPixel(m_nFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel component
*/
uint32 TextureBuffer::GetBytesPerPixelComponent() const
{
	return GetBytesPerPixelComponent(m_nFormat);
}

/**
*  @brief
*    Returns the number of bytes per pixel
*/
uint32 TextureBuffer::GetBytesPerPixel() const
{
	return GetBytesPerPixel(m_nFormat);
}

/**
*  @brief
*    Returns the number of mipmap levels
*/
uint32 TextureBuffer::GetNumOfMipmaps() const
{
	return m_nNumOfMipmaps;
}

/**
*  @brief
*    Returns the number of faces
*/
uint8 TextureBuffer::GetNumOfFaces() const
{
	return (GetType() == TypeTextureBufferCube) ? 6 : 1;
}

/**
*  @brief
*    Returns the total number of pixels including all mipmaps
*/
uint32 TextureBuffer::GetTotalNumOfPixels() const
{
	// The total number of pixels
	uint32 nTotalNumOfPixels = 0;

	// Sum up the pixels of all mipmaps
	for (uint32 i=0; i<m_nNumOfMipmaps; i++)
		nTotalNumOfPixels += GetNumOfPixels(i);

	// Return the total number of pixels
	return nTotalNumOfPixels;
}

/**
*  @brief
*    Returns the total number of bytes required for the texture buffer data including all mipmaps
*/
uint32 TextureBuffer::GetTotalNumOfBytes() const
{
	return m_nTotalNumOfBytes;
}

/**
*  @brief
*    Downloads the texture buffer content and returns the number of NAN values in it
*/
uint32 TextureBuffer::GetNumOfNANValues(uint32 nMipmap, uint8 nFace)
{
	// The number of found NANs
	uint32 nNumOfNANs = 0;

	// The texture buffer format must be a floating point one
	if (IsFloatingPointFormat()) {
		// Get the number of pixels on the given mipmap level for one face
		const uint32 nNumOfPixels = GetNumOfPixels(nMipmap)/GetNumOfFaces();
		if (nNumOfPixels != 0) {
			// Get the number of elements
			const uint32 nNumOfElements = nNumOfPixels*GetComponentsPerPixel();

			// Get the number of bytes per pixel component
			const uint32 nBytesPerPixelComponent = GetBytesPerPixelComponent();

			// 32 bit floating point
			if (nBytesPerPixelComponent == 4) {
				// Allocate host side texture buffer
				float *pfData = new float[nNumOfElements];

				// Download the texture buffer from the GPU to the host
				if (Download(nMipmap, m_nFormat, pfData, nFace)) {
					// Count the number of NANs
					for (float *pfCurrent=pfData, *pfEnd=pfData+nNumOfElements; pfCurrent<pfEnd; pfCurrent++) {
						// Is this value a NAN?
						if (Math::IsNotANumber(*pfCurrent))
							nNumOfNANs++;
					}
				}

				// Cleanup
				delete [] pfData;
			} else if (nBytesPerPixelComponent == 2) {
				// 16 bit floating point format (half)

				// Allocate host side texture buffer
				uint16 *pnData = new uint16[nNumOfElements];

				// Download the texture buffer from the GPU to the host
				if (Download(nMipmap, m_nFormat, pnData, nFace)) {
					// Count the number of NANs
					for (uint16 *pnCurrent=pnData, *pnEnd=pnData+nNumOfElements; pnCurrent<pnEnd; pnCurrent++) {
						// Is this value a NAN?
						if (Half::IsNotANumber(*pnCurrent))
							nNumOfNANs++;
					}
				}

				// Cleanup
				delete [] pnData;
			}
		}
	}

	// Return the number of found NANs
	return nNumOfNANs;
}

/**
*  @brief
*    Downloads the texture buffer content, replaces pixels containing a NAN value by a given color, and uploads the fixed texture buffer
*/
uint32 TextureBuffer::FixNANValues(const Color4 &cColor, uint32 nMipmap, uint8 nFace)
{
	// The number of found NAN pixels
	uint32 nNumOfNANs = 0;

	// The texture buffer format must be a floating point one
	if (IsFloatingPointFormat()) {
		// Get the number of pixels on the given mipmap level for one face
		const uint32 nNumOfPixels = GetNumOfPixels(nMipmap)/GetNumOfFaces();
		if (nNumOfPixels != 0) {
			// Get the number of components per pixel
			const uint32 nComponentsPerPixel = GetComponentsPerPixel();

			// Get the number of elements
			const uint32 nNumOfElements = nNumOfPixels*nComponentsPerPixel;

			// Get the number of bytes per pixel component
			const uint32 nBytesPerPixelComponent = GetBytesPerPixelComponent();

			// 32 bit floating point
			if (nBytesPerPixelComponent == 4) {
				// Allocate host side texture buffer
				float *pfData = new float[nNumOfElements];

				// Download the texture buffer from the GPU to the host
				if (Download(nMipmap, m_nFormat, pfData, nFace)) {
					// Count the number of NANs
					for (float *pfCurrent=pfData, *pfEnd=pfData+nNumOfElements; pfCurrent<pfEnd; pfCurrent+=nComponentsPerPixel) {
						// Loop through the components of the current pixel
						float *pfCurrentPixel = pfCurrent;
						for (uint32 nComponent=0; nComponent<nComponentsPerPixel; nComponent++) {
							// Is this value a NAN?
							if (Math::IsNotANumber(pfCurrentPixel[nComponent])) {
								// Write down the given color
								*pfCurrentPixel = cColor.r;
								if (nComponentsPerPixel > 1)
									pfCurrentPixel[1] = cColor.g;
								else if (nComponentsPerPixel > 2)
									pfCurrentPixel[2] = cColor.b;
								else if (nComponentsPerPixel > 3)
									pfCurrentPixel[3] = cColor.a;

								// Update the number of NAN pixels
								nNumOfNANs++;

								// Get us out of the pixel loop
								nComponent = nComponentsPerPixel;
							}
						}
					}
				}

				// Upload the fixed texture buffer to the GPU
				Upload(nMipmap, m_nFormat, pfData, nFace);

				// Cleanup
				delete [] pfData;
			} else if (nBytesPerPixelComponent == 2) {
				// 16 bit floating point format (half)

				// Convert the given color into half
//				const uint16 nHalfColor[4] = {Half::FromFloat(cColor.r), Half::FromFloat(cColor.g), Half::FromFloat(cColor.b), Half::FromFloat(cColor.a)};
				// [TODO] Internal, Half::FromFloat() is not implemented yet and returns always 0
				const uint16 nHalfColor[4] = {Half::One, Half::Zero, Half::Zero, Half::One};

				// Allocate host side texture buffer
				uint16 *pnData = new uint16[nNumOfElements];

				// Download the texture buffer from the GPU to the host
				if (Download(nMipmap, m_nFormat, pnData, nFace)) {
					// Count the number of NANs
					for (uint16 *pnCurrent=pnData, *pnEnd=pnData+nNumOfElements; pnCurrent<pnEnd; pnCurrent+=nComponentsPerPixel) {
						// Loop through the components of the current pixel
						uint16 *pnCurrentPixel = pnCurrent;
						for (uint32 nComponent=0; nComponent<nComponentsPerPixel; nComponent++) {
							// Is this value a NAN?
							if (Half::IsNotANumber(pnCurrentPixel[nComponent])) {
								// Write down the given color
								*pnCurrentPixel = nHalfColor[0];
								if (nComponentsPerPixel > 1)
									pnCurrentPixel[1] = nHalfColor[1];
								if (nComponentsPerPixel > 2)
									pnCurrentPixel[2] = nHalfColor[2];
								if (nComponentsPerPixel > 3)
									pnCurrentPixel[3] = nHalfColor[3];

								// Update the number of NAN pixels
								nNumOfNANs++;

								// Get us out of the components loop
								nComponent = nComponentsPerPixel;
							}
						}
					}
				}

				// Upload the fixed texture buffer to the GPU
				Upload(nMipmap, m_nFormat, pnData, nFace);

				// Cleanup
				delete [] pnData;
			}
		}
	}

	// Return the number of found NAN pixels
	return nNumOfNANs;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureBuffer::TextureBuffer(Renderer &cRenderer, EType nType, uint32 nFlags) : Resource(cRenderer, nType),
	m_nFlags(nFlags),
	m_nFormat(Unknown),
	m_nNumOfElements(0),
	m_nNumOfMipmaps(0),
	m_nTotalNumOfBytes(0)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
TextureBuffer::TextureBuffer(const TextureBuffer &cSource) : Resource(cSource.GetRenderer(), cSource.GetType()),
	m_nFlags(cSource.m_nFlags),
	m_nFormat(cSource.m_nFormat),
	m_nNumOfElements(cSource.m_nNumOfElements),
	m_nNumOfMipmaps(cSource.m_nNumOfMipmaps),
	m_nTotalNumOfBytes(cSource.m_nTotalNumOfBytes)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
TextureBuffer &TextureBuffer::operator =(const TextureBuffer &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
