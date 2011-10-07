/*********************************************************\
 *  File: VirtualStandardController.h                    *
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
*
*  @remarks
*    3D coordinate system:
*    @code
*      y = > Translation: Move up/down (+/-) => Rotation: Yaw (also called 'heading') change is turning to the left or right
*      |
*      |
*      *---x => Translation: Strafe left/right (+/-) => Rotation: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)
*     /
*    z => Translation: Move forwards/backwards (+/-) => Rotation: Roll (also called 'attitude') change is moving one wingtip up and the other down
*    @endcode
**/
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
		Axis		MouseX;						/**< X axis */
		Axis		MouseY;						/**< Y axis */
		Axis		MouseWheel;					/**< Mouse wheel */
		Button		MouseLeft;					/**< Left mouse button (mouse button #0) */
		Button		MouseRight;					/**< Right mouse button (mouse button #1) */
		Button		MouseMiddle;				/**< Middle mouse button (mouse button #2) */
		Button		MouseButton4;				/**< Mouse button #4 */
		Button		MouseButton5;				/**< Mouse button #5 */
		Button		MouseButton6;				/**< Mouse button #6 */
		Button		MouseButton7;				/**< Mouse button #7 */
		Button		MouseButton8;				/**< Mouse button #8 */
		Button		MouseButton9;				/**< Mouse button #9 */
		Button		MouseButton10;				/**< Mouse button #10 */
		Button		MouseButton11;				/**< Mouse button #11 */
		Button		MouseButton12;				/**< Mouse button #12 */

		// Keyboard
		Button		KeyboardBackspace;			/**< Backspace */
		Button		KeyboardTab;				/**< Tab */
		Button		KeyboardClear;				/**< Clear (not available everywhere) */
		Button		KeyboardReturn;				/**< Return (often the same as "Enter") */
		Button		KeyboardShift;				/**< Shift */
		Button		KeyboardControl;			/**< Control ("Ctrl") */
		Button		KeyboardAlt;				/**< Alt */
		Button		KeyboardPause;				/**< Pause */
		Button		KeyboardCapsLock;			/**< Caps lock */
		Button		KeyboardEscape;				/**< Escape */
		Button		KeyboardSpace;				/**< Space */
		Button		KeyboardPageUp;				/**< Page up */
		Button		KeyboardPageDown;			/**< Page down */
		Button		KeyboardEnd;				/**< End */
		Button		KeyboardHome;				/**< Home */
		Button		KeyboardLeft;				/**< Left arrow */
		Button		KeyboardUp;					/**< Up arrow */
		Button		KeyboardRight;				/**< Right arrow */
		Button		KeyboardDown;				/**< Down arrow */
		Button		KeyboardSelect;				/**< Select (not available everywhere) */
		Button		KeyboardExecute;			/**< Execute (not available everywhere) */
		Button		KeyboardPrint;				/**< Print screen */
		Button		KeyboardInsert;				/**< Insert */
		Button		KeyboardDelete;				/**< Delete */
		Button		KeyboardHelp;				/**< Help (not available everywhere) */
		Button		Keyboard0;					/**< 0 */
		Button		Keyboard1;					/**< 1 */
		Button		Keyboard2;					/**< 2 */
		Button		Keyboard3;					/**< 3 */
		Button		Keyboard4;					/**< 4 */
		Button		Keyboard5;					/**< 5 */
		Button		Keyboard6;					/**< 6 */
		Button		Keyboard7;					/**< 7 */
		Button		Keyboard8;					/**< 8 */
		Button		Keyboard9;					/**< 9 */
		Button		KeyboardA;					/**< A */
		Button		KeyboardB;					/**< B */
		Button		KeyboardC;					/**< C */
		Button		KeyboardD;					/**< D */
		Button		KeyboardE;					/**< E */
		Button		KeyboardF;					/**< F */
		Button		KeyboardG;					/**< G */
		Button		KeyboardH;					/**< H */
		Button		KeyboardI;					/**< I */
		Button		KeyboardJ;					/**< J */
		Button		KeyboardK;					/**< K */
		Button		KeyboardL;					/**< L */
		Button		KeyboardM;					/**< M */
		Button		KeyboardN;					/**< N */
		Button		KeyboardO;					/**< O */
		Button		KeyboardP;					/**< P */
		Button		KeyboardQ;					/**< Q */
		Button		KeyboardR;					/**< R */
		Button		KeyboardS;					/**< S */
		Button		KeyboardT;					/**< T */
		Button		KeyboardU;					/**< U */
		Button		KeyboardV;					/**< V */
		Button		KeyboardW;					/**< W */
		Button		KeyboardX;					/**< X */
		Button		KeyboardY;					/**< Y */
		Button		KeyboardZ;					/**< Z */
		Button		KeyboardNumpad0;			/**< Numeric keypad 0 */
		Button		KeyboardNumpad1;			/**< Numeric keypad 1 */
		Button		KeyboardNumpad2;			/**< Numeric keypad 2 */
		Button		KeyboardNumpad3;			/**< Numeric keypad 3 */
		Button		KeyboardNumpad4;			/**< Numeric keypad 4 */
		Button		KeyboardNumpad5;			/**< Numeric keypad 5 */
		Button		KeyboardNumpad6;			/**< Numeric keypad 6 */
		Button		KeyboardNumpad7;			/**< Numeric keypad 7 */
		Button		KeyboardNumpad8;			/**< Numeric keypad 8 */
		Button		KeyboardNumpad9;			/**< Numeric keypad 9 */
		Button		KeyboardNumpadMultiply;		/**< Numeric keypad "Multiply" */
		Button		KeyboardNumpadAdd;			/**< Numeric keypad "Add" */
		Button		KeyboardNumpadSeparator;	/**< Numeric keypad "Separator" */
		Button		KeyboardNumpadSubtract;		/**< Numeric keypad "Subtract" */
		Button		KeyboardNumpadDecimal;		/**< Numeric keypad "Decimal" */
		Button		KeyboardNumpadDivide;		/**< Numeric keypad "Divide" */
		Button		KeyboardF1;					/**< F1 */
		Button		KeyboardF2;					/**< F2 */
		Button		KeyboardF3;					/**< F3 */
		Button		KeyboardF4;					/**< F4 */
		Button		KeyboardF5;					/**< F5 */
		Button		KeyboardF6;					/**< F6 */
		Button		KeyboardF7;					/**< F7 */
		Button		KeyboardF8;					/**< F8 */
		Button		KeyboardF9;					/**< F9 */
		Button		KeyboardF10;				/**< F10 */
		Button		KeyboardF11;				/**< F11 */
		Button		KeyboardF12;				/**< F12 */
		Button		KeyboardNumLock;			/**< Num lock */
		Button		KeyboardScrollLock;			/**< Scroll lock */
		Button		KeyboardCircumflex;			/**< Circumflex (^) */

		// Main character controls
		Axis		TransX;						/**< X translation axis: Strafe left/right (+/-) */
		Axis		TransY;						/**< Y translation axis: Move up/down (+/-) */
		Axis		TransZ;						/**< Z translation axis: Move forwards/backwards (+/-) */
		Button		Pan;						/**< Keep pressed to pan */
		Axis		PanX;						/**< X pan translation axis: Strafe left/right (+/-) */
		Axis		PanY;						/**< Y pan translation axis: Move up/down (+/-) */
		Axis		PanZ;						/**< Z pan translation axis: Move forwards/backwards (+/-) */
		Axis		RotX;						/**< X rotation axis: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa) */
		Axis		RotY;						/**< Y rotation axis: Yaw (also called 'heading') change is turning to the left or right */
		Axis		RotZ;						/**< Z rotation axis: Roll (also called 'attitude') change is moving one wingtip up and the other down */
		Button		Rotate;						/**< Keep pressed to rotate */
		Button		Forward;					/**< Move forwards */
		Button		Backward;					/**< Move backwards */
		Button		Left;						/**< Move (rotate) left */
		Button		Right;						/**< Move (rotate) right */
		Button		StrafeLeft;					/**< Strafe left */
		Button		StrafeRight;				/**< Strafe right */
		Button		Up;							/**< Move up */
		Button		Down;						/**< Move down */
		Button		Run;						/**< Keep pressed to run */
		Button		Crouch;						/**< Keep pressed to crouch */
		Button		Jump;						/**< Jump */
		Button		Zoom;						/**< Keep pressed to zoom */
		Axis		ZoomAxis;					/**< Zoom axis to zoom in or out (+/-) */
		Button		Button1;					/**< Button for action #1 */
		Button		Button2;					/**< Button for action #2 */
		Button		Button3;					/**< Button for action #3 */
		Button		Button4;					/**< Button for action #4 */
		Button		Button5;					/**< Button for action #5 */

		// Interaction
		Button		Pickup;						/**< Keep pressed to pickup */
		Button		Throw;						/**< Throw the picked object */
		Button		IncreaseForce;				/**< Keep pressed to increase the force applied to the picked object */
		Button		DecreaseForce;				/**< Keep pressed to decrease the force applied to the picked object */
		Axis		PushPull;					/**< Used to push/pull the picked object */


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
		PLINPUT_API virtual void ConnectToDevices() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_VIRTUALSTANDARDCONTROLLER_H__
