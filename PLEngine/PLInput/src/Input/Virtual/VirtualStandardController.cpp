/*********************************************************\
 *  File: VirtualStandardController.cpp                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/InputManager.h"
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Input/Devices/Joystick.h"
#include "PLInput/Input/Devices/SpaceMouse.h"
#include "PLInput/Input/Devices/WiiMote.h"
#include "PLInput/Input/Virtual/VirtualStandardController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(VirtualStandardController)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VirtualStandardController::VirtualStandardController() : VirtualController("VirtualStandardController", "Standard virtual input controller"),
	// Mouse
	MouseX				(this, "MouseX",		"X axis"),
	MouseY				(this, "MouseY",		"Y axis"),
	MouseWheel			(this, "MouseWheel",	"Mouse wheel"),
	MouseLeft			(this, "MouseLeft",		"Left mouse button "),
	MouseRight			(this, "MouseRight",	"Right mouse button "),
	MouseMiddle			(this, "MouseMiddle",	"Middle mouse button "),
	MouseButton4		(this, "MouseButton4",	"Mouse button #4"),
	MouseButton5		(this, "MouseButton5",	"Mouse button #5"),
	MouseButton6		(this, "MouseButton6",	"Mouse button #6"),
	MouseButton7		(this, "MouseButton7",	"Mouse button #7"),
	MouseButton8		(this, "MouseButton8",	"Mouse button #8"),
	MouseButton9		(this, "MouseButton9",	"Mouse button #9"),
	MouseButton10		(this, "MouseButton10",	"Mouse button #10"),
	MouseButton11		(this, "MouseButton11",	"Mouse button #11"),
	MouseButton12		(this, "MouseButton12",	"Mouse button #12"),
	// Keyboard
	KeyBack				(this, "Backspace",		"Backspace",							0x08),
	KeyTab				(this, "Tab",			"Tabulator",							0x09),
	KeyClear			(this, "Clear",			"Clear (not available everywhere)",		0x00),
	KeyReturn			(this, "Enter",			"Enter",								0x0D),
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
	KeyCircumflex		(this, "Circumflex",	"Circumflex",							0x00),
	// Main character controls
	TransX				(this, "TransX",		"X translation axis: Strafe left/right (+/-)"),
	TransY				(this, "TransY",		"Y translation axis: Move up/down (+/-)"),
	TransZ				(this, "TransZ",		"Z translation axis: Move forwards/backwards (+/-)"),
	RotX				(this, "RotX",			"X rotation axis: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)"),
	RotY				(this, "RotY",			"Y rotation axis: Yaw (also called 'heading') change is turning to the left or right"),
	RotZ				(this, "RotZ",			"Z rotation axis: Roll (also called 'attitude') change is moving one wingtip up and the other down"),
	Forward				(this, "Forward",		"Move forwards",						0x00),
	Backward			(this, "Backward",		"Move backwards",						0x00),
	Left				(this, "Left",			"Move (rotate) left",					0x00),
	Right				(this, "Right",			"Move (rotate) right",					0x00),
	StrafeLeft			(this, "StrafeLeft",	"Strafe left",							0x00),
	StrafeRight			(this, "StrafeRight",	"Strafe right",							0x00),
	Up					(this, "Up",			"Move up",								0x00),
	Down				(this, "Down",			"Move down",							0x00),
	Run					(this, "Run",			"Keep pressed to run",					0x00),
	Crouch				(this, "Crouch",		"Keep pressed to crouch",				0x00),
	Jump				(this, "Jump",			"Jump",									0x00),
	Button1				(this, "Button1",		"Button for action #1",					0x00),
	Button2				(this, "Button2",		"Button for action #2",					0x00),
	Button3				(this, "Button3",		"Button for action #3",					0x00),
	Button4				(this, "Button4",		"Button for action #4",					0x00),
	Button5				(this, "Button5",		"Button for action #5",					0x00)
{
}

/**
*  @brief
*    Destructor
*/
VirtualStandardController::~VirtualStandardController()
{
}


