/*********************************************************\
 *  File: LinuxProvider.cpp                              *
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
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Input/Devices/Joystick.h"
#include "PLInput/Backend/Linux/LinuxProvider.h"
#include "PLInput/Backend/Linux/LinuxKeyboardDevice.h"
#include "PLInput/Backend/Linux/LinuxMouseDevice.h"
#include "PLInput/Backend/Linux/LinuxEventDevice.h"
#include <dirent.h>
#include <fcntl.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(LinuxProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LinuxProvider::LinuxProvider() :
	m_pDisplay(NULL)
{
	// Open display
	m_pDisplay = XOpenDisplay(NULL);
}

/**
*  @brief
*    Destructor
*/
LinuxProvider::~LinuxProvider()
{
	// Close display
	if (m_pDisplay) {
		XCloseDisplay(m_pDisplay);
	}
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void LinuxProvider::QueryDevices()
{
	// Create a keyboard device
	if (!CheckDevice("Keyboard")) {
		// Add device
		LinuxKeyboardDevice *pImpl = new LinuxKeyboardDevice(m_pDisplay);
		AddDevice("Keyboard", new Keyboard("Keyboard", pImpl));
	}

	// Create a mouse device
	if (!CheckDevice("Mouse")) {
		LinuxMouseDevice *pImpl = new LinuxMouseDevice(m_pDisplay);
		AddDevice("Mouse", new Mouse("Mouse", pImpl));
	}

	// List devices in "/dev/input/event*"
	int nDevice = 0;
	DIR *pDir = opendir("/dev/input");
	if (pDir) {
		// Read first entry
		dirent *pEntry = readdir(pDir);
		while (pEntry) {
			// Check if filename is "eventX"
			String sFilename = pEntry->d_name;
			if (sFilename.GetSubstring(0, 5) == "event") {
				// Try to open the device
				int f = open(("/dev/input/" + sFilename).GetASCII(), O_RDWR | O_NONBLOCK);
				if (f > 0) {
					// Create device
					LinuxEventDevice *pImpl = new LinuxEventDevice(f);
					String sName = String("Joystick") + nDevice;
					AddDevice(sName, new Joystick(sName, pImpl));
					nDevice++;
				}
			}

			// Read next entry
			pEntry = readdir(pDir);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
