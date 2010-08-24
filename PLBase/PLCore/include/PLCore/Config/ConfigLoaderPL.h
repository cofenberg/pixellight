/*********************************************************\
 *  File: ConfigLoaderPL.h                               *
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


#ifndef __PLCORE_CONFIGLOADER_PL_H__
#define __PLCORE_CONFIGLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Config/ConfigLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Config loader implementation for the PixelLight config XML file format
*/
class ConfigLoaderPL : public ConfigLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ConfigLoaderPL, "PLCore", PLCore::ConfigLoader, "Config loader implementation for the PixelLight config XML file format")
		pl_properties
			pl_property("Formats",	"cfg")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, Config&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, const Config&, PLGeneral::File&, "Save method. Saves all configuration groups and includes default values, too.", "")
		pl_method_4(SaveParams, bool, const Config&, PLGeneral::File&, PLGeneral::String, bool, "Save method. Parameters: Configuration group to save as 'String', no default values as 'bool'.", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API bool Load(Config &cConfig, PLGeneral::File &cFile);
		PLCORE_API bool Save(const Config &cConfig, PLGeneral::File &cFile);
		PLCORE_API bool SaveParams(const Config &cConfig, PLGeneral::File &cFile, PLGeneral::String sGroup, bool bNoDefault);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API ConfigLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ConfigLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cConfig
		*    Configuration to load into
		*  @param[in] cConfigElement
		*    Configuration XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(Config &cConfig, const PLGeneral::XmlElement &cConfigElement) const;

		/**
		*  @brief
		*    Save configuration group settings
		*
		*  @param[in] cConfigElement
		*    Configuration element to write in
		*  @param[in] cGroup
		*    Configuration group to save
		*  @param[in] bNoDefault
		*    If 'true', variables with default values will be ignored
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool SaveGroup(PLGeneral::XmlElement &cConfigElement, const ConfigGroup &cGroup, bool bNoDefault = false) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONFIGLOADER_PL_H__
