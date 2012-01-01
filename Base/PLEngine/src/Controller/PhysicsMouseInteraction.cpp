/*********************************************************\
 *  File: PhysicsMouseInteraction.cpp                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Controller/PhysicsMouseInteraction.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLInput;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PhysicsMouseInteraction)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PhysicsMouseInteraction::PhysicsMouseInteraction() : Controller(ControllerVirtual, "PhysicsMouseInteraction", "Mouse physics interaction input controller"),
	Pickup			(this, "Pickup",		"Keep pressed to pickup",											0x00),
	Throw			(this, "Throw",			"Throw the picked object",											0x00),
	IncreaseForce	(this, "IncreaseForce",	"Keep pressed to increase the force applied to the picked object",	0x00),
	DecreaseForce	(this, "DecreaseForce",	"Keep pressed to decrease the force applied to the picked object",	0x00),
	PushPull		(this, "PushPull",		"Used to push/pull the picked object"),
	MouseX			(this, "MouseX",		"X-position of the mouse"),
	MouseY			(this, "MouseY",		"Y-position of the mouse")
{
}

/**
*  @brief
*    Destructor
*/
PhysicsMouseInteraction::~PhysicsMouseInteraction()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
