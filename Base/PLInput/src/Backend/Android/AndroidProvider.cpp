/*********************************************************\
 *  File: AndroidProvider.cpp                            *
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
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Input/Devices/SensorManager.h"
#include "PLInput/Backend/Android/AndroidKeyboardDevice.h"
#include "PLInput/Backend/Android/AndroidSensorManagerDevice.h"
#include "PLInput/Backend/Android/AndroidProvider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(AndroidProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
AndroidProvider::AndroidProvider()
{
}

/**
*  @brief
*    Destructor
*/
AndroidProvider::~AndroidProvider()
{
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void AndroidProvider::QueryDevices()
{
	// Create a keyboard device
	if (!CheckDevice("Keyboard")) {
		// Add device
		AndroidKeyboardDevice *pImpl = new AndroidKeyboardDevice();
		AddDevice("Keyboard", new Keyboard("Keyboard", pImpl));
	}

	// Create a sensor manager device
	if (!CheckDevice("SensorManager")) {
		AndroidSensorManagerDevice *pImpl = new AndroidSensorManagerDevice();
		AddDevice("SensorManager", new SensorManager("SensorManager", pImpl));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
