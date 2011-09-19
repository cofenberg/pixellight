/*********************************************************\
 *  File: AndroidKeyboardDevice.cpp                      *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <android/input.h>
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Backend/Android/AndroidKeyboardDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AndroidKeyboardDevice::AndroidKeyboardDevice()
{
	// Destroy device implementation automatically
	m_bDelete = true;
}

/**
*  @brief
*    Destructor
*/
AndroidKeyboardDevice::~AndroidKeyboardDevice()
{
}

/**
*  @brief
*    Call this to process the next key input event
*/
void AndroidKeyboardDevice::OnKeyInputEvent(const struct AInputEvent &cAKeyInputEvent)
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get Android key code
		const int32_t nKeyCode = AKeyEvent_getKeyCode(&cAKeyInputEvent);

		// Lookout! The virtual keyboard of Android sends "down" and "up" directly one after another
		// -> This is really a problem and we have to delay further keys...
		if (m_lstProcessedKeys.IsElement(nKeyCode)) {
			// Add key for later processing
			KeyInfo sKeyInfo;
			sKeyInfo.nKeyCode = nKeyCode;
			sKeyInfo.bPressed = (AKeyEvent_getAction(&cAKeyInputEvent) == AKEY_EVENT_ACTION_DOWN);
			m_lstDelayedKeys.Add(sKeyInfo);
		} else {
			// Get keyboard device
			Keyboard *pKeyboard = static_cast<Keyboard*>(m_pDevice);

			// Get button
			Button *pButton = GetKeyboardKey(*pKeyboard, nKeyCode);
			if (pButton) {
				// Get button state
				const bool bPressed = (AKeyEvent_getAction(&cAKeyInputEvent) == AKEY_EVENT_ACTION_DOWN);

				// Propagate changes
				if (pButton->IsPressed() != bPressed)
					pButton->SetPressed(bPressed);
			}

			// Add this key to the processed keys
			m_lstProcessedKeys.Add(nKeyCode);
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void AndroidKeyboardDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get keyboard device
		Keyboard *pKeyboard = static_cast<Keyboard*>(m_pDevice);

		// Process delayed keys
		for (uint32 i=0; i<m_lstDelayedKeys.GetNumOfElements(); i++) {
			const KeyInfo &sKeyInfo = m_lstDelayedKeys[i];

			// Get button
			Button *pButton = GetKeyboardKey(*pKeyboard, sKeyInfo.nKeyCode);
			if (pButton) {
				// Get button state
				const bool bPressed = sKeyInfo.bPressed;

				// Propagate changes
				if (pButton->IsPressed() != bPressed)
					pButton->SetPressed(bPressed);
			}
		}
		m_lstDelayedKeys.Clear();
		m_lstProcessedKeys.Clear();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get key for Android key code
*/
Button *AndroidKeyboardDevice::GetKeyboardKey(Keyboard &cKeyboard, int32_t nKeyCode)
{
	// Return key that corresponds to the given Android key code
	switch (nKeyCode) {
		// AKEYCODE_SOFT_LEFT			-> ignored
		// AKEYCODE_SOFT_RIGHT			-> ignored
		case AKEYCODE_HOME:				return &cKeyboard.KeyHome;
		case AKEYCODE_BACK:				return &cKeyboard.KeyBack;
		// AKEYCODE_CALL				-> ignored
		// AKEYCODE_ENDCAL				-> ignored
		case AKEYCODE_0:				return &cKeyboard.Key0;
		case AKEYCODE_1:				return &cKeyboard.Key1;
		case AKEYCODE_2:				return &cKeyboard.Key2;
		case AKEYCODE_3:				return &cKeyboard.Key3;
		case AKEYCODE_4:				return &cKeyboard.Key4;
		case AKEYCODE_5:				return &cKeyboard.Key5;
		case AKEYCODE_6:				return &cKeyboard.Key6;
		case AKEYCODE_7:				return &cKeyboard.Key7;
		case AKEYCODE_8:				return &cKeyboard.Key8;
		case AKEYCODE_9:				return &cKeyboard.Key9;
		// AKEYCODE_STAR				-> ignored
		// AKEYCODE_POUND				-> ignored
		case AKEYCODE_DPAD_UP:			return &cKeyboard.KeyUp;
		case AKEYCODE_DPAD_DOWN:		return &cKeyboard.KeyDown;
		case AKEYCODE_DPAD_LEFT:		return &cKeyboard.KeyLeft;
		case AKEYCODE_DPAD_RIGHT:		return &cKeyboard.KeyRight;
		// AKEYCODE_DPAD_CENTER			-> ignored
		// AKEYCODE_VOLUME_UP			-> ignored
		// AKEYCODE_VOLUME_DOWN			-> ignored
		// AKEYCODE_POWER				-> ignored
		// AKEYCODE_CAMERA				-> ignored
		case AKEYCODE_CLEAR:			return &cKeyboard.KeyClear;
		case AKEYCODE_A:				return &cKeyboard.KeyA;
		case AKEYCODE_B:				return &cKeyboard.KeyB;
		case AKEYCODE_C:				return &cKeyboard.KeyC;
		case AKEYCODE_D:				return &cKeyboard.KeyD;
		case AKEYCODE_E:				return &cKeyboard.KeyE;
		case AKEYCODE_F:				return &cKeyboard.KeyF;
		case AKEYCODE_G:				return &cKeyboard.KeyG;
		case AKEYCODE_H:				return &cKeyboard.KeyH;
		case AKEYCODE_I:				return &cKeyboard.KeyI;
		case AKEYCODE_J:				return &cKeyboard.KeyJ;
		case AKEYCODE_K:				return &cKeyboard.KeyK;
		case AKEYCODE_L:				return &cKeyboard.KeyL;
		case AKEYCODE_M:				return &cKeyboard.KeyM;
		case AKEYCODE_N:				return &cKeyboard.KeyN;
		case AKEYCODE_O:				return &cKeyboard.KeyO;
		case AKEYCODE_P:				return &cKeyboard.KeyP;
		case AKEYCODE_Q:				return &cKeyboard.KeyQ;
		case AKEYCODE_R:				return &cKeyboard.KeyR;
		case AKEYCODE_S:				return &cKeyboard.KeyS;
		case AKEYCODE_T:				return &cKeyboard.KeyT;
		case AKEYCODE_U:				return &cKeyboard.KeyU;
		case AKEYCODE_V:				return &cKeyboard.KeyV;
		case AKEYCODE_W:				return &cKeyboard.KeyW;
		case AKEYCODE_X:				return &cKeyboard.KeyX;
		case AKEYCODE_Y:				return &cKeyboard.KeyY;
		case AKEYCODE_Z:				return &cKeyboard.KeyZ;
		// AKEYCODE_COMMA				-> ignored
		// AKEYCODE_PERIOD				-> ignored
		case AKEYCODE_ALT_LEFT:			return &cKeyboard.KeyAlt;
		case AKEYCODE_ALT_RIGHT:		return &cKeyboard.KeyControl;
		case AKEYCODE_SHIFT_LEFT:		return &cKeyboard.KeyShift;
		// AKEYCODE_SHIFT_RIGHT			-> ignored
		case AKEYCODE_TAB:				return &cKeyboard.KeyTab;
		case AKEYCODE_SPACE:			return &cKeyboard.KeySpace;
		// AKEYCODE_SYM					-> ignored
		// AKEYCODE_EXPLORER			-> ignored
		// AKEYCODE_ENVELOPE			-> ignored
		case AKEYCODE_ENTER:			return &cKeyboard.KeyReturn;
		case AKEYCODE_DEL:				return &cKeyboard.KeyDelete;
		// AKEYCODE_GRAVE				-> ignored
		case AKEYCODE_MINUS:			return &cKeyboard.KeyNumpadSubtract;
		// AKEYCODE_EQUALS				-> ignored
		// AKEYCODE_LEFT_BRACKET		-> ignored
		// AKEYCODE_RIGHT_BRACKET		-> ignored
		// AKEYCODE_BACKSLASH			-> ignored
		// AKEYCODE_SEMICOLON			-> ignored
		// AKEYCODE_APOSTROPHE			-> ignored
		// AKEYCODE_SLASH				-> ignored
		// AKEYCODE_AT					-> ignored
		// AKEYCODE_NUM					-> ignored
		// AKEYCODE_HEADSETHOOK			-> ignored
		// AKEYCODE_FOCUS				-> ignored
		case AKEYCODE_PLUS:				return &cKeyboard.KeyNumpadAdd;
		// AKEYCODE_MENU				-> ignored
		// AKEYCODE_NOTIFICATION		-> ignored
		// AKEYCODE_SEARCH				-> ignored
		case AKEYCODE_MEDIA_PLAY_PAUSE:	return &cKeyboard.KeyPause;
		// AKEYCODE_MEDIA_STOP			-> ignored
		// AKEYCODE_MEDIA_NEXT			-> ignored
		// AKEYCODE_MEDIA_PREVIOUS		-> ignored
		// AKEYCODE_MEDIA_REWIND		-> ignored
		// AKEYCODE_MEDIA_FAST_FORWARD	-> ignored
		// AKEYCODE_MUTE				-> ignored
		case AKEYCODE_PAGE_UP:			return &cKeyboard.KeyPageUp;
		case AKEYCODE_PAGE_DOWN:		return &cKeyboard.KeyPageDown;
		// AKEYCODE_PICTSYMBOLS			-> ignored
		// AKEYCODE_SWITCH_CHARSET		-> ignored
		case AKEYCODE_BUTTON_A:			return &cKeyboard.KeyA;
		case AKEYCODE_BUTTON_B:			return &cKeyboard.KeyB;
		case AKEYCODE_BUTTON_C:			return &cKeyboard.KeyC;
		case AKEYCODE_BUTTON_X:			return &cKeyboard.KeyX;
		case AKEYCODE_BUTTON_Y:			return &cKeyboard.KeyY;
		case AKEYCODE_BUTTON_Z:			return &cKeyboard.KeyZ;
		// AKEYCODE_BUTTON_L1			-> ignored
		// AKEYCODE_BUTTON_R1			-> ignored
		// AKEYCODE_BUTTON_L2			-> ignored
		// AKEYCODE_BUTTON_R2			-> ignored
		// AKEYCODE_BUTTON_THUMBL		-> ignored
		// AKEYCODE_BUTTON_THUMBR		-> ignored
		// AKEYCODE_BUTTON_START		-> ignored
		case AKEYCODE_BUTTON_SELECT:	return &cKeyboard.KeySelect;
		// AKEYCODE_BUTTON_MODE			-> ignored
		default:						return nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
