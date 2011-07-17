/*********************************************************\
 *  File: ImageLoaderEXR.h                               *
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


#ifndef __PLIMAGELOADEREXR_IMAGELOADER_EXR_H__
#define __PLIMAGELOADEREXR_IMAGELOADER_EXR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Image/ImageLoader.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLImageLoaderEXR {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image loader implementation for the OpenEXR format (high dynamic range image file format)
*
*  @note
*    - Have a look at http://www.openexr.com
*    - There's sample data at http://www.openexr.com/downloads.html if you want to play around with the exr format
*    - Internally the OpenEXR half image is handled as float
*/
class ImageLoaderEXR : public PLGraphics::ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ImageLoaderEXR, "PLImageLoaderEXR", PLGraphics::ImageLoader, "Image loader implementation for the OpenEXR format (high dynamic range image file format)")
		// Properties
		pl_properties
			pl_property("Formats",	"exr,EXR")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	PLGraphics::Image&,			PLGeneral::File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	const PLGraphics::Image&,	PLGeneral::File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLGraphics::Image &cImage, PLGeneral::File &cFile);
		bool Save(const PLGraphics::Image &cImage, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		ImageLoaderEXR();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ImageLoaderEXR();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLImageLoaderEXR


#endif // __PLIMAGELOADEREXR_IMAGELOADER_EXR_H__
