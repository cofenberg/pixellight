/*********************************************************\
 *  File: VolumeLoaderDDS.h                              *
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


#ifndef __PLVOLUME_VOLUMELOADER_DDS_H__
#define __PLVOLUME_VOLUMELOADER_DDS_H__
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
*    Volume loader implementation for the "DDS" volume data file format
*
*  @remarks
*    This file format supports GPU texture compression formats like LATC1 and therefore makes it possible to load in
*    compressed volume data as efficient as possible by directly passing thru the compressed loaded data to the GPU
*    without need for any further processing.
*
*  @note
*    - DirectDraw Surface file format from Microsoft
*    - Use e.g. "The Compressonator" from AMD (http://developer.amd.com/tools/compressonator/pages/default.aspx) to open, view, edit and save the dds-file
*    - BGR(A) color format is automatically converted to RGB(A)
*      This volume loader is in fact just a comfort wrapper around the DDS image loader
*/
class VolumeLoaderDDS : public VolumeLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, VolumeLoaderDDS, "PLVolume", PLVolume::VolumeLoader, "Volume loader implementation for the \"DDS\" volume data file format")
		// Properties
		pl_properties
			pl_property("Formats",	"dds,DDS")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	Volume&,		PLCore::File&,							"Load method, voxel size is set to default",															"")
		pl_method_5(LoadParams,	pl_ret_type(bool),	Volume&,		PLCore::File&,	float,	float,	float,	"Load method. Parameters: First, second and third 'float' parameters are the x, y and z voxel size.",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const Volume&,	PLCore::File&,							"Save method",																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(Volume &cVolume, PLCore::File &cFile);
		bool LoadParams(Volume &cVolume, PLCore::File &cFile, float fVoxelSizeX, float fVoxelSizeY, float fVoxelSizeZ);
		bool Save(const Volume &cVolume, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		VolumeLoaderDDS();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VolumeLoaderDDS();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_VOLUMELOADER_DDS_H__
