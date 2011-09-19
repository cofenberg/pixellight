/*********************************************************\
 *  File: GuiAndroid.cpp                                 *
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
#include <PLCore/System/SystemAndroid.h>
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Base/Keys.h"
#include "PLGui/Gui/Base/GuiMessage.h"
#include "PLGui/Backend/Android/GuiAndroid.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiAndroid::GuiAndroid(Gui *pGui) : GuiNull(pGui),
	SlotInputEvent(&GuiAndroid::OnInputEvent, this),
 	m_bLeftMouseButton(false)
{
	// Connect the Android input event handler
	SystemAndroid::EventInputEvent.Connect(SlotInputEvent);
}

/**
*  @brief
*    Destructor
*/
GuiAndroid::~GuiAndroid()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called to process the next Android input event
*/
void GuiAndroid::OnInputEvent(const struct AInputEvent &cAInputEvent)
{
	// Check the input event type
	switch (AInputEvent_getType(&cAInputEvent)) {
		// Key (e.g. from the soft keyboard)
		case AINPUT_EVENT_TYPE_KEY:
			OnKeyInputEvent(cAInputEvent);
			break;

		// Motion (e.g. from the touchscreen)
		case AINPUT_EVENT_TYPE_MOTION:
			OnMotionInputEvent(cAInputEvent);
			break;
	}
}

/**
*  @brief
*    Call this to process the next key input event
*/
void GuiAndroid::OnKeyInputEvent(const struct AInputEvent &cAKeyInputEvent)
{
	// Get PLGui key code
	const uint32 nKeyCode = GetKeyboardKey(AKeyEvent_getKeyCode(&cAKeyInputEvent));
	if (nKeyCode) {
		// Get the meta key state of the Android key
		const int32_t nAndroidMetaState = AKeyEvent_getMetaState(&cAKeyInputEvent);

		// Get state of modifier keys
		uint32 nModifiers = 0;
		if (nAndroidMetaState & AMETA_ALT_ON)
			nModifiers |= PLGUIMOD_ALT;
		if (nAndroidMetaState & AMETA_SHIFT_ON)
			nModifiers |= PLGUIMOD_SHIFT;

		// Send OnKeyDown/OnKeyUp message
		if (AKeyEvent_getAction(&cAKeyInputEvent) == AKEY_EVENT_ACTION_DOWN)
			m_pGui->SendMessage(GuiMessage::OnKeyDown(m_pGui->GetRootWidget(), nKeyCode, nModifiers));
		else
			m_pGui->SendMessage(GuiMessage::OnKeyUp(m_pGui->GetRootWidget(), nKeyCode, nModifiers));
	}
}

