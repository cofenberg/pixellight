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
#include "PLGeneral/System/System.h"
#include "PLGeneral/Network/Host.h"
#include "PLGeneral/Network/Connection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


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
*    Get host that owns this connection
*/
const Host &Connection::GetHost() const
{
	// Return host
	return *m_pHost;
}

/**
*  @brief
*    Get host that owns this connection
*/
Host &Connection::GetHost()
{
	// Return host
	return *m_pHost;
}

/**
*  @brief
*    Get name of connected host
*/
String Connection::GetHostname() const
{
	// Return host name
	return m_sHostname;
}

/**
*  @brief
*    Get port
*/
uint32 Connection::GetPort() const
{
	// Return port number
	return m_nPort;
}

/**
*  @brief
*    Get socket
*/
const Socket &Connection::GetSocket() const
{
	// Return socket
	return m_cSocket;
}

/**
*  @brief
*    Get socket
*/
Socket &Connection::GetSocket()
{
	// Return socket
	return m_cSocket;
}

/**
*  @brief
*    Check if connection is active
*/
bool Connection::IsConnected() const
{
	// Return state
	return m_bConnected;
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
*    Get receive mode
*/
Connection::EReceiveMode Connection::GetReceiveMode() const
{
	// Return receive mode
	return m_nReceiveMode;
}

/**
*  @brief
*    Set receive mode
*/
void Connection::SetReceiveMode(EReceiveMode nReceiveMode)
{
	// Set receive mode
	m_nReceiveMode = nReceiveMode;
}

/**
*  @brief
*    Receive data
*/
int Connection::Receive(char *pBuffer, uint32 nSize)
{
	// Read data from socket
	int nBytes = m_cSocket.Receive(pBuffer, nSize);
	if (nBytes > 0) {
		OnReceive(pBuffer, nSize);
	}
	return nBytes;
}

/**
*  @brief
*    Read line of text
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

/**
*  @brief
*    Send data
*/
int Connection::Send(const char *pBuffer, uint32 nSize) const
{
	// Send data buffer
	return (pBuffer && nSize > 0) ? m_cSocket.Send(pBuffer, nSize) : -1;
}

/**
*  @brief
*    Send string
*/
int Connection::Send(const String &sString) const
{
	// Check if string is not empty
	if (sString.GetLength()) {
		// Send string
		// [TODO] What's with Unicode strings?? Check \0 at the end...
		return Send(sString.GetASCII(), sString.GetLength());
	} else return -1; // Error, invalid string
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
	if (IsConnected()) Disconnect();

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
	if (IsConnected()) Disconnect();

	// Get connection socket
	if (cSocket.IsValid()) {
		// Save socket
		m_cSocket = cSocket;
	} else return false; // Error!

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
			} else Disconnect(); // Error!
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
	while (ReceiveData());

	// Leave thread
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
