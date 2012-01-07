/*********************************************************\
 *  File: SceneCreatorLoadableTypeMesh.h                 *
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


#ifndef __PLENGINE_SCENECREATOR_LOADABLETYPE_MESH_H__
#define __PLENGINE_SCENECREATOR_LOADABLETYPE_MESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/SceneCreator/SceneCreatorLoadableType.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loadable type scene creator
*/
class SceneCreatorLoadableTypeMesh : public SceneCreatorLoadableType {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SceneCreatorLoadableTypeMesh, "PLEngine", PLEngine::SceneCreatorLoadableType, "Mesh loadable type scene creator")
		// Properties
		pl_properties
			pl_property("Type",	"Mesh")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API SceneCreatorLoadableTypeMesh();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SceneCreatorLoadableTypeMesh();


	//[-------------------------------------------------------]
	//[ Public virtual SceneCreator functions                 ]
	//[-------------------------------------------------------]
	public:
		PL_API virtual PLScene::SNCamera *Create(PLScene::SceneContainer &cSceneContainer) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENECREATOR_LOADABLETYPE_MESH_H__
