/*********************************************************\
 *  File: ImageLoaderPNG.cpp                             *
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
#include <png.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Url.h>
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImagePalette.h"
#include "PLGraphics/Image/Loader/ImageLoaderPNG.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderPNG)


//[-------------------------------------------------------]
//[ Static helper functions                               ]
//[-------------------------------------------------------]
void PngError(png_structp pPtr, png_const_charp pszError)
{
}

void PngWarning(png_structp pPtr, png_const_charp pszWarning)
{
}

void PngReadData(png_structp pPng, png_bytep pBuffer, png_size_t nSize)
{
	// Get file pointer
	File *pFile = static_cast<File*>(png_get_io_ptr(pPng));

	// Read data from file
	pFile->Read(pBuffer, nSize, 1);
}

void PngWriteData(png_structp pPng, png_bytep pBuffer, png_size_t nSize)
{
	// Get file pointer
	File *pFile = static_cast<File*>(png_get_io_ptr(pPng));

	// Write data to file
	pFile->Write(pBuffer, nSize, 1);
}

void PngFlushData(png_structp pPng)
{
	// Get file pointer
	File *pFile = static_cast<File*>(png_get_io_ptr(pPng));

	// Flush the file buffer
	pFile->Flush();
}

png_voidp PngMalloc(png_structp pPng, png_size_t nSize)
{
	return MemoryManager::Allocator(MemoryManager::NewArray, nSize);
}

void PngFree(png_structp pPng, png_voidp pBuffer)
{
	MemoryManager::Deallocator(MemoryManager::DeleteArray, pBuffer);
}


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderPNG::Load(Image &cImage, File &cFile)
{
	// Initialize libpng
	png_structp pPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, PngError, PngWarning);
	if (pPng) {
		// Create PNG info struct
		png_infop pPngInfo = png_create_info_struct(pPng);
		if (pPngInfo) {
			// Set read function to use PL file functions
			png_set_read_fn(pPng, &cFile, PngReadData);

			// Load image headers
			png_read_info(pPng, pPngInfo);

			// Get image info
			png_byte	nBitDepth	= png_get_bit_depth	  (pPng, pPngInfo);
			png_byte	nColorType	= png_get_color_type  (pPng, pPngInfo);
			png_uint_32 nWidth		= png_get_image_width (pPng, pPngInfo);
			png_uint_32 nHeight		= png_get_image_height(pPng, pPngInfo);

			// Get data format
			EDataFormat nDataFormat;
			unsigned char nBytes = 0;
			switch (nBitDepth) {
				case 1:
				case 2:
				case 4:
					// 1, 2 or 4 Bit (Unsupported, we will use 8 Bit instead)
					nDataFormat = DataByte;
					nBytes		= 1;

					// Convert 1, 2 and 4 Bit grayscale images to 8 Bit
					png_set_expand_gray_1_2_4_to_8(pPng);
					break;

				case 8:
					// 8 Bit (Color/Palette)
					nDataFormat = DataByte;
					nBytes		= 1;
					break;

				case 16:
					// 16 Bit (Color)
					nDataFormat = DataWord;
					nBytes		= 2;
					break;
			}
			if (nBytes != 0) {
				// Get color format
				EColorFormat nColorFormat;
				unsigned char nComponents = 0;
				switch (nColorType) {
					case PNG_COLOR_TYPE_GRAY:			// (Bit depths 1, 2, 4, 8, 16)
						// Grayscale image
						nColorFormat = ColorGrayscale;
						nComponents  = 1;

						// We want grayscale in direct values, no palette please
						png_set_palette_to_rgb(pPng);
						break;

					case PNG_COLOR_TYPE_GRAY_ALPHA:		// (Bit depths 8, 16)
						// Grayscale image with additional alpha channel
						nColorFormat = ColorGrayscaleA;
						nComponents  = 2;
						break;

					case PNG_COLOR_TYPE_PALETTE:		// (Bit depths 1, 2, 4, 8)
						// Color palette (indexed colors)
						nColorFormat = ColorPalette;
						nComponents  = 1;
						break;

					case PNG_COLOR_TYPE_RGB:			// (Bit depths 8, 16)
						// RGB colors
						nColorFormat = ColorRGB;
						nComponents  = 3;
						break;

					case PNG_COLOR_TYPE_RGB_ALPHA:		// (Bit depths 8, 16)
						// RGB colors and alpha channel
						nColorFormat = ColorRGBA;
						nComponents  = 4;
						break;

					default:
						// Whatever this is, we don't support it at the moment ;-)
						break;
				}
				if (nComponents != 0) {
					// Convert transparency info into RGBA, but only if we have RGB/RGBA, not indexed colors
					if (nColorFormat == ColorRGB || nColorFormat == ColorRGBA)
						png_set_tRNS_to_alpha(pPng);

					// Create image buffer
					cImage.Clear();
					ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
					pImageBuffer->CreateImage(nDataFormat, nColorFormat, Vector3i(nWidth, nHeight, 1));

					// Get pointer to image buffer
					uint8 *pBuffer = pImageBuffer->GetData();

					// Make array with pointers to each individual row inside the image buffer
					uint32 nRowBytes = png_get_rowbytes(pPng, pPngInfo);
					uint32		nRowSize		= nBytes * nComponents * nWidth;
					png_bytepp	ppRowPointers	= new png_bytep[nHeight];
					for (uint32 i=0; i<nHeight; i++)
						ppRowPointers[i] = &pBuffer[i*nRowSize];

					// Read image
					png_read_image(pPng, ppRowPointers);

					// Read palette
					if (nColorFormat == ColorPalette) {
						// Get color palette
						png_colorp pPLTE;
						int nColors;
						if (png_get_PLTE(pPng, pPngInfo, &pPLTE, &nColors) == PNG_INFO_PLTE) {
							// Create palette
							ImagePalette *pPalette = new ImagePalette();
							pPalette->Create(nColors);

							// Copy palette data
							MemoryManager::Copy(pPalette->GetData(), pPLTE, nColors*3);

							// Set palette
							pImageBuffer->SetPalette(pPalette);
						}
					}

					// Clean up
					png_read_end(pPng, nullptr);
					png_destroy_read_struct(&pPng, &pPngInfo, nullptr);
					delete [] ppRowPointers;

					// Done
					return true;
				}
			}

			// Error: Unsupported data or color format
			return false;
		} else {
			// Error: Could not create png_info structure
			png_destroy_read_struct(&pPng, nullptr, nullptr);
			return false;
		}
	} else {
		// Error: Could not create png_struct structure
		return false;
	}
}

bool ImageLoaderPNG::Save(const Image &cImage, File &cFile)
{
	// Get the image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer && pImageBuffer->GetRowSize()) {
		// Get the type
		int nType = -1;
		switch (pImageBuffer->GetColorFormat()) {
			case ColorRGB:
				if (pImageBuffer->GetDataFormat() == DataByte  || pImageBuffer->GetDataFormat() == DataWord)
					nType = PNG_COLOR_TYPE_RGB;
				break;

			case ColorRGBA:
				if (pImageBuffer->GetDataFormat() == DataByte  || pImageBuffer->GetDataFormat() == DataWord)
					nType = PNG_COLOR_TYPE_RGBA;
				break;

			case ColorBGR:
				// [TODO]
				break;

			case ColorBGRA:
				// [TODO]
				break;

			case ColorGrayscale:
				if (pImageBuffer->GetDataFormat() == DataByte  || pImageBuffer->GetDataFormat() == DataWord)
					nType = PNG_COLOR_TYPE_GRAY;
				break;

			case ColorGrayscaleA:
				if (pImageBuffer->GetDataFormat() == DataByte  || pImageBuffer->GetDataFormat() == DataWord)
					nType = PNG_COLOR_TYPE_GRAY_ALPHA;
				break;

			case ColorPalette:
				// [TODO]
				break;
		}

		// Type found?
		if (nType != -1) {
			// Initialize libpng
			png_structp pPng = png_create_write_struct_2(PNG_LIBPNG_VER_STRING, nullptr, PngError, PngWarning, nullptr, PngMalloc, PngFree);
			if (pPng) {
				// Create PNG info struct
				png_infop pPngInfo = png_create_info_struct(pPng);
				if (pPngInfo) {
					// Set write function to use PL file functions
					png_set_write_fn(pPng, &cFile, PngWriteData, PngFlushData);

					// Get the height of the image
					const uint32 nHeight = pImageBuffer->GetSize().y;

					// Setup
					png_set_IHDR(pPng, pPngInfo, pImageBuffer->GetSize().x, nHeight, pImageBuffer->GetBytesPerPixelComponent()*8,
								 nType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
					png_write_info(pPng, pPngInfo);

					// Get the data pointer and the number of bytes per row
					const uint8 *pnData		  = pImageBuffer->GetData();
					const uint32 nBytesPerRow = pImageBuffer->GetRowSize();

					// Do we need to take care of endian?
					if (pImageBuffer->GetBytesPerPixelComponent() > 1) {
						// [TODO] An endian helper class would be nice :D
					} else {
						// Write down all rows
						const uint8 *pnCurrentData = pnData;
						for (uint32 nY=0; nY<nHeight; nY++, pnCurrentData+=nBytesPerRow)
							png_write_row(pPng, reinterpret_cast<png_bytep>(const_cast<png_bytep>(pnCurrentData)));
					}
				}

				// Cleanup
				png_write_end(pPng, pPngInfo);
				png_destroy_write_struct(&pPng, &pPngInfo);

				// Done
				return true;
			}
		} else {
			// Error: Unsupported color or data format
		}
	} else {
		// Error: Failed to get image buffer
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ImageLoaderPNG::ImageLoaderPNG() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderPNG::~ImageLoaderPNG()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
