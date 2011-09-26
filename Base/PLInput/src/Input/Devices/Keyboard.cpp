
/*********************************************************\
 *  File: Keyboard.cpp                                   *
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
#include "PLInput/Backend/UpdateDevice.h"
#include "PLInput/Input/Devices/Keyboard.h"


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
Keyboard::Keyboard(const String &sName, DeviceImpl *pImpl) : Device(sName, "Keyboard input controller", pImpl),
	KeyBack				(this, "Backspace",		"Backspace",							0x08),
	KeyTab				(this, "Tab",			"Tabulator",							0x09),
	KeyClear			(this, "Clear",			"Clear (not available everywhere)",		0x00),
	KeyReturn			(this, "Return",		"Return (often the same as \"Enter\")",	0x0D),
	KeyShift			(this, "Shift",			"Shift",								0x00),
	KeyControl			(this, "Ctrl",			"Ctrl",									0x00),
	KeyAlt				(this, "Alt",			"Alt",									0x00),
	KeyPause			(this, "Pause",			"Pause",								0x00),
	KeyCapsLock			(this, "CapsLock",		"Caps lock",							0x00),
	KeyEscape			(this, "Escape",		"Escape",								0x1B),
	KeySpace			(this, "Space",			"Space",								0x20),
	KeyPageUp			(this, "PageUp",		"Page up",								0x00),
	KeyPageDown			(this, "PageDown",		"Page down",							0x00),
	KeyEnd				(this, "End",			"End",									0x00),
	KeyHome				(this, "Home",			"Home",									0x00),
	KeyLeft				(this, "Left",			"Left arrow",							0x00),
	KeyUp				(this, "Up",			"Up arrow",								0x00),
	KeyRight			(this, "Right",			"Right arrow",							0x00),
	KeyDown				(this, "Down",			"Down arrow",							0x00),
	KeySelect			(this, "Select",		"Select (not available everywhere)",	0x00),
	KeyExecute			(this, "Execute",		"Execute (not available everywhere)",	0x00),
	KeyPrintScreen		(this, "Print",			"Print screen",							0x00),
	KeyInsert			(this, "Insert",		"Insert",								0x00),
	KeyDelete			(this, "Delete",		"Delete",								0x7F),
	KeyHelp				(this, "Help",			"Help (not available everywhere)",		0x00),
	Key0				(this, "0",				"0",									 '0'),
	Key1				(this, "1",				"1",									 '1'),
	Key2				(this, "2",				"2",									 '2'),
	Key3				(this, "3",				"3",									 '3'),
	Key4				(this, "4",				"4",									 '4'),
	Key5				(this, "5",				"5",									 '5'),
	Key6				(this, "6",				"6",									 '6'),
	Key7				(this, "7",				"7",									 '7'),
	Key8				(this, "8",				"8",									 '8'),
	Key9				(this, "9",				"9",									 '9'),
	KeyA				(this, "A",				"A",									 'a'),
	KeyB				(this, "B",				"B",									 'b'),
	KeyC				(this, "C",				"C",									 'c'),
	KeyD				(this, "D",				"D",									 'd'),
	KeyE				(this, "E",				"E",									 'e'),
	KeyF				(this, "F",				"F",									 'f'),
	KeyG				(this, "G",				"G",									 'g'),
	KeyH				(this, "H",				"H",									 'h'),
	KeyI				(this, "I",				"I",									 'i'),
	KeyJ				(this, "J",				"J",									 'j'),
	KeyK				(this, "K",				"K",									 'k'),
	KeyL				(this, "L",				"L",									 'l'),
	KeyM				(this, "M",				"M",									 'm'),
	KeyN				(this, "N",				"N",									 'n'),
	KeyO				(this, "O",				"O",									 'o'),
	KeyP				(this, "P",				"P",									 'p'),
	KeyQ				(this, "Q",				"Q",									 'q'),
	KeyR				(this, "R",				"R",									 'r'),
	KeyS				(this, "S",				"S",									 's'),
	KeyT				(this, "T",				"T",									 't'),
	KeyU				(this, "U",				"U",									 'u'),
	KeyV				(this, "V",				"V",									 'v'),
	KeyW				(this, "W",				"W",									 'w'),
	KeyX				(this, "X",				"X",									 'x'),
	KeyY				(this, "Y",				"Y",									 'y'),
	KeyZ				(this, "Z",				"Z",									 'z'),
	KeyNumpad0			(this, "Num0",			"Numpad 0",								 '0'),
	KeyNumpad1			(this, "Num1",			"Numpad 1",								 '1'),
	KeyNumpad2			(this, "Num2",			"Numpad 2",								 '2'),
	KeyNumpad3			(this, "Num3",			"Numpad 3",								 '3'),
	KeyNumpad4			(this, "Num4",			"Numpad 4",								 '4'),
	KeyNumpad5			(this, "Num5",			"Numpad 5",								 '5'),
	KeyNumpad6			(this, "Num6",			"Numpad 6",								 '6'),
	KeyNumpad7			(this, "Num7",			"Numpad 7",								 '7'),
	KeyNumpad8			(this, "Num8",			"Numpad 8",								 '8'),
	KeyNumpad9			(this, "Num9",			"Numpad 9",								 '9'),
	KeyNumpadMultiply	(this, "NumMultiply",	"Numpad Multiply",						 '*'),
	KeyNumpadAdd		(this, "NumAdd",		"Numpad Add",							 '+'),
	KeyNumpadSeparator	(this, "NumSeparator",	"Numpad Separator",						 ','),
	KeyNumpadSubtract	(this, "NumSubtract",	"Numpad Subtract",						 '-'),
	KeyNumpadDecimal	(this, "NumDecimal",	"Numpad Decimal",						 '.'),
	KeyNumpadDivide		(this, "NumDivide",		"Numpad Divide",						 '/'),
	KeyF1				(this, "F1",			"F1",									0x00),
	KeyF2				(this, "F2",			"F2",									0x00),
	KeyF3				(this, "F3",			"F3",									0x00),
	KeyF4				(this, "F4",			"F4",									0x00),
	KeyF5				(this, "F5",			"F5",									0x00),
	KeyF6				(this, "F6",			"F6",									0x00),
	KeyF7				(this, "F7",			"F7",									0x00),
	KeyF8				(this, "F8",			"F8",									0x00),
	KeyF9				(this, "F9",			"F9",									0x00),
	KeyF10				(this, "F10",			"F10",									0x00),
	KeyF11				(this, "F11",			"F11",									0x00),
	KeyF12				(this, "F12",			"F12",									0x00),
	KeyNumLock			(this, "NumLock",		"NumLock",								0x00),
	KeyScrollLock		(this, "ScrollLock",	"ScrollLock",							0x00),
	KeyCircumflex		(this, "Circumflex",	"Circumflex",							0x00)
{
}

/**
*  @brief
*    Destructor
*/
Keyboard::~Keyboard()
{
}


//[-------------------------------------------------------]
//[ Public virtual Controller functions                   ]
//[-------------------------------------------------------]
void Keyboard::Update()
{
	// Update device backend
	if (m_pImpl && m_pImpl->GetBackendType() == BackendUpdateDevice) {
		static_cast<UpdateDevice*>(m_pImpl)->Update();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
