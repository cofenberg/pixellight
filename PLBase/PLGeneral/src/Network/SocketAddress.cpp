/*********************************************************\
 *  File: SocketAddress.cpp                              *
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
	#undef SetPort // We need to undefine this else a linker error occures... if not in this project then
				   // in another one like PLNetwork :(
#endif
#ifdef LINUX
	#include <netdb.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif
#include "PLGeneral/Core/MemoryManager.h"
#include "PLGeneral/Network/SocketAddress.h"


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
SocketAddress::SocketAddress() :
	m_pSockAddress(new sockaddr_in)
{
	// Set up socket address
	m_pSockAddress->sin_family		= AF_INET;
	m_pSockAddress->sin_port		= 0;
	m_pSockAddress->sin_addr.s_addr	= 0;
}

/**
*  @brief
*    Constructor
*/
SocketAddress::SocketAddress(uint32 nPort) :
	m_pSockAddress(new sockaddr_in)
{
	// Set up socket address
	m_pSockAddress->sin_family		= AF_INET;
	m_pSockAddress->sin_port		= htons((u_short)nPort);
	m_pSockAddress->sin_addr.s_addr = INADDR_ANY;
}

/**
*  @brief
*    Copy constructor
*/
SocketAddress::SocketAddress(const SocketAddress &cSource) :
	m_pSockAddress(new sockaddr_in)
{
	*m_pSockAddress = *cSource.m_pSockAddress;
}

/**
*  @brief
*    Constructor
*/
SocketAddress::SocketAddress(const String &sHost, uint32 nPort) :
	m_pSockAddress(new sockaddr_in)
{
	// Set up socket address
	m_pSockAddress->sin_family      = AF_INET;
	m_pSockAddress->sin_port        = htons((u_short)nPort);
	m_pSockAddress->sin_addr.s_addr = INADDR_ANY;

	// Get host address
	if (sHost.GetLength()) {
		m_pSockAddress->sin_addr.s_addr = inet_addr(sHost);
		if (m_pSockAddress->sin_addr.s_addr == INADDR_NONE) {
			// Try to resolve host
			hostent *pHost = gethostbyname(sHost);
			if (pHost)
				MemoryManager::Copy((char*)&m_pSockAddress->sin_addr.s_addr, pHost->h_addr, 4);
		}
	}
}

/**
*  @brief
*    Destructor
*/
SocketAddress::~SocketAddress()
{
	delete m_pSockAddress;
}

/**
*  @brief
*    Returns the host address
*/
String SocketAddress::GetHost() const
{
	// Return host address
	return inet_ntoa(m_pSockAddress->sin_addr);
}

/**
*  @brief
*    Sets the host address
*/
void SocketAddress::SetHost(const String &sHost)
{
	// If host address valid set host address, else set to any host address
	m_pSockAddress->sin_addr.s_addr = sHost.GetLength() ? inet_addr(sHost) : INADDR_ANY;
}

/**
*  @brief
*    Sets the host address by using the name of the host
*/
bool SocketAddress::SetHostByName(const String &sHostName)
{
	// Get host address
	hostent *pHost = gethostbyname(sHostName);
	if (pHost) {
		// Host found
		m_pSockAddress->sin_addr.s_addr = *(unsigned long*)pHost->h_addr;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Returns the host port number
*/
uint32 SocketAddress::GetPort() const
{
	// Get port number
	return ntohs(m_pSockAddress->sin_port);
}

/**
*  @brief
*    Sets the host port number
*/
bool SocketAddress::SetPort(uint32 nPort)
{
	// Set port number
	m_pSockAddress->sin_port = htons((u_short)nPort);

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
SocketAddress &SocketAddress::operator =(const SocketAddress &cSource)
{
	*m_pSockAddress = *cSource.m_pSockAddress;

	// Return this
	return *this;
}

/**
*  @brief
*    Compare operator
*/
bool SocketAddress::operator ==(const SocketAddress &cSource) const
{
	return (m_pSockAddress->sin_addr.s_addr == cSource.m_pSockAddress->sin_addr.s_addr &&
			m_pSockAddress->sin_port		== cSource.m_pSockAddress->sin_port);
}

/**
*  @brief
*    Compare operator
*/
bool SocketAddress::operator !=(const SocketAddress &cSource) const
{
	return (m_pSockAddress->sin_addr.s_addr != cSource.m_pSockAddress->sin_addr.s_addr ||
			m_pSockAddress->sin_port		!= cSource.m_pSockAddress->sin_port);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
