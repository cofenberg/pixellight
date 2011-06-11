/*********************************************************\
 *  File: ImageLoaderJPG.h                               *
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


#ifndef __PLGRAPHICS_IMAGELOADER_JPG_H__
#define __PLGRAPHICS_IMAGELOADER_JPG_H__
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image loader implementation for JPEG ("Joint Photographic Experts Group") file formats
*
*  @note
*    - Using libjpeg (http://www.ijg.org/)
*/
class ImageLoaderJPG : public ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, ImageLoaderJPG, "PLGraphics", PLGraphics::ImageLoader, "Image loader implementation for JPEG (\"Joint Photographic Experts Group\") file formats")
		// Properties
		pl_properties
			pl_property("Formats",	"jpg,jpeg,jpe,jif,jfif,jfi,JPG,JPEG,JPE,JIF,JFIF,JFI")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	Image&,			PLGeneral::File&,						"Load method, no fancy upsampling and no interblock smoothing is applied",																											"")
		pl_method_4(LoadParams,	pl_ret_type(bool),	Image&,			PLGeneral::File&,	bool,	bool,		"Load method. Parameters: First 'bool' parameter determines whether or not fancy upsampling is applied, second 'bool' parameter whether or not interblock smoothing is applied.",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const Image&,	PLGeneral::File&,						"Save method, using 100% quality setting",																																			"")
		pl_method_3(SaveParams,	pl_ret_type(bool),	const Image&,	PLGeneral::File&,	PLGeneral::uint32,	"Save method, quality (0...100) as first parameter",																																"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLGRAPHICS_API bool Load(Image &cImage, PLGeneral::File &cFile);
		PLGRAPHICS_API bool LoadParams(Image &cImage, PLGeneral::File &cFile, bool bBlockSmoothing, bool bFancyUpsampling);
		PLGRAPHICS_API bool Save(const Image &cImage, PLGeneral::File &cFile);
		PLGRAPHICS_API bool SaveParams(const Image &cImage, PLGeneral::File &cFile, PLGeneral::uint32 nQuality);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGRAPHICS_API ImageLoaderJPG();

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~ImageLoaderJPG();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGELOADER_JPG_H__
