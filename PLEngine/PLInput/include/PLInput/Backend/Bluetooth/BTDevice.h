/*********************************************************\
 *  File: BTDevice.h                                     *
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


#ifndef __PLINPUT_BLUETOOTH_DEVICE_H__
#define __PLINPUT_BLUETOOTH_DEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLInput/Backend/ConnectionDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bluetooth device
*/
class BTDevice : public ConnectionDevice {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class BTLinux;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API BTDevice();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    BTDevice to copy from
		*/
		PLINPUT_API BTDevice(const BTDevice &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API ~BTDevice();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    BTDevice to copy from
		*
		*  @return
		*    Reference to this BTDevice
		*/
		PLINPUT_API BTDevice &operator =(const BTDevice &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    BTDevice to compare with
		*
		*  @return
		*    'true', if both are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const BTDevice &cSource);

		/**
		*  @brief
		*    Get device name
		*
		*  @return
		*    Device name
		*/
		PLINPUT_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get device address
		*
		*  @param[in] nIndex
		*    Address component (0..7)
		*
		*  @return
		*    Address
		*/
		PLINPUT_API PLGeneral::uint8 GetAddress(PLGeneral::int8 nIndex) const;

		/**
		*  @brief
		*    Get device class
		*
		*  @param[in] nIndex
		*    Class component (0..2)
		*
		*  @return
		*    Class
		*/
		PLINPUT_API PLGeneral::uint8 GetClass(PLGeneral::int8 nIndex) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Device data
		PLGeneral::String m_sName;			/**< Device name */
		PLGeneral::uint8  m_nAddress[8];	/**< Bluetooth address */
		PLGeneral::uint8  m_nClass[3];		/**< Bluetooth device class */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_BLUETOOTH_DEVICE_H__
