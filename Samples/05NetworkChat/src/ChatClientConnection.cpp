/*********************************************************\
 *  File: ChatClientConnection.cpp                       *
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
#include "ChatClientConnection.h"


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
ChatClientConnection::ChatClientConnection(Host &cClient) : Connection(cClient)
{
}

/**
*  @brief
*    Destructor
*/
ChatClientConnection::~ChatClientConnection()
{
}

/**
*  @brief
*    Copy constructor
*/
ChatClientConnection::ChatClientConnection(ChatClientConnection &cSource) : Connection(cSource.GetHost())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ChatClientConnection &ChatClientConnection::operator =(const ChatClientConnection &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private PLCore::Connection functions                  ]
//[-------------------------------------------------------]
void ChatClientConnection::OnConnect()
{
	System::GetInstance()->GetConsole().Print("Client started");
}

void ChatClientConnection::OnDisconnect()
{
	System::GetInstance()->GetConsole().Print("Client shutdown");
}

void ChatClientConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	if (pBuffer) {
		// We really need to check whether there's already terminating zero
		for (uint32 i=0; i<nSize; i++) {
			if (pBuffer[i] == '\0')
				nSize = i; // 'Clamp' the size, the loop will now stop automatically
		}

		// Print message (we use the string copy constructor to ensure that there's a correct terminating zero)
		System::GetInstance()->GetConsole().Print(String(pBuffer, true, nSize));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // NetworkChat
