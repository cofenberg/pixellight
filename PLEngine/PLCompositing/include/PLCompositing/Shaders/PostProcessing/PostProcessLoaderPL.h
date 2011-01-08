/*********************************************************\
 *  File: PostProcessLoaderPL.h                          *
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


#ifndef __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSLOADER_PL_H__
#define __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/Shaders/PostProcessing/PostProcessLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Post process loader implementation for the PixelLight post process XML file format
*/
class PostProcessLoaderPL : public PostProcessLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, PostProcessLoaderPL, "PLCompositing", PLCompositing::PostProcessLoader, "Post process loader implementation for the PixelLight post process XML file format")
		pl_properties
			pl_property("Formats",	"pp,PP")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PostProcessManager&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, PostProcessManager&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API bool Load(PostProcessManager &cPostProcessManager, PLGeneral::File &cFile);
		PLCOM_API bool Save(PostProcessManager &cPostProcessManager, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API PostProcessLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~PostProcessLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cPostProcessManager
		*    Post process manager to load into
		*  @param[in] cPostProcessElement
		*    Post process XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(PostProcessManager &cPostProcessManager, const PLGeneral::XmlElement &cPostProcessElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSLOADER_PL_H__
