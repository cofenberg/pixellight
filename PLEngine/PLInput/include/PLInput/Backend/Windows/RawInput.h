/*********************************************************\
 *  File: RawInput2.h                                    *
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


#ifndef __PLINPUT_RAWINPUT_H__
#define __PLINPUT_RAWINPUT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Singleton.h>
#include <PLGeneral/Container/List.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLGeneral/System/Thread.h>
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class RawInput;
class RawInputDevice;


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
PLINPUT_TEMPLATE template class PLINPUT_API PLGeneral::Singleton<RawInput>;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Wrapper for the Raw-Input API on Windows
*/
class RawInput : public PLGeneral::Singleton<RawInput> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLGeneral::Singleton<RawInput>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Remove all devices
		*/
		PLINPUT_API void Clear();

		/**
		*  @brief
		*    Detect available Raw-Input devices
		*/
		PLINPUT_API void DetectDevices();

		/**
		*  @brief
		*    Get list of available input devices
		*
		*  @return
		*    Device list
		*
		*  @remarks
		*    There are two virtual devices:
		*    The virtual keyboard device named "Keyboard" catches all events from all keyboard devices.
		*    The virtual mouse device named "Mouse" catches all events from all mouse devices.
		*    All other devices represent real devices and have names given from Windows.
		*/
		PLINPUT_API const PLGeneral::List<RawInputDevice*> &GetDevices() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		RawInput();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RawInput();

		/**
		*  @brief
		*    Raw-Input message processing
		*
		*  @param[in] nMsg
		*    Received message
		*  @param[in] wParam
		*    First parameter of the received message
		*  @param[in] lParam
		*    Second parameter of the received message
		*
		*  @return
		*    Error code, 0 = success
		*/
		LRESULT ProcessRawInput(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Window callback function
		*
		*  @param[in] hWnd
		*    Window the message came from
		*  @param[in] nMsg
		*    Received message
		*  @param[in] wParam
		*    First parameter of the received message
		*  @param[in] lParam
		*    Second parameter of the received message
		*
		*  @return
		*    Error code, 0 = success
		*/
		static LRESULT WINAPI WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

		/**
		*  @brief
		*    Thread for reading raw-input messages constantly
		*
		*  @param[in] pData
		*    User parameter, containing a pointer to the RawInput-Object
		*
		*  @return
		*    Error code, 0 = success
		*/
		static int RawInputThread(void *pData);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Raw-Input system
		WNDCLASS												m_cWndClass;		/**< Window class */
		HWND													m_hWnd;				/**< Window that will receive input messages */
		PLGeneral::Thread										m_cThread;			/**< Raw-Input thread */
		bool													m_bThreadFinished;	/**< Finished-flag for thread */

		// Raw-Input devices
		PLGeneral::List<RawInputDevice*>						m_lstDevices;		/**< List of input devices */
		PLGeneral::HashMap<PLGeneral::uint32, RawInputDevice*>	m_mapDevices;		/**< Hash map: HANDLE -> Raw-Input device */
		RawInputDevice										   *m_pDeviceKeyboard;	/**< Virtual keyboard device (all events from all keyboards) */
		RawInputDevice										   *m_pDeviceMouse;		/**< Virtual mouse device (all events from all mice) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_RAWINPUT_H__
