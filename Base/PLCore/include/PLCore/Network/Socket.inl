/*********************************************************\
 *  File: Socket.inl                                     *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
inline Socket::Socket(const Socket &cSocket) :
	m_cSocketAddress(cSocket.m_cSocketAddress),
	m_nSocket(cSocket.m_nSocket)
{
}

/**
*  @brief
*    Constructor
*/
inline Socket::Socket(handle nSocket) :
	m_nSocket(nSocket)
{
}

/**
*  @brief
*    Destructor
*/
inline Socket::~Socket()
{
	// Note that we are NOT allowed to close the current socket in here automatically
	// or we may end up in an ugly mess
}

/**
*  @brief
*    Returns the socket address object
*/
inline const SocketAddress &Socket::GetSocketAddress() const
{
	// Return socket address
	return m_cSocketAddress;
}

/**
*  @brief
*    Establishes a connection to a host by using an address and port
*/
inline bool Socket::Connect(const String &sAddress, uint32 nPort)
{
	return Connect(SocketAddress(sAddress, nPort));
}

/**
*  @brief
*    Associate local address with socket
*/
inline bool Socket::Bind(uint32 nPort)
{
	// Bind socket to port
	return Bind(SocketAddress(nPort));
}

/**
*  @brief
*    Associate local address with socket
*/
inline bool Socket::Bind(const String &sAddress, uint32 nPort)
{
	// Bind socket to address and port
	return Bind(SocketAddress(sAddress, nPort));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
