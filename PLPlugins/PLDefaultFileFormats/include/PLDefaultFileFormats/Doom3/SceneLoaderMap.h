/*********************************************************\
 *  File: SceneLoaderMap.h                               *
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


#ifndef __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_MAP_H__
#define __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_MAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneLoader/SceneLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}
namespace PLScene {
	class SceneContainer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene loader for the standard 'map' format
*
*  @remarks
*    The 'map' is used by multiple games such as Quake, Half-Life, Doom 3 etc. and there are
*    many map editors like Quark (http://quark.planetquake.gamespy.com/) supporting this format.
*    Such a 'map' consists of multiple 'entities'. An 'entity' can be a 'brush' defining map geometry
*    or lights, monsters etc. The brushs are triangulated receive meshes.
*/
class SceneLoaderMap : public PLScene::SceneLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SceneLoaderMap, "PLDefaultFileFormats", PLScene::SceneLoader, "Scene loader for the standard 'map' format")
		pl_properties
			pl_property("Formats",	"map,MAP")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLScene::SceneContainer&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, PLScene::SceneContainer&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLScene::SceneContainer &cContainer, PLGeneral::File &cFile);
		bool Save(PLScene::SceneContainer &cContainer, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SceneLoaderMap();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SceneLoaderMap();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_MAP_H__
