/*********************************************************\
 *  File: ImageLoaderDDS.cpp                             *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/File/File.h>
#include "PLGraphics/Color/Color3.h"
#include "PLGraphics/Color/Color4.h"
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/Loader/ImageLoaderDDS.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#define DDSCAPS2_CUBEMAP 0x00000200L
#define DDS_FOURCC		 0x00000004L
#define DDS_LUMINANCE	 0x00020000L
#define DDS_ALPHAPIXELS	 0x00000001L
#define DDS_LINEARSIZE	 0x00080000L
#define DDS_PITCH		 0x00000008L


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
struct DDSHeader {
	uint8  nMagic[4];
	uint32 nSize;
	uint32 nFlags;
	uint32 nHeight;
	uint32 nWidth;
	uint32 nPitchOrLinearSize;
	uint32 nDepth; 
	uint32 nMipMapCount;
	uint32 nReserved[11];

	struct {
		uint32 nSize;
		uint32 nFlags;
		uint32 nFourCC;
		uint32 nRGBBitCount;
		uint32 nRBitMask;
		uint32 nGBitMask;
		uint32 nBBitMask;
		uint32 nRGBAlphaBitMask;
	} ddpfPixelFormat;

	struct {
		uint32 nCaps1;
		uint32 nCaps2;
		uint32 nReserved[2];
	} ddsCaps;

	uint32 nReserved2;
};

struct DDSHeaderDX10 {
	uint32 nDXGIFormat;
	uint32 nResourceDimension;
	uint32 nMiscFlag;
	uint32 nArraySize;
	uint32 nReserved;
};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderDDS)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderDDS::Load(Image &cImage, File &cFile)
{
	#define MCHAR4(a, b, c, d) (a | (b << 8) | (c << 16) | (d << 24))

	// Read the header
	DDSHeader sHeader;
	cFile.Read(&sHeader, sizeof(sHeader), 1);
	if (sHeader.nMagic[0] == 'D' && sHeader.nMagic[1] == 'D' && sHeader.nMagic[2] == 'S' && sHeader.nMagic[3] == ' ' &&
		// Note that if "nSize" is "DDS " this is not a valid dds file according
		// to the file spec. Some broken tool out there seems to produce files
		// with this value in the size field, so we support reading them...
		sHeader.nSize == 124 || sHeader.nSize != MCHAR4('D', 'D', 'S', ' ')) {

		// Get the color format and compression
		EColorFormat nColorFormat;
		EColorFormat nInternalColorFormat;
		ECompression nCompression = CompressionNone;

		// Get the depth
		const uint32 nDepth = sHeader.nDepth ? sHeader.nDepth : 1;

		// Is this image compressed?
		if (sHeader.ddpfPixelFormat.nFlags & DDS_FOURCC) {
			// The image is compressed
			if (sHeader.ddpfPixelFormat.nFourCC == MCHAR4('D', 'X', '1', '0')) {
				// Read the DX10 header
				DDSHeaderDX10 sDX10Header;
				cFile.Read(&sDX10Header, sizeof(sDX10Header), 1);

				// Get the color format and compression
				switch (sDX10Header.nDXGIFormat) {
					case 61:
						nInternalColorFormat = nColorFormat = ColorGrayscale;
						break;

					case 49:
						nInternalColorFormat = (sHeader.ddpfPixelFormat.nBBitMask == 0xFF) ? ColorBGR : ColorRGB;
						nColorFormat = ColorRGB;
						break;

					case 28:
						nInternalColorFormat = (sHeader.ddpfPixelFormat.nBBitMask == 0xFF) ? ColorBGRA : ColorRGBA;
						nColorFormat = ColorRGBA;
						break;

					case 71:
						nInternalColorFormat = nColorFormat = ColorRGB;
						nCompression = CompressionDXT1;
						break;

					case 74:
						nInternalColorFormat = nColorFormat = ColorRGBA;
						nCompression = CompressionDXT3;
						break;

					case 77:
						nInternalColorFormat = nColorFormat = ColorRGBA;
						nCompression = CompressionDXT5;
						break;

					case 80:
						nInternalColorFormat = nColorFormat = ColorGrayscale;
						nCompression = CompressionATI1N;
						break;

					case 83:
						nInternalColorFormat = nColorFormat = ColorGrayscaleA;
						nCompression = CompressionATI2N;
						break;

					default:
						// Error: Unsupported format
						return false;
				}
			} else {
				switch (sHeader.ddpfPixelFormat.nFourCC) {
					case MCHAR4('D', 'X', 'T', '1'):
						nInternalColorFormat = nColorFormat = ColorRGB;
						nCompression = CompressionDXT1;
						break;

					case MCHAR4('D', 'X', 'T', '3'):
						nInternalColorFormat = nColorFormat = ColorRGBA;
						nCompression = CompressionDXT3;
						break;

					case MCHAR4('D', 'X', 'T', '5'):
						nInternalColorFormat = nColorFormat = ColorRGBA;
						nCompression = CompressionDXT5;
						break;

					case MCHAR4('A', 'T', 'I', '1'):
						nInternalColorFormat = nColorFormat = ColorGrayscale;
						nCompression = CompressionATI1N;
						break;

					case MCHAR4('A', 'T', 'I', '2'):
						nInternalColorFormat = nColorFormat = ColorGrayscaleA;
						nCompression = CompressionATI2N;
						break;

					default:
						switch (sHeader.ddpfPixelFormat.nRGBBitCount) {
							case 8:
								nInternalColorFormat = nColorFormat = ColorGrayscale;
								break;

							case 16:
								if (sHeader.ddpfPixelFormat.nRGBAlphaBitMask == 0xFF00)
									nInternalColorFormat = nColorFormat = ColorGrayscaleA;
								else {
									// Error: Unsupported format
									return false;
								}
								break;

							case 24:
								nInternalColorFormat = (sHeader.ddpfPixelFormat.nBBitMask == 0xFF) ? ColorBGR : ColorRGB;
								nColorFormat         = ColorRGB;
								break;

							case 32:
								if (sHeader.ddpfPixelFormat.nRBitMask != 0x3FF00000) {
									nInternalColorFormat = (sHeader.ddpfPixelFormat.nBBitMask == 0xFF) ? ColorBGRA : ColorRGBA;
									nColorFormat         = ColorRGBA;
								} else {
									// Error: Unsupported format
									return false;
								}
								break;

							default:
								// Error: Unsupported format
								return false;
						}
				}
			}
		} else {
			// The image is not compressed
			if (sHeader.ddpfPixelFormat.nFlags & DDS_LUMINANCE) {
				if (sHeader.ddpfPixelFormat.nFlags & DDS_ALPHAPIXELS) {
					nInternalColorFormat = nColorFormat = ColorGrayscaleA;
				} else {
					nInternalColorFormat = nColorFormat = ColorGrayscale;
				}
			} else {
				if (sHeader.ddpfPixelFormat.nFlags & DDS_ALPHAPIXELS) {
					// Set color format, please not that all bit mask relevant stuff is done inside "DecompressRGBA()"
					nInternalColorFormat = nColorFormat = ColorRGBA;
				} else {
					// Set color format, please not that all bit mask relevant stuff is done inside "DecompressRGBA()"
					nInternalColorFormat = nColorFormat = ColorRGB;
				}
			}

			// Microsoft bug, they're not following their own documentation.
			if (!(sHeader.ddpfPixelFormat.nFlags & (DDS_LINEARSIZE | DDS_PITCH)) || !sHeader.nPitchOrLinearSize) {
				sHeader.ddpfPixelFormat.nFlags |= DDS_LINEARSIZE;
				sHeader.nPitchOrLinearSize		= (sHeader.nWidth * sHeader.nHeight * nDepth * (sHeader.ddpfPixelFormat.nRGBBitCount >> 3));
			}
		}

		// Clear the old image
		cImage.Clear();

		// Get the number of mipmaps
		const uint32 nMipmaps = (!sHeader.nMipMapCount) ? 1 : sHeader.nMipMapCount;

		// Cube map?
		const uint32 nNumOfFaces = (sHeader.ddsCaps.nCaps2 & DDSCAPS2_CUBEMAP) ? 6 : 1;

		// Loop through all faces
		for (uint32 nFace=0; nFace<nNumOfFaces; nFace++){
			// Create image part with reasonable semantic
			ImagePart *pImagePart = cImage.CreatePart((nNumOfFaces == 6) ? ImagePartCubeSidePosX + nFace : 0);
			if (pImagePart) {
				// Load in all mipmaps
				for (uint32 nMipmap=0; nMipmap<nMipmaps; nMipmap++) {
					// Create image buffer
					ImageBuffer *pImageBuffer = pImagePart->CreateMipmap();
					pImageBuffer->CreateImage(DataByte,
											  nColorFormat,
											  Vector3i(ImageBuffer::GetMipmapSize(sHeader.nWidth,  nMipmap),
													   ImageBuffer::GetMipmapSize(sHeader.nHeight, nMipmap),
													   nDepth),
											  nCompression);

					// Read in compressed data?
					if (nCompression == CompressionNone) {
						// If the "DDS_LINEARSIZE" flag is set we need to do some more work...
						if (sHeader.ddpfPixelFormat.nFlags & DDS_LINEARSIZE) {
							// Allocate temp data
							uint8 *pnTempData = new uint8[sHeader.nPitchOrLinearSize];

							// Read the data
							cFile.Read(pnTempData, 1, sHeader.nPitchOrLinearSize);

							// Decompress the image data
							DecompressRGBA(sHeader, *pImageBuffer, pnTempData);

							// Cleanup temp data
							delete [] pnTempData;
						} else {
							// A simple one: Just read in the whole uncompressed data
							cFile.Read(pImageBuffer->GetData(), 1, pImageBuffer->GetDataSize());
						}
					} else {
						// A simple one: Just read in the whole compressed data
						cFile.Read(pImageBuffer->GetCompressedData(), 1, pImageBuffer->GetCompressedDataSize());
					}
				}
			}
		}

		// Convert BGR(A) to RGB(A)
		if (nInternalColorFormat == ColorBGR) {
			// Loop through all faces
			for (uint32 nFace=0; nFace<nNumOfFaces; nFace++){
				// Create image part with reasonable semantic
				ImagePart *pImagePart = cImage.GetPartBySemantics((nNumOfFaces == 6) ? ImagePartCubeSidePosX + nFace : 0);
				if (pImagePart) {
					// Load in all mipmaps
					for (uint32 nMipmap=0; nMipmap<nMipmaps; nMipmap++) {
						// Get image buffer
						ImageBuffer *pImageBuffer = pImagePart->GetMipmap(nMipmap);

						// Swap R/B
						Color3::SwapRB(pImageBuffer->GetData(), pImageBuffer->GetNumOfPixels());
					}
				}
			}
		} else if (nInternalColorFormat == ColorBGRA) {
			// Loop through all faces
			for (uint32 nFace=0; nFace<nNumOfFaces; nFace++){
				// Create image part with reasonable semantic
				ImagePart *pImagePart = cImage.GetPartBySemantics((nNumOfFaces == 6) ? ImagePartCubeSidePosX + nFace : 0);
				if (pImagePart) {
					// Load in all mipmaps
					for (uint32 nMipmap=0; nMipmap<nMipmaps; nMipmap++) {
						// Get image buffer
						ImageBuffer *pImageBuffer = pImagePart->GetMipmap(nMipmap);

						// Swap R/B
						Color4::SwapRB(pImageBuffer->GetData(), pImageBuffer->GetNumOfPixels());
					}
				}
			}
		}

		// Done
		return true;
	} else {
		// Error: Invalid magic number
	}

	// Error!
	return false;
}

bool ImageLoaderDDS::Save(const Image &cImage, File &cFile)
{
	// [TODO] Implement
	return false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ImageLoaderDDS::ImageLoaderDDS() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderDDS::~ImageLoaderDDS()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns bits from a given bit mask
*/
void ImageLoaderDDS::GetBitsFromMask(uint32 nMask, uint32 &nShiftLeft, uint32 &nShiftRight) const
{
	if (nMask) {
		uint32 nTemp = nMask;
		uint32 i;
		for (i=0; i<32; i++, nTemp >>= 1) {
			if (nTemp & 1)
				break;
		}
		nShiftRight = i;

		// Temp is preserved, so use it again:
		for (i=0; i<8; i++, nTemp >>= 1) {
			if (!(nTemp & 1))
				break;
		}
		nShiftLeft = 8 - i;
	} else {
		nShiftLeft = nShiftRight = 0;
	}
}

