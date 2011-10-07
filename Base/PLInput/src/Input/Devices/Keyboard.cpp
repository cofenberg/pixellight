
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
	Backspace		(this, "Backspace",			"Backspace",							0x08),
	Tab				(this, "Tab",				"Tabulator",							0x09),
	Clear			(this, "Clear",				"Clear (not available everywhere)",		0x00),
	Return			(this, "Return",			"Return (often the same as \"Enter\")",	0x0D),
	Shift			(this, "Shift",				"Shift",								0x00),
	Control			(this, "Control",			"Control (\"Ctrl\")",					0x00),
	Alt				(this, "Alt",				"Alt",									0x00),
	Pause			(this, "Pause",				"Pause",								0x00),
	CapsLock		(this, "CapsLock",			"Caps lock",							0x00),
	Escape			(this, "Escape",			"Escape",								0x1B),
	Space			(this, "Space",				"Space",								0x20),
	PageUp			(this, "PageUp",			"Page up",								0x00),
	PageDown		(this, "PageDown",			"Page down",							0x00),
	End				(this, "End",				"End",									0x00),
	Home			(this, "Home",				"Home",									0x00),
	Left			(this, "Left",				"Left arrow",							0x00),
	Up				(this, "Up",				"Up arrow",								0x00),
	Right			(this, "Right",				"Right arrow",							0x00),
	Down			(this, "Down",				"Down arrow",							0x00),
	Select			(this, "Select",			"Select (not available everywhere)",	0x00),
	Execute			(this, "Execute",			"Execute (not available everywhere)",	0x00),
	Print			(this, "Print",				"Print screen",							0x00),
	Insert			(this, "Insert",			"Insert",								0x00),
	Delete			(this, "Delete",			"Delete",								0x7F),
	Help			(this, "Help",				"Help (not available everywhere)",		0x00),
	Key0			(this, "0",					"0",									 '0'),
	Key1			(this, "1",					"1",									 '1'),
	Key2			(this, "2",					"2",									 '2'),
	Key3			(this, "3",					"3",									 '3'),
	Key4			(this, "4",					"4",									 '4'),
	Key5			(this, "5",					"5",									 '5'),
	Key6			(this, "6",					"6",									 '6'),
	Key7			(this, "7",					"7",									 '7'),
	Key8			(this, "8",					"8",									 '8'),
	Key9			(this, "9",					"9",									 '9'),
	A				(this, "A",					"A",									 'a'),
	B				(this, "B",					"B",									 'b'),
	C				(this, "C",					"C",									 'c'),
	D				(this, "D",					"D",									 'd'),
	E				(this, "E",					"E",									 'e'),
	F				(this, "F",					"F",									 'f'),
	G				(this, "G",					"G",									 'g'),
	H				(this, "H",					"H",									 'h'),
	I				(this, "I",					"I",									 'i'),
	J				(this, "J",					"J",									 'j'),
	K				(this, "K",					"K",									 'k'),
	L				(this, "L",					"L",									 'l'),
	M				(this, "M",					"M",									 'm'),
	N				(this, "N",					"N",									 'n'),
	O				(this, "O",					"O",									 'o'),
	P				(this, "P",					"P",									 'p'),
	Q				(this, "Q",					"Q",									 'q'),
	R				(this, "R",					"R",									 'r'),
	S				(this, "S",					"S",									 's'),
	T				(this, "T",					"T",									 't'),
	U				(this, "U",					"U",									 'u'),
	V				(this, "V",					"V",									 'v'),
	W				(this, "W",					"W",									 'w'),
	X				(this, "X",					"X",									 'x'),
	Y				(this, "Y",					"Y",									 'y'),
	Z				(this, "Z",					"Z",									 'z'),
	Numpad0			(this, "Numpad0",			"Numpad 0",								 '0'),
	Numpad1			(this, "Numpad1",			"Numpad 1",								 '1'),
	Numpad2			(this, "Numpad2",			"Numpad 2",								 '2'),
	Numpad3			(this, "Numpad3",			"Numpad 3",								 '3'),
	Numpad4			(this, "Numpad4",			"Numpad 4",								 '4'),
	Numpad5			(this, "Numpad5",			"Numpad 5",								 '5'),
	Numpad6			(this, "Numpad6",			"Numpad 6",								 '6'),
	Numpad7			(this, "Numpad7",			"Numpad 7",								 '7'),
	Numpad8			(this, "Numpad8",			"Numpad 8",								 '8'),
	Numpad9			(this, "Numpad9",			"Numpad 9",								 '9'),
	NumpadMultiply	(this, "NumpadMultiply",	"Numpad Multiply",						 '*'),
	NumpadAdd		(this, "NumpadAdd",			"Numpad Add",							 '+'),
	NumpadSeparator	(this, "NumpadSeparator",	"Numpad Separator",						 ','),
	NumpadSubtract	(this, "NumpadSubtract",	"Numpad Subtract",						 '-'),
	NumpadDecimal	(this, "NumpadDecimal",		"Numpad Decimal",						 '.'),
	NumpadDivide	(this, "NumpadDivide",		"Numpad Divide",						 '/'),
	F1				(this, "F1",				"F1",									0x00),
	F2				(this, "F2",				"F2",									0x00),
	F3				(this, "F3",				"F3",									0x00),
	F4				(this, "F4",				"F4",									0x00),
	F5				(this, "F5",				"F5",									0x00),
	F6				(this, "F6",				"F6",									0x00),
	F7				(this, "F7",				"F7",									0x00),
	F8				(this, "F8",				"F8",									0x00),
	F9				(this, "F9",				"F9",									0x00),
	F10				(this, "F10",				"F10",									0x00),
	F11				(this, "F11",				"F11",									0x00),
	F12				(this, "F12",				"F12",									0x00),
	NumLock			(this, "NumLock",			"NumLock",								0x00),
	ScrollLock		(this, "ScrollLock",		"ScrollLock",							0x00),
	Circumflex		(this, "Circumflex",		"Circumflex",							0x00)
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
