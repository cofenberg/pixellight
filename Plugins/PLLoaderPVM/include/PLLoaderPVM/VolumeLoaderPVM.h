/*********************************************************\
 *  File: VolumeLoaderPVM.h                              *
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


#ifndef __PLLOADERPVM_VOLUMELOADER_PVM_H__
#define __PLLOADERPVM_VOLUMELOADER_PVM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLVolume/Loader/VolumeLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLVolume {
	class Volume;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLLoaderPVM {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume loader implementation for the "PVM"-format
*
*  @note
*    - Lookout! Due to the lack of an image file format specification, this loader is using GPL code from the V^3 volume rendering package -> Don't use this loader when you're e.g. using LGPL...
*    - The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html and it appears that there's no format specification, just source code
*    - Sample data sets are available at http://www9.informatik.uni-erlangen.de/External/vollib/
*/
class VolumeLoaderPVM : public PLVolume::VolumeLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, VolumeLoaderPVM, "PLLoaderPVM", PLVolume::VolumeLoader, "Volume loader implementation for the \"PVM\"-format. The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html .")
		// Properties
		pl_properties
			pl_property("Formats",	"pvm,PVM")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,			"Load method, by default 8 bit is enforced",																							"")
		pl_method_3(LoadParams,	pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not to enforce 8 bit (may result in a visible quality loss).",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const PLVolume::Volume&,	PLCore::File&,			"Save method",																															"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLVolume::Volume &cVolume, PLCore::File &cFile);
		bool LoadParams(PLVolume::Volume &cVolume, PLCore::File &cFile, bool bForce8Bit);
		bool Save(const PLVolume::Volume &cVolume, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		VolumeLoaderPVM();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VolumeLoaderPVM();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderPVM


#endif // __PLLOADERPVM_VOLUMELOADER_PVM_H__
