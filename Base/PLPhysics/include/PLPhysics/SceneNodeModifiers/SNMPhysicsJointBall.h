/*********************************************************\
 *  File: SNMPhysicsJointBall.h                          *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_JOINTBALL_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_JOINTBALL_H__
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
*    Physics ball and socket joint scene node modifier
*
*  @note
*    - All non-zero value for 'MaxConeAngle' are clamped between 5 degree and 175 degrees 
*    - Don't use 'NewtonBallSetConeLimits()' directly within your code, instead use the RTTI to set the variables
*      (... else this RTTI variables may have wrong values...)
*/
class SNMPhysicsJointBall : public SNMPhysicsJoint {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsJointBall, "PLPhysics", PLPhysics::SNMPhysicsJoint, "Physics ball and socket joint scene node modifier")
		// Attributes
		pl_attribute(PivotPoint,	PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Origin of the ball and socket in local space",																							"")
		pl_attribute(PinDir,		PLMath::Vector3,	PLMath::Vector3(0.0f, 1.0f, 0.0f),	ReadWrite,	GetSet,	"Vector defining the cone axis in scene container space if the 'LocalPinDirection'-flag is not set, else in local scene node space",	"")
		// [TODO] Implement me
		// DEFINE_VAR(PL_VAR_FLOAT,	m_fMaxConeAngle,	"MaxConeAngle",		"0.0",			"Max angle in degree the attached body is allow to swing relative to the pin axis, a value of zero will disable this limits",	"",	"")
		// DEFINE_VAR(PL_VAR_FLOAT,	m_fMaxTwistAngle,	"MaxTwistAngle",	"0.0",			"Max angle in degree the attached body is allow to twist relative to the pin axis, a value of zero will disable this limits",	"",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
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
		PLPHYSICS_API SNMPhysicsJointBall(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsJointBall();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vPivotPoint;	/**< Origin of the ball and socket in local space */
		PLMath::Vector3 m_vPinDir;		/**< Vector defining the cone axis in local space */
		// [TODO] Implement me
		// float			m_fMaxConeAngle;
		// float			m_fMaxTwistAngle;


	//[-------------------------------------------------------]
	//[ Private virtual SNMPhysicsJoint functions             ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsJoint() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_JOINTBALL_H__
