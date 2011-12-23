/*********************************************************\
 *  File: RawInput2.h                                    *
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


#ifndef __PLINPUT_RAWINPUT_H__
#define __PLINPUT_RAWINPUT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/System/Thread.h>
#include <PLCore/Core/Singleton.h>
#include <PLCore/Container/List.h>
#include <PLCore/Container/HashMap.h>
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Wrapper for the Raw-Input API on Windows
*/
class RawInput : public PLCore::Singleton<RawInput> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLCore::Singleton<RawInput>;


	//[-------------------------------------------------------]
	//[ Public static PLCore::Singleton functions             ]
	//[-------------------------------------------------------]
	// This solution enhances the compatibility with legacy compilers like GCC 4.2.1 used on Mac OS X 10.6
	// -> The C++11 feature "extern template" (C++11, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates) can only be used on modern compilers like GCC 4.6
	// -> We can't break legacy compiler support, especially when only the singletons are responsible for the break
	// -> See PLCore::Singleton for more details about singletons
	public:
		PLINPUT_API static RawInput *GetInstance();
		PLINPUT_API static bool HasInstance();


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
		PLINPUT_API const PLCore::List<RawInputDevice*> &GetDevices() const;


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
		WNDCLASS											m_cWndClass;		/**< Window class */
		HWND												m_hWnd;				/**< Window that will receive input messages */
		PLCore::Thread										m_cThread;			/**< Raw-Input thread */
		bool												m_bThreadFinished;	/**< Finished-flag for thread */

		// Raw-Input devices
		PLCore::List<RawInputDevice*>						m_lstDevices;		/**< List of input devices */
		PLCore::HashMap<PLCore::uint32, RawInputDevice*>	m_mapDevices;		/**< Hash map: HANDLE -> Raw-Input device */
		RawInputDevice									   *m_pDeviceKeyboard;	/**< Virtual keyboard device (all events from all keyboards) */
		RawInputDevice									   *m_pDeviceMouse;		/**< Virtual mouse device (all events from all mice) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_RAWINPUT_H__
