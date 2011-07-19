/*********************************************************\
 *  File: Socket.cpp                                     *
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
#ifdef WIN32
	#include <winsock.h>
#endif
#ifdef LINUX
	#include <netdb.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif
#include "PLCore/Network/Socket.h"


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#ifdef WIN32
	#define socklen_t int
#endif
#ifdef LINUX
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR   -1
#endif


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
Socket::Socket() :
	m_nSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
}

/**
*  @brief
*    Copy constructor
*/
Socket::Socket(const Socket &cSocket) :
	m_cSocketAddress(cSocket.m_cSocketAddress),
	m_nSocket(cSocket.m_nSocket)
{
}

/**
*  @brief
*    Constructor
*/
Socket::Socket(int nSocket) :
	m_nSocket(nSocket)
{
}

/**
*  @brief
*    Destructor
*/
Socket::~Socket()
{
	// Note that we are NOT allowed to close the current socket in here automatically
	// or we may end up in an ugly mess
}

/**
*  @brief
*    Returns whether the socket is currently valid
*/
bool Socket::IsValid() const
{
	return (m_nSocket != INVALID_SOCKET);
}

/**
*  @brief
*    Closes the socket
*/
bool Socket::Close()
{
	// Valid socket?
	if (m_nSocket != INVALID_SOCKET) {
		// Close server socket
		#ifdef WIN32
			const int nResult = closesocket(m_nSocket);
		#else
			const int nResult = close(m_nSocket);
		#endif

		// Reset socket address
		m_cSocketAddress = SocketAddress();
		m_nSocket        = INVALID_SOCKET;

		// Done
		return !nResult;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Returns the socket address object
*/
const SocketAddress &Socket::GetSocketAddress() const
{
	// Return socket address
	return m_cSocketAddress;
}

/**
*  @brief
*    Establishes a connection to a host by using an address and port
*/
bool Socket::Connect(const String &sAddress, uint32 nPort)
{
	return Connect(SocketAddress(sAddress, nPort));
}

/**
*  @brief
*    Establishes a connection to a host by using a given socked address
*/
bool Socket::Connect(const SocketAddress &cSocketAddress)
{
	return (m_nSocket != INVALID_SOCKET && connect(m_nSocket, reinterpret_cast<sockaddr*>(cSocketAddress.m_pSockAddress), sizeof(*cSocketAddress.m_pSockAddress)) != SOCKET_ERROR);
}

/**
*  @brief
*    Associate local address with socket
*/
bool Socket::Bind(uint32 nPort)
{
	// Bind socket to port
	return Bind(SocketAddress(nPort));
}

/**
*  @brief
*    Associate local address with socket
*/
bool Socket::Bind(const String &sAddress, uint32 nPort)
{
	// Bind socket to address and port
	return Bind(SocketAddress(sAddress, nPort));
}

/**
*  @brief
*    Associate local address with socket
*/
bool Socket::Bind(const SocketAddress &cSocketAddress)
{
	// Valid socket?
	if (m_nSocket != INVALID_SOCKET) {
		// Bind socket to a socket address
		m_cSocketAddress = cSocketAddress;
		return (bind(m_nSocket, reinterpret_cast<sockaddr*>(m_cSocketAddress.m_pSockAddress), sizeof(*m_cSocketAddress.m_pSockAddress)) != SOCKET_ERROR);
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Mark a socket as accepting connections
*/
bool Socket::Listen(int nMaxQueue) const
{
	// If valid socket, listen for new connections
	return (m_nSocket != INVALID_SOCKET && listen(m_nSocket, nMaxQueue > 0 ? nMaxQueue : SOMAXCONN) != SOCKET_ERROR);
}

/**
*  @brief
*    Accept a connection on a socket (blocking)
*/
Socket Socket::Accept() const
{
	Socket cSocket(INVALID_SOCKET);

	// Valid socket?
	if (m_nSocket != INVALID_SOCKET) {
		// Accept a new connection
		socklen_t nSize = sizeof(*cSocket.m_cSocketAddress.m_pSockAddress);
		cSocket.m_nSocket = accept(m_nSocket, reinterpret_cast<sockaddr*>(cSocket.m_cSocketAddress.m_pSockAddress), &nSize);
	}

	// Return new socket
	return cSocket;
}

/**
*  @brief
*    Sends data
*/
int Socket::Send(const char *pBuffer, uint32 nSize) const
{
	return ((pBuffer && m_nSocket != INVALID_SOCKET) ? send(m_nSocket, pBuffer, nSize, 0) : -1);
}

/**
*  @brief
*    Receives data
*/
int Socket::Receive(char *pBuffer, uint32 nSize) const
{
	return ((pBuffer && m_nSocket != INVALID_SOCKET) ? recv(m_nSocket, pBuffer, nSize, 0) : -1);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
