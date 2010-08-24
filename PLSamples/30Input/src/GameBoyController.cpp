/*********************************************************\
 *  File: GameBoyController.cpp                          *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "GameBoyController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLInput;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(GameBoyController)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GameBoyController::GameBoyController() : Controller(ControllerVirtual, "GameBoy", "Sample GameBoy input controller"),
	X	  (this, "X",		"Axis 'X'"),
	Y	  (this, "Y",		"Axis 'Y'"),
	A	  (this, "A",		"Button 'A'"),
	B	  (this, "B",		"Button 'B'"),
	Start (this, "Start",	"Button 'Start'"),
	Select(this, "Select",	"Button 'Select'")
{
}

/**
*  @brief
*    Destructor
*/
GameBoyController::~GameBoyController()
{
}
