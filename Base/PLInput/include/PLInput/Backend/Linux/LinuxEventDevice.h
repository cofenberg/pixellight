/*********************************************************\
 *  File: LinuxEventDevice.h                             *
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


#ifndef __PLINPUT_LINUX_EVENTDEVICE_H__
#define __PLINPUT_LINUX_EVENTDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/UpdateDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux device implementation using the event subsystem of input.h
*/
class LinuxEventDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nFile
		*    File handle
		*/
		PLINPUT_API LinuxEventDevice(int nFile);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~LinuxEventDevice();

		/**
		*  @brief
		*    Get bus type
		*
		*  @return
		*    Bus type
		*/
		PLINPUT_API PLCore::uint16 GetBusType() const;

		/**
		*  @brief
		*    Get vendor ID
		*
		*  @return
		*    Vendor ID
		*/
		PLINPUT_API PLCore::uint16 GetVendorID() const;

		/**
		*  @brief
		*    Get product ID
		*
		*  @return
		*    Product ID
		*/
		PLINPUT_API PLCore::uint16 GetProductID() const;

		/**
		*  @brief
		*    Get version
		*
		*  @return
		*    Version
		*/
		PLINPUT_API PLCore::uint16 GetVersion() const;


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void Update() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int				m_nFile;	/**< File handle */
		PLCore::uint16	m_nBusType;	/**< Bus type (e.g. USB) */
		PLCore::uint16	m_nVendor;	/**< Vendor ID */
		PLCore::uint16	m_nProduct;	/**< Product ID */
		PLCore::uint16	m_nVersion;	/**< Version */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_LINUX_EVENTDEVICE_H__
