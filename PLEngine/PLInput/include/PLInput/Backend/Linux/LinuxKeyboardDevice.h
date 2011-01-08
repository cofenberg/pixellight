/*********************************************************\
 *  File: LinuxKeyboardDevice.h                          *
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


#ifndef __PLINPUT_LINUXKEYBOARDDEVICE_H__
#define __PLINPUT_LINUXKEYBOARDDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/PLInputLinuxIncludes.h"
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
*    Keyboard implementation for Linux
*/
class LinuxKeyboardDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pDisplay
		*    Display connection
		*/
		LinuxKeyboardDevice(::Display *pDisplay);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~LinuxKeyboardDevice();


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void Update();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Get currently pressed modifier keys
		*/
		int GetKeyModifiers();

		/**
		*  @brief
		*    Map key code to X symbolic key
		*
		*  @param[in] nKeyCode
		*    Key code
		*  @param[in] nModifier
		*    Currently pressed modifier
		*
		*  @return
		*    Symbolic key
		*/
		int MapKeyCodeToSymKey(int nKeyCode, int nModifier);

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
		*    Corresponding key, a null pointer if key code is invalid
		*/
		Button *GetKeyboardKey(Keyboard *pKeyboard, int nKey);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		::Display			*m_pDisplay;		/**< X server display connection */
		::XModifierKeymap	*m_pModifierMap;	/**< Modifier key map */
		char	   			 m_nKeys[32];		/**< State of all keys */



};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_LINUXKEYBOARDDEVICE_H__
