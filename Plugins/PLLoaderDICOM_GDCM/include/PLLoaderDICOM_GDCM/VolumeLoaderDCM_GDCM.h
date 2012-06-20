/*********************************************************\
 *  File: VolumeLoaderDCM_GDCM.h                         *
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


#ifndef __PLLOADERDCM_GDCM_H__
#define __PLLOADERDCM_GDCM_H__
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
namespace PLLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume loader implementation for the "dcm" image data file format by using GDCM (Grassroots DICOM) (http://sourceforge.net/projects/gdcm/)
*
*  @note
*    - DICOM (Digital Imaging and Communications in Medicine)
*/
class VolumeLoaderDCM_GDCM : public PLVolume::VolumeLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, VolumeLoaderDCM_GDCM, "PLLoaderDICOM_GDCM", PLVolume::VolumeLoader, "Volume loader implementation for the \"dcm\" image data file format by using GDCM (Grassroots DICOM) (http://sourceforge.net/projects/gdcm/)")
		// Properties
		pl_properties
			pl_property("Formats",	",dcm,DCM,dicom,DICOM")	// DICOM data can be within a given directory instead of a file, the comma at the beginning of the string denotes that no extension is also valid
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,					pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,				"Load method, by default 8 bit is enforced",																									"")
		pl_method_3(LoadParams,				pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,		bool,	"Load method. Parameters: First 'bool' parameter determines whether or not to enforce 8 bit (may result in a visible quality loss).",			"")
		pl_method_2(LoadDirectory,			pl_ret_type(bool),	PLVolume::Volume&,			PLCore::Directory&,			"Load directory method, by default 8 bit is enforced",																							"")
		pl_method_3(LoadDirectoryParams,	pl_ret_type(bool),	PLVolume::Volume&,			PLCore::Directory&,	bool,	"Load directory method. Parameters: First 'bool' parameter determines whether or not to enforce 8 bit (may result in a visible quality loss).",	"")
		pl_method_2(Save,					pl_ret_type(bool),	const PLVolume::Volume&,	PLCore::File&,				"Save method",																																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLVolume::Volume &cVolume, PLCore::File &cFile);
		bool LoadParams(PLVolume::Volume &cVolume, PLCore::File &cFile, bool bForce8Bit);
		bool LoadDirectory(PLVolume::Volume &cVolume, PLCore::Directory &cDirectory);
		bool LoadDirectoryParams(PLVolume::Volume &cVolume, PLCore::Directory &cDirectory, bool bForce8Bit);
		bool Save(const PLVolume::Volume &cVolume, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		VolumeLoaderDCM_GDCM();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VolumeLoaderDCM_GDCM();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderDICOM_GDCM


#endif // __PLLOADERDCM_GDCM_H__
