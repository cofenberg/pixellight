/*********************************************************\
 *  File: SceneCreatorLoadableTypeVolume.h               *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
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
