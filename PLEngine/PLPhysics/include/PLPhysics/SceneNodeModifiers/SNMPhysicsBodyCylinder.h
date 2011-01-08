/*********************************************************\
 *  File: SNMPhysicsBodyCylinder.h                       *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_BODYCYLINDER_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_BODYCYLINDER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics cylinder body scene node modifier
*/
class SNMPhysicsBodyCylinder : public SNMPhysicsBody {



	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsBodyCylinder, "PLPhysics", PLPhysics::SNMPhysicsBody, "Physics cylinder body scene node modifier")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(Radius,	float,	1.0f,	ReadWrite,	GetSet,	"Cylinder radius at the base",				"Min='0.0'")
		pl_attribute(Height,	float,	1.0f,	ReadWrite,	GetSet,	"Cylinder height along the x local axis",	"Min='0.0'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API float GetRadius() const;
		PLPHYSICS_API void SetRadius(float fValue);
		PLPHYSICS_API float GetHeight() const;
		PLPHYSICS_API void SetHeight(float fValue);


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
		PLPHYSICS_API SNMPhysicsBodyCylinder(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsBodyCylinder();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fRadius;	/**< Cylinder radius at the base */
		float m_fHeight;	/**< Cylinder height along the x local axis */


	//[-------------------------------------------------------]
	//[ Private virtual SNMPhysicsBody functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsBody();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_BODYCYLINDER_H__
