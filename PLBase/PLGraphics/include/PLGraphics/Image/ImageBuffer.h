/*********************************************************\
 *  File: ImageBuffer.h                                  *
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


#ifndef __PLGRAPHICS_IMAGEBUFFER_H__
#define __PLGRAPHICS_IMAGEBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3i.h>
#include "PLGraphics/PLGraphics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ImageData;
class ImagePalette;
class ImageEffect;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image buffer class
*
*  @remarks
*    The image buffer class uses a 'copy on change' technique - therefore copying one image
*    buffer into another is quite performant because the internal image buffer data is shared
*    as long as a image buffer doesn't change.
*
*  @note
*    - The origin (0, 0) is on the upper-left ("top-down")
*    - The image components are stored in a linear byte array. RGB example:\n
*      R1G1B1R2G2B2R3G3B3...
*    - Implementation of the proxy design pattern, this class is the proxy
*/
class ImageBuffer {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the number of components per pixel
		*
		*  @param[in] nColorFormat
		*    Color format
		*
		*  @return
		*    The number of components per pixel
		*/
		PLGRAPHICS_API static PLGeneral::uint32 GetComponentsPerPixel(EColorFormat nColorFormat);

		/**
		*  @brief
		*    Returns the number of bytes per pixel component
		*
		*  @param[in] nDataFormat
		*    Data format
		*
		*  @return
		*    The number of bytes per pixel component
		*/
		PLGRAPHICS_API static PLGeneral::uint32 GetBytesPerPixelComponent(EDataFormat nDataFormat);

		/**
		*  @brief
		*    Returns the number of bytes per pixel
		*
		*  @param[in] nDataFormat
		*    Data format
		*  @param[in] nColorFormat
		*    Color format
		*
		*  @return
		*    The number of bytes per pixel
		*/
		PLGRAPHICS_API static PLGeneral::uint32 GetBytesPerPixel(EDataFormat nDataFormat, EColorFormat nColorFormat);

		/**
		*  @brief
		*    Returns the size of a certain mipmap
		*
		*  @param[in] nBaseSize
		*    Size of the base level
		*  @param[in] nMipmap
		*    Mipmap level
		*
		*  @return
		*    The size of a certain mipmap
		*/
		PLGRAPHICS_API static PLGeneral::uint32 GetMipmapSize(PLGeneral::uint32 nBaseSize, PLGeneral::uint32 nMipmap);

		/**
		*  @brief
		*    Returns whether or not the given color format has an alpha channel
		*
		*  @param[in] nColorFormat
		*    Color format to check
		*
		*  @return
		*    'true' if the given color format has an alpha channel, else 'false'
		*/
		PLGRAPHICS_API static bool IsAlphaChannelColorFormat(EColorFormat nColorFormat);

		/**
		*  @brief
		*    Returns a version with alpha channel of the given color format
		*
		*  @param[in] nColorFormat
		*    Color format to return a color format with alpha channel from
		*
		*  @return
		*    Color format with alpha channel on success, same color format channel if the given color format
		*    has already a alpha channel or when there's no version of the given color format with alpha channel
		*/
		PLGRAPHICS_API static EColorFormat GetAlphaChannelColorFormat(EColorFormat nColorFormat);

