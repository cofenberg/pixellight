/*********************************************************\
 *  File: HIDProvider.cpp                                *
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
#include "PLInput/Input/Devices/Joystick.h"
#include "PLInput/Input/Devices/WiiMote.h"
#include "PLInput/Input/Devices/SpaceMouse.h"
#include "PLInput/Backend/HID/HID.h"
#include "PLInput/Backend/HID/HIDDefinitions.h"
#include "PLInput/Backend/HID/HIDDevice.h"
#include "PLInput/Backend/HID/HIDProvider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(HIDProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
HIDProvider::HIDProvider()
{
}

/**
*  @brief
*    Destructor
*/
HIDProvider::~HIDProvider()
{
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void HIDProvider::QueryDevices()
{
	// Device counter
	int nSpaceMouse = 0;
	int nWiiMote	= 0;
// [TODO] HIDJoystick not finished yet ...
	int nJoystick	= 0;

	// Get list of HID-devices
	const Array<HIDDevice*> &lstDevices = HID::GetInstance()->GetDevices();
	for (uint32 i=0; i<lstDevices.GetNumOfElements(); i++) {
		// Get device
		HIDDevice *pDevice = lstDevices[i];

		// Get vendor and product ID
		uint32 nVendor    = pDevice->GetVendor();
		uint32 nProduct   = pDevice->GetProduct();
		uint32 nUsage	  = pDevice->GetUsage();
		uint32 nUsagePage = pDevice->GetUsagePage();

		// Check device type
		if (nVendor == SpaceMouse::VendorID && nUsagePage == UsagePageGeneric && nUsage == UsageMultiAxisController) {
			// SpaceMouse
			String sName = String("SpaceMouse") + nSpaceMouse;
			nSpaceMouse++;
			if (!CheckDevice(sName)) {
				AddDevice(sName, new SpaceMouse(sName, pDevice));
			}
		} else if (nVendor == WiiMote::VendorID && nProduct == WiiMote::ProductID) {
			// WiiMote
			String sName = String("WiiMote") + nWiiMote;
			nWiiMote++;
			if (!CheckDevice(sName)) {
				AddDevice(sName, new WiiMote(sName, pDevice));
			}
		} else if (nUsagePage == UsagePageGeneric && (nUsage == UsageJoystick || nUsage == UsageGamepad)) {
			// Joystick or Joypad
			String sName = String("Joystick") + nJoystick;
			nJoystick++;
			if (!CheckDevice(sName)) {
				AddDevice(sName, new Joystick(sName, pDevice));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
HIDProvider::HIDProvider(const HIDProvider &cSource)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Copy operator
*/
HIDProvider &HIDProvider::operator =(const HIDProvider &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
