/*********************************************************\
 *  File: EffectLoaderPL.h                               *
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


#ifndef __PLRENDERER_EFFECTLOADER_PL_H__
#define __PLRENDERER_EFFECTLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Effect/EffectLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect loader implementation for the PixelLight effect XML file format
*/
class EffectLoaderPL : public EffectLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, EffectLoaderPL, "PLRenderer", PLRenderer::EffectLoader, "Effect loader implementation for the PixelLight effect XML file format")
		pl_properties
			pl_property("Formats",	"plfx,PLFX")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, Effect&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, const Effect&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API bool Load(Effect &cEffect, PLGeneral::File &cFile);
		PLRENDERER_API bool Save(const Effect &cEffect, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API EffectLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~EffectLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cFX
		*    Effect to load into
		*  @param[in] cFXElement
		*    Effect XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(Effect &cFX, const PLGeneral::XmlElement &cFXElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_EFFECTLOADER_PL_H__
