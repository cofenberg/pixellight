/*********************************************************\
 *  File: HIDDeviceLinux.cpp                             *
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
#include "PLInput/Backend/HID/HIDDeviceLinux.h"


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
HIDDeviceLinux::HIDDeviceLinux()
{
	// Do not destroy device implementation automatically, because this is managed by HIDLinux
	m_bDelete = false;
}

/**
*  @brief
*    Destructor
*/
HIDDeviceLinux::~HIDDeviceLinux()
{
	// Close a possibly open connection
	Close();
}


//[-------------------------------------------------------]
//[ Public virtual ConnectionDevice functions             ]
//[-------------------------------------------------------]
bool HIDDeviceLinux::Open(uint16 nOutputPort, uint16 nInputPort)
{
	// Close first
	if (IsOpen()) Close();

	// [TODO]
	/*
	// Connect

	// Start read thread
	InitThread();

	// Call event
	EventOnConnect();

	// Done
	return true;
	*/

	// Error
	return false;
}

bool HIDDeviceLinux::Close()
{
	if (IsOpen()) {
		// [TODO]
		/*
		// Stop read thread
		StopThread();

		// Call event
		EventOnDisconnect();

		// Disconnect

		// Done
		return true;
		*/
	}

	// Error
	return false;
}

bool HIDDeviceLinux::IsOpen() const
{
	// [TODO]
	return false;
}

bool HIDDeviceLinux::Read(uint8 *pBuffer, uint32 nSize)
{
	// [TODO]

	// Error!
	return false;
}

bool HIDDeviceLinux::Write(const uint8 *pBuffer, uint32 nSize)
{
	// [TODO]

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
