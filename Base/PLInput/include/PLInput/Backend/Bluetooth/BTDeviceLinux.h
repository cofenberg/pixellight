/*********************************************************\
 *  File: BTDeviceLinux.h                                *
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


#ifndef __PLINPUT_BLUETOOTH_DEVICELINUX_H__
#define __PLINPUT_BLUETOOTH_DEVICELINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/Bluetooth/BTDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux implementation of 'BTDevice'
*/
class BTDeviceLinux : public BTDevice {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class BTLinux;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API BTDeviceLinux();

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~BTDeviceLinux();

		/**
		*  @brief
		*    Read handshake response
		*
		*  @return
		*    'true' if the handshake was successful, else 'false'
		*/
		PLINPUT_API bool ReadHandshake();


	//[-------------------------------------------------------]
	//[ Public virtual ConnectionDevice functions             ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual bool Open(PLCore::uint16 nOutputPort = 0, PLCore::uint16 nInputPort = 0);
		PLINPUT_API virtual bool Close();
		PLINPUT_API virtual bool IsOpen() const;
		PLINPUT_API virtual bool Read(PLCore::uint8 *pBuffer, PLCore::uint32 nSize);
		PLINPUT_API virtual bool Write(const PLCore::uint8 *pBuffer, PLCore::uint32 nSize);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int m_nCtrlSocket;	/**< Control channel socket */
		int m_nIntSocket;	/**< Interrupt channel socket */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_BLUETOOTH_DEVICELINUX_H__
