/*********************************************************\
 *  File: InputManager.h                                 *
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


#ifndef __PLINPUT_INPUTMANAGER_H__
#define __PLINPUT_INPUTMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Core/Singleton.h>
#include <PLCore/Base/Event/Event.h>
#include <PLCore/Container/List.h>
#include <PLCore/Container/HashMap.h>
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Thread;
	class Mutex;
}
namespace PLInput {
	class Provider;
	class Device;
	class Keyboard;
	class Mouse;
	class Control;
	class Controller;
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
*    Input manager
*
*  @remarks
*    The input manager stores all available devices that are present on the computer and
*    controls the update of input messages.
*/
class InputManager : public PLCore::Singleton<InputManager> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLCore::Singleton<InputManager>;
	friend class Provider;
	friend class Control;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<bool>							EventOnDetectDevices;		/**< Called when device detection has started or stopped */
		PLCore::Event<Controller*, PLCore::String>	EventInputControllerFound;	/**< An input controller has been found. Use this event to for instance connect the input controller to real input devices. Found input controller as first parameter, input semantic as second parameter. */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Update input manager once per frame
		*
		*  @remarks
		*    This function must be called once per frame to allow devices to update their status
		*    and to process input messages read from these devices. This is also done to make sure
		*    that input messages are processed synchronously in the main thread, rather than sending
		*    messages from other threads asynchronously.
		*/
		PLINPUT_API void Update();

		/**
		*  @brief
		*    Detect devices
		*
		*  @param[in] bReset
		*    If 'true', delete all input devices and re-detect them all. Otherwise,
		*    only new and removed input devices will be detected.
		*
		*  @remarks
		*    bReset = true should only be used if really necessary, because existing
		*    input handlers will most certainly lose their connection to the device.
		*/
		PLINPUT_API void DetectDevices(bool bReset = false);

		/**
		*  @brief
		*    Get list of input providers
		*
		*  @return
		*    Provider list, do not destroy the returned instances!
		*/
		PLINPUT_API const PLCore::List<Provider*> &GetProviders() const;

		/**
		*  @brief
		*    Get list of detected input providers
		*
		*  @return
		*    Provider list, do not destroy the returned instances!
		*/
		PLINPUT_API PLCore::List<Provider*> &GetProviders();

		/**
		*  @brief
		*    Get a specific input provider
		*
		*  @param[in] sProvider
		*    Name of provider
		*
		*  @return
		*    Provider, or a null pointer if it doesn't exist, do not destroy the returned instance!
		*/
		PLINPUT_API Provider *GetProvider(const PLCore::String &sProvider);

		/**
		*  @brief
		*    Get list of devices
		*
		*  @return
		*    Device list, do not destroy the returned instances!
		*/
		PLINPUT_API PLCore::List<Device*> &GetDevices();

		/**
		*  @brief
		*    Get a specific device
		*
		*  @param[in] sDevice
		*    Name of device
		*
		*  @return
		*    Device, or a null pointer if it doesn't exist, do not destroy the returned instance!
		*/
		PLINPUT_API Device *GetDevice(const PLCore::String &sDevice) const;

		/**
		*  @brief
		*    Get default keyboard device
		*
		*  @return
		*    Default keyboard, can be a null pointer, do not destroy the returned instance!
		*/
		PLINPUT_API Keyboard *GetKeyboard() const;

		/**
		*  @brief
		*    Get default mouse device
		*
		*  @return
		*    Default mouse, can be a null pointer, do not destroy the returned instance!
		*/
		PLINPUT_API Mouse *GetMouse() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		InputManager();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		InputManager(const InputManager &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~InputManager();

		/**
		*  @brief
		*    Destroy all input providers and devices
		*/
		void Clear();

		/**
		*  @brief
		*    Detect devices from a specific provider
		*
		*  @param[in] sProvider
		*    Name of provider
		*  @param[in] bReset
		*    If 'true', delete all input devices and re-detect them all. Otherwise,
		*    only new and removed input devices will be detected.
		*
		*  @remarks
		*    If the provider is already present, it's Detect()-method will be called. Otherwise,
		*    a new instance of the provider will be created, then Detect() will be called as well.
		*/
		void DetectProvider(const PLCore::String &sProvider, bool bReset);

		/**
		*  @brief
		*    Add a new input device
		*
		*  @param[in] pDevice
		*    Input device, shouldn't be a null pointer (but a null pointer is caught internally)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool AddDevice(Device *pDevice);

		/**
		*  @brief
		*    Remove device
		*
		*  @param[in] pDevice
		*    Input device, shouldn't be a null pointer (but a null pointer is caught internally)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool RemoveDevice(Device *pDevice);

		/**
		*  @brief
		*    Remove control
		*
		*  @param[in] pControl
		*    Input control to remove, shouldn't be a null pointer (but a null pointer is caught internally)
		*/
		void RemoveControl(Control *pControl);

		/**
		*  @brief
		*    Update control
		*
		*  @param[in] pControl
		*    Input control, shouldn't be a null pointer (but a null pointer is caught internally)
		*
		*  @remarks
		*    This marks the control as being updated recently, which will fire a message
		*    in the next Update()-call.
		*/
		void UpdateControl(Control *pControl);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Providers and devices
		PLCore::List<Provider*>						 m_lstProviders;		/**< List of providers */
		PLCore::HashMap<PLCore::String, Provider*>	 m_mapProviders;		/**< Hash map of providers */
		PLCore::List<Device*>						 m_lstDevices;			/**< List of devices */
		PLCore::HashMap<PLCore::String, Device*>	 m_mapDevices;			/**< Hash map of devices */
		PLCore::Mutex								*m_pMutex;				/**< Mutex for reading/writing input messages, always valid! */
		PLCore::List<Control*>						 m_lstUpdatedControls;	/**< List of controls that have been updated (message list) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
namespace PLCore {
	PLINPUT_TEMPLATE template class PLINPUT_API Singleton<PLInput::InputManager>;
}


#endif // __PLINPUT_INPUTMANAGER_H__
