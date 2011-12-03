/*********************************************************\
 *  File: Connection.cpp                                 *
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
#include "PLCore/System/System.h"
#include "PLCore/Network/Host.h"
#include "PLCore/Network/Connection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Connection::Connection(Host &cHost) :
	m_pHost(&cHost),
	m_bConnected(false),
	m_nPort(0),
	m_nReceiveMode(ReceiveAutomatic)
{
}

/**
*  @brief
*    Disconnect
*/
bool Connection::Disconnect()
{
	// Are we still connected?
	if (m_bConnected) {
		// Disconnect
		m_bConnected = false;

		// Close connection
		m_cSocket.Close();

		// Emit disconnect event
		OnDisconnect();
		m_pHost->OnDisconnect(*this);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Receive data (blocking request)
*/
int Connection::Receive(char *pBuffer, uint32 nSize)
{
	// Read data from socket
	const int nBytes = m_cSocket.Receive(pBuffer, nSize);
	if (nBytes > 0)
		OnReceive(pBuffer, nBytes);
	return nBytes;
}

/**
*  @brief
*    Read line of text (blocking request)
*/
String Connection::ReadLine()
{
	// Read a line
	char szBuffer[256], *pszBuffer = szBuffer;
	while (Receive(pszBuffer, 1) == 1) {
		if (*pszBuffer == 10) {
			// End of line '\n'
			pszBuffer[1] = 0;
			return szBuffer;
		} else {
			// Next char
			if (pszBuffer < szBuffer + 254)	// Avoid buffer overflow
				pszBuffer++;
		}
	}

	// Error!
	return "";
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Connection::~Connection()
{
	// Stop connection
	Disconnect();
}

/**
*  @brief
*    Establish a connection to a host by specifying address and port
*/
bool Connection::Connect(const String &sHost, uint32 nPort)
{
	// Disconnect first
	if (IsConnected())
		Disconnect();

	// Create socket
	if (m_cSocket.IsValid()) {
		// Create socket address
		SocketAddress cSocketAddress;
		if (cSocketAddress.SetHostByName(sHost) && cSocketAddress.SetPort(nPort)) {
			// Connect to host
			if (m_cSocket.Connect(cSocketAddress)) {
				// Connection established
				m_sHostname  = sHost;
				m_nPort		 = nPort;
				m_bConnected = true;

				// Emit connect event
				OnConnect();
				m_pHost->OnConnect(*this);

				// Start connection thread
				Start();

				// Done
				return true;
			} // Error: Connecting to host at the given port failed!
		} // Error: Could not find host at the given port!
	} // Error: Opening socket failed!

	// Error!
	return false;
}

/**
*  @brief
*    Establish a connection to a host by using a given socket
*/
bool Connection::Connect(Socket &cSocket)
{
	// Disconnect first
	if (IsConnected())
		Disconnect();

	// Get connection socket
	if (cSocket.IsValid()) {
		// Save socket
		m_cSocket = cSocket;
	} else {
		// Error!
		return false;
	}

	// Connection established
	m_bConnected = true;

	// Emit connect event
	OnConnect();
	m_pHost->OnConnect(*this);

	// Start connection thread
	Start();

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Protected virtual Connection functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the connection is established
*/
void Connection::OnConnect()
{
	// To be implemented by derived classes
}

/**
*  @brief
*    Called when the connection is disconnected
*/
void Connection::OnDisconnect()
{
	// To be implemented by derived classes
}

/**
*  @brief
*    Called when the connection receives data
*/
void Connection::OnReceive(const char *pBuffer, uint32 nSize)
{
	// To be implemented by derived classes
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Connection::Connection(const Connection &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Connection &Connection::operator =(const Connection &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Receive data
*/
bool Connection::ReceiveData()
{
	// Check if connected
	if (m_bConnected) {
		// Shall data be received automatically?
		if (m_nReceiveMode == ReceiveAutomatic) {
			// Receive data
			char pBuffer[4096];
			if (Receive(pBuffer, 4096) > 0) {
				// Done
				return true;
			} else {
				// Error!
				Disconnect();
			}
		} else {
			// No, wait a second
			System::GetInstance()->Sleep(1000);
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual ThreadFunction functions              ]
//[-------------------------------------------------------]
int Connection::Run()
{
	// Receive new data from connection
	while (ReceiveData())
		;	// Nothing to do in here

	// Leave thread
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
