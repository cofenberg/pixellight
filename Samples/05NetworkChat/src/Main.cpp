/*********************************************************\
 *  File: Main.cpp                                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Main.h>
#include <PLCore/ModuleMain.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include "ChatServer.h"
#include "ChatClient.h"
#include "ChatClientConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace NetworkChat {


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("05NetworkChat")
	pl_module_vendor("Copyright (C) 2002-2012 by The PixelLight Team")
	pl_module_license("\"MIT License\" which is also known as \"X11 License\" or \"MIT X License\" (mit-license.org)")
	pl_module_description("PixelLight chat sample")
pl_module_end


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Run server
*/
int RunServer()
{
	// Create server at port '4000' with a maximum allowed number of '16' connections
	ChatServer cServer;
	cServer.SetMaxConnections(16);
	cServer.Listen(4000);

	// Main loop
	System::GetInstance()->GetConsole().Print("Press 'ESC' to exit the server\n");
	while (cServer.IsListening()) {
		// Let the system some time to process other system tasks etc.
		// If this isn't done the CPU usage is nearly up to 100%!
		System::GetInstance()->Sleep(1);

		// Check keys
		if (System::GetInstance()->GetConsole().IsKeyHit()) {
			// ESC: Exit server
			if (System::GetInstance()->GetConsole().GetCharacter() == 27) {
				// Shut down server
				cServer.Close();
			}
		}
	}

	// Done
	return 0;
}

/**
*  @brief
*    Run client
*/
void RunClient()
{
	// Create client
	ChatClient cClient;

	// Create a client connection at host address 'localhost' (our local server) at port '4000'
	ChatClientConnection *pConnection = static_cast<ChatClientConnection*>(cClient.Connect("localhost", 4000));
	if (pConnection) {
		bool bActive = true;
		String sMessage;

		// Main loop
		System::GetInstance()->GetConsole().Print("Input text to send and press 'Enter'\nPress 'ESC' to exit the client\n");
		while (bActive) {
			// Let the system some time to process other system tasks etc.
			// If this isn't done the CPU usage is nearly up to 100%!
			System::GetInstance()->Sleep(1);

			// Update client
			if (pConnection->IsConnected()) {
				// Check keys
				if (System::GetInstance()->GetConsole().IsKeyHit()) {
					// Get key and interpret it as character, not number
					const wchar_t nCharacter = static_cast<wchar_t>(System::GetInstance()->GetConsole().GetCharacter());

					// Quit
					if (nCharacter == 27)
						bActive = false;

					// Message
					else if (nCharacter == 13) {
						// New line on the console, please
						System::GetInstance()->GetConsole().Print('\n');

						// Send the message
						pConnection->Send(sMessage, sMessage.GetLength() + 1);

						// Clear the message
						sMessage = "";

					// Character
					} else {
						// Add character to the message
						sMessage += nCharacter;

						// Output the character on the console
						System::GetInstance()->GetConsole().Print(nCharacter);
					}
				}
			} else {
				// Connection broken...
				System::GetInstance()->GetConsole().Print("Error: Connection to the server broken... press any key to exit\n");
				bActive = false;

				// Wait for the 'any key'
				System::GetInstance()->GetConsole().GetCharacter();
			}
		}

		// Shutdown our client
		pConnection->Disconnect();
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Error: Could not connect to server... press any key to exit\n");

		// Wait for the 'any key'
		System::GetInstance()->GetConsole().GetCharacter();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // NetworkChat


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Main function
*/
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Start server or client
	System::GetInstance()->GetConsole().Print("Please choose S)erver or C)lient\n");
	if (System::GetInstance()->GetConsole().GetCharacter() == 's')
		NetworkChat::RunServer();
	else
		NetworkChat::RunClient();

	// Done
	return 0;
}
