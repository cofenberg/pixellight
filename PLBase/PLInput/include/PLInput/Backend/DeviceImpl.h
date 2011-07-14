/*********************************************************\
 *  File: DeviceImpl.h                                   *
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


#ifndef __PLINPUT_DEVICEIMPL_H__
#define __PLINPUT_DEVICEIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/PLInput.h"
#include "PLInput/PLInputDefinitions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Device;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Device implementation base class
*
*  @remarks
*    A device implementation class represents a concrete device interface implementation, such as a HID device
*    or a Windows RawInput device. A logical device will use an implementation class to interface with the unterlying
*    system device, and concrete backend implementation will implement those interface for their specific systems.
*/
class DeviceImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Device;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API DeviceImpl();

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~DeviceImpl();

		/**
		*  @brief
		*    Get backend type
		*
		*  @return
		*    Type of backend
		*/
		PLINPUT_API EDeviceBackend GetBackendType() const;

		/**
		*  @brief
		*    Get device
		*
		*  @return
		*    Device that owns this device implementation, can be a null pointer
		*/
		PLINPUT_API Device *GetDevice() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Set device
		*
		*  @param[in] pDevice
		*    Device that owns this device implementation, can be a null pointer
		*/
		PLINPUT_API void SetDevice(Device *pDevice);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EDeviceBackend	 m_nBackendType;	/**< Device backend type */
		Device			*m_pDevice;			/**< Device that owns to this device implementation, can be a null pointer */
		bool			 m_bDelete;			/**< If 'true', the device implementation will be destroyed automatically with the Device, else it must be destroyed manually */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_DEVICEIMPL_H__
