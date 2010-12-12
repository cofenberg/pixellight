/*********************************************************\
 *  File: TerrainLoaderPL.h                              *
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


#ifndef __PLSCENE_SCENENODE_TERRAINLOADER_PL_H__
#define __PLSCENE_SCENENODE_TERRAINLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodes/Terrain/TerrainLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Terrain loader implementation for the PixelLight terrain XML file format
*/
class TerrainLoaderPL : public TerrainLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, TerrainLoaderPL, "PLScene", PLScene::TerrainLoader, "Terrain loader implementation for the PixelLight terrain XML file format")
		pl_properties
			pl_property("Formats",	"terrain,TERRAIN")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, SNTerrain&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, SNTerrain&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLS_API bool Load(SNTerrain &cSNTerrain, PLGeneral::File &cFile);
		PLS_API bool Save(SNTerrain &cSNTerrain, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default Constructor
		*/
		PLS_API TerrainLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~TerrainLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cSNTerrain
		*    Terrain to load into
		*  @param[in] cTerrainElement
		*    Terrain XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(SNTerrain &cSNTerrain, const PLGeneral::XmlElement &cTerrainElement) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_TERRAINLOADER_PL_H__
