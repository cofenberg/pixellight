/*********************************************************\
 *  File: HID.cpp                                        *
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
#include "PLInput/Backend/HID/HID.h"
#include "PLInput/Backend/HID/HIDImpl.h"
#if defined(WIN32)
	#include "PLInput/Backend/HID/HIDWindows.h"
#elif defined(LINUX)
	#include "PLInput/Backend/HID/HIDLinux.h"
#endif


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
*    Detect available HID devices
*/
void HID::DetectDevices()
{
	// Clear list
	Clear();

	// Check HID implementation
	if (m_pHIDImpl) {
		// Enumerate devices
		m_pHIDImpl->EnumerateDevices(m_lstDevices);
	}
}

/**
*  @brief
*    Get list of available HID devices
*/
const List<HIDDevice*> &HID::GetDevices() const
{
	// Return list
	return m_lstDevices;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HID::HID() :
	m_pHIDImpl(NULL)
{
	// Create HID implementation
	#if defined(WIN32)
		m_pHIDImpl = new HIDWindows();
	#elif defined(LINUX)
		m_pHIDImpl = new HIDLinux();
	#endif

	// Detect devices
	DetectDevices();
}

/**
*  @brief
*    Destructor
*/
HID::~HID()
{
	// Clear devices
	Clear();

	// Delete HID implementation
	if (m_pHIDImpl) delete m_pHIDImpl;
}

/**
*  @brief
*    Remove all devices
*/
void HID::Clear()
{
	// Destroy devices
	m_lstDevices.Clear();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
