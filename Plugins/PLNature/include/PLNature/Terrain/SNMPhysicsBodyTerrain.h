/*********************************************************\
 *  File: SNMPhysicsBodyTerrain.h                        *
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


#ifndef __PLNATURE_SCENENODEMODIFIERS_BODYTERRAIN_H__
#define __PLNATURE_SCENENODEMODIFIERS_BODYTERRAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h>
#include "PLNature/PLNature.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLNature {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics terrain body scene node modifier
*/
class SNMPhysicsBodyTerrain : public PLPhysics::SNMPhysicsBody {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLNATURE_RTTI_EXPORT, SNMPhysicsBodyTerrain, "PLNature", PLPhysics::SNMPhysicsBody, "Physics terrain body scene node modifier")
		// Properties
		pl_properties
			pl_property("SceneNodeClass",	"PLNature::SNTerrain")
		pl_properties_end
		// Attributes
		pl_attribute(Scale,	PLMath::Vector3,	PLMath::Vector3::One,	ReadWrite,	GetSet,	"Height field scale",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLNATURE_API const PLMath::Vector3 &GetScale() const;
		PLNATURE_API void SetScale(const PLMath::Vector3 &vValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLNATURE_API SNMPhysicsBodyTerrain(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API virtual ~SNMPhysicsBodyTerrain();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vScale;	/**< Height field scale */


	//[-------------------------------------------------------]
	//[ Private virtual PLPhysics::SNMPhysicsBody functions   ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsBody() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLNATURE_SCENENODEMODIFIERS_BODYTERRAIN_H__
