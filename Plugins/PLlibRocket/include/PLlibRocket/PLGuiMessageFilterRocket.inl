/*********************************************************\
 *  File: PLGuiMessageFilterRocket.inl                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Gui/Base/GuiMessage.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Devices/Keyboard.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLGuiMessageFilterRocket::PLGuiMessageFilterRocket(Rocket::Core::Context &cRocketContext, PLGui::Widget *pTargetWidget) :
	m_pRocketContext(&cRocketContext),
	m_pTargetWidget(pTargetWidget)
{
	// Build the key maps
	BuildKeyMaps();
}

/**
*  @brief
*    Destructor
*/
PLGuiMessageFilterRocket::~PLGuiMessageFilterRocket()
{
}

/**
*  @brief
*    Returns the used libRocket context
*/
Rocket::Core::Context &PLGuiMessageFilterRocket::GetRocketContext() const
{
	return *m_pRocketContext;
}

/**
*  @brief
*    Get message target widget
*/
PLGui::Widget *PLGuiMessageFilterRocket::GetTargetWidget() const
{
	return m_pTargetWidget;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Builds the key maps
*/
void PLGuiMessageFilterRocket::BuildKeyMaps()
{
	// [TODO] Map circumflex
//	#define 	 PLGUIKEY_CIRCUMFLEX		0xDC		// ^ circumflex */

	m_mapKeyIdentifier.Add(0,					Rocket::Core::Input::KI_UNKNOWN);
	m_mapKeyIdentifier.Add(PLGUIKEY_SPACE,		Rocket::Core::Input::KI_SPACE);
	m_mapKeyIdentifier.Add(PLGUIKEY_0,			Rocket::Core::Input::KI_0);
	m_mapKeyIdentifier.Add(PLGUIKEY_1,			Rocket::Core::Input::KI_1);
	m_mapKeyIdentifier.Add(PLGUIKEY_2,			Rocket::Core::Input::KI_2);
	m_mapKeyIdentifier.Add(PLGUIKEY_3,			Rocket::Core::Input::KI_3);
	m_mapKeyIdentifier.Add(PLGUIKEY_4,			Rocket::Core::Input::KI_4);
	m_mapKeyIdentifier.Add(PLGUIKEY_5,			Rocket::Core::Input::KI_5);
	m_mapKeyIdentifier.Add(PLGUIKEY_6,			Rocket::Core::Input::KI_6);
	m_mapKeyIdentifier.Add(PLGUIKEY_7,			Rocket::Core::Input::KI_7);
	m_mapKeyIdentifier.Add(PLGUIKEY_8,			Rocket::Core::Input::KI_8);
	m_mapKeyIdentifier.Add(PLGUIKEY_9,			Rocket::Core::Input::KI_9);
	m_mapKeyIdentifier.Add(PLGUIKEY_A,			Rocket::Core::Input::KI_A);
	m_mapKeyIdentifier.Add(PLGUIKEY_B,			Rocket::Core::Input::KI_B);
	m_mapKeyIdentifier.Add(PLGUIKEY_C,			Rocket::Core::Input::KI_C);
	m_mapKeyIdentifier.Add(PLGUIKEY_D,			Rocket::Core::Input::KI_D);
	m_mapKeyIdentifier.Add(PLGUIKEY_E,			Rocket::Core::Input::KI_E);
	m_mapKeyIdentifier.Add(PLGUIKEY_F,			Rocket::Core::Input::KI_F);
	m_mapKeyIdentifier.Add(PLGUIKEY_G,			Rocket::Core::Input::KI_G);
	m_mapKeyIdentifier.Add(PLGUIKEY_H,			Rocket::Core::Input::KI_H);
	m_mapKeyIdentifier.Add(PLGUIKEY_I,			Rocket::Core::Input::KI_I);
	m_mapKeyIdentifier.Add(PLGUIKEY_J,			Rocket::Core::Input::KI_J);
	m_mapKeyIdentifier.Add(PLGUIKEY_K,			Rocket::Core::Input::KI_K);
	m_mapKeyIdentifier.Add(PLGUIKEY_L,			Rocket::Core::Input::KI_L);
	m_mapKeyIdentifier.Add(PLGUIKEY_M,			Rocket::Core::Input::KI_M);
	m_mapKeyIdentifier.Add(PLGUIKEY_N,			Rocket::Core::Input::KI_N);
	m_mapKeyIdentifier.Add(PLGUIKEY_O,			Rocket::Core::Input::KI_O);
	m_mapKeyIdentifier.Add(PLGUIKEY_P,			Rocket::Core::Input::KI_P);
	m_mapKeyIdentifier.Add(PLGUIKEY_Q,			Rocket::Core::Input::KI_Q);
	m_mapKeyIdentifier.Add(PLGUIKEY_R,			Rocket::Core::Input::KI_R);
	m_mapKeyIdentifier.Add(PLGUIKEY_S,			Rocket::Core::Input::KI_S);
	m_mapKeyIdentifier.Add(PLGUIKEY_T,			Rocket::Core::Input::KI_T);
	m_mapKeyIdentifier.Add(PLGUIKEY_U,			Rocket::Core::Input::KI_U);
	m_mapKeyIdentifier.Add(PLGUIKEY_V,			Rocket::Core::Input::KI_V);
	m_mapKeyIdentifier.Add(PLGUIKEY_W,			Rocket::Core::Input::KI_W);
	m_mapKeyIdentifier.Add(PLGUIKEY_X,			Rocket::Core::Input::KI_X);
	m_mapKeyIdentifier.Add(PLGUIKEY_Y,			Rocket::Core::Input::KI_Y);
	m_mapKeyIdentifier.Add(PLGUIKEY_Z,			Rocket::Core::Input::KI_Z);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_1);				// US standard keyboard; the ';:' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_PLUS);			// Any region; the '=+' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_COMMA);			// Any region; the ',<' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_MINUS);			// Any region; the '-_' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_PERIOD);		// Any region; the '.>' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_2);				// Any region; the '/?' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_3);				// Any region; the '`~' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_4);				// US standard keyboard; the '[{' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_5);				// US standard keyboard; the '\|' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_6);				// US standard keyboard; the ']}' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_7);				// US standard keyboard; the ''"' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_8);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_102);			// RT 102-key keyboard; the '<>' or '\|' key
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD0,	Rocket::Core::Input::KI_NUMPAD0);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD1,	Rocket::Core::Input::KI_NUMPAD1);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD2,	Rocket::Core::Input::KI_NUMPAD2);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD3,	Rocket::Core::Input::KI_NUMPAD3);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD4,	Rocket::Core::Input::KI_NUMPAD4);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD5,	Rocket::Core::Input::KI_NUMPAD5);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD6,	Rocket::Core::Input::KI_NUMPAD6);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD7,	Rocket::Core::Input::KI_NUMPAD7);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD8,	Rocket::Core::Input::KI_NUMPAD8);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMPAD9,	Rocket::Core::Input::KI_NUMPAD9);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_NUMPADENTER);
	m_mapKeyIdentifier.Add(PLGUIKEY_MULTIPLY,	Rocket::Core::Input::KI_MULTIPLY);			// Asterisk on the numeric keypad
	m_mapKeyIdentifier.Add(PLGUIKEY_ADD,		Rocket::Core::Input::KI_ADD);				// Plus on the numeric keypad
	m_mapKeyIdentifier.Add(PLGUIKEY_SEPARATOR,	Rocket::Core::Input::KI_SEPARATOR);
	m_mapKeyIdentifier.Add(PLGUIKEY_SUBTRACT,	Rocket::Core::Input::KI_SUBTRACT);			// Minus on the numeric keypad
	m_mapKeyIdentifier.Add(PLGUIKEY_DECIMAL,	Rocket::Core::Input::KI_DECIMAL);			// Period on the numeric keypad
	m_mapKeyIdentifier.Add(PLGUIKEY_DIVIDE,		Rocket::Core::Input::KI_DIVIDE);			// Forward Slash on the numeric keypad
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_NEC_EQUAL);		// Equals key on the numeric keypad
	m_mapKeyIdentifier.Add(PLGUIKEY_BACK,		Rocket::Core::Input::KI_BACK);				// Backspace key
	m_mapKeyIdentifier.Add(PLGUIKEY_TAB,		Rocket::Core::Input::KI_TAB);				// Tab key
	m_mapKeyIdentifier.Add(PLGUIKEY_CLEAR,		Rocket::Core::Input::KI_CLEAR);
	m_mapKeyIdentifier.Add(PLGUIKEY_RETURN,		Rocket::Core::Input::KI_RETURN);
	m_mapKeyIdentifier.Add(PLGUIKEY_PAUSE,		Rocket::Core::Input::KI_PAUSE);
	m_mapKeyIdentifier.Add(PLGUIKEY_CAPITAL,	Rocket::Core::Input::KI_CAPITAL);			// Caps-lock key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_KANA);				// IME Kana mode
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_HANGUL);			// IME Hangul mode
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_JUNJA);				// IME Junja mode
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_FINAL);				// IME final mode
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_HANJA);				// IME Hanja mode
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_KANJI);				// IME Kanji mode
	m_mapKeyIdentifier.Add(PLGUIKEY_ESCAPE,		Rocket::Core::Input::KI_ESCAPE);			// Escape key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_CONVERT);			// IME convert
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_NONCONVERT);		// IME nonconvert
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ACCEPT);			// IME accept
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_MODECHANGE);		// IME mode change request
	m_mapKeyIdentifier.Add(PLGUIKEY_PRIOR,		Rocket::Core::Input::KI_PRIOR);				// Page Up key
	m_mapKeyIdentifier.Add(PLGUIKEY_NEXT,		Rocket::Core::Input::KI_NEXT);				// Page Down key
	m_mapKeyIdentifier.Add(PLGUIKEY_END,		Rocket::Core::Input::KI_END);
	m_mapKeyIdentifier.Add(PLGUIKEY_HOME,		Rocket::Core::Input::KI_HOME);
	m_mapKeyIdentifier.Add(PLGUIKEY_LEFT,		Rocket::Core::Input::KI_LEFT);				// Left Arrow key
	m_mapKeyIdentifier.Add(PLGUIKEY_UP,			Rocket::Core::Input::KI_UP);				// Up Arrow key
	m_mapKeyIdentifier.Add(PLGUIKEY_RIGHT,		Rocket::Core::Input::KI_RIGHT);				// Right Arrow key
	m_mapKeyIdentifier.Add(PLGUIKEY_DOWN,		Rocket::Core::Input::KI_DOWN);				// Down Arrow key
	m_mapKeyIdentifier.Add(PLGUIKEY_SELECT,		Rocket::Core::Input::KI_SELECT);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_PRINT);
	m_mapKeyIdentifier.Add(PLGUIKEY_EXECUTE,	Rocket::Core::Input::KI_EXECUTE);
	m_mapKeyIdentifier.Add(PLGUIKEY_SNAPSHOT,	Rocket::Core::Input::KI_SNAPSHOT);			// Print Screen key
	m_mapKeyIdentifier.Add(PLGUIKEY_INSERT,		Rocket::Core::Input::KI_INSERT);
	m_mapKeyIdentifier.Add(PLGUIKEY_DELETE,		Rocket::Core::Input::KI_DELETE);
	m_mapKeyIdentifier.Add(PLGUIKEY_HELP,		Rocket::Core::Input::KI_HELP);
	m_mapKeyIdentifier.Add(PLGUIMOD_WIN,		Rocket::Core::Input::KI_LWIN);				// Left Windows key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_RWIN);				// Right Windows key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_APPS);				// Applications key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_POWER);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_SLEEP);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_WAKE);
	m_mapKeyIdentifier.Add(PLGUIKEY_F1,			Rocket::Core::Input::KI_F1);
	m_mapKeyIdentifier.Add(PLGUIKEY_F2,			Rocket::Core::Input::KI_F2);
	m_mapKeyIdentifier.Add(PLGUIKEY_F3,			Rocket::Core::Input::KI_F3);
	m_mapKeyIdentifier.Add(PLGUIKEY_F4,			Rocket::Core::Input::KI_F4);
	m_mapKeyIdentifier.Add(PLGUIKEY_F5,			Rocket::Core::Input::KI_F5);
	m_mapKeyIdentifier.Add(PLGUIKEY_F6,			Rocket::Core::Input::KI_F6);
	m_mapKeyIdentifier.Add(PLGUIKEY_F7,			Rocket::Core::Input::KI_F7);
	m_mapKeyIdentifier.Add(PLGUIKEY_F8,			Rocket::Core::Input::KI_F8);
	m_mapKeyIdentifier.Add(PLGUIKEY_F9,			Rocket::Core::Input::KI_F9);
	m_mapKeyIdentifier.Add(PLGUIKEY_F10,		Rocket::Core::Input::KI_F10);
	m_mapKeyIdentifier.Add(PLGUIKEY_F11,		Rocket::Core::Input::KI_F11);
	m_mapKeyIdentifier.Add(PLGUIKEY_F12,		Rocket::Core::Input::KI_F12);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F13);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F14);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F15);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F16);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F17);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F18);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F19);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F20);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F21);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F22);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F23);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_F24);
	m_mapKeyIdentifier.Add(PLGUIKEY_NUMLOCK,	Rocket::Core::Input::KI_NUMLOCK);			// Numlock key
	m_mapKeyIdentifier.Add(PLGUIKEY_SCROLL,		Rocket::Core::Input::KI_SCROLL);			// Scroll Lock key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_FJ_JISHO);		// 'Dictionary' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_FJ_MASSHOU);	// 'Unregister word' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_FJ_TOUROKU);	// 'Register word' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_FJ_LOYA);		// 'Left OYAYUBI' key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_FJ_ROYA);		// 'Right OYAYUBI' key
	m_mapKeyIdentifier.Add(PLGUIKEY_SHIFT,		Rocket::Core::Input::KI_LSHIFT);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_RSHIFT);
	m_mapKeyIdentifier.Add(PLGUIKEY_CONTROL,	Rocket::Core::Input::KI_LCONTROL);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_RCONTROL);
	m_mapKeyIdentifier.Add(PLGUIKEY_MENU,		Rocket::Core::Input::KI_LMENU);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_RMENU);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_BACK);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_FORWARD);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_REFRESH);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_STOP);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_SEARCH);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_FAVORITES);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_BROWSER_HOME);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_VOLUME_MUTE);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_VOLUME_DOWN);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_VOLUME_UP);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_MEDIA_NEXT_TRACK);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_MEDIA_PREV_TRACK);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_MEDIA_STOP);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_MEDIA_PLAY_PAUSE);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_LAUNCH_MAIL);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_LAUNCH_MEDIA_SELECT);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_LAUNCH_APP1);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_LAUNCH_APP2);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_AX);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ICO_HELP);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ICO_00);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_PROCESSKEY);		// IME Process key
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ICO_CLEAR);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ATTN);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_CRSEL);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_EXSEL);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_EREOF);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_PLAY);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_ZOOM);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_PA1);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_OEM_CLEAR);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_LMETA);
//	m_mapKeyIdentifier.Add(?,					Rocket::Core::Input::KI_RMETA);
}

