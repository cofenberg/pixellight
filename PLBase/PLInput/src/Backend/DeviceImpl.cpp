/*********************************************************\
 *  File: DeviceImpl.cpp                                 *
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
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Backend/DeviceImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DeviceImpl::DeviceImpl() :
	m_nBackendType(BackendUnknown),
	m_pDevice(nullptr),
	m_bDelete(true)
{
}

/**
*  @brief
*    Destructor
*/
DeviceImpl::~DeviceImpl()
{
	// Remove from device
	if (m_pDevice) {
		m_pDevice->m_pImpl = nullptr;
	}
}

/**
*  @brief
*    Get backend type
*/
EDeviceBackend DeviceImpl::GetBackendType() const
{
	// Return backend type
	return m_nBackendType;
}

/**
*  @brief
*    Get device
*/
Device *DeviceImpl::GetDevice() const
{
	// Return device
	return m_pDevice;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set device
*/
void DeviceImpl::SetDevice(Device *pDevice)
{
	// Set device
	m_pDevice = pDevice;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
