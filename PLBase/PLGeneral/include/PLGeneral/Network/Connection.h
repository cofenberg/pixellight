/*********************************************************\
 *  File: Connection.h                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_CONNECTION_H__
#define __PLGENERAL_CONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/System/Thread.h"
#include "PLGeneral/Network/Socket.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Host;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Connection base class
*
*  @remarks
*    This is the most important base class of the PLGeneral network classes for the 'concrete'
*    communication. This class 'only' offers low-level methods for the communication on a pure
*    abstract data layer, meaning sending of strings or data-arrays without known usage/semantic.
*    Derived connection classes have to implement the concrete content layer.
*    For example a chat-connection offers methods like SendMessage(), SendPrivateMessage(),
*    SlapUser(), defining in this way what the user can do within the network. Within this
*    methods a data-package is created and send by using Connection::Send(). In another usage
*    a game-connection may have something like SynchronizeObject(Object*), GetUpdate(),
*    SendAction(Action*).
*    In short, the task of the derived connection class is to define the concrete protocol
*    and to hide the rest so the application do not have to care about it. The application
*    should 'only' use the methods of the concrete for instance game-connection class - NEVER
*    creating somewhere data-packages and sending them by itself using Connection::Send()!
*/
class Connection : protected Thread {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Host;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Receive mode
		*/
		enum EReceiveMode {
			ReceiveAutomatic = 0,	/**< Date is received automatically (see OnReceive()) */
			ReceiveManual			/**< Data is received manually (see Receive()) */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHost
		*    Owner host
		*/
		PLGENERAL_API Connection(Host &cHost);

		/**
		*  @brief
		*    Get host that owns this connection
		*
		*  @return
		*    Host
		*/
		PLGENERAL_API const Host &GetHost() const;

		/**
		*  @brief
		*    Get host that owns this connection
		*
		*  @return
		*    Host
		*/
		PLGENERAL_API Host &GetHost();

		/**
		*  @brief
		*    Get name of connected host
		*
		*  @return
		*    Name of host
		*/
		PLGENERAL_API String GetHostname() const;

		/**
		*  @brief
		*    Get port
		*
		*  @return
		*    Port number
		*/
		PLGENERAL_API uint32 GetPort() const;

		/**
		*  @brief
		*    Get socket
		*
		*  @return
		*    The socket object
		*/
		PLGENERAL_API const Socket &GetSocket() const;

		/**
		*  @brief
		*    Get socket
		*
		*  @return
		*    The socket object
		*/
		PLGENERAL_API Socket &GetSocket();

		/**
		*  @brief
		*    Check if connection is active
		*
		*  @return
		*    'true' if the connection is currently established, else 'false'
		*/
		PLGENERAL_API bool IsConnected() const;

		/**
		*  @brief
		*    Disconnect
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no connection established?)
		*/
		PLGENERAL_API bool Disconnect();

		/**
		*  @brief
		*    Get receive mode
		*
		*  @return
		*    Receive mode
		*/
		PLGENERAL_API EReceiveMode GetReceiveMode() const;

		/**
		*  @brief
		*    Set receive mode
		*
		*  @param[in] nReceiveMode
		*    Receive mode
		*
		*  @remarks
		*    If mode is ReceiveAutomatic, data is read from the connection automatically.
		*    If mode is ReceiveManual, no data will be read until the method ReceiveData() has been
		*    called. In both cases, OnReceive() will be called whenever new data has arrived. 
		*    By default, mode is set to ReceiveAutomatic.
		*/
		PLGENERAL_API void SetReceiveMode(EReceiveMode nReceiveMode);

		/**
		*  @brief
		*    Send data
		*
		*  @param[in] pBuffer
		*    Data to send, if NULL nothing happens
		*  @param[in] nSize
		*    Size in bytes of the buffer to send, MUST be valid!
		*
		*  @return
		*    Total number of bytes sent. Can be less than the requested size
		*    to be sent, negative value on error
		*/
		PLGENERAL_API int Send(const char *pBuffer, uint32 nSize) const;

		/**
		*  @brief
		*    Send string
		*
		*  @param[in] sString
		*    String
		*
		*  @return
		*    Total number of bytes sent, negative value on error
		*/
		PLGENERAL_API int Send(const String &sString) const;

		/**
		*  @brief
		*    Receive data
		*
		*  @param[in] pBuffer
		*    Data buffer
		*  @param[in] nSize
		*    Size in bytes
		*
		*  @return
		*    Total number of bytes read. Can be less than the requested size
		*    to be sent, negative value on error
		*/
		PLGENERAL_API int Receive(char *pBuffer, uint32 nSize);

		/**
		*  @brief
		*    Read line of text
		*
		*  @return
		*    Line read
		*/
		PLGENERAL_API PLGeneral::String ReadLine();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~Connection();

		/**
		*  @brief
		*    Establish a connection to a host by specifying address and port
		*
		*  @param[in] sHost
		*    Host name
		*  @param[in] nPort
		*    Port number
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool Connect(const String &sHost, uint32 nPort);

		/**
		*  @brief
		*    Establish a connection to a host by using a given socket
		*
		*  @param[in] cSocket
		*    Socket of the host to connect to
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool Connect(Socket &cSocket);


	//[-------------------------------------------------------]
	//[ Protected virtual Connection functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the connection is established
		*/
		PLGENERAL_API virtual void OnConnect();

		/**
		*  @brief
		*    Called when the connection is disconnected
		*/
		PLGENERAL_API virtual void OnDisconnect();

		/**
		*  @brief
		*    Called when the connection receives data
		*
		*  @param[in] pBuffer
		*    Buffer with the received data, NULL on terrible error
		*  @param[in] nSize
		*    Size in bytes of the buffer with the received data (always valid!)
		*
		*  @note
		*    - Do NOT keep a pointer/reference to 'nBuffer' because this buffer is only valid
		*      inside this function
		*/
		PLGENERAL_API virtual void OnReceive(const char *pBuffer, uint32 nSize);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Connection(const Connection &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Connection &operator =(const Connection &cSource);

		/**
		*  @brief
		*    Receive data
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no connection established?)
		*/
		bool ReceiveData();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Host			*m_pHost;			/**< Pointer to host, NEVER NULL! */
		volatile bool	 m_bConnected;		/**< Connection status */
		String			 m_sHostname;		/**< Name of host */
		uint32			 m_nPort;			/**< Port number */
		Socket			 m_cSocket;			/**< Connection socket */
		EReceiveMode	 m_nReceiveMode;	/**< Receive mode */


	//[-------------------------------------------------------]
	//[ Private virtual ThreadFunction functions              ]
	//[-------------------------------------------------------]
	private:
		PLGENERAL_API virtual int Run();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_CONNECTION_H__
