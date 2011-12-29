/*********************************************************\
 *  File: SNMEgoOrbitingController.h                     *
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


#ifndef __PLENGINE_CONTROLLER_SNMEGOORBITINGCONTROLLER_H__
#define __PLENGINE_CONTROLLER_SNMEGOORBITINGCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Controller/SNMOrbitingController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node modifier class rotating a scene node towards a target scene node using an input controller with 3D restriction
*
*  @remarks
*    When using the unchanged virtual standard controller:
*    Hold the left mouse button to rotate, the right mouse button to zoom and the middle mouse button to pan.
*
*  @note
*    - Primary intended for rapid prototyping
*    - Restricted 3D rotation via Euler angles
*    - The up-vector is automatically calculated by using the set scene node rotation quaternion
*/
class SNMEgoOrbitingController : public SNMOrbitingController {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNMEgoOrbitingController, "PLEngine", PLEngine::SNMOrbitingController, "Scene node modifier class rotating a scene node towards a target scene node using an input controller with 3D restriction")
		// Attributes
		pl_attribute(UpVector,		PLMath::Vector3,	PLMath::Vector3(0.0f, 1.0f, 0.0f),	ReadWrite,	DirectValue,	"Up vector",																											"")
		pl_attribute(RollFactor,	float,				0.25f,								ReadWrite,	DirectValue,	"Roll factor. If there's an absolute z-axis (e.g. when using a 3D mouse), apply roll -> looks & feels more natural.",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_0(OnRotation,	"Called when the scene node rotation changed",	"")
	pl_class_end


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
		PL_API SNMEgoOrbitingController(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNMEgoOrbitingController();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Protected virtual SNMEgoOrbitingController functions  ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnUpdate() override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node rotation changed
		*/
		void OnRotation();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3	m_vUpVector;	/**< Up vector */
		float			m_fPitch;		/**< X rotation axis: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa) - in degree [-89.9, 89.9] */
		float			m_fYaw;			/**< Y rotation axis: Yaw (also called 'heading') change is turning to the left or right - in degree [0, 360] */
		bool			m_bListen;		/**< Listen to rotation signals? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CONTROLLER_SNMEGOORBITINGCONTROLLER_H__