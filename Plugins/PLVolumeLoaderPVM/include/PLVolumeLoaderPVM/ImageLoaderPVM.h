/*********************************************************\
 *  File: ImageLoaderPVM.h                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLVOLUMELOADERPVM_IMAGELOADER_PVM_H__
#define __PLVOLUMELOADERPVM_IMAGELOADER_PVM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Image/ImageLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Image;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeLoaderPVM {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image loader implementation for the "PVM"-format
*
*  @note
*    - Lookout! Due to the lack of an image file format specification, this loader is using GPL code from the V^3 volume rendering package -> Don't use this loader when you're e.g. using LGPL...
*    - The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html and it appears that there's no format specification, just source code
*    - Sample data sets are available at http://www9.informatik.uni-erlangen.de/External/vollib/
*    - The image loader is only able to deal with the volumetric image data, not with volumetic specific additional information like voxel size
*/
class ImageLoaderPVM : public PLGraphics::ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ImageLoaderPVM, "PLVolumeLoaderPVM", PLGraphics::ImageLoader, "Image loader implementation for the \"PVM\"-format. The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html .")
		// Properties
		pl_properties
			pl_property("Formats",	"pvm,PVM")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		// [TODO] This is just a proof-of-concept and not that useful within the master-thesis (results in a question within PLViewerQt when loading a resource)
		//pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	PLGraphics::Image&,			PLCore::File&,			"Load method, by default 8 bit is enforced",																							"")
		pl_method_3(LoadParams,	pl_ret_type(bool),	PLGraphics::Image&,			PLCore::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not to enforce 8 bit (may result in a visible quality loss).",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const PLGraphics::Image&,	PLCore::File&,			"Save method",																															"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLGraphics::Image &cImage, PLCore::File &cFile);
		bool LoadParams(PLGraphics::Image &cImage, PLCore::File &cFile, bool bForce8Bit);
		bool Save(const PLGraphics::Image &cImage, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		ImageLoaderPVM();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ImageLoaderPVM();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeLoaderPVM


#endif // __PLVOLUMELOADERPVM_IMAGELOADER_PVM_H__
