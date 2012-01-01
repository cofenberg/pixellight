/*********************************************************\
 *  File: OrbitingController.h                           *
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


#ifndef __PLENGINE_CONTROLLER_ORBITINGCONTROLLER_H__
#define __PLENGINE_CONTROLLER_ORBITINGCONTROLLER_H__
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
*    Orbiting input controller
*
*  @note
*    - Primary intended for rapid prototyping
*/
class OrbitingController : public PLInput::Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, OrbitingController, "PLEngine", PLInput::Controller, "Orbiting input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis	RotX;		/**< X rotation axis: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa) */
		PLInput::Axis	RotY;		/**< Y rotation axis: Yaw (also called 'heading') change is turning to the left or right */
		PLInput::Axis	RotZ;		/**< Z rotation axis: Roll (also called 'attitude') change is moving one wingtip up and the other down */
		PLInput::Axis	PanX;		/**< X pan translation axis: Strafe left/right (+/-) */
		PLInput::Axis	PanY;		/**< Y pan translation axis: Move up/down (+/-) */
		PLInput::Axis	PanZ;		/**< Z pan translation axis: Move forwards/backwards (+/-) */
		PLInput::Button	Rotate;		/**< Keep pressed to rotate */
		PLInput::Button	Pan;		/**< Keep pressed to pan */
		PLInput::Button	Zoom;		/**< Keep pressed to zoom */
		PLInput::Axis	ZoomAxis;	/**< Zoom axis to zoom in or out (+/-) */
		PLInput::Button	Run;		/**< Keep pressed to run */
		PLInput::Button	Crouch;		/**< Keep pressed to crouch */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PL_API OrbitingController();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~OrbitingController();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CONTROLLER_ORBITINGCONTROLLER_H__