/**
*  @brief
*    Gets the libRocket key modifier state
*/
int PLGuiMessageFilterRocket::GetRocketKeyModifierState() const
{
	int nRocketModifierState = 0;

	// Get keyboard input device
	PLInput::Keyboard *pKeyboard = PLInput::InputManager::GetInstance()->GetKeyboard();
	if (pKeyboard) {
		if (pKeyboard->Control.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_CTRL;
		if (pKeyboard->Shift.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_SHIFT;
		if (pKeyboard->Alt.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_ALT;
		if (pKeyboard->CapsLock.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_CAPSLOCK;
		if (pKeyboard->NumLock.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_NUMLOCK;
		if (pKeyboard->ScrollLock.IsPressed())
			nRocketModifierState |= Rocket::Core::Input::KM_SCROLLLOCK;
	}

	// Return the modifier state
	return nRocketModifierState;
}


//[-------------------------------------------------------]
//[ Protected virtual PLGui::MessageFilter functions      ]
//[-------------------------------------------------------]
void PLGuiMessageFilterRocket::OnGuiMessage(const PLGui::GuiMessage &cMessage)
{
	// Send messages from all widgets to libRocket or just messages from a certain widget?
	if (!m_pTargetWidget || m_pTargetWidget == cMessage.GetWidget()) {
		// Check message type
		switch (cMessage.GetType()) {
			case PLGui::MessageOnMouseMove:
				m_pRocketContext->ProcessMouseMove(cMessage.GetPosSize().x, cMessage.GetPosSize().y, GetRocketKeyModifierState());
				break;

			case PLGui::MessageOnMouseButtonDown:
				// First "ProcessMouseButtonDown()"-parameter: 0 for the left button, 1 for right, and any others from 2 onwards... so we able to directly map this value to "PLGui::EMouseButton"
				m_pRocketContext->ProcessMouseButtonDown(cMessage.GetMouseButton(), GetRocketKeyModifierState());
				break;

			case PLGui::MessageOnMouseButtonUp:
				// First "ProcessMouseButtonDown()"-parameter: 0 for the left button, 1 for right, and any others from 2 onwards... so we able to directly map this value to "PLGui::EMouseButton"
				m_pRocketContext->ProcessMouseButtonUp(cMessage.GetMouseButton(), GetRocketKeyModifierState());
				break;

			case PLGui::MessageOnMouseWheel:
				m_pRocketContext->ProcessMouseWheel(cMessage.GetDelta(), GetRocketKeyModifierState());
				break;

			case PLGui::MessageOnKeyDown:
			{
				Rocket::Core::Input::KeyIdentifier nKeyIdentifier = m_mapKeyIdentifier.Get(cMessage.GetKey());

				if (nKeyIdentifier != Rocket::Core::Input::KI_UNKNOWN)
					m_pRocketContext->ProcessKeyDown(nKeyIdentifier, GetRocketKeyModifierState());

				// Send through the ASCII value as text input if it is printable
				if (cMessage.GetKey() >= 32)
					m_pRocketContext->ProcessTextInput(static_cast<Rocket::Core::word>(cMessage.GetKey()));
				else if (nKeyIdentifier == Rocket::Core::Input::KI_RETURN)
					m_pRocketContext->ProcessTextInput(static_cast<Rocket::Core::word>('\n'));
				break;
			}

			case PLGui::MessageOnKeyUp:
			{
				Rocket::Core::Input::KeyIdentifier nKeyIdentifier = m_mapKeyIdentifier.Get(cMessage.GetKey());
				if (nKeyIdentifier != Rocket::Core::Input::KI_UNKNOWN)
					m_pRocketContext->ProcessKeyUp(nKeyIdentifier, GetRocketKeyModifierState());
				break;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLlibRocket
