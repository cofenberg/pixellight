/*********************************************************\
 *  File: Device.cpp                                     *
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
#include "PLInput/Backend/DeviceImpl.h"
#include "PLInput/Input/Devices/Device.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Device)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Device::Device(const String &sName, const String &sDescription, DeviceImpl *pImpl) : Controller(ControllerDevice, sName, sDescription),
	m_pImpl(pImpl),
	m_bDeleteImpl(false)
{
	// Set device
	if (m_pImpl) {
		m_pImpl->SetDevice(this);
		m_bDeleteImpl = m_pImpl->m_bDelete;
	}
}

/**
*  @brief
*    Destructor
*/
Device::~Device()
{
	// Destroy device implementation
	if (m_pImpl && m_bDeleteImpl)
		delete m_pImpl;
}

/**
*  @brief
*    Get device implementation
*/
DeviceImpl *Device::GetImpl() const
{
	// Return device implementation
	return m_pImpl;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
