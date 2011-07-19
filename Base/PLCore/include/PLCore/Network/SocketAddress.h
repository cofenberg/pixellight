/*********************************************************\
 *  File: SocketAddress.h                                *
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


#ifndef __PLCORE_NETWORK_SOCKETADDRESS_H__
#define __PLCORE_NETWORK_SOCKETADDRESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Socket address class encapsulating an IP/internet address
*/
class SocketAddress {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Socket;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API SocketAddress();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nPort
		*    Number of the port to use
		*/
		PLCORE_API SocketAddress(uint32 nPort);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Socket address to copy from
		*/
		PLCORE_API SocketAddress(const SocketAddress &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sAddress
		*    Host address
		*  @param[in] nPort
		*    Number of the port to use
		*/
		PLCORE_API SocketAddress(const String &sAddress, uint32 nPort);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API ~SocketAddress();

		/**
		*  @brief
		*    Returns the host address
		*
		*  @return
		*    The host address
		*/
		PLCORE_API String GetHost() const;

		/**
		*  @brief
		*    Sets the host address
		*
		*  @param[in] sAddress
		*    New host address (if empty, set to any host address)
		*/
		PLCORE_API void SetHost(const String &sAddress);

		/**
		*  @brief
		*    Sets the host address by using the name of the host
		*
		*  @param[in] sHostName
		*    Name of the host
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool SetHostByName(const String &sHostName);

		/**
		*  @brief
		*    Returns the host port number
		*
		*  @return
		*    The host port number
		*/
		PLCORE_API uint32 GetPort() const;

		/**
		*  @brief
		*    Sets the host port number
		*
		*  @param[in] nPort
		*    Number of the port to use
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool SetPort(uint32 nPort);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Socket address to copy from
		*
		*  @return
		*    Reference to this socket address
		*/
		PLCORE_API SocketAddress &operator =(const SocketAddress &cSource);

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] cSource
		*    Socket address to compare with
		*
		*  @return
		*    'true' if both socket addresses are equal, else 'false'
		*/
		PLCORE_API bool operator ==(const SocketAddress &cSource) const;

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] cSource
		*    Socket address to compare with
		*
		*  @return
		*    'true' if both socket addresses are not equal, else 'false'
		*/
		PLCORE_API bool operator !=(const SocketAddress &cSource) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		struct sockaddr_in *m_pSockAddress;	/**< Socket address (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_NETWORK_SOCKETADDRESS_H__
