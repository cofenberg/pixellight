/*********************************************************\
 *  File: VolumeLoaderRAW.h                              *
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


#ifndef __PLVOLUME_VOLUMELOADER_RAW_H__
#define __PLVOLUME_VOLUMELOADER_RAW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolume/Loader/VolumeLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Volume;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume loader implementation for the "RAW" volume data file format (Lookout! You have to provide correct data type, width, height and depth loader parameters!)
*
*  @note
*    - Primitive chunk of a certain data type
*    - Lookout! This loader requires the user to provide correct loader parameters! (data type, width, height and depth)
*/
class VolumeLoaderRAW : public VolumeLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, VolumeLoaderRAW, "PLVolume", PLVolume::VolumeLoader, "Volume loader implementation for the \"RAW\" volume data file format (Lookout! You have to provide correct data type, width, height and depth loader parameters!)")
		// Properties
		pl_properties
			pl_property("Formats",	"raw,RAW")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_6(LoadParams,	pl_ret_type(bool),	Volume&,		PLCore::File&,	PLCore::uint8, PLCore::uint16, PLCore::uint16, PLCore::uint16,	"Load method. Parameters: First 'integer' parameter determines the data type (0=byte, 1=word, 2=half, 3=float, 4=double), the other parameters are the width, height and depth.",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const Volume&,	PLCore::File&,																	"Save method",																																										"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool LoadParams(Volume &cVolume, PLCore::File &cFile, PLCore::uint8, PLCore::uint16, PLCore::uint16, PLCore::uint16);
		bool Save(const Volume &cVolume, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		VolumeLoaderRAW();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VolumeLoaderRAW();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_VOLUMELOADER_RAW_H__
