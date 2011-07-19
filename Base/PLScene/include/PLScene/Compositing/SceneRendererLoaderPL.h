/*********************************************************\
 *  File: SceneRendererLoaderPL.h                        *
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


#ifndef __PLSCENE_COMPOSITING_SCENERENDERERLOADER_PL_H__
#define __PLSCENE_COMPOSITING_SCENERENDERERLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Compositing/SceneRendererLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer loader implementation for the PixelLight scene renderer XML file format
*
*  @note
*    - If the save function recives a boolean 'NoDefault'-parameter with 'true', (default setting)
*      variables with default values are not saved
*/
class SceneRendererLoaderPL : public SceneRendererLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneRendererLoaderPL, "PLScene", PLScene::SceneRendererLoader, "Scene renderer loader implementation for the PixelLight scene renderer XML file format")
		// Properties
		pl_properties
			pl_property("Formats",	"sr,SR")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	SceneRenderer&,	PLCore::File&,			"Load method",												"")
		pl_method_2(Save,		pl_ret_type(bool),	SceneRenderer&,	PLCore::File&,			"Save method. Default values are not written.",				"")
		pl_method_3(SaveParams, pl_ret_type(bool),	SceneRenderer&,	PLCore::File&,	bool,	"Save method. Parameters: No default values as 'bool'.",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLS_API bool Load(SceneRenderer &cSceneRenderer, PLCore::File &cFile);
		PLS_API bool Save(SceneRenderer &cSceneRenderer, PLCore::File &cFile);
		PLS_API bool SaveParams(SceneRenderer &cSceneRenderer, PLCore::File &cFile, bool bNoDefault);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SceneRendererLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneRendererLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cSceneRenderer
		*    Scene renderer to load into
		*  @param[in] cSceneRendererElement
		*    Scene senderer XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(SceneRenderer &cSceneRenderer, const PLCore::XmlElement &cSceneRendererElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_SCENERENDERERLOADER_PL_H__
