/*********************************************************\
 *  File: Provider.cpp                                   *
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
#include "PLInput/Input/InputManager.h"
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Backend/Provider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Provider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Provider::Provider()
{
}

/**
*  @brief
*    Destructor
*/
Provider::~Provider()
{
	// Clean up
	Clear();
}

/**
*  @brief
*    Get list of devices
*/
const List<Device*> &Provider::GetDevices() const
{
	// Return device list
	return m_lstDevices;
}

/**
*  @brief
*    Detect devices
*/
void Provider::DetectDevices(bool bReset)
{
	// Delete all devices?
	if (bReset)
		Clear();

	// Flag all current devices as 'not confirmed'
	for (uint32 i=0; i<m_lstDevices.GetNumOfElements(); i++)
		m_lstDevices[i]->m_bConfirmed = false;

	// Detect new devices (the ones that are already there will be ignored by AddDevice)
	QueryDevices();

	// Delete all devices that are no longer there (confirmed == false)
	for (uint32 i=0; i<m_lstDevices.GetNumOfElements(); i++) {
		Device *pDevice = m_lstDevices[i];
		if (!pDevice->m_bConfirmed) {
			// Remove device
			InputManager::GetInstance()->RemoveDevice(pDevice);
			m_lstDevices.Remove(pDevice);
			delete pDevice;
			i--;
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destroy all devices
*/
void Provider::Clear()
{
	// Delete all input devices
	for (uint32 i=0; i<m_lstDevices.GetNumOfElements(); i++) {
		Device *pDevice = m_lstDevices[i];
		InputManager::GetInstance()->RemoveDevice(pDevice);
		delete pDevice;
	}
	m_lstDevices.Clear();
}

/**
*  @brief
*    Check if a device is already known
*/
bool Provider::CheckDevice(const String &sName)
{
	// Check if the device is already present
	Device *pDevice = InputManager::GetInstance()->GetDevice(sName);
	if (pDevice) {
		// Update device
		pDevice->m_bConfirmed = true;
		return true;
	}

	// Not found
	return false;
}

/**
*  @brief
*    Add a new input device
*/
bool Provider::AddDevice(const String &sName, Device *pDevice)
{
	// Check if the device is already present
	Device *pDeviceFound = InputManager::GetInstance()->GetDevice(sName);
	if (!pDeviceFound) {
		// Add device to manager
		if (InputManager::GetInstance()->AddDevice(pDevice)) {
			// Add device to own list - if we're in here, we now that the pDevice pointer is valid
			m_lstDevices.Add(pDevice);
			pDevice->m_bConfirmed = true;
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
