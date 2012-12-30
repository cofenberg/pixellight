/*********************************************************\
 *  File: ChatClientConnection.cpp                       *
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
	System::GetInstance()->GetConsole().Print("Client started\n");
}

void ChatClientConnection::OnDisconnect()
{
	System::GetInstance()->GetConsole().Print("Client shutdown\n");
}

void ChatClientConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	if (pBuffer) {
		// Print message (we use the string copy constructor to ensure that there's a correct terminating zero)
		System::GetInstance()->GetConsole().Print(String(pBuffer, true, nSize-1) + '\n');	// -1 = excluding the terminating zero
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // NetworkChat
