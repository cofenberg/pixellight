/*********************************************************\
 *  File: SNFog.h                                        *
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


#ifndef __PLSCENE_FOG_H__
#define __PLSCENE_FOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract fog scene node base class
*/
class SNFog : public SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNFog, "PLScene", PLScene::SceneNode, "Abstract fog scene node base class")
		// Attributes
		pl_attribute(Color,	PLGraphics::Color3,	PLGraphics::Color3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Fog color (r/g/b)",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual SNFog functions                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether this scene node is a spherical fog (SNSphereFog) or not
		*
		*  @return
		*    'true' if this scene node is a spherical fog, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNSphereFog")
		*/
		PLS_API virtual bool IsSphereFog() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNFog();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNFog();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_FOG_H__
