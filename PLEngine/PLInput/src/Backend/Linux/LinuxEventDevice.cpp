/*********************************************************\
 *  File: LinuxEventDevice.cpp                           *
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
#include "PLInput/Backend/Linux/LinuxEventDevice.h"
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LinuxEventDevice::LinuxEventDevice(int nFile) :
	m_nFile(nFile),
	m_nBusType(0),
	m_nVendor(0),
	m_nProduct(0),
	m_nVersion(0)
{
	// Do not destroy device implementation automatically, because this is managed by HIDLinux
	m_bDelete = false;

	// Get device info
	input_id sDeviceInfo;
	if (!ioctl(m_nFile, EVIOCGID, &sDeviceInfo)) {
		// Save device info
		m_nBusType = sDeviceInfo.bustype;
		m_nVendor  = sDeviceInfo.vendor;
		m_nProduct = sDeviceInfo.product;
		m_nVersion = sDeviceInfo.version;
	}
}

/**
*  @brief
*    Destructor
*/
LinuxEventDevice::~LinuxEventDevice()
{
	// Close file
	close(m_nFile);
}

/**
*  @brief
*    Get bus type
*/
uint16 LinuxEventDevice::GetBusType() const
{
	// Return bus type
	return m_nBusType;
}

/**
*  @brief
*    Get vendor ID
*/
uint16 LinuxEventDevice::GetVendorID() const
{
	// Return vendor ID
	return m_nVendor;
}

/**
*  @brief
*    Get product ID
*/
uint16 LinuxEventDevice::GetProductID() const
{
	// Return product ID
	return m_nProduct;
}

/**
*  @brief
*    Get version
*/
uint16 LinuxEventDevice::GetVersion() const
{
	// Return version
	return m_nVersion;
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void LinuxEventDevice::Update()
{
	// Read input events
	struct input_event pEvents[64];
	ssize_t nSize = read(m_nFile, pEvents, sizeof(struct input_event)*64);
	int nEvents = (nSize > 0 ? (int)(nSize / sizeof(struct input_event)) : 0);
	for (int i=0; i<nEvents; i++) {
		// Get corresponding control
		Control *pControl = NULL;
		if (pEvents[i].code == ABS_X)
			pControl = m_pDevice->GetControl("X");
		else if (pEvents[i].code == ABS_Y)
			pControl = m_pDevice->GetControl("Y");
		else if (pEvents[i].code == ABS_Z)
			pControl = m_pDevice->GetControl("Z");
		else if (pEvents[i].code == ABS_RX)
			pControl = m_pDevice->GetControl("RX");
		else if (pEvents[i].code == ABS_RY)
			pControl = m_pDevice->GetControl("RY");
		else if (pEvents[i].code == ABS_RZ)
			pControl = m_pDevice->GetControl("RZ");
		else if (pEvents[i].code == ABS_HAT0X)
			pControl = m_pDevice->GetControl("Hat");
		else if (pEvents[i].code >= BTN_JOYSTICK && pEvents[i].code < BTN_GAMEPAD)
			pControl = m_pDevice->GetControl(String("Button") + (pEvents[i].code - BTN_JOYSTICK));
		else if (pEvents[i].code >= BTN_GAMEPAD && pEvents[i].code < BTN_DIGI)
			pControl = m_pDevice->GetControl(String("Button") + (pEvents[i].code - BTN_GAMEPAD));

		// Get control type
		Axis   *pAxis   = (pControl != NULL && pControl->GetType() == ControlAxis)   ? (Axis*)  pControl : NULL;
		Button *pButton = (pControl != NULL && pControl->GetType() == ControlButton) ? (Button*)pControl : NULL;

		// Set control value
		if (pEvents[i].type == EV_KEY && pButton) {
			// Button
			pButton->SetPressed(pEvents[i].value != 0);
		} else if ((pEvents[i].type == EV_ABS || pEvents[i].type == EV_REL) && pAxis) {
			// Absolute or relative axis
			// Get minimum and maximum values
			input_absinfo sAbsInfo;
			if (!ioctl(m_nFile, EVIOCGABS(0), &sAbsInfo)) {
				// Get value in a range of -1.0 - +1.0
				float fValue = ((float)(pEvents[i].value - sAbsInfo.minimum) / (float)(sAbsInfo.maximum - sAbsInfo.minimum)) * 2.0f - 1.0f;
				if (fValue >  1.0f) fValue =  1.0f;
				if (fValue < -1.0f) fValue = -1.0f;
				pAxis->SetValue(fValue);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
