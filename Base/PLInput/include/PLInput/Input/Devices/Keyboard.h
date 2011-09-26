/*********************************************************\
 *  File: Keyboard.h                                     *
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
		PLInput::Button	KeyBack;			/**< Backspace */
		PLInput::Button	KeyTab;				/**< Tab */
		PLInput::Button	KeyClear;			/**< Clear (not available everywhere) */
		PLInput::Button	KeyReturn;			/**< Return (often the same as "Enter") */
		PLInput::Button	KeyShift;			/**< Shift */
		PLInput::Button	KeyControl;			/**< Ctrl */
		PLInput::Button	KeyAlt;				/**< Alt */
		PLInput::Button	KeyPause;			/**< Pause */
		PLInput::Button	KeyCapsLock;		/**< Caps lock */
		PLInput::Button	KeyEscape;			/**< Escape */
		PLInput::Button	KeySpace;			/**< Space */
		PLInput::Button	KeyPageUp;			/**< Page up */
		PLInput::Button	KeyPageDown;		/**< Page down */
		PLInput::Button	KeyEnd;				/**< End */
		PLInput::Button	KeyHome;			/**< Home */
		PLInput::Button	KeyLeft;			/**< Left arrow */
		PLInput::Button	KeyUp;				/**< Up arrow */
		PLInput::Button	KeyRight;			/**< Right arrow */
		PLInput::Button	KeyDown;			/**< Down arrow */
		PLInput::Button	KeySelect;			/**< Select (not available everywhere) */
		PLInput::Button	KeyExecute;			/**< Execute (not available everywhere) */
		PLInput::Button	KeyPrintScreen;		/**< Print screen */
		PLInput::Button	KeyInsert;			/**< Insert */
		PLInput::Button	KeyDelete;			/**< Delete */
		PLInput::Button	KeyHelp;			/**< Help (not available everywhere) */
		PLInput::Button	Key0;				/**< 0 */
		PLInput::Button	Key1;				/**< 1 */
		PLInput::Button	Key2;				/**< 2 */
		PLInput::Button	Key3;				/**< 3 */
		PLInput::Button	Key4;				/**< 4 */
		PLInput::Button	Key5;				/**< 5 */
		PLInput::Button	Key6;				/**< 6 */
		PLInput::Button	Key7;				/**< 7 */
		PLInput::Button	Key8;				/**< 8 */
		PLInput::Button	Key9;				/**< 9 */
		PLInput::Button	KeyA;				/**< A */
		PLInput::Button	KeyB;				/**< B */
		PLInput::Button	KeyC;				/**< C */
		PLInput::Button	KeyD;				/**< D */
		PLInput::Button	KeyE;				/**< E */
		PLInput::Button	KeyF;				/**< F */
		PLInput::Button	KeyG;				/**< G */
		PLInput::Button	KeyH;				/**< H */
		PLInput::Button	KeyI;				/**< I */
		PLInput::Button	KeyJ;				/**< J */
		PLInput::Button	KeyK;				/**< K */
		PLInput::Button	KeyL;				/**< L */
		PLInput::Button	KeyM;				/**< M */
		PLInput::Button	KeyN;				/**< N */
		PLInput::Button	KeyO;				/**< O */
		PLInput::Button	KeyP;				/**< P */
		PLInput::Button	KeyQ;				/**< Q */
		PLInput::Button	KeyR;				/**< R */
		PLInput::Button	KeyS;				/**< S */
		PLInput::Button	KeyT;				/**< T */
		PLInput::Button	KeyU;				/**< U */
		PLInput::Button	KeyV;				/**< V */
		PLInput::Button	KeyW;				/**< W */
		PLInput::Button	KeyX;				/**< X */
		PLInput::Button	KeyY;				/**< Y */
		PLInput::Button	KeyZ;				/**< Z */
		PLInput::Button	KeyNumpad0;			/**< Numeric keypad 0 */
		PLInput::Button	KeyNumpad1;			/**< Numeric keypad 1 */
		PLInput::Button	KeyNumpad2;			/**< Numeric keypad 2 */
		PLInput::Button	KeyNumpad3;			/**< Numeric keypad 3 */
		PLInput::Button	KeyNumpad4;			/**< Numeric keypad 4 */
		PLInput::Button	KeyNumpad5;			/**< Numeric keypad 5 */
		PLInput::Button	KeyNumpad6;			/**< Numeric keypad 6 */
		PLInput::Button	KeyNumpad7;			/**< Numeric keypad 7 */
		PLInput::Button	KeyNumpad8;			/**< Numeric keypad 8 */
		PLInput::Button	KeyNumpad9;			/**< Numeric keypad 9 */
		PLInput::Button	KeyNumpadMultiply;	/**< Numeric keypad "Multiply" */
		PLInput::Button	KeyNumpadAdd;		/**< Numeric keypad "Add" */
		PLInput::Button	KeyNumpadSeparator;	/**< Numeric keypad "Separator" */
		PLInput::Button	KeyNumpadSubtract;	/**< Numeric keypad "Subtract" */
		PLInput::Button	KeyNumpadDecimal;	/**< Numeric keypad "Decimal" */
		PLInput::Button	KeyNumpadDivide;	/**< Numeric keypad "Divide" */
		PLInput::Button	KeyF1;				/**< F1 */
		PLInput::Button	KeyF2;				/**< F2 */
		PLInput::Button	KeyF3;				/**< F3 */
		PLInput::Button	KeyF4;				/**< F4 */
		PLInput::Button	KeyF5;				/**< F5 */
		PLInput::Button	KeyF6;				/**< F6 */
		PLInput::Button	KeyF7;				/**< F7 */
		PLInput::Button	KeyF8;				/**< F8 */
		PLInput::Button	KeyF9;				/**< F9 */
		PLInput::Button	KeyF10;				/**< F10 */
		PLInput::Button	KeyF11;				/**< F11 */
		PLInput::Button	KeyF12;				/**< F12 */
		PLInput::Button	KeyNumLock;			/**< Num lock */
		PLInput::Button	KeyScrollLock;		/**< Scroll lock */
		PLInput::Button	KeyCircumflex;		/**< Circumflex (^) */


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
