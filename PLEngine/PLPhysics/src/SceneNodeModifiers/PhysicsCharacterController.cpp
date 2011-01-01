/*********************************************************\
 *  File: PhysicsCharacterController.cpp                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/SceneNodeModifiers/PhysicsCharacterController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLInput;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PhysicsCharacterController)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PhysicsCharacterController::PhysicsCharacterController() : Controller(ControllerVirtual, "PhysicsCharacterController", "Physics character input controller"),
	TransX		(this, "TransX",		"X translation axis: Strafe left/right (+/-)"),
	TransY		(this, "TransY",		"Y translation axis: Move up/down (+/-)"),
	TransZ		(this, "TransZ",		"Z translation axis: Move forwards/backwards (+/-)"),
	RotY		(this, "RotY",			"Y rotation axis: Yaw (also called 'heading') change is turning to the left or right"),
	Forward		(this, "Forward",		"Move forwards",			0x00),
	Backward	(this, "Backward",		"Move backwards",			0x00),
	Left		(this, "Left",			"Move (rotate) left",		0x00),
	Right		(this, "Right",			"Move (rotate) right",		0x00),
	StrafeLeft	(this, "StrafeLeft",	"Strafe left",				0x00),
	StrafeRight	(this, "StrafeRight",	"Strafe right",				0x00),
	Up			(this, "Up",			"Move up",					0x00),
	Down		(this, "Down",			"Move down",				0x00),
	Run			(this, "Run",			"Keep pressed to run",		0x00),
	Crouch		(this, "Crouch",		"Keep pressed to crouch",	0x00),
	Jump		(this, "Jump",			"Jump",						0x00)
{
}

/**
*  @brief
*    Destructor
*/
PhysicsCharacterController::~PhysicsCharacterController()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
