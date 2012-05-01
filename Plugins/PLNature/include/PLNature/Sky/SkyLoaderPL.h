/*********************************************************\
 *  File: SkyLoaderPL.h                                  *
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


#ifndef __PLNATURE_SCENENODE_SKYLOADER_PL_H__
#define __PLNATURE_SCENENODE_SKYLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLNature/Sky/SkyLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLNature {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sky loader implementation for the PixelLight sky XML file format
*/
class SkyLoaderPL : public SkyLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLNATURE_RTTI_EXPORT, SkyLoaderPL, "PLNature", PLNature::SkyLoader, "Sky loader implementation for the PixelLight sky XML file format")
		// Properties
		pl_properties
			pl_property("Formats",	"sky,SKY")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	SNSky&,		PLCore::File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	SNSky&,		PLCore::File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLNATURE_API bool Load(SNSky &cSky, PLCore::File &cFile);
		PLNATURE_API bool Save(SNSky &cSky, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLNATURE_API SkyLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API virtual ~SkyLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cSky
		*    Sky to load into
		*  @param[in] cSkyElement
		*    Sky XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(SNSky &cSky, const PLCore::XmlElement &cSkyElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature


#endif // __PLNATURE_SCENENODE_SKYLOADER_PL_H__