/**
*  @brief
*    Decompresses a RGB/RGBA image
*/
void ImageLoaderDDS::DecompressRGBA(const DDSHeader &sHeader, ImageBuffer &cImageBuffer, const uint8 *pnCompressedData) const
{
	// Get bits from mask
	uint32 nRedL, nRedR, nGreenL, nGreenR, nBlueL, nBlueR, nAlphaL, nAlphaR;
	GetBitsFromMask(sHeader.ddpfPixelFormat.nRBitMask,        nRedL,   nRedR);
	GetBitsFromMask(sHeader.ddpfPixelFormat.nGBitMask,        nGreenL, nGreenR);
	GetBitsFromMask(sHeader.ddpfPixelFormat.nBBitMask,        nBlueL,  nBlueR);
	GetBitsFromMask(sHeader.ddpfPixelFormat.nRGBAlphaBitMask, nAlphaL, nAlphaR);

	// Get data
	const uint32  nBpp             = sHeader.ddpfPixelFormat.nRGBBitCount / 8;
	const uint32  nDataSize        = cImageBuffer.GetDataSize();
	const uint32  nBytesPerPixel   = cImageBuffer.GetBytesPerPixel();
		  uint8  *pDestinationData = cImageBuffer.GetData();

	// Loop through all pixel
	for (uint32 i=0; i<nDataSize; i+=nBytesPerPixel) {
		uint32 nReadI = 0;
		if (nDataSize - i < 4) { // Less than 4 byte to write?
			if (nBpp == 3) {	// This branch is extra-SLOOOW
				nReadI =
					*pnCompressedData
					| ((*(pnCompressedData + 1)) << 8)
					| ((*(pnCompressedData + 2)) << 16);
			} else if (nBpp == 1) {
				nReadI = *((uint8*)pnCompressedData);
			} else if (nBpp == 2) {
				nReadI = pnCompressedData[0] | (pnCompressedData[1] << 8);
			}
		} else {
			nReadI = pnCompressedData[0] | (pnCompressedData[1] << 8) | (pnCompressedData[2] << 16) | (pnCompressedData[3] << 24);
		}
		pnCompressedData += nBpp;

		pDestinationData[i] = ((nReadI & sHeader.ddpfPixelFormat.nRBitMask) >> nRedR) << nRedL;

		if (nBytesPerPixel >= 3) {
			pDestinationData[i+1] = ((nReadI & sHeader.ddpfPixelFormat.nGBitMask) >> nGreenR) << nGreenL;
			pDestinationData[i+2] = ((nReadI & sHeader.ddpfPixelFormat.nBBitMask) >> nBlueR) << nBlueL;

			if (nBytesPerPixel == 4) {
				pDestinationData[i+3] = ((nReadI & sHeader.ddpfPixelFormat.nRGBAlphaBitMask) >> nAlphaR) << nAlphaL;
				if (nAlphaL >= 7) {
					pDestinationData[i+3] = pDestinationData[i+3] ? 0xFF : 0x00;
				} else if (nAlphaL >= 4) {
					pDestinationData[i+3] = pDestinationData[i+3] | (pDestinationData[i+3] >> 4);
				}
			}
		} else if (nBytesPerPixel == 2) {
			pDestinationData[i+1] = ((nReadI & sHeader.ddpfPixelFormat.nRGBAlphaBitMask) >> nAlphaR) << nAlphaL;
			if (nAlphaL >= 7) {
				pDestinationData[i+1] = pDestinationData[i+1] ? 0xFF : 0x00;
			} else if (nAlphaL >= 4) {
				pDestinationData[i+1] = pDestinationData[i+1] | (pDestinationData[i+3] >> 4);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
