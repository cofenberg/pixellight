/*********************************************************\
 *  File: BTDevice.cpp                                   *
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
#include <PLCore/Core/MemoryManager.h>
#include "PLInput/Backend/Bluetooth/BTDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BTDevice::BTDevice()
{
	// Set device type
	m_nDeviceType = ConnectionDevice::DeviceTypeBluetooth;

	// Initialize device
	MemoryManager::Set(m_nAddress, 0, 6);
	MemoryManager::Set(m_nClass,   0, 3);
}

/**
*  @brief
*    Copy constructor
*/
BTDevice::BTDevice(const BTDevice &cSource) :
	m_sName(cSource.m_sName)
{
	// Set device type
	m_nDeviceType = ConnectionDevice::DeviceTypeBluetooth;

	// Copy device
	MemoryManager::Copy(m_nAddress, cSource.m_nAddress, 6);
	MemoryManager::Copy(m_nClass,	cSource.m_nClass,   3);
}

/**
*  @brief
*    Destructor
*/
BTDevice::~BTDevice()
{
}

/**
*  @brief
*    Assignment operator
*/
BTDevice &BTDevice::operator =(const BTDevice &cSource)
{
	// Copy device
	m_sName = cSource.m_sName;
	MemoryManager::Copy(m_nAddress, cSource.m_nAddress, 6);
	MemoryManager::Copy(m_nClass,	cSource.m_nClass,   3);
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool BTDevice::operator ==(const BTDevice &cSource)
{
	// Compare devices
	return (m_sName == cSource.m_sName &&
			MemoryManager::Compare(m_nAddress,	cSource.m_nAddress, 6) == 0 &&
			MemoryManager::Compare(m_nClass,	cSource.m_nClass,   3) == 0);
}

/**
*  @brief
*    Get device name
*/
String BTDevice::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get device address
*/
uint8 BTDevice::GetAddress(int8 nIndex) const
{
	// Return address part
	return (nIndex >= 0 && nIndex < 6) ? m_nAddress[nIndex] : 0;
}

/**
*  @brief
*    Get device class
*/
uint8 BTDevice::GetClass(int8 nIndex) const
{
	// Return class part
	return (nIndex >= 0 && nIndex < 3) ? m_nClass[nIndex] : 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
