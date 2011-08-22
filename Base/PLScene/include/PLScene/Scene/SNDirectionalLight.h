/*********************************************************\
 *  File: SNDirectionalLight.h                           *
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


#ifndef __PLSCENE_DIRECTIONALLIGHT_H__
#define __PLSCENE_DIRECTIONALLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SNLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Directional light scene node representing parallel light beams coming from an infinite distance at a certain direction
*/
class SNDirectionalLight : public SNLight {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNDirectionalLight, "PLScene", PLScene::SNLight, "Directional light scene node representing parallel light beams coming from an infinite distance at a certain direction")
		// Attributes
		pl_attribute(AABBMin,	PLMath::Vector3,	PLMath::Vector3(-10000.0f, -10000.0f, -10000.0f),	ReadWrite,	GetSet,	"Minimum position of the 'scene node space' axis aligned bounding box",	"")
		pl_attribute(AABBMax,	PLMath::Vector3,	PLMath::Vector3( 10000.0f,  10000.0f,  10000.0f),	ReadWrite,	GetSet,	"Maximum position of the 'scene node space' axis aligned bounding box",	"")
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
		PLS_API SNDirectionalLight();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNDirectionalLight();


	//[-------------------------------------------------------]
	//[ Public virtual SNLight functions                      ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsRenderLight() const override;
		PLS_API virtual bool IsDirectionalLight() const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_DIRECTIONALLIGHT_H__
