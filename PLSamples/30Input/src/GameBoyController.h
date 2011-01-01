/*********************************************************\
 *  File: GameBoyController.h                            *
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


#ifndef __30INPUT_GAMEBOYCONTROLLER_H__
#define __30INPUT_GAMEBOYCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Controller.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GameBoy input controller (sample)
*/
class GameBoyController : public PLInput::Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(1, GameBoyController, "", PLInput::Controller, "Sample GameBoy input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis	X;			/**< Axis 'X' */
		PLInput::Axis	Y;			/**< Axis 'Y' */
		PLInput::Button	A;			/**< Button 'A' */
		PLInput::Button	B;			/**< Button 'B' */
		PLInput::Button	Start;		/**< Button 'Start' */
		PLInput::Button	Select;		/**< Button 'Stop' */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		GameBoyController();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GameBoyController();


};


#endif // __30INPUT_GAMEBOYCONTROLLER_H__
