/*********************************************************\
 *  File: VirtualController.h                            *
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


#ifndef __PLINPUT_VIRTUALCONTROLLER_H__
#define __PLINPUT_VIRTUALCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Controller.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual input controller
*
*  @remarks
*    A virtual input controller is a controller that is used to map real input devices to virtual controls.
*    Usually, you have one virtual input controller for your application, or in rare occasions more than one,
*    e.g. one for every window or player. The virtual controller connects itself to the physical input devices,
*    a virtual function can be used to alter this behaviour in derived classes. The virtual controller should
*    then be connected to the controllers of input-enabled objects, such as scene nodes or modifiers.
*/
class VirtualController : public Controller {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, VirtualController, "PLInput", PLInput::Controller, "Virtual input controller base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Controller name
		*  @param[in] sDescription
		*    Controller description
		*/
		PLINPUT_API VirtualController(const PLGeneral::String &sName, const PLGeneral::String &sDescription);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~VirtualController();


	//[-------------------------------------------------------]
	//[ Public virtual VirtualController functions            ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Connect virtual controller to physical devices
		*
		*  @remarks
		*    This function shall enumerate the available devices and connect
		*    itself to the proper controls of those input devices. Override
		*    this function in derived classes to alter it's behaviour or to
		*    support your own type of virtual controllers
		*/
		PLINPUT_API virtual void ConnectToDevices();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_VIRTUALCONTROLLER_H__
