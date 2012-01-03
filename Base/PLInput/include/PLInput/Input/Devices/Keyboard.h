/*********************************************************\
 *  File: Keyboard.h                                     *
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


#ifndef __PLINPUT_KEYBOARD_H__
#define __PLINPUT_KEYBOARD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Input/Controls/Button.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Keyboard device
*
*  @remarks
*    This class supports the following device backend types:
*    - UpdateDevice
*/
class Keyboard : public Device {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, Keyboard, "PLInput", PLInput::Device, "Keyboard input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		PLInput::Button	Backspace;			/**< Backspace */
		PLInput::Button	Tab;				/**< Tab */
		PLInput::Button	Clear;				/**< Clear (not available everywhere) */
		PLInput::Button	Return;				/**< Return (often the same as "Enter") */
		PLInput::Button	Shift;				/**< Shift */
		PLInput::Button	Control;			/**< Control ("Ctrl") */
		PLInput::Button	Alt;				/**< Alt */
		PLInput::Button	Pause;				/**< Pause */
		PLInput::Button	CapsLock;			/**< Caps lock */
		PLInput::Button	Escape;				/**< Escape */
		PLInput::Button	Space;				/**< Space */
		PLInput::Button	PageUp;				/**< Page up */
		PLInput::Button	PageDown;			/**< Page down */
		PLInput::Button	End;				/**< End */
		PLInput::Button	Home;				/**< Home */
		PLInput::Button	Left;				/**< Left arrow */
		PLInput::Button	Up;					/**< Up arrow */
		PLInput::Button	Right;				/**< Right arrow */
		PLInput::Button	Down;				/**< Down arrow */
		PLInput::Button	Select;				/**< Select (not available everywhere) */
		PLInput::Button	Execute;			/**< Execute (not available everywhere) */
		PLInput::Button	Print;				/**< Print screen */
		PLInput::Button	Insert;				/**< Insert */
		PLInput::Button	Delete;				/**< Delete */
		PLInput::Button	Help;				/**< Help (not available everywhere) */
		PLInput::Button	Key0;				/**< 0 (control name is "0") */
		PLInput::Button	Key1;				/**< 1 (control name is "1") */
		PLInput::Button	Key2;				/**< 2 (control name is "2") */
		PLInput::Button	Key3;				/**< 3 (control name is "3") */
		PLInput::Button	Key4;				/**< 4 (control name is "4") */
		PLInput::Button	Key5;				/**< 5 (control name is "5") */
		PLInput::Button	Key6;				/**< 6 (control name is "6") */
		PLInput::Button	Key7;				/**< 7 (control name is "7") */
		PLInput::Button	Key8;				/**< 8 (control name is "8") */
		PLInput::Button	Key9;				/**< 9 (control name is "9") */
		PLInput::Button	A;					/**< A */
		PLInput::Button	B;					/**< B */
		PLInput::Button	C;					/**< C */
		PLInput::Button	D;					/**< D */
		PLInput::Button	E;					/**< E */
		PLInput::Button	F;					/**< F */
		PLInput::Button	G;					/**< G */
		PLInput::Button	H;					/**< H */
		PLInput::Button	I;					/**< I */
		PLInput::Button	J;					/**< J */
		PLInput::Button	K;					/**< K */
		PLInput::Button	L;					/**< L */
		PLInput::Button	M;					/**< M */
		PLInput::Button	N;					/**< N */
		PLInput::Button	O;					/**< O */
		PLInput::Button	P;					/**< P */
		PLInput::Button	Q;					/**< Q */
		PLInput::Button	R;					/**< R */
		PLInput::Button	S;					/**< S */
		PLInput::Button	T;					/**< T */
		PLInput::Button	U;					/**< U */
		PLInput::Button	V;					/**< V */
		PLInput::Button	W;					/**< W */
		PLInput::Button	X;					/**< X */
		PLInput::Button	Y;					/**< Y */
		PLInput::Button	Z;					/**< Z */
		PLInput::Button	Numpad0;			/**< Numeric keypad 0 */
		PLInput::Button	Numpad1;			/**< Numeric keypad 1 */
		PLInput::Button	Numpad2;			/**< Numeric keypad 2 */
		PLInput::Button	Numpad3;			/**< Numeric keypad 3 */
		PLInput::Button	Numpad4;			/**< Numeric keypad 4 */
		PLInput::Button	Numpad5;			/**< Numeric keypad 5 */
		PLInput::Button	Numpad6;			/**< Numeric keypad 6 */
		PLInput::Button	Numpad7;			/**< Numeric keypad 7 */
		PLInput::Button	Numpad8;			/**< Numeric keypad 8 */
		PLInput::Button	Numpad9;			/**< Numeric keypad 9 */
		PLInput::Button	NumpadMultiply;		/**< Numeric keypad "Multiply" */
		PLInput::Button	NumpadAdd;			/**< Numeric keypad "Add" */
		PLInput::Button	NumpadSeparator;	/**< Numeric keypad "Separator" */
		PLInput::Button	NumpadSubtract;		/**< Numeric keypad "Subtract" */
		PLInput::Button	NumpadDecimal;		/**< Numeric keypad "Decimal" */
		PLInput::Button	NumpadDivide;		/**< Numeric keypad "Divide" */
		PLInput::Button	F1;					/**< F1 */
		PLInput::Button	F2;					/**< F2 */
		PLInput::Button	F3;					/**< F3 */
		PLInput::Button	F4;					/**< F4 */
		PLInput::Button	F5;					/**< F5 */
		PLInput::Button	F6;					/**< F6 */
		PLInput::Button	F7;					/**< F7 */
		PLInput::Button	F8;					/**< F8 */
		PLInput::Button	F9;					/**< F9 */
		PLInput::Button	F10;				/**< F10 */
		PLInput::Button	F11;				/**< F11 */
		PLInput::Button	F12;				/**< F12 */
		PLInput::Button	NumLock;			/**< Num lock */
		PLInput::Button	ScrollLock;			/**< Scroll lock */
		PLInput::Button	Circumflex;			/**< Circumflex (^) */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Device name
		*  @param[in] pImpl
		*    System specific device implementation, can, but shouldn't be a null pointer
		*/
		PLINPUT_API Keyboard(const PLCore::String &sName, DeviceImpl *pImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Keyboard();


	//[-------------------------------------------------------]
	//[ Public virtual Controller functions                   ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void Update() override;



};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_KEYBOARD_H__
