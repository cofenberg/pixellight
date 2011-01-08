/*********************************************************\
 *  File: RawInputDevice.cpp                             *
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
#include <PLGeneral/Core/MemoryManager.h>
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Backend/Windows/RawInputDevice.h"


//[-------------------------------------------------------]
//[ Global definitions                                    ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual keys
*/
enum EKey {
	KeyBack				= 0x08,		/**< Backspace */
	KeyTab				= 0x09,		/**< Tab */
	KeyClear			= 0x0C,		/**< Clear (not available everywhere) */
	KeyReturn			= 0x0D,		/**< Enter */
	KeyShift			= 0x10,		/**< Shift */
	KeyControl			= 0x11,		/**< Ctrl */
	KeyAlt				= 0x12,		/**< Alt */
	KeyPause			= 0x13,		/**< Pause */
	KeyCapsLock			= 0x14,		/**< Caps lock */
	KeyEscape			= 0x1B,		/**< Escape */
	KeySpace			= 0x20,		/**< Space */
	KeyPageUp			= 0x21,		/**< Page up */
	KeyPageDown			= 0x22,		/**< Page down */
	KeyEnd				= 0x23,		/**< End */
	KeyHome				= 0x24,		/**< Home */
	KeyLeft				= 0x25,		/**< Left arrow */
	KeyUp				= 0x26,		/**< Up arrow */
	KeyRight			= 0x27,		/**< Right arrow */
	KeyDown				= 0x28,		/**< Down arrow */
	KeySelect			= 0x29,		/**< Select (not available everywhere) */
	KeyExecute			= 0x2B,		/**< Execute (not available everywhere) */
	KeyPrintScreen		= 0x2C,		/**< Print screen */
	KeyInsert			= 0x2D,		/**< Insert */
	KeyDelete			= 0x2E,		/**< Delete */
	KeyHelp				= 0x2F,		/**< Help (not available everywhere) */
	Key0				= 0x30,		/**< 0 */
	Key1				= 0x31,		/**< 1 */
	Key2				= 0x32,		/**< 2 */
	Key3				= 0x33,		/**< 3 */
	Key4				= 0x34,		/**< 4 */
	Key5				= 0x35,		/**< 5 */
	Key6				= 0x36,		/**< 6 */
	Key7				= 0x37,		/**< 7 */
	Key8				= 0x38,		/**< 8 */
	Key9				= 0x39,		/**< 9 */
	KeyA				= 0x41,		/**< A */
	KeyB				= 0x42,		/**< B */
	KeyC				= 0x43,		/**< C */
	KeyD				= 0x44,		/**< D */
	KeyE				= 0x45,		/**< E */
	KeyF				= 0x46,		/**< F */
	KeyG				= 0x47,		/**< G */
	KeyH				= 0x48,		/**< H */
	KeyI				= 0x49,		/**< I */
	KeyJ				= 0x4A,		/**< J */
	KeyK				= 0x4B,		/**< K */
	KeyL				= 0x4C,		/**< L */
	KeyM				= 0x4D,		/**< M */
	KeyN				= 0x4E,		/**< N */
	KeyO				= 0x4F,		/**< O */
	KeyP				= 0x50,		/**< P */
	KeyQ				= 0x51,		/**< Q */
	KeyR				= 0x52,		/**< R */
	KeyS				= 0x53,		/**< S */
	KeyT				= 0x54,		/**< T */
	KeyU				= 0x55,		/**< U */
	KeyV				= 0x56,		/**< V */
	KeyW				= 0x57,		/**< W */
	KeyX				= 0x58,		/**< X */
	KeyY				= 0x59,		/**< Y */
	KeyZ				= 0x5A,		/**< Z */
	KeyNumpad0			= 0x60,		/**< Numeric keypad 0 */
	KeyNumpad1			= 0x61,		/**< Numeric keypad 1 */
	KeyNumpad2			= 0x62,		/**< Numeric keypad 2 */
	KeyNumpad3			= 0x63,		/**< Numeric keypad 3 */
	KeyNumpad4			= 0x64,		/**< Numeric keypad 4 */
	KeyNumpad5			= 0x65,		/**< Numeric keypad 5 */
	KeyNumpad6			= 0x66,		/**< Numeric keypad 6 */
	KeyNumpad7			= 0x67,		/**< Numeric keypad 7 */
	KeyNumpad8			= 0x68,		/**< Numeric keypad 8 */
	KeyNumpad9			= 0x69,		/**< Numeric keypad 9 */
	KeyNumpadMultiply	= 0x6A,		/**< Numeric keypad "Multiply" */
	KeyNumpadAdd		= 0x6B,		/**< Numeric keypad "Add" */
	KeyNumpadSeparator	= 0x6C,		/**< Numeric keypad "Separator" */
	KeyNumpadSubtract	= 0x6D,		/**< Numeric keypad "Subtract" */
	KeyNumpadDecimal	= 0x6E,		/**< Numeric keypad "Decimal" */
	KeyNumpadDivide		= 0x6F,		/**< Numeric keypad "Divide" */
	KeyF1				= 0x70,		/**< F1 */
	KeyF2				= 0x71,		/**< F2 */
	KeyF3				= 0x72,		/**< F3 */
	KeyF4				= 0x73,		/**< F4 */
	KeyF5				= 0x74,		/**< F5 */
	KeyF6				= 0x75,		/**< F6 */
	KeyF7				= 0x76,		/**< F7 */
	KeyF8				= 0x77,		/**< F8 */
	KeyF9				= 0x78,		/**< F9 */
	KeyF10				= 0x79,		/**< F10 */
	KeyF11				= 0x7A,		/**< F11 */
	KeyF12				= 0x7B,		/**< F12 */
	KeyNumLock			= 0x90,		/**< Num lock */
	KeyScrollLock		= 0x91,		/**< Scroll lock */
	KeyCircumflex		= 0xDC		/**< Circumflex (^) */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RawInputDevice::RawInputDevice() :
	m_nType(0),
	m_hDevice(nullptr),
	m_bVirtual(false),
	m_nOldX(0),
	m_nOldY(0)
{
	// Do not destroy device implementation automatically, because this is managed by RawInput
	m_bDelete = false;

	// Clear deviceinfo struct
	MemoryManager::Set(&m_sDeviceInfo, 0, sizeof(m_sDeviceInfo));
}

/**
*  @brief
*    Copy constructor
*/
RawInputDevice::RawInputDevice(const RawInputDevice &cSource) :
	m_sName(cSource.m_sName),
	m_nType(cSource.m_nType),
	m_hDevice(cSource.m_hDevice),
	m_bVirtual(cSource.m_bVirtual)
{
	// Do not destroy device implementation automatically, because this is managed by RawInput
	m_bDelete = false;

	// Copy deviceinfo struct
	MemoryManager::Copy(&m_sDeviceInfo, &cSource.m_sDeviceInfo, sizeof(m_sDeviceInfo));
}

/**
*  @brief
*    Destructor
*/
RawInputDevice::~RawInputDevice()
{
}

/**
*  @brief
*    Copy operator
*/
RawInputDevice &RawInputDevice::operator =(const RawInputDevice &cSource)
{
	m_sName		= cSource.m_sName;
	m_nType		= cSource.m_nType;
	m_hDevice	= cSource.m_hDevice;
	m_bVirtual	= cSource.m_bVirtual;
	MemoryManager::Copy(&m_sDeviceInfo, &cSource.m_sDeviceInfo, sizeof(m_sDeviceInfo));
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool RawInputDevice::operator ==(const RawInputDevice &cSource)
{
	return (m_sName		== cSource.m_sName &&
			m_nType		== cSource.m_nType &&
			m_hDevice	== cSource.m_hDevice &&
			m_bVirtual	== cSource.m_bVirtual &&
			MemoryManager::Compare(&m_sDeviceInfo, &cSource.m_sDeviceInfo, sizeof(m_sDeviceInfo)) == 0);
}

/**
*  @brief
*    Get device name
*/
String RawInputDevice::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Get device type
*/
DWORD RawInputDevice::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Get device handle
*/
HANDLE RawInputDevice::GetHandle() const
{
	return m_hDevice;
}

/**
*  @brief
*    Get device info
*/
RID_DEVICE_INFO RawInputDevice::GetDeviceInfo() const
{
	return m_sDeviceInfo;
}

/**
*  @brief
*    Check if the device is a virtual device
*/
bool RawInputDevice::IsVirtual() const
{
	// Check virtual device
	return m_bVirtual;
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void RawInputDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice && m_nType == RIM_TYPEMOUSE) {
		// Get mouse device
		Mouse *pMouse = (Mouse*)m_pDevice;

		// Reset mouse movement
		if (pMouse->X.GetValue() != 0.0f)
			pMouse->X.SetValue(0.0f, true);
		if (pMouse->Y.GetValue() != 0.0f)
			pMouse->Y.SetValue(0, true);
		if (pMouse->Wheel.GetValue() != 0.0f)
			pMouse->Wheel.SetValue(0, true);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Process raw keyboard data
*/
void RawInputDevice::ProcessKeyboardData(unsigned short nMakeCode, unsigned short nFlags, unsigned short nReserved, unsigned short nKey, unsigned int nMessage, unsigned long nExtra)
{
	// Check if input device is valid
	if (m_pDevice && m_nType == RIM_TYPEKEYBOARD) {
		// Get keyboard device
		Keyboard *pKeyboard = (Keyboard*)m_pDevice;

		// Get button
		Button *pButton = GetKeyboardKey(pKeyboard, nKey);
		if (pButton) {
			// Make or break code?
			bool bPressed = ((nFlags & RI_KEY_BREAK) == 0);
			if (pButton->IsPressed() != bPressed)
				pButton->SetPressed(bPressed);
		}
	}
}

/**
*  @brief
*    Process raw mouse data
*/
void RawInputDevice::ProcessMouseData(unsigned short nFlags, unsigned long nButtons, unsigned short nButtonFlags, unsigned short nButtonData, long nRawButtons, long nLastX, long nLastY, unsigned long nExtra)
{
	// Check if input device is valid
	if (m_pDevice && m_nType == RIM_TYPEMOUSE) {
		// Get mouse device
		Mouse *pMouse = (Mouse*)m_pDevice;

		// Update axes
		float fX, fY;
		if (nFlags & MOUSE_MOVE_ABSOLUTE) {
			// Absolute position
			fX = pMouse->X.GetValue() + (float)(nLastX - m_nOldX);
			fY = pMouse->Y.GetValue() + (float)(nLastY - m_nOldY);
			m_nOldX = nLastX;
			m_nOldY = nLastY;
		} else {
			// Relative position
			fX = pMouse->X.GetValue() + (float)nLastX;
			fY = pMouse->Y.GetValue() + (float)nLastY;
		}

		// Set axis values
		if (pMouse->X.GetValue() != fX)
			pMouse->X.SetValue(fX, true);
		if (pMouse->Y.GetValue() != fY)
			pMouse->Y.SetValue(fY, true);

		// Update buttons
		if (nButtonFlags) {
			if (nButtonFlags & RI_MOUSE_BUTTON_1_DOWN) {
				if (!pMouse->Left.IsPressed()) pMouse->Left.SetPressed(true);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_1_UP) {
				if (pMouse->Left.IsPressed()) pMouse->Left.SetPressed(false);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_2_DOWN) {
				if (!pMouse->Right.IsPressed()) pMouse->Right.SetPressed(true);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_2_UP) {
				if (pMouse->Right.IsPressed()) pMouse->Right.SetPressed(false);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_3_DOWN) {
				if (!pMouse->Middle.IsPressed()) pMouse->Middle.SetPressed(true);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_3_UP) {
				if (pMouse->Middle.IsPressed()) pMouse->Middle.SetPressed(false);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_4_DOWN) {
				if (!pMouse->Button4.IsPressed()) pMouse->Button4.SetPressed(true);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_4_UP) {
				if (pMouse->Button4.IsPressed()) pMouse->Button4.SetPressed(false);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_5_DOWN) {
				if (!pMouse->Button5.IsPressed()) pMouse->Button5.SetPressed(true);
			}
			if (nButtonFlags & RI_MOUSE_BUTTON_5_UP) {
				if (pMouse->Button5.IsPressed()) pMouse->Button5.SetPressed(false);
			}
			if (nButtonFlags & RI_MOUSE_WHEEL) {
				// Well ... nButtonData is unsigned, but the wheel delta can be negative. So let's cast USHORT to SHORT.
				float fValue = (float) *((short*)&nButtonData);
				if (pMouse->Wheel.GetValue() != fValue)
					pMouse->Wheel.SetValue(fValue, true);
			}
		}
	}
}

/**
*  @brief
*    Get key for virtual key code
*/
Button *RawInputDevice::GetKeyboardKey(Keyboard *pKeyboard, unsigned short nKey)
{
	// Return key that corresponds to the given key code
	switch (nKey) {
		case KeyBack:			return &pKeyboard->KeyBack;
		case KeyTab:			return &pKeyboard->KeyTab;
		case KeyClear:			return &pKeyboard->KeyClear;
		case KeyReturn:			return &pKeyboard->KeyReturn;
		case KeyShift:			return &pKeyboard->KeyShift;
		case KeyControl:		return &pKeyboard->KeyControl;
		case KeyAlt:			return &pKeyboard->KeyAlt;
		case KeyPause:			return &pKeyboard->KeyPause;
		case KeyCapsLock:		return &pKeyboard->KeyCapsLock;
		case KeyEscape:			return &pKeyboard->KeyEscape;
		case KeySpace:			return &pKeyboard->KeySpace;
		case KeyPageUp:			return &pKeyboard->KeyPageUp;
		case KeyPageDown:		return &pKeyboard->KeyPageDown;
		case KeyEnd:			return &pKeyboard->KeyEnd;
		case KeyHome:			return &pKeyboard->KeyHome;
		case KeyLeft:			return &pKeyboard->KeyLeft;
		case KeyUp:				return &pKeyboard->KeyUp;
		case KeyRight:			return &pKeyboard->KeyRight;
		case KeyDown:			return &pKeyboard->KeyDown;
		case KeySelect:			return &pKeyboard->KeySelect;
		case KeyExecute:		return &pKeyboard->KeyExecute;
		case KeyPrintScreen:	return &pKeyboard->KeyPrintScreen;
		case KeyInsert:			return &pKeyboard->KeyInsert;
		case KeyDelete:			return &pKeyboard->KeyDelete;
		case KeyHelp:			return &pKeyboard->KeyHelp;
		case Key0:				return &pKeyboard->Key0;
		case Key1:				return &pKeyboard->Key1;
		case Key2:				return &pKeyboard->Key2;
		case Key3:				return &pKeyboard->Key3;
		case Key4:				return &pKeyboard->Key4;
		case Key5:				return &pKeyboard->Key5;
		case Key6:				return &pKeyboard->Key6;
		case Key7:				return &pKeyboard->Key7;
		case Key8:				return &pKeyboard->Key8;
		case Key9:				return &pKeyboard->Key9;
		case KeyA:				return &pKeyboard->KeyA;
		case KeyB:				return &pKeyboard->KeyB;
		case KeyC:				return &pKeyboard->KeyC;
		case KeyD:				return &pKeyboard->KeyD;
		case KeyE:				return &pKeyboard->KeyE;
		case KeyF:				return &pKeyboard->KeyF;
		case KeyG:				return &pKeyboard->KeyG;
		case KeyH:				return &pKeyboard->KeyH;
		case KeyI:				return &pKeyboard->KeyI;
		case KeyJ:				return &pKeyboard->KeyJ;
		case KeyK:				return &pKeyboard->KeyK;
		case KeyL:				return &pKeyboard->KeyL;
		case KeyM:				return &pKeyboard->KeyM;
		case KeyN:				return &pKeyboard->KeyN;
		case KeyO:				return &pKeyboard->KeyO;
		case KeyP:				return &pKeyboard->KeyP;
		case KeyQ:				return &pKeyboard->KeyQ;
		case KeyR:				return &pKeyboard->KeyR;
		case KeyS:				return &pKeyboard->KeyS;
		case KeyT:				return &pKeyboard->KeyT;
		case KeyU:				return &pKeyboard->KeyU;
		case KeyV:				return &pKeyboard->KeyV;
		case KeyW:				return &pKeyboard->KeyW;
		case KeyX:				return &pKeyboard->KeyX;
		case KeyY:				return &pKeyboard->KeyY;
		case KeyZ:				return &pKeyboard->KeyZ;
		case KeyNumpad0:		return &pKeyboard->KeyNumpad0;
		case KeyNumpad1:		return &pKeyboard->KeyNumpad1;
		case KeyNumpad2:		return &pKeyboard->KeyNumpad2;
		case KeyNumpad3:		return &pKeyboard->KeyNumpad3;
		case KeyNumpad4:		return &pKeyboard->KeyNumpad4;
		case KeyNumpad5:		return &pKeyboard->KeyNumpad5;
		case KeyNumpad6:		return &pKeyboard->KeyNumpad6;
		case KeyNumpad7:		return &pKeyboard->KeyNumpad7;
		case KeyNumpad8:		return &pKeyboard->KeyNumpad8;
		case KeyNumpad9:		return &pKeyboard->KeyNumpad9;
		case KeyNumpadMultiply:	return &pKeyboard->KeyNumpadMultiply;
		case KeyNumpadAdd:		return &pKeyboard->KeyNumpadAdd;
		case KeyNumpadSeparator:return &pKeyboard->KeyNumpadSeparator;
		case KeyNumpadSubtract:	return &pKeyboard->KeyNumpadSubtract;
		case KeyNumpadDecimal:	return &pKeyboard->KeyNumpadDecimal;
		case KeyNumpadDivide:	return &pKeyboard->KeyNumpadDivide;
		case KeyF1:				return &pKeyboard->KeyF1;
		case KeyF2:				return &pKeyboard->KeyF2;
		case KeyF3:				return &pKeyboard->KeyF3;
		case KeyF4:				return &pKeyboard->KeyF4;
		case KeyF5:				return &pKeyboard->KeyF5;
		case KeyF6:				return &pKeyboard->KeyF6;
		case KeyF7:				return &pKeyboard->KeyF7;
		case KeyF8:				return &pKeyboard->KeyF8;
		case KeyF9:				return &pKeyboard->KeyF9;
		case KeyF10:			return &pKeyboard->KeyF10;
		case KeyF11:			return &pKeyboard->KeyF11;
		case KeyF12:			return &pKeyboard->KeyF12;
		case KeyNumLock:		return &pKeyboard->KeyNumLock;
		case KeyScrollLock:		return &pKeyboard->KeyScrollLock;
		case KeyCircumflex:		return &pKeyboard->KeyCircumflex;
		default:				return  nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
