/*********************************************************\
 *  File: ImageLoaderDDS.h                               *
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


#ifndef __PLGRAPHICS_IMAGELOADER_DDS_H__
#define __PLGRAPHICS_IMAGELOADER_DDS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImageLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct DDSHeader;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image loader implementation for DDS file formats
*
*  @note
*    - BGR(A) color format is automatically converted to RGB(A)
*/
class ImageLoaderDDS : public ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, ImageLoaderDDS, "PLGraphics", PLGraphics::ImageLoader, "Image loader implementation for DDS file formats")
		pl_properties
			pl_property("Formats",	"dds,DDS")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, Image&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, const Image&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLGRAPHICS_API bool Load(Image &cImage, PLGeneral::File &cFile);
		PLGRAPHICS_API bool Save(const Image &cImage, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGRAPHICS_API ImageLoaderDDS();

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~ImageLoaderDDS();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns bits from a given bit mask
		*
		*  @param[in]  nMask
		*    Bit mask
		*  @param[out] nShiftLeft
		*    Receives the shift left
		*  @param[out] nShiftRight
		*    Receives the shift right
		*/
		void GetBitsFromMask(PLGeneral::uint32 nMask, PLGeneral::uint32 &nShiftLeft, PLGeneral::uint32 &nShiftRight) const;

		/**
		*  @brief
		*    Decompresses a RGB/RGBA image
		*
		*  @param[in]      sHeader
		*    DDS header
		*  @param[in, out] cImageBuffer
		*    Image buffer
		*  @param[in] pnCompressedData
		*    Data to decompress
		*/
		void DecompressRGBA(const DDSHeader &sHeader, ImageBuffer &cImageBuffer, const PLGeneral::uint8 *pnCompressedData) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGELOADER_DDS_H__
