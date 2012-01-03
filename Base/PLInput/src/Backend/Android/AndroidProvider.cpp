/*********************************************************\
 *  File: AndroidProvider.cpp                            *
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
#include <android/input.h>
#include <PLCore/System/SystemAndroid.h>
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Input/Devices/SplitTouchPad.h"
#include "PLInput/Input/Devices/SensorManager.h"
#include "PLInput/Backend/Android/AndroidMouseDevice.h"
#include "PLInput/Backend/Android/AndroidKeyboardDevice.h"
#include "PLInput/Backend/Android/AndroidSplitTouchPadDevice.h"
#include "PLInput/Backend/Android/AndroidSensorManagerDevice.h"
#include "PLInput/Backend/Android/AndroidProvider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
AndroidProvider::AndroidProvider() :
	SlotInputEvent(&AndroidProvider::OnInputEvent, this),
	m_pAndroidKeyboardDevice(nullptr),
	m_pAndroidSplitTouchPadDevice(nullptr),
	m_pAndroidMouseDevice(nullptr)
{
	// Connect the Android input event handler
	SystemAndroid::EventInputEvent.Connect(SlotInputEvent);
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
		m_pAndroidKeyboardDevice = new AndroidKeyboardDevice();
		AddDevice("Keyboard", new Keyboard("Keyboard", m_pAndroidKeyboardDevice));
	}

	// Create a splitscreen touch pad device
	if (!CheckDevice("SplitTouchPad")) {
		// Add device
		m_pAndroidSplitTouchPadDevice = new AndroidSplitTouchPadDevice();
		AddDevice("SplitTouchPad", new SplitTouchPad("SplitTouchPad", m_pAndroidSplitTouchPadDevice));
	}

	// Create a mouse device
	if (!CheckDevice("Mouse")) {
		// Add device
		m_pAndroidMouseDevice = new AndroidMouseDevice(m_pAndroidSplitTouchPadDevice);
		AddDevice("Mouse", new Mouse("Mouse", m_pAndroidMouseDevice));
	}

	// Create a sensor manager device
	if (!CheckDevice("SensorManager")) {
		AndroidSensorManagerDevice *pImpl = new AndroidSensorManagerDevice();
		AddDevice("SensorManager", new SensorManager("SensorManager", pImpl));
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called to process the next Android input event
*/
void AndroidProvider::OnInputEvent(const struct AInputEvent &cAInputEvent)
{
	// Check the input event type
	switch (AInputEvent_getType(&cAInputEvent)) {
		// Key (e.g. from the soft keyboard)
		case AINPUT_EVENT_TYPE_KEY:
			if (m_pAndroidKeyboardDevice)
				m_pAndroidKeyboardDevice->OnKeyInputEvent(cAInputEvent);
			break;

		// Motion (e.g. from the touchscreen)
		case AINPUT_EVENT_TYPE_MOTION:
			if (m_pAndroidMouseDevice)
				m_pAndroidMouseDevice->OnMotionInputEvent(cAInputEvent);
			if (m_pAndroidSplitTouchPadDevice)
				m_pAndroidSplitTouchPadDevice->OnMotionInputEvent(cAInputEvent);
			break;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput