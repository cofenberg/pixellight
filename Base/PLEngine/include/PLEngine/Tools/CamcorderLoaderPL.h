/*********************************************************\
 *  File: CamcorderLoaderPL.h                            *
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


#ifndef __PLENGINE_CAMCORDERLOADER_PL_H__
#define __PLENGINE_CAMCORDERLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Tools/CamcorderLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class XmlElement;
}
namespace PLEngine {
	class Camcorder;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Camcorder loader implementation for the PixelLight camcorder XML file format
*/
class CamcorderLoaderPL : public CamcorderLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, CamcorderLoaderPL, "PLEngine", PLEngine::CamcorderLoader, "Camcorder loader implementation for the PixelLight camcorder XML file format")
		// Properties
		pl_properties
			pl_property("Formats",	"cam,CAM")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	Camcorder&,	PLCore::File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	Camcorder&,	PLCore::File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PL_API bool Load(Camcorder &cCamcorder, PLCore::File &cFile);
		PL_API bool Save(Camcorder &cCamcorder, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API CamcorderLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~CamcorderLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cCamcorder
		*    Camcorder to load into
		*  @param[in] cCamcorderElement
		*    Camcorder XML element to read the data from
		*  @param[in] cFile
		*    File to load from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(Camcorder &cCamcorder, const PLCore::XmlElement &cCamcorderElement, PLCore::File &cFile) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CAMCORDERLOADER_PL_H__