/**
*  @brief
*    Get PLGui key for Android key code
*/
uint32 GuiAndroid::GetKeyboardKey(int32_t nKeyCode)
{
	// Return key that corresponds to the given Android key code
	switch (nKeyCode) {
		// AKEYCODE_SOFT_LEFT			-> ignored
		// AKEYCODE_SOFT_RIGHT			-> ignored
		case AKEYCODE_HOME:				return PLGUIKEY_HOME;
		case AKEYCODE_BACK:				return PLGUIKEY_BACK;
		// AKEYCODE_CALL				-> ignored
		// AKEYCODE_ENDCAL				-> ignored
		case AKEYCODE_0:				return PLGUIKEY_0;
		case AKEYCODE_1:				return PLGUIKEY_1;
		case AKEYCODE_2:				return PLGUIKEY_2;
		case AKEYCODE_3:				return PLGUIKEY_3;
		case AKEYCODE_4:				return PLGUIKEY_4;
		case AKEYCODE_5:				return PLGUIKEY_5;
		case AKEYCODE_6:				return PLGUIKEY_6;
		case AKEYCODE_7:				return PLGUIKEY_7;
		case AKEYCODE_8:				return PLGUIKEY_8;
		case AKEYCODE_9:				return PLGUIKEY_9;
		// AKEYCODE_STAR				-> ignored
		// AKEYCODE_POUND				-> ignored
		case AKEYCODE_DPAD_UP:			return PLGUIKEY_UP;
		case AKEYCODE_DPAD_DOWN:		return PLGUIKEY_DOWN;
		case AKEYCODE_DPAD_LEFT:		return PLGUIKEY_LEFT;
		case AKEYCODE_DPAD_RIGHT:		return PLGUIKEY_RIGHT;
		// AKEYCODE_DPAD_CENTER			-> ignored
		// AKEYCODE_VOLUME_UP			-> ignored
		// AKEYCODE_VOLUME_DOWN			-> ignored
		// AKEYCODE_POWER				-> ignored
		// AKEYCODE_CAMERA				-> ignored
		case AKEYCODE_CLEAR:			return PLGUIKEY_CLEAR;
		case AKEYCODE_A:				return PLGUIKEY_A;
		case AKEYCODE_B:				return PLGUIKEY_B;
		case AKEYCODE_C:				return PLGUIKEY_C;
		case AKEYCODE_D:				return PLGUIKEY_D;
		case AKEYCODE_E:				return PLGUIKEY_E;
		case AKEYCODE_F:				return PLGUIKEY_F;
		case AKEYCODE_G:				return PLGUIKEY_G;
		case AKEYCODE_H:				return PLGUIKEY_H;
		case AKEYCODE_I:				return PLGUIKEY_I;
		case AKEYCODE_J:				return PLGUIKEY_J;
		case AKEYCODE_K:				return PLGUIKEY_K;
		case AKEYCODE_L:				return PLGUIKEY_L;
		case AKEYCODE_M:				return PLGUIKEY_M;
		case AKEYCODE_N:				return PLGUIKEY_N;
		case AKEYCODE_O:				return PLGUIKEY_O;
		case AKEYCODE_P:				return PLGUIKEY_P;
		case AKEYCODE_Q:				return PLGUIKEY_Q;
		case AKEYCODE_R:				return PLGUIKEY_R;
		case AKEYCODE_S:				return PLGUIKEY_S;
		case AKEYCODE_T:				return PLGUIKEY_T;
		case AKEYCODE_U:				return PLGUIKEY_U;
		case AKEYCODE_V:				return PLGUIKEY_V;
		case AKEYCODE_W:				return PLGUIKEY_W;
		case AKEYCODE_X:				return PLGUIKEY_X;
		case AKEYCODE_Y:				return PLGUIKEY_Y;
		case AKEYCODE_Z:				return PLGUIKEY_Z;
		// AKEYCODE_COMMA				-> ignored
		// AKEYCODE_PERIOD				-> ignored
		// AKEYCODE_ALT_LEFT			-> ignored
		// AKEYCODE_ALT_RIGHT			-> ignored
		case AKEYCODE_SHIFT_LEFT:		return PLGUIKEY_SHIFT;
		// AKEYCODE_SHIFT_RIGHT			-> ignored
		case AKEYCODE_TAB:				return PLGUIKEY_TAB;
		case AKEYCODE_SPACE:			return PLGUIKEY_SPACE;
		// AKEYCODE_SYM					-> ignored
		// AKEYCODE_EXPLORER			-> ignored
		// AKEYCODE_ENVELOPE			-> ignored
		case AKEYCODE_ENTER:			return PLGUIKEY_RETURN;
		case AKEYCODE_DEL:				return PLGUIKEY_DELETE;
		// AKEYCODE_GRAVE				-> ignored
		case AKEYCODE_MINUS:			return PLGUIKEY_SUBTRACT;
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
		// AKEYCODE_PLUS				-> ignored
		case AKEYCODE_MENU:				return PLGUIKEY_MENU;
		// AKEYCODE_NOTIFICATION		-> ignored
		// AKEYCODE_SEARCH				-> ignored
		case AKEYCODE_MEDIA_PLAY_PAUSE:	return PLGUIKEY_PAUSE;
		// AKEYCODE_MEDIA_STOP			-> ignored
		case AKEYCODE_MEDIA_NEXT:		return PLGUIKEY_NEXT;
		case AKEYCODE_MEDIA_PREVIOUS: 	return PLGUIKEY_PRIOR;
		// AKEYCODE_MEDIA_REWIND		-> ignored
		// AKEYCODE_MEDIA_FAST_FORWARD	-> ignored
		// AKEYCODE_MUTE				-> ignored
		// AKEYCODE_PAGE_UP				-> ignored
		// AKEYCODE_PAGE_DOWN			-> ignored
		// AKEYCODE_PICTSYMBOLS			-> ignored
		// AKEYCODE_SWITCH_CHARSET		-> ignored
		// AKEYCODE_BUTTON_A			-> ignored
		// AKEYCODE_BUTTON_B			-> ignored
		// AKEYCODE_BUTTON_C			-> ignored
		// AKEYCODE_BUTTON_X			-> ignored
		// AKEYCODE_BUTTON_Y			-> ignored
		// AKEYCODE_BUTTON_Z			-> ignored
		// AKEYCODE_BUTTON_L1			-> ignored
		// AKEYCODE_BUTTON_R1			-> ignored
		// AKEYCODE_BUTTON_L2			-> ignored
		// AKEYCODE_BUTTON_R2			-> ignored
		// AKEYCODE_BUTTON_THUMBL		-> ignored
		// AKEYCODE_BUTTON_THUMBR		-> ignored
		// AKEYCODE_BUTTON_START		-> ignored
		case AKEYCODE_BUTTON_SELECT:	return PLGUIKEY_SELECT;
		// AKEYCODE_BUTTON_MODE			-> ignored
		default:						return 0;
	}
}

