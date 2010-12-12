/*********************************************************\
 *  File: SceneLoaderPL.h                                *
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


#ifndef __PLSCENE_SCENELOADER_PL_H__
#define __PLSCENE_SCENELOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneLoader/SceneLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}
namespace PLScene {
	class SceneNode;
	class SceneNodeModifier;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene loader implementation for the PixelLight scene XML file format
*
*  @note
*    - If the save function recives a boolean 'NoDefault'-parameter with 'true', (default setting)
*      variables with default values are not saved
*/
class SceneLoaderPL : public SceneLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneLoaderPL, "PLScene", PLScene::SceneLoader, "Scene loader implementation for the PixelLight scene XML file format")
		pl_properties
			pl_property("Formats",	"scene,SCENE")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, SceneContainer&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, SceneContainer&, PLGeneral::File&, "Save method", "")
		pl_method_3(SaveParams, bool, SceneContainer&, PLGeneral::File&, bool, "Save method. Parameters: No default values as 'bool'.", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLS_API bool Load(SceneContainer &cContainer, PLGeneral::File &cFile);
		PLS_API bool Save(SceneContainer &cContainer, PLGeneral::File &cFile);
		PLS_API bool SaveParams(SceneContainer &cContainer, PLGeneral::File &cFile, bool bNoDefault);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal per instance data
		*/
		struct SInstance {
			SceneContainer *pContainer;					/**< Scene root container (the one we currently 'load in', always valid) */
			// Statistics
			PLGeneral::uint32 nTotalNumOfContainers;	/**< Total number of containers within the scene (without the root container itself) */
			PLGeneral::uint32 nTotalNumOfNodes;			/**< Total number of nodes (without containers) within the scene */
			PLGeneral::uint32 nTotalNumOfModifiers;		/**< Total number of modifiers within the scene */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SceneLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cContainer
		*    Scene container to load into
		*  @param[in] cSceneElement
		*    Scene XML element to read the data from
		*  @param[in] cFile
		*    File to load from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(SceneContainer &cContainer, const PLGeneral::XmlElement &cSceneElement, PLGeneral::File &cFile) const;

		/**
		*  @brief
		*    Recursive part of the load function
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cContainer
		*    Scene container object
		*  @param[in] cParent
		*    Parent XML element
		*  @param[in] nFirstSceneRow
		*    First scene Row
		*  @param[in] nLastSceneRow
		*    Last scene Row
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadRec(SInstance &sInstance, SceneContainer &cContainer, const PLGeneral::XmlElement &cParent, PLGeneral::uint32 nFirstSceneRow, PLGeneral::uint32 nLastSceneRow) const;

		/**
		*  @brief
		*    Loads a scene node and returns it
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cContainer
		*    Scene container object
		*  @param[in] cNode
		*    XML node
		*  @param[in] bContainer
		*    Is this a scene container?
		*
		*  @return
		*    The created scene node, NULL on error (maybe XML element has no class attribute?)
		*/
		SceneNode *LoadNode(SInstance &sInstance, SceneContainer &cContainer, const PLGeneral::XmlElement &cNode, bool bContainer) const;

		/**
		*  @brief
		*    Loads a scene node modifier and returns it
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cNode
		*    XML node
		*  @param[in] cSceneNode
		*    Scene node where to add the modifier
		*
		*  @return
		*    The created scene node modifier, NULL on error (maybe XML element has no class attribute?)
		*/
		SceneNodeModifier *LoadModifier(SInstance &sInstance, const PLGeneral::XmlElement &cNode, SceneNode &cSceneNode) const;

		/**
		*  @brief
		*    Recursive part of the save function
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cContainer
		*    Scene container object
		*  @param[in] cParent
		*    Parent XML element
		*  @param[in] bNoDefault
		*    If 'true', variables with default values will be ignored
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool SaveRec(SInstance &sInstance, const SceneContainer &cContainer, PLGeneral::XmlElement &cParent, bool bNoDefault = true) const;

		/**
		*  @brief
		*    Modifiers part of the save function
		*
		*  @param[in] sInstance
		*    Per instance data
		*  @param[in] cParent
		*    Parent XML element
		*  @param[in] cSceneNode
		*    Node to save the modifiers from
		*  @param[in] bNoDefault
		*    If 'true', variables with default values will be ignored
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool SaveModifiers(SInstance &sInstance, PLGeneral::XmlElement &cParent, const SceneNode &cSceneNode, bool bNoDefault = true) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENELOADER_PL_H__
