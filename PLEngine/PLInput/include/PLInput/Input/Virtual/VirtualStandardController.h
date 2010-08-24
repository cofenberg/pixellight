/*********************************************************\
 *  File: VirtualStandardController.h                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLINPUT_VIRTUALSTANDARDCONTROLLER_H__
#define __PLINPUT_VIRTUALSTANDARDCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Virtual/VirtualController.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Standard virtual input controller
*/
class VirtualStandardController : public VirtualController {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, VirtualStandardController, "PLInput", PLInput::VirtualController, "Standard virtual input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		// Mouse
		PLInput::Axis		MouseX;				/**< X axis */
		PLInput::Axis		MouseY;				/**< Y axis */
		PLInput::Axis		MouseWheel;			/**< Mouse wheel */
		PLInput::Button		MouseLeft;			/**< Left mouse button  */
		PLInput::Button		MouseRight;			/**< Right mouse button  */
		PLInput::Button		MouseMiddle;		/**< Middle mouse button  */
		PLInput::Button		MouseButton4;		/**< Mouse button #4 */
		PLInput::Button		MouseButton5;		/**< Mouse button #5 */
		PLInput::Button		MouseButton6;		/**< Mouse button #6 */
		PLInput::Button		MouseButton7;		/**< Mouse button #7 */
		PLInput::Button		MouseButton8;		/**< Mouse button #8 */
		PLInput::Button		MouseButton9;		/**< Mouse button #9 */
		PLInput::Button		MouseButton10;		/**< Mouse button #10 */
		PLInput::Button		MouseButton11;		/**< Mouse button #11 */
		PLInput::Button		MouseButton12;		/**< Mouse button #12 */

