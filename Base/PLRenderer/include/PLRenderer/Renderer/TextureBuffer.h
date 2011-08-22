/*********************************************************\
 *  File: TextureBuffer.h                                *
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


#ifndef __PLRENDERER_TEXTUREBUFFER_H__
#define __PLRENDERER_TEXTUREBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Resource.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Image;
	class Color4;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer texture buffer resource base class
*
*  @remarks
*    In the literature, for a volume an element is called voxel, and a texture element is called texel.
*    To stay name compatible with PLGraphics::ImageBuffer, we will just use the term pixel.
*/
class TextureBuffer : public Resource {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RendererBackend;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture buffer flags
		*/
		enum EFlags {
			Mipmaps      = 1<<0,	/**< Use mipmaps (see GetNumOfMipmaps() for more information) */
			Compression  = 1<<1,	/**< Use texture buffer compression if possible (is ignored if a certain internal format is forced) */
			RenderTarget = 1<<2		/**< This texture buffer can be used as render target */
		};

		/**
		*  @brief
		*    Texture buffer pixel formats
		*/
		enum EPixelFormat {
			// Unsigned formats
			L8            =  0,	/**< 8-bit pixel format, all bits luminance */
			L16           =  1,	/**< 16-bit pixel format, all bits luminance */
			A8            =  2,	/**< 8-bit pixel format, all bits alpha */
			L4A4          =  3,	/**< 8-bit pixel format, 4 bits for luminance and alpha */
			L8A8          =  4,	/**< 16-bit pixel format, 8 bits for luminance and alpha */
			D16           =  5,	/**< 16-bit z-buffer bit depth */
			D24           =  6,	/**< 32-bit z-buffer bit depth using 24 bits for the depth channel */
			D32           =  7,	/**< 32-bit z-buffer bit depth */
			R3G3B2        =  8,	/**< 8-bit pixel format, 3 bits red, 3 bits green and 2 bits blue  */
			R5G6B5        =  9,	/**< 16-bit pixel format, 5 bits red, 6 bits green and 5 bits blue  */
			R5G5B5A1      = 10,	/**< 16-bit pixel format, 5 bits red, 5 bits green, 5 bits blue and 1 bits alpha  */
			R4G4B4A4      = 11,	/**< 16-bit pixel format, 4 bits for red, green, blue and alpha  */
			R8G8B8        = 12,	/**< 24-bit (or 32-bit if 24-bits are not supported by the hardware) pixel format, 8 bits for red, green and blue */
			R8G8B8A8      = 13,	/**< 32-bit pixel format, 8 bits for red, green, blue and alpha */
			R10G10B10A2   = 14,	/**< 32-bit pixel format, 10 bits for red, green, blue and 2 bits for alpha */
			R16G16B16A16  = 15,	/**< 64-bit pixel format, 16 bits for red, green, blue and alpha */
			DXT1          = 16,	/**< DXT1 format (known as BC1 in DirectX 10, RGB compression: 8:1) */
			DXT3          = 17,	/**< DXT3 format (known as BC2 in DirectX 10, RGBA compression: 4:1) */
			DXT5          = 18,	/**< DXT5 format (known as BC3 in DirectX 10, RGBA compression: 4:1) */
			LATC1         = 19,	/**< 1 component texture compression (also known as 3DC+/ATI1N, known as BC4 in DirectX 10, 8 bytes per block) */
			LATC2         = 20, /**< 2 component texture compression (luminance & alpha compression 4:1 -> normal map compression, also known as 3DC/ATI2N, known as BC5 in DirectX 10, 16 bytes per block) */
			// Floating-point formats
			L16F          = 21,	/**< 16-bit float format using 16 bits for luminance */
			L32F          = 22,	/**< 32-bit float format using 32 bits for luminance */
			R16G16B16A16F = 23,	/**< 64-bit float format using 16 bits for the each channel (red, green, blue, alpha) */
			R32G32B32A32F = 24,	/**< 128-bit float format using 32 bits for the each channel (red, green, blue, alpha) */
			// End
			Unknown       = 25	/**< Unknown texture buffer pixel format */
		};
		static const PLCore::uint32 NumOfPixelFormats = 25;	/**< Number of pixel formats */


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the texture buffer pixel format of a given image (PLGraphics::Image)
		*
		*  @param[in] cImage
		*    Image to get the texture buffer pixel format from
		*  @param[in] bNoCompression
		*    Do NOT use texture buffer compression?
		*
		*  @return
		*    The texture buffer pixel format of the given image
		*/
		PLRENDERER_API static EPixelFormat GetFormatFromImage(const PLGraphics::Image &cImage, bool bNoCompression = false);

