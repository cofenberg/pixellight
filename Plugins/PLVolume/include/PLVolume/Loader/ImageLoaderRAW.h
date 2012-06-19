/*********************************************************\
 *  File: ImageLoaderRAW.h                               *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUME_IMAGELOADER_RAW_H__
#define __PLVOLUME_IMAGELOADER_RAW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Image/ImageLoader.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Image;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image loader implementation for the "RAW" volume data file format (Lookout! You have to provide correct data type, width, height and depth loader parameters!)
*
*  @note
*    - Primitive chunk of a certain data type
*    - Lookout! This loader requires the user to provide correct loader parameters! (data type, width, height and depth)
*    - The image loader is only able to deal with the volumetric image data, not with volumetic specific additional information like voxel size
*/
class ImageLoaderRAW : public PLGraphics::ImageLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, ImageLoaderRAW, "PLVolume", PLGraphics::ImageLoader, "Image loader implementation for the \"RAW\" volume data file format (Lookout! You have to provide correct data type, width, height and depth loader parameters!)")
		// Properties
		pl_properties
			pl_property("Formats",	"raw,RAW")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		// [TODO] This is just a proof-of-concept and not that useful within the master-thesis (results in a question within PLViewerQt when loading a resource)
		// pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_6(LoadParams,	pl_ret_type(bool),	PLGraphics::Image&,			PLCore::File&,	PLCore::uint8, PLCore::uint16, PLCore::uint16, PLCore::uint16,	"Load method. Parameters: First 'integer' parameter determines the data type (0=byte, 1=word, 2=half, 3=float, 4=double), the other parameters are the width, height and depth.",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const PLGraphics::Image&,	PLCore::File&,																	"Save method",																																										"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool LoadParams(PLGraphics::Image &cImage, PLCore::File &cFile, PLCore::uint8, PLCore::uint16, PLCore::uint16, PLCore::uint16);
		bool Save(const PLGraphics::Image &cImage, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		ImageLoaderRAW();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ImageLoaderRAW();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_IMAGELOADER_RAW_H__
