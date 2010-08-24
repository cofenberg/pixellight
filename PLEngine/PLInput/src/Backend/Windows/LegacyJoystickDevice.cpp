/*********************************************************\
 *  File: LegacyJoystickDevice.cpp                       *
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
#include <PLGeneral/Core/MemoryManager.h>
#include <PLMath/Math.h>
#include "PLInput/Input/Devices/Joystick.h"
#include "PLInput/Backend/Windows/LegacyJoystickDevice.h"
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LegacyJoystickDevice::LegacyJoystickDevice(uint32 nJoystickID) :
	m_nJoystickID (nJoystickID),
	m_nFallbackPOV(0)
{
	// Destroy device implementation automatically
	m_bDelete = true;

	// Check whether or not the joystick supports POV
	JOYCAPS sJoyCaps;
	MemoryManager::Set(&sJoyCaps, 0, sizeof(sJoyCaps));
	if (joyGetDevCaps (m_nJoystickID, &sJoyCaps, sizeof(sJoyCaps)) == JOYERR_NOERROR && !(sJoyCaps.wCaps & JOYCAPS_HASPOV)) {
		// Get joystick state
		JOYINFOEX sJoyInfo;
		sJoyInfo.dwSize  = sizeof(JOYINFOEX);
		sJoyInfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(m_nJoystickID, &sJoyInfo) == JOYERR_NOERROR) {
			// Use the initial position as POV
			m_nFallbackPOV = sJoyInfo.dwXpos;
		}
	}
}

/**
*  @brief
*    Destructor
*/
LegacyJoystickDevice::~LegacyJoystickDevice()
{
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void LegacyJoystickDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get joystick device
		Joystick *pJoystick = (Joystick*)m_pDevice;

		// Get joystick state
		JOYINFOEX sJoyInfo;
		sJoyInfo.dwSize  = sizeof(JOYINFOEX);
		sJoyInfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(m_nJoystickID, &sJoyInfo) == JOYERR_NOERROR) {
			// Update axes
			for (uint32 i=0; i<6; i++) {
				// Get POV
				int nPOV = m_nFallbackPOV ? m_nFallbackPOV : sJoyInfo.dwPOV / 2;

				// Calculate delta
				int nDelta = 0;
				switch (i) {
					case 0: nDelta = (int)(sJoyInfo.dwXpos - nPOV); break;
					case 1: nDelta = (int)(sJoyInfo.dwYpos - nPOV); break;
					case 2: nDelta = (int)(sJoyInfo.dwZpos - nPOV); break;
					case 3: nDelta = (int)(sJoyInfo.dwRpos - nPOV); break;
					case 4: nDelta = (int)(sJoyInfo.dwUpos - nPOV); break;
					case 5: nDelta = (int)(sJoyInfo.dwVpos - nPOV); break;
				}

				// Calculate axis values (between -1.0f and 1.0f)
				float fPos		 = 0.0f;
				int   nThreshold = pJoystick->GetThreshold();
				if (PLMath::Math::Abs(nDelta) >= nThreshold) {
					if (nDelta < 0.0f)	fPos = (float) (nDelta + nThreshold) / (nPOV - nThreshold);
					else				fPos = (float) (nDelta - nThreshold) / (nPOV - nThreshold);
					if (fPos < -1.0f)	fPos = -1.0f;
					if (fPos >  1.0f)	fPos =  1.0f;
				}

				// Set new value
				Axis *pAxis = pJoystick->GetAxes()[i];
				if (pAxis && pAxis->GetValue() != fPos)
					pAxis->SetValue(fPos);
			}

			// Update buttons
			uint32 nFlag = 1;
			for (uint32 i=0; i<32; i++) {
				bool bPressed = ((sJoyInfo.dwButtons & nFlag) != 0);
				Button *pButton = pJoystick->GetButtons()[i];
				if (pButton && pButton->IsPressed() != bPressed)
					pButton->SetPressed(bPressed);
				nFlag = nFlag << 1;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
