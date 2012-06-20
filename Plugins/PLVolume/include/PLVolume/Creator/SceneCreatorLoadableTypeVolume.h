/*********************************************************\
 *  File: SceneCreatorLoadableTypeVolume.h               *
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


#ifndef __PLVOLUME_SCENECREATOR_LOADABLETYPE_IMAGE_H__
#define __PLVOLUME_SCENECREATOR_LOADABLETYPE_IMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/SceneCreator/SceneCreatorLoadableType.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume loadable type scene creator
*/
class SceneCreatorLoadableTypeVolume : public PLEngine::SceneCreatorLoadableType {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, SceneCreatorLoadableTypeVolume, "PLVolume", PLEngine::SceneCreatorLoadableType, "Volume loadable type scene creator")
		// Properties
		pl_properties
			pl_property("Type",	"Volume")
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
		PLVOLUME_API SceneCreatorLoadableTypeVolume();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUME_API virtual ~SceneCreatorLoadableTypeVolume();


	//[-------------------------------------------------------]
	//[ Public virtual PLEngine::SceneCreator functions       ]
	//[-------------------------------------------------------]
	public:
		PLVOLUME_API virtual PLScene::SNCamera *Create(PLScene::SceneContainer &cSceneContainer) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_SCENECREATOR_LOADABLETYPE_IMAGE_H__
