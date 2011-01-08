/*********************************************************\
 *  File: PLGraphics.h                                   *
 *      Main header file of this project
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


/**
*  @mainpage PLGraphics
*
*  @section intro_sec Introduction
*
*  This is the PLGraphics reference.
*/


#ifndef __PLGRAPHICS_PLGRAPHICS_H__
#define __PLGRAPHICS_PLGRAPHICS_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLGraphics/PLGraphicsWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLGraphics/PLGraphicsLinux.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test images
*/
enum ETestImage {
	TestImage2DSimple = 0,	/**< Simple blue test image (256x256, RGB) */
	TestImage2DGradient,	/**< Gradient colored test image (256x256, RGB) */
	TestImage2DCheckers,	/**< Two-colored checkers test image (256x256, RGB) */
	TestImageCubeMap		/**< Cube map test */
};

/**
*  @brief
*    Consistency checks
*/
enum ECheckConsistency {
	CheckOk = 0,					/**< No problems */
	CheckImageBufferInvalidSize,	/**< ImageBuffer has an invalid size (<= 0) */
	CheckImageBufferNoData,			/**< ImageBuffer has no data at all */
	CheckPaletteNotAssigned,		/**< ImageBuffer has color type palette but no palette assigned */
	CheckPaletteEmpty,				/**< ImageBuffer has color type palette but palette is empty */
	CheckInconsistentDataFormat,	/**< ImageBuffers do not all have the same data format */
	CheckInconsistentColorFormat,	/**< ImageBuffers do not all have the same color format */
	CheckPartEmpty,					/**< Part contains no image buffers */
	CheckImageEmpty,				/**< Image contains no parts */
	CheckCubemapSideMissing,		/**< Cubemap does not have all 6 sides defined */
	CheckCubemapSideInvalid,		/**< Cubemap has an image part that is not a cubemap side */
	CheckCubemapSideDouble,			/**< Cubemap has more than one image part with the same side ID */
	CheckMipmapInconsistent,		/**< Mipmaps are not defined properly (everyone has to be smaller than the last) */
	CheckMipmapsNotPowerOfTwo,		/**< Not all mipmaps have a size that is power-of-two */
	CheckMipmapsNot1x1,				/**< Mipmaps have not been defined down to 1x1 */
};

/**
*  @brief
*    Semantics of image part
*
*  @remarks
*    ID used to identify parts of an image. Please note that the part ID is purely optional and can be chosen freely.
*    This enumeration contains some predefined semantics but is not a complete list, so you can choose any other value
*    as well. Therefore please always use PLGeneral::uint32 as a data type for semantics and not EImagePart directly.
*/
enum EImagePart {
	ImagePartStatic = 0,	/**< A single image */
	ImagePartCubeSidePosX,	/**< Side of cubemap: positive x */
	ImagePartCubeSideNegX,	/**< Side of cubemap: negative x */
	ImagePartCubeSidePosY,	/**< Side of cubemap: positive y */
	ImagePartCubeSideNegY,	/**< Side of cubemap: negative y */
	ImagePartCubeSidePosZ,	/**< Side of cubemap: positive z */
	ImagePartCubeSideNegZ	/**< Side of cubemap: negative z */
};

/**
*  @brief
*    Data format
*/
enum EDataFormat {
	DataByte = 0,			/**< Byte (8 bit) */
	DataWord,				/**< Word (16 bit) */
	DataFloat,				/**< Float (32 bit) */
	DataDouble				/**< Double (64 bit) */
};

/**
*  @brief
*    Color format
*/
enum EColorFormat {
	ColorRGB = 0,			/**< RGB */
	ColorRGBA,				/**< RGBA */
	ColorBGR,				/**< BGR */
	ColorBGRA,				/**< BGRA */
	ColorGrayscale,			/**< Grayscale image */
	ColorGrayscaleA,		/**< Grayscale image with alpha */
	ColorPalette			/**< Color palette */
};

/**
*  @brief
*    Compression types
*/
enum ECompression {
	CompressionNone = 0,	/**< No compression */
	CompressionDXT1,		/**< DXT1 compression (known as BC1 in DirectX 10, RGB compression: 8:1, 8 bytes per block) */
	CompressionDXT3,		/**< DXT3 compression (known as BC2 in DirectX 10, RGBA compression: 4:1, 16 bytes per block) */
	CompressionDXT5,		/**< DXT5 compression (known as BC3 in DirectX 10, RGBA compression: 4:1, 16 bytes per block) */
	CompressionLATC1,		/**< 1 component texture compression (also known as 3DC+/ATI1N, known as BC4 in DirectX 10, 8 bytes per block) */
	CompressionLATC2		/**< 2 component texture compression (luminance & alpha compression 4:1 -> normal map compression, also known as 3DC/ATI2N, known as BC5 in DirectX 10, 16 bytes per block) */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
}


#endif // __PLGRAPHICS_PLGRAPHICS_H__
