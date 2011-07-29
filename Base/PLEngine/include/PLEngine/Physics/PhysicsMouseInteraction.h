/*********************************************************\
 *  File: PhysicsMouseInteraction.h                      *
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


#ifndef __PLENGINE_PHYSICS_PHYSICSMOUSEINTERACTION_H__
#define __PLENGINE_PHYSICS_PHYSICSMOUSEINTERACTION_H__
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
*    Mouse physics interaction input controller
*
*  @note
*    - Primary intended for fast prototyping
*/
class PhysicsMouseInteraction : public PLInput::Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, PhysicsMouseInteraction, "PLEngine", PLInput::Controller, "Mouse physics interaction input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Button	Pickup;			/**< Keep pressed to pickup */
		PLInput::Button	Throw;			/**< Throw the picked object */
		PLInput::Button	IncreaseForce;	/**< Keep pressed to increase the force applied to the picked object */
		PLInput::Button	DecreaseForce;	/**< Keep pressed to decrease the force applied to the picked object */
		PLInput::Axis	PushPull;		/**< Used to push/pull the picked object */
		PLInput::Axis	MouseX;			/**< X-position of the mouse */
		PLInput::Axis	MouseY;			/**< Y-position of the mouse */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PL_API PhysicsMouseInteraction();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~PhysicsMouseInteraction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_PHYSICS_PHYSICSMOUSEINTERACTION_H__