/**
*  @brief
*    Call this to process the next motion input event
*/
void GuiAndroid::OnMotionInputEvent(const struct AInputEvent &cAMotionInputEvent)
{
	// No widget handling, just raw input

	// Get the number of pointers of data contained in this event
	const size_t nAndroidPointerCount = AMotionEvent_getPointerCount(&cAMotionInputEvent);
	if (nAndroidPointerCount) {
		// Get the current X and Y coordinate of this event for the given pointer index
		const float fAndroidX = AMotionEvent_getX(&cAMotionInputEvent, 0);
		const float fAndroidY = AMotionEvent_getY(&cAMotionInputEvent, 0);

		// Mouse position
		const Vector2i vPos(static_cast<int>(fAndroidX), static_cast<int>(fAndroidY));

		// Get the root widget
		Widget *pRootWidget = m_pGui->GetRootWidget();

		// Get the combined motion event action code and pointer index
		const int32_t nAndroidAction = AMotionEvent_getAction(&cAMotionInputEvent);
		if ((nAndroidAction & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_UP) {
			// Is the left mouse button currently down?
			if (m_bLeftMouseButton) {
				// Jap, the left mouse button is now no longer down
				m_bLeftMouseButton = false;

				// Send OnMouseButtonUp message
				m_pGui->SendMessage(GuiMessage::OnMouseButtonUp(pRootWidget, LeftButton, vPos));

				// [TODO] When to send a click-event, and when not?
				// Send OnMouseButtonClick message
				m_pGui->SendMessage(GuiMessage::OnMouseButtonClick(pRootWidget, LeftButton, vPos));
			}
		} else {
			// Mouse position changed?
			if (m_vMousePosition != vPos) {
				// Set the new mouse position
				m_vMousePosition = vPos;

				// Send OnMouseMove message
				m_pGui->SendMessage(GuiMessage::OnMouseMove(pRootWidget, vPos));
			}

			// Get the current pressure of this event for the given pointer index, ranges from 0 (no pressure at all) to 1 (normal pressure)
			const float fPressure = AMotionEvent_getPressure(&cAMotionInputEvent, 0);
			if (fPressure > 0.3f) {
				// Is the left mouse button already down?
				if (!m_bLeftMouseButton) {
					// Nope, start left mouse button down mode
					m_bLeftMouseButton = true;

					// Send OnMouseButtonDown message
					m_pGui->SendMessage(GuiMessage::OnMouseButtonDown(pRootWidget, LeftButton, vPos));
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
