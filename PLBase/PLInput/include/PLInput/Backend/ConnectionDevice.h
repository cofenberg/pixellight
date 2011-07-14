/*********************************************************\
 *  File: ConnectionDevice.h                             *
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


#ifndef __PLINPUT_CONNECTIONDEVICE_H__
#define __PLINPUT_CONNECTIONDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLInput/Backend/DeviceImpl.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Thread;
	class Mutex;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Device connection class
*
*  @remarks
*    A connection device is a device backend that uses e.g. a HID or bluetooth connection to communicate
*    directly with the input device (no use of HID features, only read/write commands) and expose an
*    interface that can be used by the device class to use that connection.
*/
class ConnectionDevice : public DeviceImpl {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Device type
		*/
		enum EDeviceType {
			DeviceTypeUnknown,	/**< Unknown device type */
			DeviceTypeHID ,		/**< HID device */
			DeviceTypeBluetooth	/**< Bluetooth device */
		};


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<> EventOnConnect;		/**< Called when device has been connected */
		PLCore::Event<> EventOnDisconnect;	/**< Called when device has been disconnected */
		PLCore::Event<> EventOnRead;		/**< Called when data has been read */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API ConnectionDevice();

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~ConnectionDevice();

		/**
		*  @brief
		*    Get device type
		*
		*  @return
		*    Device type
		*/
		PLINPUT_API EDeviceType GetDeviceType() const;

		/**
		*  @brief
		*    Get input report size
		*
		*  @return
		*    Size of an input report in bytes (unique to each HID device)
		*/
		PLINPUT_API PLGeneral::uint32 GetInputReportSize() const;

		/**
		*  @brief
		*    Set input report size
		*
		*  @param[in] nSize
		*    Size of an input report in bytes (unique to each HID device)
		*/
		PLINPUT_API void SetInputReportSize(PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Get output report size
		*
		*  @return
		*    Size of an output report in bytes
		*/
		PLINPUT_API PLGeneral::uint32 GetOutputReportSize() const;

		/**
		*  @brief
		*    Set output report size
		*
		*  @param[in] nSize
		*    Size of an output report in bytes (unique to each HID device)
		*/
		PLINPUT_API void SetOutputReportSize(PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Get input buffer
		*
		*  @return
		*    Input buffer (can be a null pointer if the device is not open), do not destroy the returned buffer!
		*/
		PLINPUT_API PLGeneral::uint8 *GetInputBuffer() const;

		/**
		*  @brief
		*    Get output buffer
		*
		*  @return
		*    Output buffer (can be a null pointer if the device is not open), do not destroy the returned buffer!
		*/
		PLINPUT_API PLGeneral::uint8 *GetOutputBuffer() const;


	//[-------------------------------------------------------]
	//[ Public virtual ConnectionDevice functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Open device connection
		*
		*  @param[in] nOutputPort
		*    Bluetooth port for output channel
		*  @param[in] nInputPort
		*    Bluetooth port for input channel
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    If you are using a HIDDevice, the output and input ports will be ignored.
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLINPUT_API virtual bool Open(PLGeneral::uint16 nOutputPort = 0, PLGeneral::uint16 nInputPort = 0);

		/**
		*  @brief
		*    Close device connection
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLINPUT_API virtual bool Close();

		/**
		*  @brief
		*    Check if the device is open
		*
		*  @return
		*    'true' if device is open, else 'false'
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLINPUT_API virtual bool IsOpen() const = 0;

		/**
		*  @brief
		*    Read from device
		*
		*  @param[out] pBuffer
		*    Buffer that will receive the data, must be valid and at least "nSize"-bytes long!
		*  @param[in]  nSize
		*    Buffer size in bytes
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLINPUT_API virtual bool Read(PLGeneral::uint8 *pBuffer, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Write to device
		*
		*  @param[in] pBuffer
		*    Buffer containing the data, must be valid and at least "nSize"-bytes long!
		*  @param[in] nSize
		*    Buffer size in bytes
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLINPUT_API virtual bool Write(const PLGeneral::uint8 *pBuffer, PLGeneral::uint32 nSize);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialize and start thread for read/write operations
		*
		*  @remarks
		*    Creates and starts the read thread and initializes m_cMutex, which should be
		*    used by derived classes in their Read() and Write() functions.
		*/
		PLINPUT_API void InitThread();

		/**
		*  @brief
		*    Stop thread for read/write operations
		*/
		PLINPUT_API void StopThread();

		/**
		*  @brief
		*    Lock read/write mutex
		*
		*  @remarks
		*    This should be used by derived classes inside their Read() and Write() functions!
		*/
		PLINPUT_API void LockMutex();

		/**
		*  @brief
		*    Unlock read/write mutex
		*
		*  @remarks
		*    This should be used by derived classes inside their Read() and Write() functions!
		*/
		PLINPUT_API void UnlockMutex();


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Device update thread function
		*
		*  @param[in] pData
		*    Pointer to this ConnectionDevice instance, always valid!
		*/
		static int ReadThread(void *pData);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Device type
		EDeviceType			 m_nDeviceType;			/**< Device type */

		// Input and output buffers
		PLGeneral::uint8	*m_pInputBuffer;		/**< Input report buffer, can be a null pointer */
		PLGeneral::uint8	*m_pOutputBuffer;		/**< Output report buffer, can be a null pointer */
		PLGeneral::uint16	 m_nInputReportSize;	/**< Size of input report in bytes */
		PLGeneral::uint16	 m_nOutputReportSize;	/**< Size of output report in bytes */

		// Read thread
		PLGeneral::Thread	*m_pThread;				/**< Update thread, can be a null pointer */
		PLGeneral::Mutex	*m_pMutex;				/**< Update mutex, can be a null pointer */
		bool				 m_bThreadExit;			/**< Flag to exit the thread */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_CONNECTIONDEVICE_H__