		/**
		*  @brief
		*    Returns whether or not the given texture buffer format is compressed
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    'true' if the texture buffer format is compressed, else 'false'
		*/
		PLRENDERER_API static bool IsCompressedFormat(EPixelFormat nFormat);

		/**
		*  @brief
		*    Returns whether or not the given texture buffer format is a depth buffer format
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    'true' if the texture buffer format is a depth buffer format, else 'false'
		*/
		PLRENDERER_API static bool IsDepthFormat(EPixelFormat nFormat);

		/**
		*  @brief
		*    If the given texture buffer format is compressed, a proper uncompressed texture buffer format will be returned
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    Uncompressed texture buffer format, if the given format was not compressed, the given format will be returned
		*/
		PLRENDERER_API static EPixelFormat GetUncompressedFormat(EPixelFormat nFormat);

		/**
		*  @brief
		*    Returns whether or not the given texture buffer format is a floating point format
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    'true' if the texture buffer format is a floating point format, else 'false'
		*/
		PLRENDERER_API static bool IsFloatingPointFormat(EPixelFormat nFormat);

		/**
		*  @brief
		*    Returns the number of components per pixel
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    The number of components per pixel, 0 if unknown format
		*/
		PLRENDERER_API static PLCore::uint32 GetComponentsPerPixel(EPixelFormat nFormat);

		/**
		*  @brief
		*    Returns the number of bytes per pixel component
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    The number of bytes per pixel component, 0 if unknown format or no full byte per component
		*/
		PLRENDERER_API static PLCore::uint32 GetBytesPerPixelComponent(EPixelFormat nFormat);

		/**
		*  @brief
		*    Returns the number of bytes per pixel
		*
		*  @param[in] nFormat
		*    Texture buffer pixel format
		*
		*  @return
		*    The number of bytes per pixel, 0 if unknown format or no full byte per pixel (compressed format)
		*/
		PLRENDERER_API static PLCore::uint32 GetBytesPerPixel(EPixelFormat nFormat);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureBuffer();

		/**
		*  @brief
		*    Returns the texture buffer flags
		*
		*  @return
		*    The texture buffer flags (see EFlags)
		*/
		PLRENDERER_API PLCore::uint32 GetFlags() const;

		/**
		*  @brief
		*    Returns the texture buffer pixel format
		*
		*  @return
		*    The texture buffer pixel format
		*/
		PLRENDERER_API EPixelFormat GetFormat() const;

		/**
		*  @brief
		*    Returns whether or not the used texture buffer format is compressed
		*
		*  @return
		*    'true' if the used texture buffer format is compressed, else 'false'
		*/
		PLRENDERER_API bool IsCompressedFormat() const;

		/**
		*  @brief
		*    Returns whether or not the used texture buffer format is a depth buffer format
		*
		*  @return
		*    'true' if the used texture buffer format is a depth buffer format, else 'false'
		*/
		PLRENDERER_API bool IsDepthFormat() const;

		/**
		*  @brief
		*    If the used texture buffer format is compressed, a proper uncompressed texture buffer format will be returned
		*
		*  @return
		*    Uncompressed texture buffer format, if the used format was not compressed, the used format will be returned
		*/
		PLRENDERER_API EPixelFormat GetUncompressedFormat() const;

