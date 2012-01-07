/*********************************************************\
 *  File: SceneCreatorLoadableType.h                     *
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


#ifndef __PLENGINE_SCENECREATOR_LOADABLETYPE_H__
#define __PLENGINE_SCENECREATOR_LOADABLETYPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/SceneCreator/SceneCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract loadable type scene creator base class
*
*  @remarks
*    There are situations when someone wants to, for example, see an image or an mesh without writing
*    a lot of source code. Also, knowing all possible loadable types when writing the application may
*    not be possible due to dynamic plugins. A loadable type scene creator can be used to create a ready
*    to-be-used scene by just providing the loadable type and some parameters like e.g. the filename of
*    the resource to view.
*
*    Each loader should have the following properties:
*    - "Type": Loadable type ("Image", "Mesh" and so on)
*/
class SceneCreatorLoadableType : public SceneCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SceneCreatorLoadableType, "PLEngine", PLEngine::SceneCreator, "Abstract loadable type scene creator base class")
		// Properties
		pl_properties
			pl_property("Type",	"Unknown")
		pl_properties_end
		// Attributes
		pl_attribute(Filename,	PLCore::String,	"",	ReadWrite,	DirectValue,	"Resource filename",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Configures a scene by using a given loadable type in order to determine the scene creator to use
		*
		*  @param[in] cSceneContainer
		*    The scene container to add the new scene nodes to (not cleared before filled)
		*  @param[in] sType
		*    Loadable type ("Image", "Mesh" and so on)
		*  @param[in] sFilename
		*    Resource filename
		*  @param[in] sParameters
		*    Optional parameter string (without resource filename)
		*
		*  @return
		*    The preferred camera scene node, can be a null pointer
		*/
		static PL_API PLScene::SNCamera *ConfigureSceneByLoadableType(PLScene::SceneContainer &cSceneContainer, const PLCore::String &sType, const PLCore::String &sFilename, const PLCore::String &sParameters = "");

		/**
		*  @brief
		*    Returns a list of loadable types were it's possible to use a scene creator in order to configure a scene
		*
		*  @param[out] lstLoadableTypes
		*    Receives the loadable types ("Image", "Mesh" and so on, not cleared before filled)
		*/
		static PL_API void GetLoadableTypes(PLCore::Array<PLCore::String> &lstLoadableTypes);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API SceneCreatorLoadableType();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SceneCreatorLoadableType();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENECREATOR_LOADABLETYPE_H__
