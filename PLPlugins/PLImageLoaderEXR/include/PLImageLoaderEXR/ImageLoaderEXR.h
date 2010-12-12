/*********************************************************\
 *  File: ImageLoaderEXR.h                               *
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
*    Image loader implementation for the OpenEXR format
*    (High Dynamic Range Image)
*
*  @note
*    - Have a look at http://www.openexr.com
*    - Internally the OpenEXR half image is handled as float
*/
class ImageLoaderEXR : public PLGraphics::ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ImageLoaderEXR, "PLImageLoaderEXR", PLGraphics::ImageLoader, "Image loader implementation for the OpenEXR format")
		pl_properties
			pl_property("Formats",	"exr,EXR")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


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


	//[-------------------------------------------------------]
	//[ Private virtual PLGraphics::ImageLoader functions     ]
	//[-------------------------------------------------------]
	private:
		virtual bool Load(PLGraphics::Image &cImage, PLGeneral::File &cFile, const PLGeneral::Parameters *pParams) const;
		virtual bool Save(PLGraphics::Image &cImage, PLGeneral::File &cFile, const PLGeneral::Parameters *pParams) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLImageLoaderEXR


#endif // __PLIMAGELOADEREXR_IMAGELOADER_EXR_H__