		// Keyboard
		PLInput::Button		KeyBack;			/**< Backspace */
		PLInput::Button		KeyTab;				/**< Tab */
		PLInput::Button		KeyClear;			/**< Clear (not available everywhere) */
		PLInput::Button		KeyReturn;			/**< Enter */
		PLInput::Button		KeyShift;			/**< Shift */
		PLInput::Button		KeyControl;			/**< Ctrl */
		PLInput::Button		KeyAlt;				/**< Alt */
		PLInput::Button		KeyPause;			/**< Pause */
		PLInput::Button		KeyCapsLock;		/**< Caps lock */
		PLInput::Button		KeyEscape;			/**< Escape */
		PLInput::Button		KeySpace;			/**< Space */
		PLInput::Button		KeyPageUp;			/**< Page up */
		PLInput::Button		KeyPageDown;		/**< Page down */
		PLInput::Button		KeyEnd;				/**< End */
		PLInput::Button		KeyHome;			/**< Home */
		PLInput::Button		KeyLeft;			/**< Left arrow */
		PLInput::Button		KeyUp;				/**< Up arrow */
		PLInput::Button		KeyRight;			/**< Right arrow */
		PLInput::Button		KeyDown;			/**< Down arrow */
		PLInput::Button		KeySelect;			/**< Select (not available everywhere) */
		PLInput::Button		KeyExecute;			/**< Execute (not available everywhere) */
		PLInput::Button		KeyPrintScreen;		/**< Print screen */
		PLInput::Button		KeyInsert;			/**< Insert */
		PLInput::Button		KeyDelete;			/**< Delete */
		PLInput::Button		KeyHelp;			/**< Help (not available everywhere) */
		PLInput::Button		Key0;				/**< 0 */
		PLInput::Button		Key1;				/**< 1 */
		PLInput::Button		Key2;				/**< 2 */
		PLInput::Button		Key3;				/**< 3 */
		PLInput::Button		Key4;				/**< 4 */
		PLInput::Button		Key5;				/**< 5 */
		PLInput::Button		Key6;				/**< 6 */
		PLInput::Button		Key7;				/**< 7 */
		PLInput::Button		Key8;				/**< 8 */
		PLInput::Button		Key9;				/**< 9 */
		PLInput::Button		KeyA;				/**< A */
		PLInput::Button		KeyB;				/**< B */
		PLInput::Button		KeyC;				/**< C */
		PLInput::Button		KeyD;				/**< D */
		PLInput::Button		KeyE;				/**< E */
		PLInput::Button		KeyF;				/**< F */
		PLInput::Button		KeyG;				/**< G */
		PLInput::Button		KeyH;				/**< H */
		PLInput::Button		KeyI;				/**< I */
		PLInput::Button		KeyJ;				/**< J */
		PLInput::Button		KeyK;				/**< K */
		PLInput::Button		KeyL;				/**< L */
		PLInput::Button		KeyM;				/**< M */
		PLInput::Button		KeyN;				/**< N */
		PLInput::Button		KeyO;				/**< O */
		PLInput::Button		KeyP;				/**< P */
		PLInput::Button		KeyQ;				/**< Q */
		PLInput::Button		KeyR;				/**< R */
		PLInput::Button		KeyS;				/**< S */
		PLInput::Button		KeyT;				/**< T */
		PLInput::Button		KeyU;				/**< U */
		PLInput::Button		KeyV;				/**< V */
		PLInput::Button		KeyW;				/**< W */
		PLInput::Button		KeyX;				/**< X */
		PLInput::Button		KeyY;				/**< Y */
		PLInput::Button		KeyZ;				/**< Z */
		PLInput::Button		KeyNumpad0;			/**< Numeric keypad 0 */
		PLInput::Button		KeyNumpad1;			/**< Numeric keypad 1 */
		PLInput::Button		KeyNumpad2;			/**< Numeric keypad 2 */
		PLInput::Button		KeyNumpad3;			/**< Numeric keypad 3 */
		PLInput::Button		KeyNumpad4;			/**< Numeric keypad 4 */
		PLInput::Button		KeyNumpad5;			/**< Numeric keypad 5 */
		PLInput::Button		KeyNumpad6;			/**< Numeric keypad 6 */
		PLInput::Button		KeyNumpad7;			/**< Numeric keypad 7 */
		PLInput::Button		KeyNumpad8;			/**< Numeric keypad 8 */
		PLInput::Button		KeyNumpad9;			/**< Numeric keypad 9 */
		PLInput::Button		KeyNumpadMultiply;	/**< Numeric keypad "Multiply" */
		PLInput::Button		KeyNumpadAdd;		/**< Numeric keypad "Add" */
		PLInput::Button		KeyNumpadSeparator;	/**< Numeric keypad "Separator" */
		PLInput::Button		KeyNumpadSubtract;	/**< Numeric keypad "Subtract" */
		PLInput::Button		KeyNumpadDecimal;	/**< Numeric keypad "Decimal" */
		PLInput::Button		KeyNumpadDivide;	/**< Numeric keypad "Divide" */
		PLInput::Button		KeyF1;				/**< F1 */
		PLInput::Button		KeyF2;				/**< F2 */
		PLInput::Button		KeyF3;				/**< F3 */
		PLInput::Button		KeyF4;				/**< F4 */
		PLInput::Button		KeyF5;				/**< F5 */
		PLInput::Button		KeyF6;				/**< F6 */
		PLInput::Button		KeyF7;				/**< F7 */
		PLInput::Button		KeyF8;				/**< F8 */
		PLInput::Button		KeyF9;				/**< F9 */
		PLInput::Button		KeyF10;				/**< F10 */
		PLInput::Button		KeyF11;				/**< F11 */
		PLInput::Button		KeyF12;				/**< F12 */
		PLInput::Button		KeyNumLock;			/**< Num lock */
		PLInput::Button		KeyScrollLock;		/**< Scroll lock */
		PLInput::Button		KeyCircumflex;		/**< Circumflex (^) */

		// Main character controls
		PLInput::Axis		TransX;				/**< X translation axis */
		PLInput::Axis		TransY;				/**< Y translation axis */
		PLInput::Axis		TransZ;				/**< Z translation axis */
		PLInput::Axis		RotX;				/**< X rotation axis */
		PLInput::Axis		RotY;				/**< Y rotation axis */
		PLInput::Axis		RotZ;				/**< Z rotation axis */
		PLInput::Button		Forward;			/**< Move forwards */
		PLInput::Button		Backward;			/**< Move backwards */
		PLInput::Button		Left;				/**< Move (rotate) left */
		PLInput::Button		Right;				/**< Move (rotate) right */
		PLInput::Button		StrafeLeft;			/**< Strafe left */
		PLInput::Button		StrafeRight;		/**< Strafe right */
		PLInput::Button		Up;					/**< Move up */
		PLInput::Button		Down;				/**< Move down */
		PLInput::Button		Run;				/**< Keep pressed to run */
		PLInput::Button		Crouch;				/**< Keep pressed to crouch */
		PLInput::Button		Button1;			/**< Button for action #1 */
		PLInput::Button		Button2;			/**< Button for action #2 */
		PLInput::Button		Button3;			/**< Button for action #3 */
		PLInput::Button		Button4;			/**< Button for action #4 */
		PLInput::Button		Button5;			/**< Button for action #5 */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API VirtualStandardController();

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~VirtualStandardController();


	//[-------------------------------------------------------]
	//[ Public virtual VirtualController functions            ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void ConnectToDevices();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_VIRTUALSTANDARDCONTROLLER_H__