		/**
		*  @brief
		*    Returns whether or not the used texture buffer format is a floating point format
		*
		*  @return
		*    'true' if the texture buffer format is a floating point format, else 'false'
		*/
		PLRENDERER_API bool IsFloatingPointFormat() const;

		/**
		*  @brief
		*    Returns the number of components per pixel
		*
		*  @return
		*    The number of components per pixel, 0 if unknown format
		*/
		PLRENDERER_API PLCore::uint32 GetComponentsPerPixel() const;

		/**
		*  @brief
		*    Returns the number of bytes per pixel component
		*
		*  @return
		*    The number of bytes per pixel component, 0 if unknown format or no full byte per component
		*/
		PLRENDERER_API PLCore::uint32 GetBytesPerPixelComponent() const;

		/**
		*  @brief
		*    Returns the number of bytes per pixel
		*
		*  @return
		*    The number of bytes per pixel, 0 if unknown format or no full byte per pixel (compressed format)
		*/
		PLRENDERER_API PLCore::uint32 GetBytesPerPixel() const;

		/**
		*  @brief
		*    Returns the number of mipmap levels
		*
		*  @return
		*    The number of mipmap levels, 0 if there are no mipmaps
		*    (maybe not supported or not desired for this texture buffer)
		*
		*  @remarks
		*    Level 0 is the 'original' base image and GetNumOfMipmaps() is the version with the lowest resolution
		*    which is normally 1x1. For a 2D texture buffer, the number of mipmaps down to 1x1 is calculated by
		*    log2(max(width, height)). For a 32x16 texture buffer, this will result in the following additional
		*    mipmaps: 16x8, 8x4, 4x2, 2x1, 1x1
		*
		*    Note that mipmaps are only created/used from a given image if the flag 'Mipmaps' is set.
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfMipmaps() const;

		/**
		*  @brief
		*    Returns the number of faces
		*
		*  @return
		*    The number of faces, always >0!
		*/
		PLRENDERER_API PLCore::uint8 GetNumOfFaces() const;

		/**
		*  @brief
		*    Returns the total number of pixels including all mipmaps
		*
		*  @return
		*    The total number of pixels including all mipmaps
		*/
		PLRENDERER_API PLCore::uint32 GetTotalNumOfPixels() const;

		/**
		*  @brief
		*    Returns the total number of bytes required for the texture buffer data including all mipmaps
		*
		*  @return
		*    The number of bytes required for the texture buffer data including all mipmaps
		*
		*  @note
		*    - If the texture buffer is using a compressed format, compression is also taken into account
		*/
		PLRENDERER_API PLCore::uint32 GetTotalNumOfBytes() const;

		/**
		*  @brief
		*    Downloads the texture buffer content and returns the number of NAN values in it
		*
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*  @param[in] nFace
		*    ID of the texture buffer face which should be downloaded if this is a cube texture buffer
		*
		*  @return
		*    Number of NAN values (pixel components are counted individually)
		*
		*  @remarks
		*    If there are NAN values inside a texture buffer used for rendering, nasty "black boxes" (NVIDIA) or
		*    "white boxes" (ATI) may appear. This function may help you to pinpoint the place were the NANs are produces.
		*
		*  @note
		*    - This function can only be used if the texture buffer format is a floating point one
		*    - This function should only be used for debugging
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfNANValues(PLCore::uint32 nMipmap = 0, PLCore::uint8 nFace = 0);

		/**
		*  @brief
		*    Downloads the texture buffer content, replaces pixels containing a NAN value by a given color, and uploads the fixed texture buffer
		*
		*  @param[in] cColor
		*    Color for pixels containing a NAN value
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*  @param[in] nFace
		*    ID of the texture buffer face which should be fixed if this is a cube texture buffer
		*
		*  @return
		*    Number of fixed NAN pixels
		*
		*  @see
		*    - GetNumOfNANValues()
		*/
		PLRENDERER_API PLCore::uint32 FixNANValues(const PLGraphics::Color4 &cColor, PLCore::uint32 nMipmap = 0, PLCore::uint8 nFace = 0);


