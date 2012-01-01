/*********************************************************\
 *  File: AndroidKeyboardDevice.h                        *
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


#ifndef __PLINPUT_ANDROIDKEYBOARDDEVICE_H__
#define __PLINPUT_ANDROIDKEYBOARDDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/UpdateDevice.h"


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
struct AInputEvent;
typedef struct AInputEvent AInputEvent;
namespace PLInput {
	class Button;
	class Keyboard;
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
*    Keyboard implementation for Android
*/
class AndroidKeyboardDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		AndroidKeyboardDevice();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AndroidKeyboardDevice();

		/**
		*  @brief
		*    Call this to process the next key input event
		*
		*  @param[in] cAKeyInputEvent
		*    Key input event to process
		*/
		void OnKeyInputEvent(const struct AInputEvent &cAKeyInputEvent);


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void Update() override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Get key for Android key code
		*
		*  @param[in] cKeyboard
		*    Reference to keyboard device
		*  @param[in] int32_t
		*    Key code
		*
		*  @return
		*    Corresponding key, a null pointer if Android key code is invalid
		*/
		Button *GetKeyboardKey(Keyboard &cKeyboard, int32_t nKeyCode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<int32_t> m_lstProcessedKeys;
		class KeyInfo {
			public:
				int32_t nKeyCode;
				bool    bPressed;
				bool operator ==(const KeyInfo &cSource) { return false; }
		};
		PLCore::Array<KeyInfo> m_lstDelayedKeys;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_ANDROIDKEYBOARDDEVICE_H__
