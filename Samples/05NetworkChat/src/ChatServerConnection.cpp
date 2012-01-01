/*********************************************************\
 *  File: ChatServerConnection.cpp                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/Network/Server.h>
#include "ChatServerConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace NetworkChat {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ChatServerConnection::ChatServerConnection(Host &cServer) : Connection(cServer)
{
}

/**
*  @brief
*    Destructor
*/
ChatServerConnection::~ChatServerConnection()
{
}

/**
*  @brief
*    Copy constructor
*/
ChatServerConnection::ChatServerConnection(ChatServerConnection &cSource) : Connection(cSource.GetHost())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ChatServerConnection &ChatServerConnection::operator =(const ChatServerConnection &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private PLCore::Connection functions                  ]
//[-------------------------------------------------------]
void ChatServerConnection::OnConnect()
{
	System::GetInstance()->GetConsole().Print("Accepted connection from " +  GetSocket().GetSocketAddress().GetHost() + '\n');
}

void ChatServerConnection::OnDisconnect()
{
	System::GetInstance()->GetConsole().Print("Client disconnected " +  GetSocket().GetSocketAddress().GetHost() + '\n');
}

void ChatServerConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	if (pBuffer) {
		// Compose server message (we use the string copy constructor to ensure that there's a correct terminating zero)
		const String sMessage = GetSocket().GetSocketAddress().GetHost() + ": '" + String(pBuffer, true, nSize-1) + '\''; // -1 = excluding the terminating zero

		// Write the message into the log and start a new line
		System::GetInstance()->GetConsole().Print(sMessage + '\n');

		// Send message to all clients
		for (uint32 i=0; i<GetHost().GetConnections().GetNumOfElements(); i++)
			GetHost().GetConnections().Get(i)->Send(sMessage.GetASCII(), sMessage.GetLength()+1);	// +1 so we also send the terminating zero
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // NetworkChat
