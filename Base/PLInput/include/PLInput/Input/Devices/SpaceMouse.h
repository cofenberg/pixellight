/*********************************************************\
 *  File: SpaceMouse.h                                   *
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


#ifndef __PLINPUT_SPACEMOUSE_H__
#define __PLINPUT_SPACEMOUSE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Devices/Device.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class HIDDevice;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    SpaceMouse input device
*
*  @remarks
*    This class supports the following device backend types:
*    - HIDDevice
*/
class SpaceMouse : public Device {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, SpaceMouse, "PLInput", PLInput::Device, "Joystick input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    SpaceMouse IDs
		*
		*  @remarks
		*    It is not recommended to use the ProductID, because it's different for each individual product (NOT future safe)
		*/
		enum EProductID {
			VendorID				 = 1133,	/**< '3DConnexion' */
			SpaceMousePlus_ProductID = 0xc603,	/**< 'SpaceMousePlus' */
			SpaceBall_ProductID		 = 0xc621,	/**< 'SpaceBall' */
			SpaceTraveler_ProductID	 = 0xc623,	/**< 'SpaceTraveler' */
			SpacePilot_ProductID	 = 0xc625,	/**< 'SpacePilot' */
			SpaceNavigator_ProductID = 0xc626,	/**< 'SpaceNavigator' */
			SpaceExplorer_ProductID	 = 0xc627	/**< 'SpaceExplorer' */
		};


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Axis	TransX;		/**< Absolute x translation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Axis	TransY;		/**< Absolute y translation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Axis	TransZ;		/**< Absolute z translation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Axis	RotX;		/**< Absolute x rotation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Axis	RotY;		/**< Absolute y rotation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Axis	RotZ;		/**< Absolute z rotation axis (the values are usually roughly between [-400 .. 400]) */
		PLInput::Button	Button0;	/**< Button #0 */
		PLInput::Button	Button1;	/**< Button #1 */
		PLInput::Button	Button2;	/**< Button #2 */
		PLInput::Button	Button3;	/**< Button #3 */
		PLInput::Button	Button4;	/**< Button #4 */
		PLInput::Button	Button5;	/**< Button #5 */
		PLInput::Button	Button6;	/**< Button #6 */
		PLInput::Button	Button7;	/**< Button #7 */


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
		*    System specific device implementation, can, but shouldn't be a null pointer
		*/
		PLINPUT_API SpaceMouse(const PLCore::String &sName, DeviceImpl *pImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~SpaceMouse();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the HID device has read some data
		*/
		void OnDeviceRead();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<> EventHandlerOnDeviceRead;

		// HID connection
		HIDDevice *m_pHIDDevice;	/**< HID device */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_SPACEMOUSE_H__
