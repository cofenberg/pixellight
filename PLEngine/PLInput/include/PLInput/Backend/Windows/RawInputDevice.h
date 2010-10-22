/*********************************************************\
 *  File: RawInputDevice.h                               *
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


#ifndef __PLINPUT_RAWINPUTDEVICE_H__
#define __PLINPUT_RAWINPUTDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLInput/Backend/UpdateDevice.h"
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Keyboard;
class Button;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Information about a Raw-Input Device
*/
class RawInputDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RawInput;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API RawInputDevice();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLINPUT_API RawInputDevice(const RawInputDevice &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~RawInputDevice();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*/
		PLINPUT_API RawInputDevice &operator =(const RawInputDevice &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    RawInputDevice to compare with
		*
		*  @return
		*    'true', if both are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const RawInputDevice &cSource);

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
		*    Get device type
		*
		*  @return
		*    Device type
		*/
		PLINPUT_API DWORD GetType() const;

		/**
		*  @brief
		*    Get device handle
		*
		*  @return
		*    Device handle
		*/
		PLINPUT_API HANDLE GetHandle() const;

		/**
		*  @brief
		*    Get device info
		*
		*  @return
		*    Device info
		*/
		PLINPUT_API RID_DEVICE_INFO GetDeviceInfo() const;

		/**
		*  @brief
		*    Check if the device is a virtual device
		*
		*  @return
		*    'true', if it is a virtual device, else 'false'
		*/
		PLINPUT_API bool IsVirtual() const;


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void Update();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Process raw keyboard data
		*
		*  @param[in] nMakeCode
		*    Scan code
		*  @param[in] nFlags
		*    Miscellaneous scan code information
		*  @param[in] nReserved
		*    Reserved
		*  @param[in] nKey
		*    Key information
		*  @param[in] nMessage
		*    Message information
		*  @param[in] nExtra
		*    Additional device specific event information
		*/
		PLINPUT_API void ProcessKeyboardData(unsigned short nMakeCode, unsigned short nFlags, unsigned short nReserved,
											 unsigned short nKey, unsigned int nMessage, unsigned long nExtra);

		/**
		*  @brief
		*    Process raw mouse data
		*
		*  @param[in] nFlags
		*    Flags
		*  @param[in] nButtons
		*    Buttons
		*  @param[in] nButtonFlags
		*    Button flags
		*  @param[in] nButtonData
		*    Button data
		*  @param[in] nRawButtons
		*    Raw buttons
		*  @param[in] nLastX
		*    Movement in the X direction (relative or absolute)
		*  @param[in] nLastY
		*    Movement in the Y direction (relative or absolute)
		*  @param[in] nExtra
		*    Additional device specific event information
		*/
		PLINPUT_API void ProcessMouseData(unsigned short nFlags, unsigned long nButtons, unsigned short nButtonFlags,
										  unsigned short nButtonData, long nRawButtons, long nLastX, long nLastY,
										  unsigned long nExtra);

		/**
		*  @brief
		*    Get key for virtual key code
		*
		*  @param[in] pKeyboard
		*    Pointer to keyboard device (must be valid!)
		*  @param[in] nKey
		*    Virtual key code
		*
		*  @return
		*    Corresponding key, NULL if key code is invalid
		*/
		PLINPUT_API Button *GetKeyboardKey(Keyboard *pKeyboard, unsigned short nKey);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Device data
		PLGeneral::String	m_sName;		/**< Device name */
		DWORD				m_nType;		/**< Device type (keyboard, mouse or HID) */
		HANDLE				m_hDevice;		/**< Device handle */
		RID_DEVICE_INFO		m_sDeviceInfo;	/**< Device information struct */
		bool				m_bVirtual;		/**< Virtual device flag */

		// Mouse data
		long				m_nOldX;		/**< X position (if mouse only supports absolute positions) */
		long				m_nOldY;		/**< Y position (if mouse only supports absolute positions) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_RAWINPUTDEVICE_H__
