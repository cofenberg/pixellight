/*********************************************************\
 *  File: LookController.cpp                             *
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
#include "PLScene/Scene/SceneNodeModifiers/LookController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(LookController)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LookController::LookController() : Controller(ControllerVirtual, "LookController", "Look input controller"),
	RotX  (this, "RotX",	"X rotation axis: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)"),
	RotY  (this, "RotY",	"Y rotation axis: Yaw (also called 'heading') change is turning to the left or right"),
	RotZ  (this, "RotZ",	"Z rotation axis: Roll (also called 'attitude') change is moving one wingtip up and the other down"),
	Rotate(this, "Rotate",	"Keep pressed to rotate (optional)")
{
}

/**
*  @brief
*    Destructor
*/
LookController::~LookController()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