//[-------------------------------------------------------]
//[ Public virtual VirtualStandardController functions    ]
//[-------------------------------------------------------]
void VirtualStandardController::ConnectToDevices()
{
	// Connect mouse
	ConnectAll((Controller*)InputManager::GetInstance()->GetMouse(), "Mouse", "");

	// Connect keyboard
	ConnectAll((Controller*)InputManager::GetInstance()->GetKeyboard(), "", "");

	// Connect character controls
	List<Device*> &lstDevices = InputManager::GetInstance()->GetDevices();
	for (uint32 i=0; i<lstDevices.GetNumOfElements(); i++) {
		// Get device
		Device *pDevice = lstDevices[i];

		// Mouse
		if (pDevice->GetName() == "Mouse") {
			// Get mouse
			Mouse *pMouse = (Mouse*)pDevice;

			// Movement
			// RotX: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)
			Connect("RotX",			&pMouse->Y);
			// RotY: Yaw (also called 'heading') change is turning to the left or right
			Connect("RotY",			&pMouse->X, -1.0f);

			// Buttons
			Connect("Button1",		&pMouse->Left);
			Connect("Button2",		&pMouse->Right);
			Connect("Button3",		&pMouse->Middle);
			Connect("Button4",		&pMouse->Button4);
			Connect("Button5",		&pMouse->Button5);
		}

		// Keyboard
		else if (pDevice->GetName() == "Keyboard") {
			// Get keyboard
			Keyboard *pKeyboard = (Keyboard*)pDevice;

			// WASD
			Connect("Forward",		&pKeyboard->KeyW);
			Connect("Backward",		&pKeyboard->KeyS);
			Connect("StrafeLeft",   &pKeyboard->KeyA);
			Connect("StrafeRight",  &pKeyboard->KeyD);
			Connect("Left",			&pKeyboard->KeyQ);
			Connect("Right",		&pKeyboard->KeyE);

			// Cursor keys
			Connect("Forward",		&pKeyboard->KeyUp);
			Connect("Backward",		&pKeyboard->KeyDown);
			Connect("Left",			&pKeyboard->KeyLeft);
			Connect("Right",		&pKeyboard->KeyRight);

			// Look up/down
			Connect("Up",			&pKeyboard->KeyPageUp);
			Connect("Down",			&pKeyboard->KeyPageDown);

			// Run/crouch/jump
			Connect("Run",			&pKeyboard->KeyShift);
			Connect("Crouch",		&pKeyboard->KeyControl);
			Connect("Jump",			&pKeyboard->KeySpace);

			// Buttons
			Connect("Button1",		&pKeyboard->KeySpace);
			Connect("Button2",		&pKeyboard->KeyReturn);
			Connect("Button3",		&pKeyboard->KeyBack);
			Connect("Button4",		&pKeyboard->KeyAlt);
			Connect("Button5",		&pKeyboard->KeyCircumflex);
		}

		// Joystick
		else if (pDevice->GetName().IsSubstring("Joystick")) {
			// Get joystick
			Joystick *pJoystick = (Joystick*)pDevice;

			// Movement
			// RotX: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)
			Connect("RotX",			&pJoystick->Y, 4.0f);
			// RotY: Yaw (also called 'heading') change is turning to the left or right
			Connect("RotY",			&pJoystick->X, 4.0f);

			// Buttons
			Connect("Button1",		&pJoystick->Button0);
			Connect("Button2",		&pJoystick->Button1);
			Connect("Button3",		&pJoystick->Button2);
			Connect("Button4",		&pJoystick->Button3);
			Connect("Button5",		&pJoystick->Button4);
		}

		// SpaceMouse
		else if (pDevice->GetName().IsSubstring("SpaceMouse")) {
			// Get space mouse
			SpaceMouse *pSpaceMouse = (SpaceMouse*)pDevice;

			// Movement
			// RotX: Pitch (also called 'bank') change is moving the nose down and the tail up (or vice-versa)
			Connect("RotX",			&pSpaceMouse->RotX,   -1.0f/90.0f);
			// RotY: Yaw (also called 'heading') change is turning to the left or right
			Connect("RotY",			&pSpaceMouse->RotZ,   -1.0f/90.0f);
			// RotZ: Roll (also called 'attitude') change is moving one wingtip up and the other down
			Connect("RotZ",			&pSpaceMouse->RotY,   -1.0f/90.0f);
			// X translation axis: Strafe left/right (+/-)
			Connect("TransX",		&pSpaceMouse->TransX, -1.0f/90.0f);
			// Y translation axis: Move up/down (+/-)
			Connect("TransY",		&pSpaceMouse->TransY, -1.0f/90.0f);
			// Z translation axis: Move forwards/backwards (+/-)
			Connect("TransZ",		&pSpaceMouse->TransZ, -1.0f/90.0f);

			// Buttons
			Connect("Button1",		&pSpaceMouse->Button0);
			Connect("Button2",		&pSpaceMouse->Button1);
			Connect("Button3",		&pSpaceMouse->Button2);
			Connect("Button4",		&pSpaceMouse->Button3);
			Connect("Button5",		&pSpaceMouse->Button4);
		}

		// WiiMote
		else if (pDevice->GetName().IsSubstring("WiiMote")) {
			// Get WiiMote
			WiiMote *pWiiMote = (WiiMote*)pDevice;

			// Movement
			// [TODO] We need some more logic here to calculate movement from WiiMote data

			// Cursor keys
			Connect("Forward",		&pWiiMote->ButtonUp);
			Connect("Backward",		&pWiiMote->ButtonDown);
			Connect("Left",			&pWiiMote->ButtonLeft);
			Connect("Right",		&pWiiMote->ButtonRight);

			// Buttons
			Connect("Button1",		&pWiiMote->ButtonA);
			Connect("Button2",		&pWiiMote->ButtonB);
			Connect("Button3",		&pWiiMote->Button1);
			Connect("Button4",		&pWiiMote->Button2);
			Connect("Button5",		&pWiiMote->ButtonHome);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
