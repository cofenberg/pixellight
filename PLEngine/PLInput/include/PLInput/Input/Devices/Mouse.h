/*********************************************************\
 *  File: Mouse.h                                        *
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


#ifndef __PLINPUT_MOUSE_H__
#define __PLINPUT_MOUSE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Controls/Button.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mouse input device
*
*  @remarks
*    This class supports the following device backend types:
*    - UpdateDevice
*/
class Mouse : public Device {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, Mouse, "PLInput", PLInput::Device, "Mouse input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis	X;			/**< X axis */
		PLInput::Axis	Y;			/**< Y axis */
		PLInput::Axis	Wheel;		/**< Mouse wheel */
		PLInput::Button	Left;		/**< Left mouse button  */
		PLInput::Button	Right;		/**< Right mouse button  */
		PLInput::Button	Middle;		/**< Middle mouse button  */
		PLInput::Button	Button4;	/**< Mouse button #4 */
		PLInput::Button	Button5;	/**< Mouse button #5 */
		PLInput::Button	Button6;	/**< Mouse button #6 */
		PLInput::Button	Button7;	/**< Mouse button #7 */
		PLInput::Button	Button8;	/**< Mouse button #8 */
		PLInput::Button	Button9;	/**< Mouse button #9 */
		PLInput::Button	Button10;	/**< Mouse button #10 */
		PLInput::Button	Button11;	/**< Mouse button #11 */
		PLInput::Button	Button12;	/**< Mouse button #12 */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Device name
		*  @param[in] pImpl
		*    System specific device implementation, can, but shouldn't be NULL
		*/
		PLINPUT_API Mouse(const PLGeneral::String &sName, DeviceImpl *pImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Mouse();


	//[-------------------------------------------------------]
	//[ Public virtual Controller functions                   ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void Update();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
}


#endif // __PLINPUT_MOUSE_H__