	//[-------------------------------------------------------]
	//[ Public virtual TextureBuffer functions                ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the number of pixels of a certain mipmap level
		*
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*
		*  @return
		*    The number of pixels of a certain mipmap level
		*
		*  @note
		*    - If this is a cube texture, the number of pixels of all faces together will be returned
		*/
		virtual PLCore::uint32 GetNumOfPixels(PLCore::uint32 nMipmap = 0) const = 0;

		/**
		*  @brief
		*    Returns the number of bytes required to hold certain mipmap level texture buffer data
		*
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*  @param[in] nFormat
		*    Target texture buffer pixel format, if Unknown, the format of THIS texture buffer is chosen automatically
		*
		*  @return
		*    The number of bytes required to hold certain mipmap level texture buffer data
		*
		*  @note
		*    - If 'nFormat' is a compressed format, compression is also taken into account
		*    - If this is a cube texture, the number of bytes of all faces together will be returned
		*/
		virtual PLCore::uint32 GetNumOfBytes(PLCore::uint32 nMipmap = 0, EPixelFormat nFormat = Unknown) const = 0;

		/**
		*  @brief
		*    Uploads data to the GPU
		*
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*  @param[in] nFormat
		*    Texture buffer pixel format of 'pData', can not be 'Unknown'. If this is a compressed format,
		*    it MUST be the same format this texture buffer has.
		*  @param[in] pData
		*    Pointer to the data to upload, MUST have at least GetNumOfBytes(nMipmap, nFormat) bytes!
		*  @param[in] nFace
		*    ID of the texture buffer face which should be uploaded if this is a cube texture buffer
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid mipmap level? invalid data?)
		*/
		virtual bool Upload(PLCore::uint32 nMipmap, EPixelFormat nFormat, const void *pData, PLCore::uint8 nFace = 0) = 0;

		/**
		*  @brief
		*    Downloads data from the GPU
		*
		*  @param[in]  nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*  @param[in]  nFormat
		*    Texture buffer pixel format of 'pData', can not be 'Unknown'. If this is a compressed format,
		*    it MUST be the same format this texture buffer has.
		*  @param[out] pData
		*    Will receive the downloaded data, MUST have at least GetNumOfBytes(nMipmap, nFormat) bytes!
		*  @param[in] nFace
		*    ID of the texture buffer face which should be downloaded if this is a cube texture buffer
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid mipmap level? invalid data?)
		*/
		virtual bool Download(PLCore::uint32 nMipmap, EPixelFormat nFormat, void *pData, PLCore::uint8 nFace = 0) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nType
		*    Resource type
		*  @param[in] nFlags
		*    Texture buffer flags (see EFlags)
		*/
		PLRENDERER_API TextureBuffer(Renderer &cRenderer, EType nType, PLCore::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Protected virtual TextureBuffer functions             ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Makes this texture buffer to the renderers current texture buffer
		*
		*  @param[in] nStage
		*    Texture stage
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool MakeCurrent(PLCore::uint32 nStage) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::uint32 m_nFlags;			/**< Texture buffer flags (see EFlags) */
		EPixelFormat   m_nFormat;			/**< Texture buffer pixel format */
		PLCore::uint32 m_nNumOfElements;	/**< The number of elements */
		PLCore::uint32 m_nNumOfMipmaps;		/**< Number of mipmap levels (the base level is 0) */
		PLCore::uint32 m_nTotalNumOfBytes;	/**< Total number of bytes required to the texture buffer data including all mipmaps */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		TextureBuffer(const TextureBuffer &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		TextureBuffer &operator =(const TextureBuffer &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTUREBUFFER_H__
