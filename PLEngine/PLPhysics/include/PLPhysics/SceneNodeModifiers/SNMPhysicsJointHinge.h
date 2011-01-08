/*********************************************************\
 *  File: SNMPhysicsJointHinge.h                         *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_JOINTHINGE_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_JOINTHINGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsJoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics hinge joint scene node modifier
*/
class SNMPhysicsJointHinge : public SNMPhysicsJoint {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsJointHinge, "PLPhysics", PLPhysics::SNMPhysicsJoint, "Physics hinge joint scene node modifier")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(PivotPoint,	PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Origin of the hinge in local space",				"")
		pl_attribute(PinDir,		PLMath::Vector3,	PLMath::Vector3(0.0f, 1.0f, 0.0f),	ReadWrite,	GetSet,	"The line of action of the hinge in local space",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API const PLMath::Vector3 &GetPivotPoint() const;
		PLPHYSICS_API void SetPivotPoint(const PLMath::Vector3 &vValue);
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir() const;
		PLPHYSICS_API void SetPinDir(const PLMath::Vector3 &vValue);


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
		PLPHYSICS_API SNMPhysicsJointHinge(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsJointHinge();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vPivotPoint;	/**< Origin of the hinge in local space */
		PLMath::Vector3 m_vPinDir;		/**< The line of action of the hinge in local space */


	//[-------------------------------------------------------]
	//[ Private virtual SNMPhysicsJoint functions             ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsJoint();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_JOINTHINGE_H__
