/*********************************************************\
 *  File: PhysicsCharacterController.h                   *
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


#ifndef __PLENGINE_CONTROLLER_PHYSICSCHARACTERCONTROLLER_H__
#define __PLENGINE_CONTROLLER_PHYSICSCHARACTERCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Axis.h>
#include <PLInput/Input/Controls/Button.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics character input controller
*
*  @note
*    - Primary intended for rapid prototyping
*/
class PhysicsCharacterController : public PLInput::Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, PhysicsCharacterController, "PLEngine", PLInput::Controller, "Physics character input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis		TransX;			/**< X translation axis: Strafe left/right (+/-) */
		PLInput::Axis		TransY;			/**< Y translation axis: Move up/down (+/-) */
		PLInput::Axis		TransZ;			/**< Z translation axis: Move forwards/backwards (+/-) */
		PLInput::Axis		RotY;			/**< Y rotation axis: Yaw (also called 'heading') change is turning to the left or right */
		PLInput::Button		Forward;		/**< Move forwards */
		PLInput::Button		Backward;		/**< Move backwards */
		PLInput::Button		Left;			/**< Move (rotate) left */
		PLInput::Button		Right;			/**< Move (rotate) right */
		PLInput::Button		StrafeLeft;		/**< Strafe left */
		PLInput::Button		StrafeRight;	/**< Strafe right */
		PLInput::Button		Up;				/**< Move up */
		PLInput::Button		Down;			/**< Move down */
		PLInput::Button		Run;			/**< Keep pressed to run */
		PLInput::Button		Crouch;			/**< Keep pressed to crouch */
		PLInput::Button		Jump;			/**< Jump */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PL_API PhysicsCharacterController();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~PhysicsCharacterController();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CONTROLLER_PHYSICSCHARACTERCONTROLLER_H__
