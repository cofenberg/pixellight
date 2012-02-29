/*********************************************************\
 *  File: SceneCreator.h                                 *
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


#ifndef __PLENGINE_SCENECREATOR_H__
#define __PLENGINE_SCENECREATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SNCamera;
	class SceneNode;
	class SceneContainer;
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
*    Abstract scene creator base class
*/
class SceneCreator : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SceneCreator, "PLEngine", PLCore::Object, "Abstract scene creator base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Configures a generic scene
		*
		*  @param[in] cSceneContainer
		*    The scene container to add the new scene nodes to (not cleared before filled)
		*  @param[in] pPrimarySceneNode
		*    Primary scene node, for example representing the loaded mesh or a box with the loaded material etc., can be a null pointer
		*
		*  @return
		*    The preferred camera scene node, can be a null pointer
		*
		*  @note
		*    - Adds a directional light source scene node named "Light"
		*    - Adds a free camera scene node named "FreeCamera"
		*    - If primary scene node given, adds an orbiter camera scene node named "OrbiterCamera"
		*    - Makes the orbiting camera to the preferred camera scene node, if there's no orbiting camera then the free camera will be used instead
		*/
		static PL_API PLScene::SNCamera *ConfigureGenericScene(PLScene::SceneContainer &cSceneContainer, PLScene::SceneNode *pPrimarySceneNode);

		/**
		*  @brief
		*    Configures a scene
		*
		*  @param[in] cSceneContainer
		*    The scene container to add the new scene nodes to (not cleared before filled)
		*  @param[in] sClass
		*    Name of the scene creator class to use for configuring the scene
		*  @param[in] sParameters
		*    Optional parameter string
		*
		*  @return
		*    The preferred camera scene node, can be a null pointer
		*/
		static PL_API PLScene::SNCamera *ConfigureScene(PLScene::SceneContainer &cSceneContainer, const PLCore::String &sClass, const PLCore::String &sParameters = "");


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API SceneCreator();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SceneCreator();


	//[-------------------------------------------------------]
	//[ Public virtual SceneCreator functions                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates the content of a scene container
		*
		*  @param[in] cSceneContainer
		*    Scene container to manipulate (not cleared before filled)
		*
		*  @return
		*    The preferred camera scene node, can be a null pointer
		*/
		PL_API virtual PLScene::SNCamera *Create(PLScene::SceneContainer &cSceneContainer) const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENECREATOR_H__
