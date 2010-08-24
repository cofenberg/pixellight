/*********************************************************\
 *  File: LegacyJoystickProvider.cpp                     *
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
#include "PLInput/Input/Devices/Joystick.h"
#include "PLInput/Backend/Windows/LegacyJoystickDevice.h"
#include "PLInput/Backend/Windows/LegacyJoystickProvider.h"
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(LegacyJoystickProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LegacyJoystickProvider::LegacyJoystickProvider()
{
}

/**
*  @brief
*    Destructor
*/
LegacyJoystickProvider::~LegacyJoystickProvider()
{
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void LegacyJoystickProvider::QueryDevices()
{
	// Get list of joysticks
	JOYINFO sJoyInfo;
	for (uint32 nJoystick = 0; nJoystick < 16; nJoystick++) {
		// Check if joystick is valid
		if (joyGetPos(nJoystick, &sJoyInfo) == JOYERR_NOERROR) {
			// Get name and check if a device with that ID is not used already
			String sName = String("Joystick") + (int)nJoystick;
			if (!CheckDevice(sName)) {
				// Add device
				LegacyJoystickDevice *pImpl = new LegacyJoystickDevice(nJoystick);
				AddDevice(sName, new Joystick(sName, pImpl));
			}
		} else break;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LegacyJoystickProvider::LegacyJoystickProvider(const LegacyJoystickProvider &cSource)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Copy operator
*/
LegacyJoystickProvider &LegacyJoystickProvider::operator =(const LegacyJoystickProvider &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
