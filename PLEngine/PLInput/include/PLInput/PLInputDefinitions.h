/*********************************************************\
 *  File: PLInputDefinitions.h                           *
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


#ifndef __PLINPUT_DEFINITIONS_H__
#define __PLINPUT_DEFINITIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Rtti.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Controllers                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Controller type
*/
enum EControllerType {
	ControllerDevice = 0,	/**< Controller is a real input device, no input connections are allowed */
	ControllerVirtual		/**< Controller is a virtual controller, input and output connections are allowed */
};

	// RTTI definition
	pl_enum(EControllerType)
		pl_enum_value(ControllerDevice,  "Real input device, no input connections are allowed")
		pl_enum_value(ControllerVirtual, "Virtual controller, input and output connections are allowed")
	pl_enum_end

/**
*  @brief
*    Control type
*/
enum EControlType {
	ControlUnknown = 0,	/**< Unknown control */
	ControlButton = 1,	/**< Button or key */
	ControlAxis,		/**< Axis (can be absolute or relative) */
	ControlLED,			/**< LED output */
	ControlEffect		/**< Effect output */
};

	// RTTI definition
	pl_enum(EControlType)
		pl_enum_value(ControlUnknown,	"Unknown control")
		pl_enum_value(ControlButton,	"Button or key")
		pl_enum_value(ControlAxis,		"Axis")
		pl_enum_value(ControlLED,		"LED output")
		pl_enum_value(ControlEffect,	"Effect output")
	pl_enum_end

/**
*  @brief
*    Device backend type
*/
enum EDeviceBackend {
	BackendUnknown = 0,			/**< Unknown backend */
	BackendUpdateDevice,		/**< UpdateDevice backend */
	BackendConnectionDevice,	/**< ConnectionDevice backend */
	BackendHID					/**< HIDDevice backend (which is also a ConnectionDevice!) */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_DEFINITIONS_H__
