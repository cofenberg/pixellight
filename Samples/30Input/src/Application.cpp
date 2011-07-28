/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/Tools/Localization.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Devices/Device.h>
#include <PLInput/Input/Controls/Effect.h>
#include <PLInput/Input/Controls/LED.h>
#include <PLInput/Input/Virtual/VirtualStandardController.h>
#include "Application.h"
#include "GameBoyController.h"
#ifdef WIN32
	#include <Windows.h>
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLInput;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	EventHandlerOnControl(&Application::OnControl, this),
	EventHandlerOnControlExit(&Application::OnControlExit, this),
	m_bExit(false)
{
	// Set application name and title
	SetName("30Input");
	SetTitle(PLT("PLSample 30 - Input"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}

/**
*  @brief
*    Test: List devices
*/
void Application::TestDevices()
{
	// Start
	System::GetInstance()->GetConsole().Print("Input devices:\n");

	// Get device list
	const List<Device*> &lstDevices = InputManager::GetInstance()->GetDevices();
	for (uint32 i=0; i<lstDevices.GetNumOfElements(); i++) {
		// Get device
		Device *pDevice = lstDevices[i];
		String  sName = pDevice->GetName();
		String  sDesc = pDevice->GetDescription();

		// Print device info
		System::GetInstance()->GetConsole().Print("- " + sName + ": " + sDesc + '\n');
	}

	// Done
	System::GetInstance()->GetConsole().Print('\n');
}

/**
*  @brief
*    Test: Controller
*/
void Application::TestController()
{
	// Start
	System::GetInstance()->GetConsole().Print("Controller 'GameBoy'\n");
	System::GetInstance()->GetConsole().Print('\n');

	// Create test controller
	GameBoyController cController;

	// List all controls
	System::GetInstance()->GetConsole().Print("Controls:\n");
	const List<Control*> &lstControls = cController.GetControls();
	for (uint32 i=0; i<lstControls.GetNumOfElements(); i++) {
		// Get control
		Control *pControl = lstControls[i];
		if (pControl->GetType() == ControlButton) {
			System::GetInstance()->GetConsole().Print("- Button '" + pControl->GetName() + "' [" + pControl->GetDescription() + "]\n");
		} else if (pControl->GetType() == ControlAxis) {
			System::GetInstance()->GetConsole().Print("- Axis   '" + pControl->GetName() + "' [" + pControl->GetDescription() + "]\n");
		}
	}
	System::GetInstance()->GetConsole().Print('\n');

	// List buttons
	System::GetInstance()->GetConsole().Print("Buttons:\n");
	const List<Button*> &lstButtons = cController.GetButtons();
	for (uint32 i=0; i<lstButtons.GetNumOfElements(); i++) {
		Button *pButton = lstButtons[i];
		System::GetInstance()->GetConsole().Print("- Button   '" + pButton->GetName() + "' [" + pButton->GetDescription() + "]\n");
	}
	System::GetInstance()->GetConsole().Print('\n');

	// List axes
	System::GetInstance()->GetConsole().Print("Axes:\n");
	const List<Axis*> &lstAxes = cController.GetAxes();
	for (uint32 i=0; i<lstAxes.GetNumOfElements(); i++) {
		Axis *pAxis = lstAxes[i];
		System::GetInstance()->GetConsole().Print("- Axis '" + pAxis->GetName() + "' [" + pAxis->GetDescription() + "]\n");
	}
	System::GetInstance()->GetConsole().Print('\n');

	// Done
	System::GetInstance()->GetConsole().Print('\n');
}

/**
*  @brief
*    Test: Input
*/
void Application::TestInput(const String &sDevice)
{
	// Start
	System::GetInstance()->GetConsole().Print("Getting input from device '" + sDevice + "'\n");

	// Connect keyboard
	Device *pDevice = InputManager::GetInstance()->GetDevice("Keyboard");
	if (pDevice) {
		// Connect event handler
		pDevice->OnControl.Connect(EventHandlerOnControlExit);
	}

	// Get device
	pDevice = InputManager::GetInstance()->GetDevice(sDevice);
	if (pDevice) {
		// Connect event handler
		pDevice->OnControl.Connect(EventHandlerOnControl);

		// Main loop
		m_bExit = false;
		while (!m_bExit) {
			// Update devices
			PLInput::InputManager::GetInstance()->Update();

			// Get messages
			#ifdef WIN32
				MSG sMsg;
				if (PeekMessage(&sMsg, nullptr, 0, 0, FALSE)) {
					GetMessage(&sMsg, nullptr, 0, 0);
					TranslateMessage(&sMsg);
					DispatchMessage(&sMsg);
				}
			#endif

			// Wait 10 milliseconds
			System::GetInstance()->Sleep(10);
		}
	} else {
		// Error
		System::GetInstance()->GetConsole().Print("ERROR: Could not get device\n");
	}
}

/**
*  @brief
*    Test: GetChar() functionality
*/
void Application::TestGetChar(const String &sDevice)
{
	// Start
	System::GetInstance()->GetConsole().Print("Testing GetChar() with device '" + sDevice + "'\n");

	// Get device
	Device *pDevice = InputManager::GetInstance()->GetDevice(sDevice);
	if (pDevice) {
		String sInput;

		// Main loop
		m_bExit = false;
		while (!m_bExit) {
			// Get messages
			#ifdef WIN32
				MSG sMsg;
				if (PeekMessage(&sMsg, nullptr, 0, 0, FALSE)) {
					GetMessage(&sMsg, nullptr, 0, 0);
					TranslateMessage(&sMsg);
					DispatchMessage(&sMsg);
				}
			#endif

			// Update devices
			PLInput::InputManager::GetInstance()->Update();

			// Get character
			char nChar = pDevice->GetChar();
			if (nChar != '\0') {
				// Escape
				if (nChar == 0x1B) {
					// Exit
					m_bExit = true;
				}

				// Enter
				else if (nChar == 0x0D) {
					// Next word
					System::GetInstance()->GetConsole().Print('\n');
					sInput = "";
				}

				// Backspace
				else if (nChar == 0x08) {
					// Delete last character
					sInput = sInput.GetSubstring(0, sInput.GetLength()-1);

					// Print on next line
					System::GetInstance()->GetConsole().Print('\n');
					System::GetInstance()->GetConsole().Print(sInput);
				}

				// Character
				else if ((nChar >= '0' && nChar <= '9') || (nChar >= 'a' && nChar <= 'z') ||
						  nChar == '+' || nChar == '-' || nChar == '*' || nChar == '/' || nChar == ',' || nChar == '.' ||
						  nChar == 0x20)
				{
					// Add char to string
					sInput += nChar;

					// Print char
					System::GetInstance()->GetConsole().Print(String() + nChar);
				}
			}

			// Wait 10 milliseconds
			System::GetInstance()->Sleep(10);
		}
	} else {
		// Error
		System::GetInstance()->GetConsole().Print("ERROR: Could not get device\n");
	}
}

/**
*  @brief
*    Test: Connections
*/
void Application::TestConnections()
{
	// Start
	System::GetInstance()->GetConsole().Print("Connecting virtual controller\n");

	// Connect keyboard
	Device *pDevice = InputManager::GetInstance()->GetDevice("Keyboard");
	if (pDevice) {
		// Connect event handler
		pDevice->OnControl.Connect(EventHandlerOnControlExit);
	}

	// Create virtual controller
	VirtualController *pVirtualController = new VirtualStandardController();
	pVirtualController->ConnectToDevices();

	// Get device
	pDevice = reinterpret_cast<Device*>(pVirtualController);
	if (pDevice) {
		// Connect event handler
		pDevice->OnControl.Connect(EventHandlerOnControl);

		// Main loop
		m_bExit = false;
		while (!m_bExit) {
			// Update devices
			PLInput::InputManager::GetInstance()->Update();

			// Get messages
			#ifdef WIN32
				MSG sMsg;
				if (PeekMessage(&sMsg, nullptr, 0, 0, FALSE)) {
					GetMessage(&sMsg, nullptr, 0, 0);
					TranslateMessage(&sMsg);
					DispatchMessage(&sMsg);
				}
			#endif

			// Wait 10 milliseconds
			System::GetInstance()->Sleep(10);
		}
	}

	// Destroy virtual controller
	delete pVirtualController;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a control of the input controller has been activated
*/
void Application::OnControl(Control *pControl)
{
	// Get name of control
	String sControl = pControl->GetName();

	// Display control value
	String sValue;
	if (pControl->GetType() == ControlButton) {
		sValue = static_cast<Button*>(pControl)->IsPressed() ? "<pressed>" : "<released>";
	} else if (pControl->GetType() == ControlAxis) {
		sValue = String::Format("%5.2f", static_cast<Axis*>(pControl)->GetValue());
	}
	System::GetInstance()->GetConsole().Print("- '" + sControl + "': " + sValue + '\n');

	// LED test
	if ((pControl->GetName() == "Plus" || pControl->GetName() == "Minus") && static_cast<Button*>(pControl)->IsPressed()) {
		// Get LED control
		LED *pLED = static_cast<LED*>(pControl->GetController()->GetControl("LED"));
		if (pLED) {
			// Change LED value
			uint32 nLED = pLED->GetLEDs();
			if (pControl->GetName() == "Plus")	nLED++;
			else								nLED--;
			if (nLED > 15) nLED = 0;
			pLED->SetLEDs(nLED);
		}
	}

	// Rumble test
	if (pControl->GetName() == "Button1" || pControl->GetName() == "Button2") {
		// Get rumble control (try "Rumble3" first for joystick, then "Rumble1" for WiiMote)
		Effect *pRumble = static_cast<Effect*>(pControl->GetController()->GetControl("Rumble3"));
		if (!pRumble) pRumble = static_cast<Effect*>(pControl->GetController()->GetControl("Rumble1"));
		if (pRumble) {
			// Enable or disable rumble?
			if (pControl->GetName() == "Button1")
				pRumble->SetValue(1.0f);
			if (pControl->GetName() == "Button2")
				pRumble->SetValue(0.0f);
		}
	}
}

/**
*  @brief
*    Called when a control of the input controller has been activated
*/
void Application::OnControlExit(Control *pControl)
{
	// Exit?
	if (pControl->GetName() == "Escape" || pControl->GetName() == "Q") {
		m_bExit = true;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Detect input devices
	System::GetInstance()->GetConsole().Print("Detecting input devices: ");
	InputManager::GetInstance()->DetectDevices();
	System::GetInstance()->GetConsole().Print("done.\n");

	// Run test
	TestDevices();
//	TestController();
//	TestInput("Keyboard");
//	TestInput("Mouse");
//	TestInput("Joystick0");
//	TestInput("WiiMote0");
//	TestInput("SpaceMouse0");
//	TestGetChar("Keyboard");
	TestConnections();
}
