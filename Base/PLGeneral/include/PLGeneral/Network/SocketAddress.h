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


#ifndef __PLGENERAL_NETWORK_SOCKETADDRESS_H__
#define __PLGENERAL_NETWORK_SOCKETADDRESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


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
		PLGENERAL_API SocketAddress();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nPort
		*    Number of the port to use
		*/
		PLGENERAL_API SocketAddress(uint32 nPort);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Socket address to copy from
		*/
		PLGENERAL_API SocketAddress(const SocketAddress &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sAddress
		*    Host address
		*  @param[in] nPort
		*    Number of the port to use
		*/
		PLGENERAL_API SocketAddress(const String &sAddress, uint32 nPort);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~SocketAddress();

		/**
		*  @brief
		*    Returns the host address
		*
		*  @return
		*    The host address
		*/
		PLGENERAL_API String GetHost() const;

		/**
		*  @brief
		*    Sets the host address
		*
		*  @param[in] sAddress
		*    New host address (if empty, set to any host address)
		*/
		PLGENERAL_API void SetHost(const String &sAddress);

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
		PLGENERAL_API bool SetHostByName(const String &sHostName);

		/**
		*  @brief
		*    Returns the host port number
		*
		*  @return
		*    The host port number
		*/
		PLGENERAL_API uint32 GetPort() const;

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
		PLGENERAL_API bool SetPort(uint32 nPort);

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
		PLGENERAL_API SocketAddress &operator =(const SocketAddress &cSource);

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
		PLGENERAL_API bool operator ==(const SocketAddress &cSource) const;

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
		PLGENERAL_API bool operator !=(const SocketAddress &cSource) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		struct sockaddr_in *m_pSockAddress;	/**< Socket address (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_NETWORK_SOCKETADDRESS_H__