		/**
		*  @brief
		*    Returns a version without alpha channel of the given color format
		*
		*  @param[in] nColorFormat
		*    Color format to return a color format without alpha channel from
		*
		*  @return
		*    Color format without alpha channel on success, same color format channel if the given color format
		*    has already no alpha channel or when there's no version of the given color format without alpha channel
		*/
		PLGRAPHICS_API static EColorFormat GetNoneAlphaChannelColorFormat(EColorFormat nColorFormat);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGRAPHICS_API ImageBuffer();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGRAPHICS_API ImageBuffer(const ImageBuffer &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API ~ImageBuffer();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this object
		*/
		PLGRAPHICS_API ImageBuffer &operator =(const ImageBuffer &cSource);

		/**
		*  @brief
		*    Create image
		*
		*  @param[in] nDataFormat
		*    Desired data format
		*  @param[in] nColorFormat
		*    Desired color format
		*  @param[in] vSize
		*    Image size
		*  @param[in] nCompression
		*    Compression type
		*
		*  @remarks
		*    Please note that a call to Create() will not immediatly create the image buffer itself.
		*    The image buffer is created on the first call to GetData() or GetCompressedData() respectively.
		*/
		PLGRAPHICS_API void CreateImage(EDataFormat nDataFormat, EColorFormat nColorFormat, const PLMath::Vector3i &vSize, ECompression nCompression = CompressionNone);

		/**
		*  @brief
		*    Clear data
		*/
		PLGRAPHICS_API void Clear();

		/**
		*  @brief
		*    Apply image effect
		*
		*  @param[in] cEffect
		*    Image effect
		*/
		PLGRAPHICS_API void ApplyEffect(const ImageEffect &cEffect);

		/**
		*  @brief
		*    Check image for possible problems
		*
		*  @return
		*    Error code describing any problem found, 'CheckOk' if everything is fine
		*/
		PLGRAPHICS_API ECheckConsistency CheckConsistency() const;

		/**
		*  @brief
		*    Create a test image
		*
		*  @param[in] nTestImage
		*    ID of test image
		*
		*  @remarks
		*    Only 2D and 3D test images are allowed here. For images containing more than
		*    one image buffer, you have to use Image::CreateTestImage().
		*/
		PLGRAPHICS_API void CreateTestImage(ETestImage nTestImage = TestImage2DSimple);

		/**
		*  @brief
		*    Get data format
		*
		*  @return
		*    Data format
		*/
		PLGRAPHICS_API EDataFormat GetDataFormat() const;

		/**
		*  @brief
		*    Get color format
		*
		*  @return
		*    Color format
		*/
		PLGRAPHICS_API EColorFormat GetColorFormat() const;

		/**
		*  @brief
		*    Returns the number of components per pixel
		*
		*  @return
		*    The number of components per pixel
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetComponentsPerPixel() const;

		/**
		*  @brief
		*    Returns the number of bytes per pixel component
		*
		*  @return
		*    The number of bytes per pixel component
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetBytesPerPixelComponent() const;

		/**
		*  @brief
		*    Returns the number of bytes per pixel
		*
		*  @return
		*    The number of bytes per pixel
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetBytesPerPixel() const;

		/**
		*  @brief
		*    Get compression type
		*
		*  @return
		*    Compression type
		*/
		PLGRAPHICS_API ECompression GetCompression() const;

		/**
		*  @brief
		*    Set compression type
		*
		*  @param[in] nCompression
		*    Compression type
		*
		*  @remarks
		*    This will invalidate the compressed image data buffer
		*/
		PLGRAPHICS_API void SetCompression(ECompression nCompression);

		/**
		*  @brief
		*    Get image size
		*
		*  @return
		*    Size of image
		*/
		PLGRAPHICS_API PLMath::Vector3i GetSize() const;

		/**
		*  @brief
		*    Returns the number of pixels
		*
		*  @return
		*    The number of pixels
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetNumOfPixels() const;

		/**
		*  @brief
		*    Check if uncompressed data is available
		*
		*  @return
		*    'true' if image data is available, else 'false'
		*/
		PLGRAPHICS_API bool HasData() const;

		/**
		*  @brief
		*    Get size of image data in bytes
		*
		*  @return
		*    Size of image data in bytes
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetDataSize() const;

		/**
		*  @brief
		*    Get size of one row of image data in bytes
		*
		*  @return
		*    Size of one row in bytes
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetRowSize() const;

		/**
		*  @brief
		*    Get image data
		*
		*  @return
		*    Pointer to image data, a null pointer on error
		*
		*  @remarks
		*    If the image contains no uncompressed data, but compressed image data is available the data,
		*    will be decompressed automatically and stored in the decompressed image buffer this method returns.
		*/
		PLGRAPHICS_API const PLGeneral::uint8 *GetData() const;
		PLGRAPHICS_API PLGeneral::uint8 *GetData();

		/**
		*  @brief
		*    Check if compressed data is available
		*
		*  @return
		*    'true' if compressed image data is available, else 'false'
		*/
		PLGRAPHICS_API bool HasCompressedData() const;

		/**
		*  @brief
		*    Get size of compressed image data in bytes
		*
		*  @return
		*    Size of compressed image data in bytes
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetCompressedDataSize() const;

		/**
		*  @brief
		*    Get compressed image data
		*
		*  @return
		*    Pointer to compressed image data, a null pointer on error
		*/
		PLGRAPHICS_API const PLGeneral::uint8 *GetCompressedData() const;
		PLGRAPHICS_API PLGeneral::uint8 *GetCompressedData();

		/**
		*  @brief
		*    Compress image data
		*
		*  @remarks
		*    If the image contains uncompressed image data, the data will be
		*    compressed and stored in the compressed image buffer.
		*/
		PLGRAPHICS_API bool Compress();

		/**
		*  @brief
		*    Decompress image data
		*
		*  @remarks
		*    If the image contains compressed image data, the data will be
		*    decompressed and stored in the decompressed image buffer.
		*/
		PLGRAPHICS_API bool Decompress();

		/**
		*  @brief
		*    Set color palette
		*
		*  @param[in] pPalette
		*    Pointer to color palette, or a null pointer if the image has no palette
		*/
		PLGRAPHICS_API void SetPalette(ImagePalette *pPalette);

		/**
		*  @brief
		*    Get color palette
		*
		*  @return
		*    Pointer to color palette, or a null pointer if the image has no palette
		*/
		PLGRAPHICS_API const ImagePalette *GetPalette() const;
		PLGRAPHICS_API ImagePalette *GetPalette();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Make image data unique
		*/
		void MakeBufferUnique();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ImageData *m_pImageData;	/**< Shared image data, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEBUFFER_H__
