/*********************************************************\
 *  File: BluetoothProvider.cpp                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLInput/Input/Devices/WiiMote.h>
#include "PLInput/Backend/Bluetooth/Bluetooth.h"
#include "PLInput/Backend/Bluetooth/BTDevice.h"
#include "PLInput/Backend/Bluetooth/BluetoothProvider.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(BluetoothProvider)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
BluetoothProvider::BluetoothProvider()
{
}

/**
*  @brief
*    Destructor
*/
BluetoothProvider::~BluetoothProvider()
{
}


//[-------------------------------------------------------]
//[ Private virtual Provider functions                    ]
//[-------------------------------------------------------]
void BluetoothProvider::QueryDevices()
{
	// Device counter
	int nWiiMote = 0;

	// Get list of Bluetooth-devices
	const List<BTDevice*> &lstDevices = Bluetooth::GetInstance()->GetDevices();
	for (uint32 i=0; i<lstDevices.GetNumOfElements(); i++) {
		// Get device
		BTDevice *pDevice = lstDevices[i];

		// Check device type
		if ( pDevice->GetName() == "Nintendo RVL-CNT-01" ||
			(pDevice->GetClass(0) == WiiMote::DeviceClass0 &&
			 pDevice->GetClass(1) == WiiMote::DeviceClass1 &&
			 pDevice->GetClass(2) == WiiMote::DeviceClass2) ) {
			// WiiMote
			String sName = String("WiiMote") + nWiiMote;
			nWiiMote++;
			if (!CheckDevice(sName))
				AddDevice(sName, new WiiMote(sName, pDevice));
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
BluetoothProvider::BluetoothProvider(const BluetoothProvider &cSource)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Copy operator
*/
BluetoothProvider &BluetoothProvider::operator =(const BluetoothProvider &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
