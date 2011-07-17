/*********************************************************\
 *  File: GunController.h                                *
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


#ifndef __PLSAMPLE_67_GUNCONTROLLER_H__
#define __PLSAMPLE_67_GUNCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Button.h>
#include <PLInput/Input/Controls/Axis.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gun input controller
*/
class GunController : public PLInput::Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, GunController, "", PLInput::Controller, "Demo2DGame gun input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis	X;			/**< X rotation axis */
		PLInput::Button	Left;		/**< Move (rotate) left */
		PLInput::Button	Right;		/**< Move (rotate) right */
		PLInput::Button	Fire;		/**< Fire gun */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		GunController();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GunController();


};


#endif // __PLSAMPLE_67_GUNCONTROLLER_H__
