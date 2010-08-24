/*********************************************************\
 *  File: RawInputProvider.cpp                           *
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
#include "PLInput/Backend/Windows/RawInput.h"
#include "PLInput/Backend/Windows/RawInputDevice.h"
#include "PLInput/Backend/Windows/RawInputProvider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RawInputProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
RawInputProvider::RawInputProvider()
{
}

/**
*  @brief
*    Destructor
*/
RawInputProvider::~RawInputProvider()
{
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void RawInputProvider::QueryDevices()
{
	// Get list of Raw Input devices
	uint32 nKeyboard = 0;
	uint32 nMouse = 0;
	RawInput::GetInstance()->DetectDevices();
	const List<RawInputDevice*> &lstDevices = RawInput::GetInstance()->GetDevices();
	for (uint32 i=0; i<lstDevices.GetNumOfElements(); i++) {
		// Get device
		RawInputDevice *pDevice = lstDevices[i];
		if (pDevice->GetType() == RIM_TYPEKEYBOARD || pDevice->GetType() == RIM_TYPEMOUSE) {
			// Set device name
			String sName;
			if (pDevice->GetType() == RIM_TYPEKEYBOARD)	{
				// Keyboard
				sName = "Keyboard";
				if (!pDevice->IsVirtual()) {
					sName += (int)nKeyboard;
					nKeyboard++;
				}
			} else if (pDevice->GetType() == RIM_TYPEMOUSE)	{
				// Mouse
				sName = "Mouse";
				if (!pDevice->IsVirtual()) {
					sName += (int)nMouse;
					nMouse++;
				}
			}

			// Check if device is already known
			if (!CheckDevice(sName)) {
				// Create device
				if (pDevice->GetType() == RIM_TYPEKEYBOARD) {
					// Create a keyboard device
					AddDevice(sName, new Keyboard(sName, pDevice));
				} else if (pDevice->GetType() == RIM_TYPEMOUSE) {
					// Create a mouse device
					AddDevice(sName, new Mouse(sName, pDevice));
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
