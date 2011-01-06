/*********************************************************\
 *  File: SceneLoaderProc.h                              *
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


#ifndef __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_PROC_H__
#define __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_PROC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Plane.h>
#include <PLScene/Scene/SceneLoader/SceneLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}
namespace PLScene {
	class SCCell;
	class SNPointLight;
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
*    Scene loader for the Doom 3 'proc' format
*
*  @remarks
*    This is the Doom 3 map format. It consits of multiple 'models' whereby each one is a cell with
*    multiple 'surface' (mesh) nodes within it. Further there are portals connecting this cells.
*    This loader can also take the 'map' file of the 'proc' file into account to load in for instance
*    lights.
*/
class SceneLoaderProc : public PLScene::SceneLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SceneLoaderProc, "PLDefaultFileFormats", PLScene::SceneLoader, "Scene loader for the Doom 3 'proc' format")
		pl_properties
			pl_property("Formats",	"proc,PROC")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(SwapYZ,	bool,	true,	ReadWrite,	DirectValue,	"Swap y/z axis?",							"")
		pl_attribute(Scale,		float,	0.01f,	ReadWrite,	DirectValue,	"Scale",									"")
		pl_attribute(LoadMap,	bool,	true,	ReadWrite,	DirectValue,	"Load the 'map' file of this 'proc' file?",	"")
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
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    BSP node
		*/
		class Node {
		public:
			PLMath::Plane cPlane;
			int			  nPosChild, nNegChild;
			bool operator ==(const Node &cOther) const
			{
				// We do not need an implementation in here...
				return false;
			}
		};


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal per instance data
		*/
		struct SInstance {
			PLGeneral::uint32 nTotalNumOfCells;
			PLGeneral::uint32 nTotalNumOfMeshes;
			PLGeneral::uint32 nTotalNumOfVertices;
			PLGeneral::uint32 nTotalNumOfIndices;
			PLGeneral::uint32 nTotalNumOfPortals;
			PLGeneral::uint32 nTotalNumOfLights;

			PLGeneral::Array<PLScene::SCCell*>	lstCells;
			PLGeneral::Array<Node>				lstNodes;
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SceneLoaderProc();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SceneLoaderProc();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Load the 'map' file of this 'proc' file
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cContainer
		*    Scene container to use
		*  @param[in] sFilename
		*    'map' filename
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The 'map' file contains entities like lights which populate the scene. Brushs
		*    are ignored.
		*/
		bool LoadMapFile(SInstance &sInstance, PLScene::SceneContainer &cContainer, const PLGeneral::String &sFilename) const;

		/**
		*  @brief
		*    Returns the cell index
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] sName
		*    Name of the cell
		*
		*  @return
		*    Cell index, < 0 on error
		*/
		int GetCellIndexByName(SInstance &sInstance, const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Returns the cell the given position is in
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] vPos
		*    Position to use
		*
		*  @return
		*    The cell the given position is in, 0 on error (no cell found)
		*/
		int GetCell(SInstance &sInstance, const PLMath::Vector3 &vPos) const;

		/**
		*  @brief
		*    Pushs down a light to a cell
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cLight
		*    Light to push down
		*  @param[in] pNode
		*    Current node, can be a null pointer
		*/
		void PushLight(SInstance &sInstance, PLScene::SNPointLight &cLight, Node *pNode = nullptr) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DOOM3_SCENELOADER_PROC_H__
