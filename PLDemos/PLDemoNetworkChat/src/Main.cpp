/*********************************************************\
 *  File: Main.cpp                                       *
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
#include <PLGeneral/Main.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLCore/ModuleMain.h>
#include "ChatServer.h"
#include "ChatClient.h"
#include "ChatClientConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDemoNetworkChat {


//[-------------------------------------------------------]
//[ Module implementation                                 ]
//[-------------------------------------------------------]
pl_module("PLDemoNetworkChat")
	pl_module_vendor("Copyright (C) 2002-2010 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight chat demo")
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
	System::GetInstance()->GetConsole().Print("Press 'ESC' to exit the server");
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
	ChatClientConnection *pConnection = (ChatClientConnection*)cClient.Connect("localhost", 4000);
	if (pConnection) {
		bool bActive = true;
		String sMessage;

		// Main loop
		System::GetInstance()->GetConsole().Print("Input text to send and press 'Enter'\nPress 'ESC' to exit the client");
		while (bActive) {
			// Let the system some time to process other system tasks etc.
			// If this isn't done the CPU usage is nearly up to 100%!
			System::GetInstance()->Sleep(1);

			// Update client
			if (pConnection->IsConnected()) {
				// Check keys
				if (System::GetInstance()->GetConsole().IsKeyHit()) {
					// Get key
					char c = System::GetInstance()->GetConsole().GetCharacter();

					// Quit
					if (c == 27)
						bActive = false;

					// Message
					else if (c == 13) {
						// New line on the console, please
						System::GetInstance()->GetConsole().Print('\n');

						// Send the message
						pConnection->Send(sMessage, sMessage.GetLength() + 1);

						// Clear the message
						sMessage = "";

					// Character
					} else {
						// Add character to the message
						sMessage += c;

						// Output the character on the console
						System::GetInstance()->GetConsole().Print(c);
					}
				}
			} else {
				// Connection broken...
				System::GetInstance()->GetConsole().Print("Error: Connection to the server broken... press any key to exit");
				bActive = false;

				// Wait for the 'any key'
				System::GetInstance()->GetConsole().GetCharacter();
			}
		}

		// Shutdown our client
		pConnection->Disconnect();
	} else {
		// Error!
		System::GetInstance()->GetConsole().Print("Error: Could not connect to server... press any key to exit");

		// Wait for the 'any key'
		System::GetInstance()->GetConsole().GetCharacter();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDemoNetworkChat


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Main function
*/
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	// Start server or client
	System::GetInstance()->GetConsole().Print("Please choose S)erver or C)lient\n");
	if (System::GetInstance()->GetConsole().GetCharacter() == 's')
		PLDemoNetworkChat::RunServer();
	else
		PLDemoNetworkChat::RunClient();

	// Done
	return 0;
}
